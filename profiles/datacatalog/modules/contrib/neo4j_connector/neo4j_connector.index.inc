<?php
/**
 * @file
 * Indexing mechanism.
 */

// Index statuses.
define('NEO4J_CONNECTOR_INDEX_STATUS_NOT_EXIST', -1);
define('NEO4J_CONNECTOR_INDEX_STATUS_INDEX', 0);
define('NEO4J_CONNECTOR_INDEX_STATUS_INDEXED', 1);
define('NEO4J_CONNECTOR_INDEX_STATUS_DELETE', 2);
define('NEO4J_CONNECTOR_INDEX_STATUS_UPDATE', 3);

/**
 * Mark entity for indexing to Neo4J.
 *
 * @param $entity_type
 *  Entity type.
 * @param $entity_id
 *  Entity ID.
 */
function neo4j_connector_index_send_to_index($entity_type, $entity_id) {
  $index_status = neo4j_connector_index_get_index_status($entity_type, $entity_id);

  switch ($index_status) {
    case NEO4J_CONNECTOR_INDEX_STATUS_NOT_EXIST:
      _neo4j_connector_index_mark($entity_type, $entity_id, NEO4J_CONNECTOR_INDEX_STATUS_INDEX);
      break;

    case NEO4J_CONNECTOR_INDEX_STATUS_DELETE:
    case NEO4J_CONNECTOR_INDEX_STATUS_INDEXED:
      _neo4j_connector_index_mark($entity_type, $entity_id, NEO4J_CONNECTOR_INDEX_STATUS_UPDATE);
      break;

    case NEO4J_CONNECTOR_INDEX_STATUS_INDEX:
    case NEO4J_CONNECTOR_INDEX_STATUS_UPDATE:
      // Nothing to do, it's already waiting in line.
      break;

    default:
      watchdog(__FUNCTION__, 'Unexpected index status @status for entity: @entity_type - @entity_id', array(
        '@status' => $index_status,
        '@entity_type' => $entity_type,
        '@entity_id' => $entity_id,
      ), WATCHDOG_ERROR);
      break;
  }
}

/**
 * Returns the index status of an entity.
 *
 * @param $entity_type
 *  Entity type.
 * @param $entity_id
 *  Entity ID.
 * @return int
 *  Index status code. Examples:
 *    NEO4J_CONNECTOR_INDEX_STATUS_NOT_EXIST
 *    NEO4J_CONNECTOR_INDEX_STATUS_INDEX
 *    NEO4J_CONNECTOR_INDEX_STATUS_INDEXED
 *    NEO4J_CONNECTOR_INDEX_STATUS_DELETE
 *    NEO4J_CONNECTOR_INDEX_STATUS_UPDATE
 */
