<?php
/**
 * @file
 * data_catalog_node_source.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_catalog_node_source_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function data_catalog_node_source_node_info() {
  $items = array(
    'source' => array(
      'name' => t('Source'),
      'base' => 'node_content',
      'description' => t('Source can be added'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
