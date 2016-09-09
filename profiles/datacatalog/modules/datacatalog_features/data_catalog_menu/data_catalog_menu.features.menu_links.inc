<?php
/**
 * @file
 * data_catalog_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function data_catalog_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_communities:communities.
  $menu_links['main-menu_communities:communities'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'communities',
    'router_path' => 'communities',
    'link_title' => 'Communities',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'class' => array(
          0 => 'cmnts',
        ),
      ),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'external' => 0,
      'identifier' => 'main-menu_communities:communities',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: main-menu_groups:groups.
  $menu_links['main-menu_groups:groups'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'groups',
    'router_path' => 'groups',
    'link_title' => 'Groups',
    'options' => array(
      'alter' => TRUE,
      'external' => 0,
      'identifier' => 'main-menu_groups:groups',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 10,
    'customized' => 1,
  );
  // Exported menu link: main-menu_owners-lookup:owners.
  $menu_links['main-menu_owners-lookup:owners'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'owners',
    'router_path' => 'owners',
    'link_title' => 'Owners Lookup',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'class' => array(
          0 => 'ownrs',
        ),
      ),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'external' => 0,
      'identifier' => 'main-menu_owners-lookup:owners',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Communities');
  t('Groups');
  t('Owners Lookup');

  return $menu_links;
}
