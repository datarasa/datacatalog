<?php
/**
 * @file
 * furp_test2.features.inc
 */

/**
 * Implements hook_user_default_roles_plus().
 */
function furp_test2_user_default_roles_plus() {
  $roles = array();

  // Exported role: new_role
  $roles['new_role'] = array(
    'name' => 'new_role',
    'weight' => 0,
    'permissions' => array(
      'access content' => TRUE,
      'administer features' => TRUE,
    ),
  );

  return $roles;
}
