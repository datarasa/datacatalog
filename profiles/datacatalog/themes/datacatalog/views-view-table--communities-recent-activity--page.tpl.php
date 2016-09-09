<div class="item-list">
  <ul>
<?php foreach ($rows as $row_count => $row): ?>  
    <li <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  } ?>> 
      <span class="views-field views-field-picture"> 
        <span class="field-content"><?php echo $row["picture"]?></span> 
      </span> 
      <div class="col_rt">
        <div class="arrow-lft"> </div>
        <div class="hdr-rcnt-actvty-strm">
          <span class="views-field views-field-name"> 
            <span class="field-content"><?php echo $row["name"]?></span> 
          </span> 
          <span class="views-field views-field-title"> 
            <span class="field-content"><?php echo $row["title"]?></span> 
          </span>
          <span class="views-field views-field-timestamp">        
            <span class="field-content"><?php echo $row["timestamp"]?></span>  
          </span>
        </div>
        <div class="views-field views-field-title-1"> 
          <span class="views-label views-label-title-1">Community:</span>
          <span class="field-content"><?php echo $row["title_1"]?></span> 
        </div>
        <div class="views-field views-field-body">
          <div class="field-content"><?php echo $row["body"]?></div>
        </div>
      </div>
    </li>
<?php endforeach; ?>    
  </ul>
</div>
