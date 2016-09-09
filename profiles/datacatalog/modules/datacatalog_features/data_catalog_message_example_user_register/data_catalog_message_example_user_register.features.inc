<?php
/**
 * @file
 * data_catalog_message_example_user_register.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_catalog_message_example_user_register_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
