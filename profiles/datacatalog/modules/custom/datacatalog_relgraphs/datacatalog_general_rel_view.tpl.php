<?php
$mod_path = drupal_get_path ( 'module', 'datacatalog_relgraphs' );
$loader_img = '/'.$mod_path.'/images/loading.gif';
drupal_add_js ( $mod_path . '/js/build_general_d3graph.js');
drupal_add_js ( $mod_path . '/js/loadingoverlay.js');
?>
<div class="graph_json">[<?php echo $output;?>]</div>
<div class="row row-eq-ht">
	<div class="sidebar sidebar-graph col-md-3">
		<h2>Browse By:</h2>
		<form role="form" accept-charset="UTF-8" id="console-form" method="post" action="">
<?php 
$community_query = '{"statements":[{"statement":"MATCH (n:Community) RETURN n","resultDataContents":["row","graph"],"includeStats":true}]};';
$source_query = '{"statements":[{"statement":"MATCH (n:Source) RETURN n","resultDataContents":["row","graph"],"includeStats":true}]};';
$tags_query = '{"statements":[{"statement":"MATCH (n:Tags) RETURN n","resultDataContents":["row","graph"],"includeStats":true}]};';
$user_query = '{"statements":[{"statement":"MATCH (n:User) RETURN n","resultDataContents":["row","graph"],"includeStats":true}]};';
$business_process_query = '{"statements":[{"statement":"MATCH (n:Business_Process) RETURN n","resultDataContents":["row","graph"],"includeStats":true}]};';
		    ?>
			<div class="form-group" id="communityCheckbox">
				<h2><a href="#communityCheckboxInner" class="" data-toggle="collapse">Communities</a></h2>
				<div class="collapse" id="communityCheckboxInner">
				<div class="toggle-link"><a href="#">Select All</a></div>
				<?php 
$curl = curl_init ();
curl_setopt ( $curl, CURLOPT_URL, 'http://localhost:7575/db/data/transaction/commit' );
curl_setopt ( $curl, CURLOPT_RETURNTRANSFER, 1 );
curl_setopt ( $curl, CURLOPT_HTTPHEADER, array (
  'Accept: application/json; charset=UTF-8',
  'Content-Type: application/json',
  'Content-Length: ' . strlen ( $community_query ),
  'X-Stream: true'
) );
curl_setopt ( $curl, CURLOPT_CUSTOMREQUEST, "POST" );
curl_setopt ( $curl, CURLOPT_POSTFIELDS, $community_query );
$community_result = curl_exec ( $curl );
// echo $relation_result;
curl_close ( $curl );
$res = json_decode (  $community_result );
foreach ( $res->results[0]->data as $record ) {
  $id = $record->graph->nodes[0]->id;
  $label = $record->graph->nodes[0]->properties->title;
?>
				    <div class="checkbox">
  					  <label><input type="checkbox" value="<?php echo $id; ?>"><?php echo $label; ?></label>
				    </div>
					
				    <?php 	} ?>
				</div>
			</div>
			<div class="form-group" id="sourceCheckbox">
				<h2><a href="#sourceCheckboxInner" class="" data-toggle="collapse">Sources</a></h2>
				<div class="collapse" id="sourceCheckboxInner">
				<div class="toggle-link"><a href="#">Select All</a></div>
				<?php 
$curl = curl_init ();
curl_setopt ( $curl, CURLOPT_URL, 'http://localhost:7474/db/data/transaction/commit' );
curl_setopt ( $curl, CURLOPT_RETURNTRANSFER, 1 );
curl_setopt ( $curl, CURLOPT_HTTPHEADER, array (
  'Accept: application/json; charset=UTF-8',
  'Content-Type: application/json',
  'Content-Length: ' . strlen ( $source_query ),
  'X-Stream: true'
) );
curl_setopt ( $curl, CURLOPT_CUSTOMREQUEST, "POST" );
curl_setopt ( $curl, CURLOPT_POSTFIELDS, $source_query );
$source_result = curl_exec ( $curl );
curl_close ( $curl );
$res1 = json_decode (  $source_result );
foreach ( $res1->results[0]->data as $record ) {
  $id = $record->graph->nodes[0]->id;
  $label = $record->graph->nodes[0]->properties->title;
					?>
				    <div class="checkbox">
  					  <label><input type="checkbox" value="<?php echo $id; ?>"><?php echo $label; ?></label>
				    </div>
 <?php 	} ?>
				</div>    
			</div>
			<div class="form-group" id="tagsCheckbox">
				<h2><a href="#tagsCheckboxInner" class="" data-toggle="collapse">Tags</a></h2>
				<div class="collapse" id="tagsCheckboxInner">
				<div class="toggle-link"><a href="#">Select All</a></div>
				<?php 
$curl = curl_init ();
curl_setopt ( $curl, CURLOPT_URL, 'http://localhost:7474/db/data/transaction/commit' );
curl_setopt ( $curl, CURLOPT_RETURNTRANSFER, 1 );
curl_setopt ( $curl, CURLOPT_HTTPHEADER, array (
  'Accept: application/json; charset=UTF-8',
  'Content-Type: application/json',
  'Content-Length: ' . strlen ( $tags_query ),
  'X-Stream: true'
) );
curl_setopt ( $curl, CURLOPT_CUSTOMREQUEST, "POST" );
curl_setopt ( $curl, CURLOPT_POSTFIELDS, $tags_query );
$tags_result = curl_exec ( $curl );
curl_close ( $curl );
$res2 = json_decode (  $tags_result );
foreach ( $res2->results[0]->data as $record ) {
  $id = $record->graph->nodes[0]->id;
  $label = $record->graph->nodes[0]->properties->name;
					?>
				    <div class="checkbox">
  					  <label><input type="checkbox" value="<?php echo $id; ?>"><?php echo $label; ?></label>
				    </div>
<?php 	} ?>
			  </div>	    
			</div>
			<div class="form-group" id="ownersCheckbox">
				<h2><a href="#ownersCheckboxInner" class="" data-toggle="collapse">Owners</a></h2>
				<div class="collapse" id="ownersCheckboxInner">
				<div class="toggle-link"><a href="#">Select All</a></div>
				<?php 
