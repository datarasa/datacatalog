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
?>
<?php 
 $uid = $row->_entity_properties['user'];
 $comment_user = user_load($uid);
 $options = array(
    'attributes' => array('title'=>'view user profile'),
    'html' => TRUE,
  );
  if ($comment_user->picture == ''):
    $profile_path = "/".drupal_get_path_alias('user/' . $comment_user->uid);	
    $img_path = '/sites/default/files/pictures/user-default.png';
    $style = 'activity_stream_user_image';
    $img = '<img width="50" height="50" title="'.$comment_user->name.'\'s default picture" alt="'.$comment_user->name.'\'s default picture" src="/sites/default/files/pictures/user-default.png">';
    $output = l($img, $profile_path, $options);
  else:
    $profile_path = "/".drupal_get_path_alias('user/' . $comment_user->uid);	
    $img_path = $comment_user->picture->uri;
    $style = 'activity_stream_user_image';
    $img = '<img title="'.$comment_user->name.'\'s picture" alt="'.$comment_user->name.'\'s picture" src="'.image_style_url($style, $img_path).'">';
    $output = l($img, $profile_path, $options);
  endif;
?>
<?php print $output; ?>
