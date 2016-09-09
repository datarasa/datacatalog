<div class="item-list">
  <ul>
<?php foreach ($rows as $row_count => $row): 
//print_r($row);
?>  
    <li <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  } ?>> 
    <span class="views-field views-field-picture"> 
      <span class="field-content"><?php echo $row["user"]?></span> 
    </span> 
    <div class="col_rt">
    <div class="arrow-lft"> </div>
    <div class="hdr-rcnt-actvty-strm">
    <span class="views-field views-field-timestamp">        
      <span class="field-content"><span class="glyphicon glyphicon-calendar"></span> <?php echo $row["timestamp"]?></span>  
    </span>
    </div>
      <div class="views-field views-field-body">
        <div class="field-content"><?php echo $row["text"]?></div>
      </div>
      </div>
    </li>
   
<?php endforeach; ?>   
 
  </ul>
</div>
<?php 
 if(!isset($rows)){
 	echo "No result found.";
 } 
?>