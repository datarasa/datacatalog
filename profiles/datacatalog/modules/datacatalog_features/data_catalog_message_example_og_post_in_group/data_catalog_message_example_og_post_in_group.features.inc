<?php
/**
 * @file
 * data_catalog_message_example_og_post_in_group.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_catalog_message_example_og_post_in_group_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
