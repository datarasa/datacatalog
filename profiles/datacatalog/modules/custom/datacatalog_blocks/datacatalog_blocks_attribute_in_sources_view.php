<?php
if (isset($_REQUEST['ng_lightbox_path'])) {
  $url = $_REQUEST['ng_lightbox_path'];
  $srch_key_arr = explode("?",$_REQUEST["ng_lightbox_path"]);
  $srch_key_arr = explode("=",$srch_key_arr[1]);
  $cnid = $srch_key_arr[2];
  $attrib_key_arr = explode("&",$srch_key_arr[1]);
  $attribute = $attrib_key_arr[0];
  $type = "source";
  $nodes = array();
  $nodes = node_load_multiple(array(), array('type' => $type));
  if (count($nodes) > 0) {
 ?>     
      <p>Attribute <?php echo $attribute; ?> exist in following Sources:<p>
     <ul>
 <?php        
    foreach ($nodes as $source) {
      if (isset($source->field_csv_file['und'][0]['uri']) && $source->field_csv_file['und'][0]['uri'] != '') {
        $file_path = $source->field_csv_file['und'][0]['uri'];
        $dir_uri = file_stream_wrapper_get_instance_by_uri($file_path);
        $file_link = $dir_uri->realpath();
        $csvfile = file($file_link, FILE_SKIP_EMPTY_LINES);
        $csv = array_map("str_getcsv", $csvfile);
        $keys = array_shift($csv);
        if (in_array($attribute, $keys)) {
          $alias = drupal_get_path_alias('node/' . $source->nid);
  ?>          
           <li> <?php echo l($source->title, $alias); ?> </li>
 <?php           
        }  
      }
    }
   ?>   
      </ul>
  <?php    
  }else {
      ?>
      <p>Attribute <?php echo $attribute ?> not found in anyother Source<p>
 <?php         
  }
}
?>

