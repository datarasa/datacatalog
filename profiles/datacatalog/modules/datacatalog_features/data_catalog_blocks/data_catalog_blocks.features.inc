<?php
/**
 * @file
 * data_catalog_blocks.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_catalog_blocks_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "quicktabs" && $api == "quicktabs") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
