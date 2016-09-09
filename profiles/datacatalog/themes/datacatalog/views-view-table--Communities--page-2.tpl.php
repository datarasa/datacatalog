<?php 
global $user; 
foreach ($rows as $row_count => $row):
  if (!in_array('community admin', $user->roles)):
    $gid = $row["nid"];
    $query = db_select('users', 'u');
    $query->condition('u.uid', $user->uid, '=')
          ->condition('ogm.state', 1, '>=')
          ->fields('ogm', array('state'))
          ->join('og_membership', 'ogm', "ogm.gid = :gid AND u.uid = ogm.etid AND ogm.entity_type = 'user'", array(':gid' => $gid ));
  
    $mem_found = $query->execute()->rowCount();
    $state = $query->execute()->fetchField();
    if ($mem_found == 1):
      if ($state == 2):
        $mem_lnk = '<span id="pndng_aprvl">Pending request...</span>';  
      elseif ($state == 1) :
        $mem_lnk_path = 'group/node/'.$gid.'/unsubscribe';
        $mem_lnk_txt = "Unsubscribe";
      //$mem_lnk = '<a class="og_custom" style="cursor:pointer;" data="delete_'.$gid.'">' .$mem_lnk_txt. '</a>';
        $mem_lnk = '';
      endif;
    else:
      $mem_lnk_path = 'group/node/'.$gid.'/subscribe/og_user_node';
      $mem_lnk_txt = "Subscribe";
      $mem_lnk = '<a class="og_custom" style="cursor:pointer;" data="subscribe_'.$gid.'">' .$mem_lnk_txt. '</a>';
    endif;
  else:
    $mem_lnk = '';
  endif;
  $row["uid"] = strip_tags($row["uid"]);
  if ($row["uid"] <= 1) :
    $member = "member";
  else:
    $member = "members";
  endif;
 ?>
 <div <?php if ($row_classes[$row_count]): print 'class="views-row ' . implode(' ', $row_classes[$row_count]) .' col-md-12 col-sm-12 col-xs-12 p-5"';  endif; ?>>
   <div class="pd-wrpr col-sm-12 col-md-12 col-xs-12">
     <div id="img-wrapper" class="col-sm-2 col-md-1 col-xs-12 p-l-0 p-r-0">
       <div class="image"><?php echo $row["field_group_image"]; ?></div>
     </div>
     <div id="desc-wrapper" class="col-sm-7 col-md-9 col-xs-9 p-l-0 p-r-0">
       <div class="title col-md-9 col-xs-8 p-0">
         <?php echo $row["title"]; ?>
         <div class="status-wrapper">
         <?php 
           $show_date = time() - (60*60*24*2); //time minus 2 weeks
           if (strtotime($row["created"]) >= $show_date):?>
             <div class="status-label">(Most Recent)</div>
           <?php endif;?>
         </div>
       </div>
    
     
       <div class="member-count-posted col-md-6 col-xs-6 p-0">
      
         <!--span id="posted-by"><?php echo $row["name"]; ?></span-->
       </div>
    
     </div>
     <div id="actions-wrapper" class="col-sm-3 col-md-2 col-xs-12 p-l-0 p-r-0">       
       <div class="query-data col-md-4 col-sm-1 col-xs-3 p-0"><span class="mem-img col-xs-12 p-0"><a href="/sources-list?og_group_ref_target_id=<?php echo $row['nid']; ?>"><img src="sites/all/themes/datacatalog/images/queryicon.png" title="Query Data"></a></span></div>    
       <div class="api col-md-4 col-sm-1 col-xs-3 p-0"><span class="mem-img col-xs-12 p-0"><a href="/content/datacatalog-api"><img src="sites/all/themes/datacatalog/images/icon1.png" title="API"></a></span></div>     
     </div>
    
     <div class="bdy colpsd col-md-11 col-xs-12 p-0"><?php echo $row["body"]; ?></div>
     <div class="tags col-md-7 col-xs-12 p-0">
       <div class="field-label">Tags:&nbsp;</div>
		 <div class="field-items"><?php echo $row["field_cmnty_tags"];?></div>
     </div>
     <div class="bot-conts col-md-7 col-xs-12 p-0">
       <div class="owners col-md-6">
         <div class="field-label">Owners:&nbsp;</div>
         <div class="field-items"><?php echo $row["field_owners"];?></div>
       </div>
       <div class="chgd col-md-6">
         <div class="field-label">Last Updated:&nbsp;</div>
		 <div class="field-items"><?php echo $row["changed"];?></div>
       </div>
     </div>
     <!--div class="mem_lnk"><?php echo $mem_lnk; ?></div-->	
   </div> 
 </div>
<?php endforeach; ?>