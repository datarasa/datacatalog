<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
$type = "";
if ($row->field_node_ref_node_type == 'example_create_comment'):
  $nid = $row->_field_data['nid']['entity']->nid;
  $alias = drupal_get_path_alias('node/'.$nid);
  $read_more = l('more', $alias); 
  $output = $row->field_field_comment_ref[0]['raw']['entity']->comment_body['und'][0]['safe_value'];
  if (drupal_strlen(strip_tags($output)) > 200):
    $output = truncate_utf8(strip_tags($output), 200, TRUE, TRUE, 1)." ".$read_more;
  else:
    $output = truncate_utf8(strip_tags($output), 200, TRUE, TRUE, 1);
  endif;
endif;
if (drupal_strlen(strip_tags($output)) > 200):
  $nid = $row->_field_data['nid']['entity']->nid;
  $alias = drupal_get_path_alias('node/'.$nid);
  $read_more = l('see more', $alias, array('attributes' => array('class' => array('more-link community-recent-more-link')))); 
  $output = truncate_utf8(strip_tags($output), 200, TRUE, TRUE, 1)." ".$read_more;
else:
  $output = truncate_utf8(strip_tags($output), 200, TRUE, TRUE, 1);
endif;
?>
<?php print $output; ?>
