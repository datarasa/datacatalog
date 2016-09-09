<?php
/**
 * @file
 * data_catalog_users.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function data_catalog_users_user_default_roles() {
  $roles = array();

  // Exported role: community admin.
  $roles['community admin'] = array(
    'name' => 'community admin',
    'weight' => 3,
  );

  // Exported role: guest.
  $roles['guest'] = array(
    'name' => 'guest',
    'weight' => 7,
  );

  // Exported role: site admin.
  $roles['site admin'] = array(
    'name' => 'site admin',
    'weight' => 6,
  );

  return $roles;
}
