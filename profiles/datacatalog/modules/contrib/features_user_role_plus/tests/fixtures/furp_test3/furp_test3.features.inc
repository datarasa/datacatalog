<?php
/**
 * @file
 * furp_test3.features.inc
 */

/**
 * Implements hook_user_default_roles_plus().
 */
function furp_test3_user_default_roles_plus() {
  $roles = array();

  // Exported role: new_role3
  $roles['new_role3'] = array(
    'name' => 'new_role3',
    'weight' => 0,
    'permissions' => array(
      'permission_from_feature' => TRUE,
    ),
  );

  return $roles;
}
