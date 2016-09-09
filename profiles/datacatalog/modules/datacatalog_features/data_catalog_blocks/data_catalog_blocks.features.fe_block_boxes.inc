<?php
/**
 * @file
 * data_catalog_blocks.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function data_catalog_blocks_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Block for Add Community Link ';
  $fe_block_boxes->format = 'php_code';
  $fe_block_boxes->machine_name = 'add_community_link_block';
  $fe_block_boxes->body = '<!--a class="btn btn-primary ctools-use-modal" href="/node/add/community/nojs">Add New Community</a-->
<?php
$link = l(t(\'Add New Community\'), \'/node/add/group/nojs\', array(\'attributes\' => array(\'class\' => array(\'ctools-use-modal btn btn-primary\'))));
echo $link;
?>';

  $export['add_community_link_block'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Source csv info';
  $fe_block_boxes->format = 'php_code';
  $fe_block_boxes->machine_name = 'source_csv_info';
  $fe_block_boxes->body = '<?php
if (arg(0) == \'node\' && is_numeric(arg(1))) {
  $nid = arg(1);
  $node = node_load($nid);
  $markup = \'\';
  $business_process_id = $node->field_business_process[\'und\'][0][\'target_id\'];
  $business_node = node_load($business_process_id);
  $business_process_title = $business_node->title;
  $business_process_path = drupal_get_path_alias(\'node/\'.$business_process_id);
  $business_process_link = l( $business_process_title, $business_process_path, array(\'attributes\' => array(\'class\' => array(\'ng-lightbox\'))));

  foreach($node->field_other_documents[\'und\'] as $other_document) {
    $doc_name = $other_document[\'filename\'];
    $doc_uri = str_replace(\'public://\',\'sites/default/files/\',$other_document[\'uri\']);
    $doc_link .= l($doc_name, $doc_uri).\', \';
  }
  $doc_link = trim($doc_link,\', \');
  $author = $node->name;
  foreach($node->field_owners as $userref) {
	  foreach($userref as $usr) {
        $user = user_load($usr[\'uid\']);
        $username .= "<a href=\'/user/".$user->name."\'>".$user->name."</a>, ";
	  }
	}
	$username = trim($username,\', \');
  ?>
  <div id="csv-info-container-main">
    <div id="csv-info-container-main-inner">
      <div id="csv-info-csv-author" class="csv-info-csv"><span id="label">Created By:</span><span id="value"><?php echo $author; ?></span></div>
      <div id="csv-info-csv-date" class="csv-info-csv">
        <span id="label">Created Date:</span><span id="value"><?php echo date(\'m-d-Y\',$node->created); ?></span>
      </div>
      <?php if ($username != \'\'):?>
     <div id="csv-info-csv-author" class="csv-info-csv"><span id="label">Owners:</span><span id="value"><?php echo $username; ?></span></div>
     <?php endif;?>
      <div id="business_process-info" class="csv-info-csv"><span id="label">Business Process:</span><span id="value"><?php echo  $business_process_link; ?></span></div>
      <?php if ($doc_link !=\'\'):?>
      <div id="other-document-info" class="csv-info-csv"><span id="label">Other Documents:</span><span id="value"><?php echo $doc_link; ?></span></div>
      <?php endif;?>
    </div>
  </div>
  <?php
 }
?>
';

  $export['source_csv_info'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'sources graph';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'source_graph';
  $fe_block_boxes->body = '<div id="sourceholder" class="demo-placeholder"></div>';

  $export['source_graph'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Source metadata';
  $fe_block_boxes->format = 'php_code';
  $fe_block_boxes->machine_name = 'source_metadata';
  $fe_block_boxes->body = '<?php
  $block = module_invoke(\'datacatalog_blocks\', \'block_view\', \'datacatalog_meta_data\');
  print render($block[\'content\']);
?>';

  $export['source_metadata'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'user graph';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'user_graph';
  $fe_block_boxes->body = '<div id="placeholder" class="demo-placeholder"></div>';

  $export['user_graph'] = $fe_block_boxes;

  return $export;
}
