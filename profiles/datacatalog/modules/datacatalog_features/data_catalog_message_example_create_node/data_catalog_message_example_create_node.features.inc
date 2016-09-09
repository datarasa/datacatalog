<?php
/**
 * @file
 * data_catalog_message_example_create_node.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_catalog_message_example_create_node_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
