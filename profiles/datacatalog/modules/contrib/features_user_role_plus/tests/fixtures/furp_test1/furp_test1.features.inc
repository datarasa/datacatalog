<?php
/**
 * @file
 * furp_test1.features.inc
 */

/**
 * Implements hook_user_default_roles_plus().
 */
function furp_test1_user_default_roles_plus() {
  $roles = array();

  // Exported role: anonymous user
  $roles['anonymous user'] = array(
    'name' => 'anonymous user',
    'weight' => 0,
    'permissions' => array(
      'access content' => TRUE,
    ),
  );

  return $roles;
}