function neo4j_connector_index_get_index_status($entity_type, $entity_id) {
  $result = db_query("
    SELECT status
    FROM {neo4j_connector_index}
    WHERE entity_type = :entity_type AND entity_id = :entity_id
  ", array(':entity_type' => $entity_type, ':entity_id' => $entity_id))->fetchField();

  return $result === FALSE ? NEO4J_CONNECTOR_INDEX_STATUS_NOT_EXIST : $result;
}

/**
 * Delete entity from the index. At this point the entity must not have the graph node in the db.
 *
 * @param $entity_type
 *  Entity type.
 * @param $entity_id
 *  Entity ID.
 */
function neo4j_connector_index_delete($entity_type, $entity_id) {
  db_query("
    DELETE FROM {neo4j_connector_index}
    WHERE entity_type = :entity_type AND entity_id = :entity_id
  ", array(':entity_type' => $entity_type, ':entity_id' => $entity_id));
}

/**
 * Delete all index. At this point nothing should be in the graph db.
 */
function neo4j_connector_index_delete_all() {
  db_query("DELETE FROM {neo4j_connector_index}");
  watchdog(__FUNCTION__, 'Index has been purged.', array(), WATCHDOG_INFO);
}

/**
 * Mark entity in the index. Valid statuses are defined as NEO4J_CONNECTOR_INDEX_STATUS_<SUFFIX>.
 *
 * @param $entity_type
 *  Entity type.
 * @param $entity_id
 *  Entity ID.
 * @param $index_status
 *  Index status code.
 */
function _neo4j_connector_index_mark($entity_type, $entity_id, $index_status) {
  $result = db_query("
    SELECT *
    FROM {neo4j_connector_index}
    WHERE entity_type = :entity_type AND entity_id = :entity_id
  ", array(':entity_type' => $entity_type, ':entity_id' => $entity_id))->fetchObject();

  $index_item = NULL;
  if (!$result) {
    $index_item = new stdClass();
    $index_item->entity_type = $entity_type;
    $index_item->entity_id = $entity_id;
  }
  else {
    $index_item = $result;
  }

  $index_item->changed = $_SERVER['REQUEST_TIME'];
  $index_item->status = $index_status;

  if (!$result) {
    drupal_write_record('neo4j_connector_index', $index_item);
  }
  else {
    drupal_write_record('neo4j_connector_index', $index_item, array('entity_type', 'entity_id'));
  }
}

/**
 * Processing elements from the index table: indexing or deleting.
 *
 * @param int|NULL $limit
 *  Number of items to process.
 */
function neo4j_connector_index_process_index($limit = NULL) {
  if (!$limit) {
    $limit = variable_get('neo4j_connector_index_process_limit', 100);
  }

  $records = db_query_range("
    SELECT *
    FROM {neo4j_connector_index}
    WHERE status != :status
    ORDER BY changed ASC
  ", 0, $limit, array(':status' => NEO4J_CONNECTOR_INDEX_STATUS_INDEXED))->fetchAll();

  foreach ($records as $record) {
    $entity = entity_load_single($record->entity_type, $record->entity_id);

    // It's necessary to re-load the status: when indexing a content it might have a reference that is not indexed.
    // In that case we need to pre-index the referenced item (without fields) in order to be able to reference that.
    // That action will change the referenced item status to UPDATED. Since here the query is already in PHP
    // we have to make sure we fetch the up-to-date status.
    $status = neo4j_connector_index_get_index_status($record->entity_type, $record->entity_id);

    switch ($status) {
      case NEO4J_CONNECTOR_INDEX_STATUS_INDEX:
        $graph_node = neo4j_connector_add_entity_to_neo4j($entity, $record->entity_type);
        break;

      case NEO4J_CONNECTOR_INDEX_STATUS_UPDATE:
        $indexParam = new Neo4JDrupalIndexParam(NEO4J_CONNECTOR_ENTITY_INDEX_PREFIX . $record->entity_type, 'entity_id', $record->entity_id);

        $properties = array();
        drupal_alter('neo4j_connector_entity_properties', $properties, $entity, $record->entity_type);

        $graph_node = Neo4JDrupal::sharedInstance()->updateEntity($entity, $record->entity_type, $properties, $indexParam);
        break;

      case NEO4J_CONNECTOR_INDEX_STATUS_DELETE:
        $indexParam = new Neo4JDrupalIndexParam(NEO4J_CONNECTOR_ENTITY_INDEX_PREFIX . $record->entity_type, 'entity_id', $record->entity_id);
        Neo4JDrupal::sharedInstance()->deleteEntity($indexParam);

        neo4j_connector_index_delete($record->entity_type, $record->entity_id);
        break;

      default:
        watchdog(__FUNCTION__, 'Unexpected index status @status for entity: @entity_type-@entity_id', array(
          '@status' => $status,
          '@entity_type' => $record->entity_type,
          '@entity_id' => $record->entity_id,
        ), WATCHDOG_ERROR);
        break;
    }

    if (isset($graph_node)) {
      $record->remote_id = $graph_node->getId();
      $record->status = NEO4J_CONNECTOR_INDEX_STATUS_INDEXED;
      $record->changed = $_SERVER['REQUEST_TIME'];
      drupal_write_record('neo4j_connector_index', $record, array('entity_type', 'entity_id'));
    }
  }
}

/**
 * Index statistics.
 *
 * @return array
 *  Key - value array of statistics information.
 */
function neo4j_connector_index_get_stat() {
  $stat = array();

  $stat['total'] = db_query("SELECT COUNT(*) FROM {neo4j_connector_index}")->fetchField();

  $stat['indexed'] = db_query("
    SELECT COUNT(*)
    FROM {neo4j_connector_index}
    WHERE status = :status
  ", array(':status' => NEO4J_CONNECTOR_INDEX_STATUS_INDEXED))->fetchField();

  $stat['non-indexed'] = $stat['total'] - $stat['indexed'];

  // Entity content details.
  $entity_types = entity_get_info();

  foreach ($entity_types as $type => $info) {
    $content_num = db_query("SELECT COUNT(*) FROM {" . db_escape_table($info['base table']) . "}")->fetchField();
    $index_num = db_query("SELECT COUNT(*) FROM {neo4j_connector_index} WHERE entity_type = :type", array(':type' => $type))->fetchField();
    $indexed_num = db_query("
      SELECT COUNT(*)
      FROM {neo4j_connector_index}
      WHERE entity_type = :type AND status = :status
    ", array(
      ':type' => $type,
      ':status' => NEO4J_CONNECTOR_INDEX_STATUS_INDEXED,
    ))->fetchField();
    $stat['entity-' . $type] = "$content_num (total) - $index_num (marked) - $indexed_num (indexed)";
  }

  return $stat;
}
