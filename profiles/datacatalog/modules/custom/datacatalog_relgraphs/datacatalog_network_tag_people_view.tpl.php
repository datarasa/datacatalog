<?php
$mod_path = drupal_get_path('module', 'datacatalog_relgraphs');
drupal_add_js($mod_path.'/js/datacatalog_relgraphs.js');
drupal_add_js($mod_path.'/js/build_d3graph.js');
?>
<div class="graph_json">[<?php echo $output;?>]</div>
<div class="searchSection">
 <div class="form-panel">
   <form accept-charset="UTF-8" id="searchForm" method="post" action="">
<input type="hidden" name="rel_type" id="rel_type" value="tag_people" />
     <div>
       <div class="form-item form-type-textfield">
         <div class="alert alert-danger search-help-block" style="display:none;">
           <a href="#" class="searchclose" >&times;</a>
           <p class="search-help"></p>
         </div>
         <span role="status" aria-live="polite" class="ui-helper-hidden-accessible">
           15 results are available, use up and down arrow keys to navigate.
         </span>
        <input type="text" class="form-control form-text ui-autocomplete-input" maxlength="128" size="120" name="srch_key"  id="searchA" placeholder="Please enter Tag to generate the graph" autocomplete="off" value="<?php echo $_POST["srch_key"];?>">
        <input type="submit" class="form-submit kb-sq-submit btn btn-primary btn-block" value="Search" id="submit" style="outline: medium none;">
        <input type="hidden" id="hideVal" value="" />
      </div>
    </div>
  </form>            
 </div>
</div>
<?php 
if (isset($_POST['srch_key']) && $_POST['srch_key'] != "") { 
  $searchedKey = $_POST['srch_key'];
  $data = '{"statements":[{"statement":"MATCH (a:User)-[r]-(b:Source)-[r2:Source_Tags]-(c:Tags) Where c.name =  \''.$searchedKey.'\' RETURN r, r2;","resultDataContents":["row","graph"],"includeStats":true}]};';
  $curl = curl_init();
  curl_setopt($curl, CURLOPT_URL, 'http://localhost:7575/db/data/transaction/commit');
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($curl,CURLOPT_HTTPHEADER,array('Accept: application/json; charset=UTF-8','Content-Type: application/json','Content-Length: ' . strlen($data),'X-Stream: true'));
  curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");                                                                     
  curl_setopt($curl, CURLOPT_POSTFIELDS,$data);
  $result1 = curl_exec($curl);
  curl_close($curl);  
  $result_decoded = json_decode($result1);
}    
?>
<div id="graphContainer" class="col-md-9">
  <?php if(isset($result_decoded) and count($result_decoded->results[0]->data) > 0){ ?>
  <?php if(isset($error)){ echo '<div style="margin:5px; color:red;">' . $error . ' </div>' ;} ?>
  <div id="zoom_slider" class="slider-container"></div>
  <div class="fullscreen_icon" title="Enter Fullscreen">
    <img src="/<?php print "$mod_path/css/images/fullscreen.png" ?>" />
  </div>
  <?php }else if(isset($result_decoded) and count($result_decoded->results[0]->data) == 0){ ?>
  <span class="no-relationship">No relationships found </span>
  <?php
  }
  ?>
</div>  

<div class="sidebar sidebar-graph col-md-3" >
  <?php if(isset($usr_name)){ ?>
  <h2>Browse User</h2>
    <ul id="listUlD">
      <?php
       $usr_img = "/".$mod_path."/images/default_person.png";
echo '<li data="'.$usr_name.'"><span><img src="'.$usr_img.'" width="28" height="28" /></span><a href="'.$target_link.'" target="_blank">'.$usr_name.'</a></li>';
      ?>
   </ul>
   <?php } ?>

  <?php 
  $relnodes = get_nodes_in_group($user->uid, $type);
  $checkduplisource = array();
  $counter = 0;
  $image = "/".$mod_path."/images/default_dataitem.png";
  ?>
  <h2>Related Sources</h2>
   <?php 
if($relnodes->rowCount()>0) { ?>
    <ul id="listUlD">
      <?php
  foreach ($relnodes as $source) {
    $relsource_link = "node/".$source->nid;
    $relalias = "/".drupal_get_path_alias($relsource_link);
    $title = strlen($source->title) > 20 ? substr($source->title, 0, 20) . "..." : $source->title;
    if(! in_array($title, $checkduplisource)){
      if($counter <= 5){
        echo '<li data="'.$title.'"><a href="'.$relalias.'" target="_blank">'.$title.'</a></li>';
      }else{
        echo '<li data="'.$title.'" class="hideLi"><a href="'.$relalias.'" target="_blank">'.$title.'</a></li>';
      }
      $checkduplisource[] = $title;
      $counter++;
    }
  }
    ?>
   </ul>
    <?php 
}else{ ?>
   <div id="container">  
    <div id="listUlD-wrapper" class="scroll-pane">
     <ul id="listUlD">
       <li id='graph-side-bar-empty'>No results found</li>
      </ul>  
    </div>  
   </div> 
  <?php  
}  ?>
</div>
<?php if($counter > 15 ) { ?>
  <div id="loadMore">Load more</div>
<?php } 
if (isset($_POST['srch_key']) && $_POST['srch_key'] != "") { 
   if($result1){
  ?>
<script>

(function($) {
  $(document).ready(function () {  
    console.log( "ready!" );
    var SearchVal = $('#searchA').val();
    var graph_data = convertNeo4jDataToD3(<?php echo $result1; ?>);
    kb = new buildGraph(graph_data,"#graphContainer",0);
	jQuery(".fullscreen_icon").on("click", function () {
      if (kb.isFullscreen()) {
        kb.exitFullscreen();
      } else {
        kb.enterFullscreen();
      }
    });
    jQuery('.sidebar li').on('mouseover', function(e){
      kb.highlightNode(jQuery(this).attr('data'), true);
    });
    jQuery('.sidebar li').on('mouseout', function(e){
      kb.highlightNode(jQuery(this).attr('data'), false);
    });  
  });
})(jQuery);
</script>
 <?php 
      }
      } ?>
