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
if(preg_match('~@@@(.*?)@@@~', $output, $result)) {
  $data = explode("___",$result[1]);  
  $alias = "source/".basename($data[2]);
  $path = drupal_lookup_path("source", $alias);
  $node = menu_get_object("node", 1, $path);
  $title = $node->title;
  $msg = '<a href="'.$data[0].'">'.$data[1].'</a> has posted <a href="'.$data[2].'">'.$title.'</a>';
  $output = preg_replace('~@@@(.*?)@@@~', " ", $output);
  $output = $msg.$output;
}
?>
<?php print html_entity_decode($output); ?>