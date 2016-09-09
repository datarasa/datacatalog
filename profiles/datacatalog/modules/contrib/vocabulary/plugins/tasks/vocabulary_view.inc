<?php

/**
 * @file
 * Handle the 'vocabulary view' override task.
 *
 * This plugin overrides taxonomy/%taxonomy_vocabulary and reroutes it to the page manager, where
 * a list of tasks can be used to service this request based upon criteria
 * supplied by access plugins.
 */

/**
 * Specialized implementation of hook_page_manager_task_tasks(). See api-task.html for
 * more information.
 */
function vocabulary_vocabulary_view_page_manager_tasks() {
  if (module_exists('taxonomy')) {
    return array(
      // This is a 'page' task and will fall under the page admin UI
      'task type' => 'page',

      'title' => t('Vocabulary template'),
      'admin title' => t('Vocabulary template'),
      'admin description' => t('When enabled, this overrides the default Drupal behavior for displaying vocabularys at <em>taxonomy/%taxonomy_vocabulary</em>. If you add variants, you may use selection criteria such as vocabulary or user access to provide different displays of the vocabulary and associated nodes. If no variant is selected, the default Drupal vocabulary display will be used. This page only affects items actually displayed ad taxonomy/%taxonomy_vocabulary. Some vocabularys, such as forums, have their displays moved elsewhere. Also please note that if you are using pathauto, aliases may make a vocabularys appear somewhere else, but as far as Drupal is concerned, they are still at taxonomy/%taxonomy_vocabulary.'),
      'admin path' => 'taxonomy/%taxonomy_vocabulary',
      'admin summary' => 'vocabulary_vocabulary_view_admin_summary',

      // Menu hooks so that we can alter the taxonomy/%taxonomy_vocabulary menu entry to point to us.
      'hook menu' => 'vocabulary_vocabulary_view_menu',
      'hook menu alter' => 'vocabulary_vocabulary_view_menu_alter',

      // Callback to add items to the page manager task administration form:
      'task admin' => 'vocabulary_vocabulary_view_task_admin',

      // This is task uses 'context' handlers and must implement these to give the
      // handler data it needs.
      'handler type' => 'context',
      'get arguments' => 'vocabulary_vocabulary_view_get_arguments',
      'get context placeholders' => 'vocabulary_vocabulary_view_get_contexts',

      // Allow this to be enabled or disabled:
      'disabled' => variable_get('vocabulary_vocabulary_view_disabled', TRUE),
      'enable callback' => 'vocabulary_vocabulary_view_enable',
      'access callback' => 'vocabulary_vocabulary_view_access_check',

      // Allow additional operations
      'operations' => array(
        'settings' => array(
          'title' => t('Settings'),
          'description' => t('Edit name, path and other basic settings for the page.'),
          'form' => 'vocabulary_vocabulary_view_settings',
        ),
      ),
    );
  }
}

/**
 * Callback defined by vocabulary_vocabulary_view_page_manager_tasks().
 *
 * Alter the vocabulary view input so that vocabulary view comes to us rather than the
 * normal vocabulary view process.
 */
function vocabulary_vocabulary_view_menu_alter(&$items, $task) {
  if (variable_get('vocabulary_vocabulary_view_disabled', TRUE)) {
    return;
  }

  // Override the vocabulary view handler for our purpose, but only if someone else
  // has not already done so.
  if (isset($items['taxonomy/%taxonomy_vocabulary']) && $items['taxonomy/%taxonomy_vocabulary']['page callback'] == 'vocabulary_page' || variable_get('page_manager_override_anyway', FALSE)) {
    $items['taxonomy/%taxonomy_vocabulary']['page callback'] = 'vocabulary_vocabulary_view_page';
    $items['taxonomy/%taxonomy_vocabulary']['file path'] = $task['path'];
    $items['taxonomy/%taxonomy_vocabulary']['file'] = $task['file'];
  }
  else {
    // automatically disable this task if it cannot be enabled.
    variable_set('vocabulary_vocabulary_view_disabled', TRUE);

    if (isset($items['taxonomy/%taxonomy_vocabulary']['page callback'])) {
      $callback = $items['taxonomy/%taxonomy_vocabulary']['page callback'];
    }
    // Because Views changes %taxonomy_vocabulary to %views_arg, check to see if that
    // is why we can't enable:
    else if (isset($items['taxonomy/%views_arg']['page callback'])) {
      $callback = $items['taxonomy/%views_arg']['page callback'];
    }
    else {
      $callback = t('an unknown callback');
    }
    if (!empty($GLOBALS['page_manager_enabling_vocabulary_view'])) {
      drupal_set_message(t('Page manager module is unable to enable taxonomy/%taxonomy_vocabulary because some other module already has overridden with %callback.', array('%callback' => $callback)), 'error');
    }
  }
}

