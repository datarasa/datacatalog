<?php
/**
 * @file
 * data_catalog_node_source.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function data_catalog_node_source_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_basic_info_col1|node|source|form';
  $field_group->group_name = 'group_basic_info_col1';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'source';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_basic_info';
  $field_group->data = array(
    'label' => 'Basic Info col1',
    'weight' => '1',
    'children' => array(
      0 => 'body',
      1 => 'field_tags_term',
      2 => 'og_group_ref',
      3 => 'field_business_process',
      4 => 'field_notes',
      5 => 'field_show_notes',
      6 => 'title',
      7 => 'path',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Basic Info col1',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-basic-info-col1 field-group-div col-xs-12 col-md-7',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_basic_info_col1|node|source|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_basic_info_col2|node|source|form';
  $field_group->group_name = 'group_basic_info_col2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'source';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_basic_info';
  $field_group->data = array(
    'label' => 'Basic Info col2',
    'weight' => '2',
    'children' => array(
      0 => 'field_owners',
      1 => 'field_other_documents',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Basic Info col2',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-basic-info-col2 field-group-div col-xs-12 col-md-5',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_basic_info_col2|node|source|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_basic_info|node|source|form';
  $field_group->group_name = 'group_basic_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'source';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_htab_group';
  $field_group->data = array(
    'label' => 'Source Info',
    'weight' => '1',
    'children' => array(
      0 => 'group_basic_info_col1',
      1 => 'group_basic_info_col2',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Source Info',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => 'sourceid',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_basic_info|node|source|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_htab_group|node|source|form';
  $field_group->group_name = 'group_htab_group';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'source';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'htab Group',
    'weight' => '0',
    'children' => array(
      0 => 'group_basic_info',
      1 => 'group_metadata',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-htab-group field-group-htabs',
      ),
    ),
  );
  $export['group_htab_group|node|source|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_metadata|node|source|form';
  $field_group->group_name = 'group_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'source';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_htab_group';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '2',
    'children' => array(
      0 => 'field_csv_file',
      1 => 'field_metadata_fields',
      2 => 'field_meta_data_input_method',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_metadata|node|source|form'] = $field_group;

  return $export;
}
