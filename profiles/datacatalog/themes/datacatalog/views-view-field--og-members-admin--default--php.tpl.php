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
$cid = arg(2); 
$comm_node = node_load($cid);
$comm_auth = $comm_node->uid;
if ( $comm_auth != $row->uid ) { 
  $gid = arg(2);
  $uid = $row->uid;
  $query = db_select('users', 'u');
  $query->condition('u.uid', $uid, '=')
	->condition('ogm.state', 1, '>=')
	->fields('ogm', array('state'))
	->join('og_membership', 'ogm', "ogm.gid = :gid AND u.uid = ogm.etid AND ogm.entity_type = 'user'", array(':gid' => $gid ));
  $state = $query->execute()->fetchField();
  if($state == 2):
    $mem_lnk_txt = "Activate";  
    $mem_lnk = '<a class="og_custom_gadmin" style="cursor:pointer;" data="approve_'.$gid.'_'.$uid.'">' .$mem_lnk_txt. '</a>';
  else:
    $mem_lnk = 'Active';
  endif;

  if($state >= 1):
    $mem_lnk_txt2 = "Unsubscribe";  
    $mem_lnk2 = '<a class="og_custom_gadmin" style="cursor:pointer;" data="delete_'.$gid.'_'.$uid.'">' .$mem_lnk_txt2. '</a>';
  endif;
?>
<div class="mem_lnk" style="float:left; width:auto;"><?php print $mem_lnk; ?> | </div>
<div class="mem_lnk" style="float:left; width:auto;"><?php print $mem_lnk2; ?></div> 
<div id="dialog-confirm" title="Deletion?" style="display: none;">
  <p><span class="ui-icon ui-icon-alert" style="float:left; margin:0 7px 20px 0;"></span>This user will be unsubscribed from the Community. Are you sure?</p>
</div>
<?php
}
?>
 