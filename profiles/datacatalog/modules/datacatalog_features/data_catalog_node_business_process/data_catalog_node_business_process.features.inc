<?php
/**
 * @file
 * data_catalog_node_business_process.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_catalog_node_business_process_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function data_catalog_node_business_process_node_info() {
  $items = array(
    'business_process' => array(
      'name' => t('Business process'),
      'base' => 'node_content',
      'description' => t('Used to add a business process'),
      'has_title' => '1',
      'title_label' => t('Business process title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
