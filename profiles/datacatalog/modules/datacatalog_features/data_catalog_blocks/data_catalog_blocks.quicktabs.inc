<?php
/**
 * @file
 * data_catalog_blocks.quicktabs.inc
 */

/**
 * Implements hook_quicktabs_default_quicktabs().
 */
function data_catalog_blocks_quicktabs_default_quicktabs() {
  $export = array();

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'communities_page';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'Communities Page';
  $quicktabs->tabs = array(
    0 => array(
      'vid' => 'communities_es',
      'display' => 'page',
      'args' => '%1',
      'title' => 'Grid View',
      'weight' => '-100',
      'type' => 'view',
    ),
    1 => array(
      'vid' => 'communities_es',
      'display' => 'page_1',
      'args' => '%1',
      'title' => 'List View',
      'weight' => '-99',
      'type' => 'view',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'Zen';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('Communities Page');
  t('Grid View');
  t('List View');

  $export['communities_page'] = $quicktabs;

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'community_page';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'Community page';
  $quicktabs->tabs = array(
    0 => array(
      'vid' => 'group_content_es',
      'display' => 'block',
      'args' => '',
      'title' => 'Sources',
      'weight' => '-100',
      'type' => 'view',
    ),
    1 => array(
      'vid' => 'community_business_process_tab_es',
      'display' => 'block',
      'args' => '',
      'title' => 'Business Processes',
      'weight' => '-99',
      'type' => 'view',
    ),
    2 => array(
      'vid' => 'group_members_es',
      'display' => 'block',
      'args' => '',
      'title' => 'Members',
      'weight' => '-98',
      'type' => 'view',
    ),
    3 => array(
      'bid' => 'views_delta_f20e31d90aff2e85304b0251bdec8dc3',
      'hide_title' => 1,
      'title' => 'Updates',
      'weight' => '-97',
      'type' => 'block',
    ),
    4 => array(
      'bid' => 'views_delta_community_wiki_es-block',
      'hide_title' => 1,
      'title' => 'Wiki',
      'weight' => '-96',
      'type' => 'block',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'Zen';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('Business Processes');
  t('Community page');
  t('Members');
  t('Sources');
  t('Updates');
  t('Wiki');

  $export['community_page'] = $quicktabs;

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'my_communities_page';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'My Communities page';
  $quicktabs->tabs = array(
    0 => array(
      'vid' => 'my_communities_es',
      'display' => 'page_1',
      'args' => '',
      'title' => 'Grid View',
      'weight' => '-100',
      'type' => 'view',
    ),
    1 => array(
      'vid' => 'my_communities_es',
      'display' => 'page_2',
      'args' => '',
      'title' => 'List View',
      'weight' => '-99',
      'type' => 'view',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'Zen';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('Grid View');
  t('List View');
  t('My Communities page');

  $export['my_communities_page'] = $quicktabs;

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'owners_lookup';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'Owners Lookup';
  $quicktabs->tabs = array(
    0 => array(
      'vid' => 'owners_es',
      'display' => 'block',
      'args' => '',
      'title' => 'Community',
      'weight' => '-100',
      'type' => 'view',
    ),
    1 => array(
      'vid' => 'owners_es',
      'display' => 'block_1',
      'args' => '',
      'title' => 'Source',
      'weight' => '-99',
      'type' => 'view',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'Zen';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('Community');
  t('Owners Lookup');
  t('Source');

  $export['owners_lookup'] = $quicktabs;

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'user_profile_page';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 1;
  $quicktabs->title = 'User Profile Page';
  $quicktabs->tabs = array(
    0 => array(
      'vid' => 'user_profile_communities_tab_es',
      'display' => 'block',
      'args' => '',
      'title' => 'Communities',
      'weight' => '-100',
      'type' => 'view',
    ),
    1 => array(
      'machine_name' => 'user_profile_source_sub_tabs',
      'title' => 'Sources',
      'weight' => '-99',
      'type' => 'qtabs',
    ),
    2 => array(
      'vid' => 'user_profile_business_processes_tab_es',
      'display' => 'block',
      'args' => '',
      'title' => 'Business Processes',
      'weight' => '-98',
      'type' => 'view',
    ),
    3 => array(
      'vid' => 'user_profile_wiki_tab_es',
      'display' => 'block',
      'args' => '',
      'title' => 'Wiki',
      'weight' => '-97',
      'type' => 'view',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'Zen';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('Business Processes');
  t('Communities');
  t('Sources');
  t('User Profile Page');
  t('Wiki');

  $export['user_profile_page'] = $quicktabs;

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'user_profile_source_sub_tabs';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'User profile Source sub tabs';
  $quicktabs->tabs = array(
    0 => array(
      'vid' => 'user_profile_sources_tab_es',
      'display' => 'block_1',
      'args' => '',
      'title' => 'All',
      'weight' => '-100',
      'type' => 'view',
    ),
    1 => array(
      'vid' => 'user_profile_sources_tab_es',
      'display' => 'block',
      'args' => '',
      'title' => 'Creator',
      'weight' => '-99',
      'type' => 'view',
    ),
    2 => array(
      'vid' => 'user_profile_sources_tab_es',
      'display' => 'block_2',
      'args' => '',
      'title' => 'Owner',
      'weight' => '-98',
      'type' => 'view',
    ),
    3 => array(
      'vid' => 'user_profile_sources_tab_es',
      'display' => 'block_3',
      'args' => '',
      'title' => 'Subscribed',
      'weight' => '-97',
      'type' => 'view',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'Zen';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('All');
  t('Creator');
  t('Owner');
  t('Subscribed');
  t('User profile Source sub tabs');

  $export['user_profile_source_sub_tabs'] = $quicktabs;

  return $export;
}
