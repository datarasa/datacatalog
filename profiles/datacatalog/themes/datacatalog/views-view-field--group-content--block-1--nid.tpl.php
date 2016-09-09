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
 
 /* global $user;
  global $base_url;
  $nid = $output;
  $s_subscrbd = chk_usr_nd_subscrptn($user->uid,$nid);
  if ($s_subscrbd == 1):
    $mem_lnk_txt = "Unsubscribe";
    $src_sub = $base_url.'/'.path_to_theme().'/images/subscribe.png';
    $mem_lnk = '<a class="node_custom" style="cursor:pointer;" data="unsub_'.$nid.'"><img src="'.$src_sub.'" title="'.$mem_lnk_txt.'" alt="'.$mem_lnk_txt.'" /></a>';
  elseif ($s_subscrbd == 0):
    $mem_lnk_txt = "Subscribe";
    $src_sub = $base_url.'/'.path_to_theme().'/images/subscribe-new.png';
    $mem_lnk = '<a class="node_custom" style="cursor:pointer;" data="sub_'.$nid.'"><img src="'.$src_sub.'" title="'.$mem_lnk_txt.'" alt="'.$mem_lnk_txt.'" /></a>';
  endif;
  echo'<div class="mem_lnk">'.$mem_lnk.'</div>';*/
?>
