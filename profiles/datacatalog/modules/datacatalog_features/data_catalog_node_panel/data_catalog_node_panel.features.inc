<?php
/**
 * @file
 * data_catalog_node_panel.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_catalog_node_panel_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function data_catalog_node_panel_node_info() {
  $items = array(
    'panel' => array(
      'name' => t('Panel'),
      'base' => 'panels_node_hook',
      'description' => t('A panel layout broken up into rows and columns.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
