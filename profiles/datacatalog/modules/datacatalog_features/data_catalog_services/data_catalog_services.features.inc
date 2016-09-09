<?php
/**
 * @file
 * data_catalog_services.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_catalog_services_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}