/**
 * Entry point for our overridden vocabulary view.
 *
 * This function asks its assigned handlers who, if anyone, would like
 * to run with it. If no one does, it passes through to the vocabulary module's
 * vocabulary view, which is vocabulary_page().
 */
function vocabulary_vocabulary_view_page($vocabulary, $depth = NULL) {
  // Prep the vocabulary to be displayed so all of the regular hooks are triggered.
  // Rather than calling vocabulary_page() directly, as it that would
  // potentially load nodes that were not necessary, execute some of the code
  // prior to identifying the correct CTools or Page Manager task handler and
  // only proceed with the rest of the code if necessary.

  // Assign the term name as the page title.
  drupal_set_title($vocabulary->name);

  // Load my task plugin
  $task = page_manager_get_task('vocabulary_view');

  // Load the term into a context.
  ctools_include('context');
  ctools_include('context-task-handler');
  $contexts = ctools_context_handler_get_task_contexts($task, '', array($vocabulary->vid));

  if (empty($contexts)) {
    return MENU_NOT_FOUND;
  }

  // Build the full output using the configured CTools plugin.
  $output = ctools_context_handler_render($task, '', $contexts, array($vocabulary->vid));
  if ($output !== FALSE) {
    return $output;
  }

  // Try loading an override plugin.
  foreach (module_implements('page_manager_override') as $module) {
    $call = $module . '_page_manager_override';
    if (($rc = $call('vocabulary_view')) && function_exists($rc)) {
      return $rc($vocabulary);
    }
  }

  // Otherwise, fall back to replicating the output normally generated by
  // vocabulary_page().

  drupal_add_feed('taxonomy/' . $vocabulary->vid . '/feed', 'RSS - ' . $vocabulary->name);
  module_load_include('pages.inc', 'vocabulary');
  return vocabulary_page($vocabulary);
}

/**
 * Callback to get arguments provided by this task handler.
 *
 * Since this is the vocabulary view and there is no UI on the arguments, we
 * create dummy arguments that contain the needed data.
 */
function vocabulary_vocabulary_view_get_arguments($task, $subtask_id) {
  return array(
    array(
      'keyword' => 'vocabulary',
      'identifier' => t('Vocabulary being viewed'),
      'id' => 1,
      'name' => 'vid',
      'settings' => array('input_form' => 'vid'),
      'default' => '404',
    ),
  );
}

/**
 * Callback to get context placeholders provided by this handler.
 */
function vocabulary_vocabulary_view_get_contexts($task, $subtask_id) {
  return ctools_context_get_placeholders_from_argument(vocabulary_vocabulary_view_get_arguments($task, $subtask_id));
}

/**
 * Callback to enable/disable the page from the UI.
 */
function vocabulary_vocabulary_view_enable($cache, $status) {
  variable_set('vocabulary_vocabulary_view_disabled', $status);

  // Set a global flag so that the menu routine knows it needs
  // to set a message if enabling cannot be done.
  if (!$status) {
    $GLOBALS['page_manager_enabling_vocabulary_view'] = TRUE;
  }
}

/**
 * Provide a nice administrative summary of the page so an admin can see at a
 * glance what this page does and how it is configured.
 */
function vocabulary_vocabulary_view_admin_summary($task, $subtask) {
  $task_name = page_manager_make_task_name($task['name'], $subtask['name']);

  $rows[] = array(
    array('class' => array('page-summary-label'), 'data' => t('Path')),
    array('class' => array('page-summary-data'), 'data' => 'taxonomy/%taxonomy_vocabulary'),
    array('class' => array('page-summary-operation'), 'data' => ''),
  );

  $rows[] = array(
    array('class' => array('page-summary-label'), 'data' => t('Access')),
    array('class' => array('page-summary-data'), 'data' => t('This page is publicly accessible.')),
    array('class' => array('page-summary-operation'), 'data' => ''),
  );

  $menu = t('No menu entry');

  $rows[] = array(
    array('class' => array('page-summary-label'), 'data' => t('Menu')),
    array('class' => array('page-summary-data'), 'data' => $menu),
    array('class' => array('page-summary-operation'), 'data' => ''),
  );

  $output = theme('table', array(), $rows, array('id' => 'page-manager-page-summary'));
  return $output;
}

/**
 * Callback to determine if a page is accessible.
 *
 * @param $task
 *   The task plugin.
 * @param $subtask_id
 *   The subtask id
 * @param $contexts
 *   The contexts loaded for the task.
 * @return
 *   TRUE if the current user can access the page.
 */
function vocabulary_vocabulary_view_access_check($task, $subtask_id, $contexts) {
  return user_access('access content');
}
