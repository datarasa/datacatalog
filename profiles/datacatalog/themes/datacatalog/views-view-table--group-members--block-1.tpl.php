<div class="mt-element-card mt-card-round mt-element-overlay"> 
<?php foreach ($rows as $row_count => $row):
 ?>
  <div <?php if ($row_classes[$row_count]): print 'class="col-lg-2 col-md-3 col-sm-3 col-xs-12 '. implode(' ', $row_classes[$row_count]) . '"';  endif; ?>>
    <div class="mt-card-item">
      <div class="mt-card-avatar mt-overlay-1">
        <?php echo $row["picture"]; ?>
          <div class="mt-overlay">
            <ul class="mt-info">
              <li>
                <?php echo $row["php_1"];?>
              </li>
            </ul>
          </div>
      </div>
      <div class="mt-card-content">
        <h3 class="mt-card-name"><?php echo $row["php"]; ?></h3>
        <p class="mt-card-desc font-grey-mint"><?php echo $row["field_profile_position"]; ?></p>
      </div>
   </div>
  </div>
<?php endforeach; ?>
</div>