$curl = curl_init ();
curl_setopt ( $curl, CURLOPT_URL, 'http://localhost:7474/db/data/transaction/commit' );
curl_setopt ( $curl, CURLOPT_RETURNTRANSFER, 1 );
curl_setopt ( $curl, CURLOPT_HTTPHEADER, array (
  'Accept: application/json; charset=UTF-8',
  'Content-Type: application/json',
  'Content-Length: ' . strlen ( $user_query ),
  'X-Stream: true'
) );
curl_setopt ( $curl, CURLOPT_CUSTOMREQUEST, "POST" );
curl_setopt ( $curl, CURLOPT_POSTFIELDS, $user_query );
$user_result = curl_exec ( $curl );
curl_close ( $curl );
$res3 = json_decode (  $user_result );
foreach ( $res3->results[0]->data as $record ) {
  $id = $record->graph->nodes[0]->id;
  $label = $record->graph->nodes[0]->properties->name;
					?>
				    <div class="checkbox">
  					  <label><input type="checkbox" value="<?php echo $id; ?>"><?php echo $label; ?></label>
				    </div>
 <?php 	} ?>
				</div>    
			</div>
			<div class="form-group" id="businessProcessCheckbox">
				<h2><a href="#businessProcessCheckboxInner" class="" data-toggle="collapse">Business Process</a></h2>
				<div class="collapse" id="businessProcessCheckboxInner">
				<div class="toggle-link"><a href="#">Select All</a></div>
				<?php 
$curl = curl_init ();
curl_setopt ( $curl, CURLOPT_URL, 'http://localhost:7474/db/data/transaction/commit' );
curl_setopt ( $curl, CURLOPT_RETURNTRANSFER, 1 );
curl_setopt ( $curl, CURLOPT_HTTPHEADER, array (
  'Accept: application/json; charset=UTF-8',
  'Content-Type: application/json',
  'Content-Length: ' . strlen ( $business_process_query ),
  'X-Stream: true'
) );
curl_setopt ( $curl, CURLOPT_CUSTOMREQUEST, "POST" );
curl_setopt ( $curl, CURLOPT_POSTFIELDS, $business_process_query );
$business_process_result = curl_exec ( $curl );
curl_close ( $curl );
$res4 = json_decode (  $business_process_result );
foreach ( $res4->results[0]->data as $record ) {
  $id = $record->graph->nodes[0]->id;
  $label = $record->graph->nodes[0]->properties->title;
					?>
				    <div class="checkbox">
  					  <label><input type="checkbox" value="<?php echo $id; ?>"><?php echo $label; ?></label>
				    </div>
 <?php 	} ?>
				 </div>   
			</div>
			<div class="apply-button-wrapper">
			  <button type="button" class="btn btn-primary" id="ApplytoGraph">Apply</button>
			</div>
	  </form>
	</div>
	<div id="graphContainer" class="col-md-9" tabindex='1'>
   
  <?php if(isset($result1) and $result1!=""){ ?>
  <?php if(isset($error)){ echo '<div style="margin:5px; color:red;">' . $error . ' </div>' ;} ?>
  <div id="zoom_slider" class="slider-container"></div>
		<div class="fullscreen_icon" title="Enter Fullscreen">
			<img src="/<?php print "$mod_path/css/images/fullscreen.png" ?>" />
		</div>
  <?php 
  }
  ?>
</div>
</div>

<?php 
if($counter > 15 ) { ?>
<div id="loadMore">Load more</div>
<?php

}

		?>
<script>

(function($) {
  $(document).ready(function () {  
    var statement1 = "";
    var statement = "";  
    var post_request = "";
    $("#ApplytoGraph").on('click',function(){
      var ids = []; 
      $("#console-form input:checkbox:checked").each(function() {
	    ids.push($(this).val()); // do your staff with each checkbox
	  });
      if(ids.length > 0){	
	    $("#graphContainer").html("");	
	    if($(this).parent().find('.ajax-progress').length == 0){
	      $(this).parent().append('<span class="ajax-progress"><span class="throbber">&nbsp;</span></span>');
	    }
 	    var ids_str = ids.join(); 
	    statement = "MATCH a -[r]- b WHERE id(a) IN["+ids_str+"] AND id(b) IN["+ids_str+"]  RETURN r";
	    post_request = {"statements":[{"statement":""+statement+"","resultDataContents":["row","graph"],"includeStats":true}]};
	    var vdata = 'ids='+ids_str; 
	    $.ajax({
	      type: "POST",
   	      url: "/relationship/get-console-data",
   	      data: vdata,
   	      success: function(data, textStatus, jqXHR){
            var res = jQuery.parseJSON(data);
	        console.log(JSON.stringify(res.results.data));	
    	    var graph_data = convertNeo4jDataToD3(res);
    	    $("#ApplytoGraph").parent().find('.ajax-progress').remove();
    	    $('#graphContainer').focus();					    	 
		    var kb = buildGraph(graph_data,"#graphContainer",0);
		  },
		  failure: function(msg){console.log("failed")}
	    });
	  }else{
	    alert("Please Select some options");
	  }
    });
  });
})(jQuery);
</script>
<?php

?>
