<?php 
global $user; 
foreach ($rows as $row_count => $row):
 ?>
 <div <?php if ($row_classes[$row_count]): print 'class="views-row ' . implode(' ', $row_classes[$row_count]) .' col-md-12 col-sm-12 col-xs-12 p-5"';  endif; ?>>
   <div class="pd-wrpr col-sm-12 col-md-12 col-xs-12">
     <div class="wrapper-2">
       <div id="img-wrapper" class="col-sm-2 col-md-1 col-xs-12 p-l-0 p-r-0">
         <div class="image"><?php echo $row["field_group_image"]; ?></div>
       </div> 
       <div class="col-md-11 col-sm-10 col-xs-12 p-0">
         <div id="desc-wrapper" class="col-sm-9 col-md-10 col-xs-9 p-l-0 p-r-0">
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
         </div>
         <div class="members col-md-1 col-sm-1 col-xs-3 p-0">
           <span class="mem-img col-xs-12">&nbsp;</span>
           <span class="col-xs-12" id="member"><?php echo $row["uid"];?></span>
         </div>
       </div>
       <?php 
		$body1 = substr($row["body"], 0, 470);
		$body2 = substr($row["body"], 470);
	   ?>
       <div class="bdy">
         <?php if (substr($body1, -1) == ' ') :
           echo "<span class='init'>".$body1."</span>"." "."<span class='rest' style='display:none;'>".$body2."</span>"; 
         else :
           echo "<span class='init'>".$body1."</span><span class='rest' style='display:none;'>".$body2."</span>";
         endif; ?>
		 
         <div class="showmore-button toggler">show more</div>
       </div>
     </div>
   </div> 
 </div>
<?php endforeach; ?>