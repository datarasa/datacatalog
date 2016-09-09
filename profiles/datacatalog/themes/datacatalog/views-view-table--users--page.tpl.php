<?php foreach ($rows as $row_count => $row): ?>
  <div <?php if ($row_classes[$row_count]): print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  endif; ?>>
    <div class="pd-wrpr">
      <div class="mem_pic"><?php echo $row["picture"]; ?></div>
      <div class="mem_dtls">
        <div class="mem_nm"><?php echo $row["php"]; ?></div>
      </div>
      <?php if ($row["edit_node"] != ""): ?> 
        <div class="edit"><?php echo $row["edit_node"]; ?></div> 
	  <?php endif; ?> 
    </div>
  </div>
<?php endforeach; ?>