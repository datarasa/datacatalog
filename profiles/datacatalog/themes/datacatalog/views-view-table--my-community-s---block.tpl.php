 <?php 
foreach ($rows as $row_count => $row):
  $query = db_select('users', 'u');
  $query -> condition('u.uid', 0, '<>')
         -> condition('u.status', 1, '=')
         -> condition('ogm.state', 1, '=')
         -> fields('u', array('uid', 'name'))
         -> join('og_membership', 'ogm', "ogm.gid = :gid AND u.uid = ogm.etid AND ogm.entity_type = 'user'", array(':gid' => $row["nid"]));
  $total_members = $query->execute()->rowCount();
   ?>
  <div <?php if ($row_classes[$row_count]): print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  endif; ?>>
    <?php echo $row["title"]; ?> (<?php echo $total_members; ?> members)
  </div>
<?php endforeach; ?>