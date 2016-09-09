<?php

$cid = $row->_entity_properties["id"];
$content_type = "source";
$found = count_nodes_ctype_og($cid,$content_type);
if($found > 0) {
  $title = "<div style='text-align:left;'>A community can not be deleted if it is having sources, delete sources first.</div>";
  echo $content = '<div class="label label-sm label-info" data-html="true" data-toggle="tooltip" data-placement="bottom" title="'.$title.'">Info!</div>';
}else {
  echo $output; 
}
?>
