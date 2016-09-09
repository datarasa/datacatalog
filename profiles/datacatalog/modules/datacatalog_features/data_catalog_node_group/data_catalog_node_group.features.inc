<?php
/**
 * @file
 * data_catalog_node_group.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_catalog_node_group_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function data_catalog_node_group_node_info() {
  $items = array(
    'group' => array(
      'name' => t('Community'),
      'base' => 'node_content',
      'description' => t('This content type is used to create groups'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
