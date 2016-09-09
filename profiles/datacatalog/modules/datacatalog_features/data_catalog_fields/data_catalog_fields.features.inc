<?php
/**
 * @file
 * data_catalog_fields.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_catalog_fields_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
