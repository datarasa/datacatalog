<?php


/**
 * Implements hook_pathauto().
 */
function vocabulary_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'vocabulary';
      $settings['token_type'] = 'vocabulary';
      $settings['groupheader'] = t('Vocabulary paths');
      $settings['patterndefault'] = 'category/[vocabulary:name]';
      $settings['patterndescr'] = t('Path pattern for vocabularies');

      $tokens = token_info();
      foreach ($tokens['tokens']['vocabulary'] as $key => $info) {
        $settings['tokens']["[vocabulary:$key]"] = $info['description'];
      }
      $settings['supportsfeeds'] = '';
      $settings['batch_update_callback'] = 'vocabulury_pathauto_bulk_update_batch_process';
      $settings['batch_file'] = drupal_get_path('module', 'vocabulary') . '/vocabulary.pathauto.inc';
      $settings['bulkname'] = t('Bulk generate aliases for vocabularies that are not aliased');
      $settings['bulkdescr'] = t('Generate aliases for all existing vocabularies which do not already have aliases.');

      return (object) $settings;
    default:
      break;
  }
}

/**
 * Update the URL aliases for an individual vocabulary.
 *
 * @param $vocabulary
 *   A vocabulary object.
 * @param $op
 *   Operation being performed on the vocabulary ('insert', 'update' or 'bulkupdate').
 * @param $options
 *   An optional array of additional options.
 */
function vocabulary_pathauto_update_alias(stdClass $vocabulary, $op, array $options = array()) {
  // Skip processing if the user has disabled pathauto for the term.
  if (isset($vocabulary->path['pathauto']) && empty($vocabulary->path['pathauto'])) {
    return;
  }

  // Skip processing if the term has no pattern.
  if (!pathauto_pattern_load_by_entity('vocabulary')) {
    return;
  }

  module_load_include('inc', 'pathauto');
  $uri = entity_uri('taxonomy_vocabulary', $vocabulary);
  pathauto_create_alias('vocabulary', $op, $uri['path'], array('vocabulary' => $vocabulary));
}

/**
 * Update the URL aliases for multiple taxonomy terms.
 *
 * @param $tids
 *   An array of term IDs.
 * @param $op
 *   Operation being performed on the nodes ('insert', 'update' or
 *   'bulkupdate').
 * @param $options
 *   An optional array of additional options.
 */
function vocabulary_pathauto_update_alias_multiple(array $vids, $op, array $options = array()) {
  $options += array('message' => FALSE);

  $vocabularies = taxonomy_vocabulary_load_multiple($vids);
  foreach ($vocabularies as $vocabulary) {
    vocabulary_pathauto_update_alias($vocabulary, $op, $options);
  }

  if (!empty($options['message'])) {
    drupal_set_message(format_plural(count($vids), 'Updated URL alias for 1 term.', 'Updated URL aliases for @count terms.'));
  }
}

/**
 * Batch processing callback; Generate aliases for vocabularies.
 */
function vocabulury_pathauto_bulk_update_batch_process(&$context) {
  if (!isset($context['sandbox']['current'])) {
    $context['sandbox']['count'] = 0;
    $context['sandbox']['current'] = 0;
  }

  $query = db_select('taxonomy_vocabulary', 'v');
  $query->leftJoin('url_alias', 'ua', "CONCAT('taxonomy/', v.vid) = ua.source");
  $query->addField('v', 'vid');
  $query->isNull('ua.source');
  $query->condition('v.vid', $context['sandbox']['current'], '>');
  // Exclude the forums terms.
  if ($forum_vid = variable_get('forum_nav_vocabulary', '')) {
    $query->condition('v.vid', $forum_vid, '<>');
  }
  $query->orderBy('v.vid');
  $query->addTag('pathauto_bulk_update');
  $query->addMetaData('entity', 'taxonomy_vocabulary');

  // Get the total amount of items to process.
  if (!isset($context['sandbox']['total'])) {
    $context['sandbox']['total'] = $query->countQuery()->execute()->fetchField();

    // If there are no nodes to update, the stop immediately.
    if (!$context['sandbox']['total']) {
      $context['finished'] = 1;
      return;
    }
  }

  $query->range(0, 25);
  $vids = $query->execute()->fetchCol();

  vocabulary_pathauto_update_alias_multiple($vids, 'bulkupdate');
  $context['sandbox']['count'] += count($vids);
  $context['sandbox']['current'] = max($vids);
  $context['message'] = t('Updated alias for vocabulary @vid.', array('@vid' => end($vids)));

  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}
