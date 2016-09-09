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
global $user;
$cid = arg(1); 
$comm_node = node_load($cid);
$comm_auth = $comm_node->uid;
if ( $comm_auth != $user->uid ): 
  $gid = strip_tags($output);
  $query = db_select('users', 'u');
  $query->condition('u.uid', $user->uid, '=')
        ->condition('ogm.state', 1, '>=')
        ->fields('ogm', array('state'))
        ->join('og_membership', 'ogm', "ogm.gid = :gid AND u.uid = ogm.etid AND ogm.entity_type = 'user'", array(':gid' => $gid ));
  
  $mem_found = $query->execute()->rowCount();
  $state = $query->execute()->fetchField();
  if ($mem_found == 1):
    if($state == 2):
      $mem_lnk = '<span id="pndng_aprvl">Pending request...</span>';  
    elseif($state == 1):
      $mem_lnk_txt = "Unsubscribe";
      $mem_lnk = '<a class="og_custom" style="cursor:pointer;" data="delete_'.$gid.'">' .$mem_lnk_txt. '</a>';
    endif;
  else:
    $mem_lnk_txt = "Subscribe";  
    $mem_lnk = '<a class="og_custom" style="cursor:pointer;" data="subscribe_'.$gid.'">' .$mem_lnk_txt. '</a>';
  endif;
else:
  $mem_lnk = '';
endif;
 
?>
<div class="mem_lnk">
  <?php print $mem_lnk; ?> 
</div>
<div class="edit-link">
  <?php 
    if (in_array('community admin', $user->roles) and $comm_auth == $user->uid): 
      $block = module_invoke('datacatalog_blocks','block_view','contextual_dropdown_links');
      print render($block['content']); 
    endif;
  ?>
</div>