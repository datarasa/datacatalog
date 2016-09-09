<?php
/**
 * @file
 * data_catalog_panels.ctools_content.inc
 */

/**
 * Implements hook_default_ctools_custom_content().
 */
function data_catalog_panels_default_ctools_custom_content() {
  $export = array();

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'source_pane';
  $content->admin_title = 'source pane';
  $content->admin_description = 'source pane';
  $content->category = 'view';
  $content->settings = array(
    'admin_title' => '',
    'title' => 'source pane',
    'body' => 'source pane',
    'format' => 'filtered_html',
    'substitute' => 1,
  );
  $export['source_pane'] = $content;

  return $export;
}
