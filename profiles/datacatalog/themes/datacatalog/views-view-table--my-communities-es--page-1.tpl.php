<?php 
global $user; 
foreach ($rows as $row_count => $row):
  //echo"<pre>";
  //print_r($row);
  if (!in_array('community admin', $user->roles)) :
    $gid = $row["nid"];
    $query = db_select('users', 'u');
    $query->condition('u.uid', $user->uid, '=')
          ->condition('ogm.state', 1, '>=')
          ->fields('ogm', array('state'))
          ->join('og_membership', 'ogm', "ogm.gid = :gid AND u.uid = ogm.etid AND ogm.entity_type = 'user'", array(':gid' => $gid ));

    $mem_found= $query->execute()->rowCount();
    $state=$query->execute()->fetchField();

    if ($mem_found == 1):
      if ($state==2):
        $mem_lnk='<span id="pndng_aprvl">Pending request...</span>';  
      elseif($state==1):
        $mem_lnk_path='group/node/'.$gid.'/unsubscribe';
        $mem_lnk_txt="Unsubscribe";
      /*$mem_lnk='<a class="og_custom" style="cursor:pointer;" data="delete_'.$gid.'">'.$mem_lnk_txt.'</a>';*/
        $mem_lnk = '';
      endif;
    else:
      $mem_lnk_path='group/node/'.$gid.'/subscribe/og_user_node';
      $mem_lnk_txt="Subscribe";
      $mem_lnk='<a class="og_custom" style="cursor:pointer;" data="subscribe_'.$gid.'">'.$mem_lnk_txt.'</a>';
    endif;
  else:
    $mem_lnk='';
  endif;
  
  $row["uid"] = strip_tags($row["uid"]);
  if($row["uid"]<=1):
    $member="member";
  else:
    $member="members";
  endif;
 
 ?>
<div <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .' col-md-4 col-sm-6 col-xs-12 p-5"';  } ?>>
  <div class="pd-wrpr">
    <div class="wrapper">   
      <div id="img-wrapper" class="col-sm-3 col-md-3 col-xs-12 p-l-0 p-r-0">
        <div class="image"><?php echo $row["field_group_image"]; ?></div>
      </div>
      <div class="col-md-9 col-sm-9 col-xs-12 p-0">
        <div id="desc-wrapper" class="col-sm-9 col-md-9 col-xs-9 p-l-0 p-r-0">
          <div class="title p-0">
            <?php echo $row["title"];?>
            <div class="status-wrapper">
              <?php 
              $show_date = time() - (60*60*24*2); //time minus 2 weeks
              if (strtotime($row["created"]) >= $show_date):?>
                <div class="status-label">(Most Recent)</div>
              <?php endif;?>
            </div>
          </div>  
        </div>
        <div class="members col-md-3 col-sm-3 col-xs-3 p-0">
          <span class="mem-img col-xs-12 p-0">&nbsp;</span>
          <span class="col-xs-12" id="member"><?php echo $row["members_1"];?></span>
        </div>
      </div>
      <?php 
        if(strlen($row["body"])>470) : 
          $shrt = substr($row["body"], 0, 470);
          $rest = substr($row["body"], 470);

          if (substr($shrt, -1) == ' ') :
            $body = '<span class="init">'.$shrt.'</span>';
            $body.= ' <span class="rest" style="display:none;">'.$rest.'</span>';
          else :
            $body = '<span class="init">'.$shrt.'</span>';
            $body.= '<span class="rest" style="display:none;">'.$rest.'</span>';
          endif;
  
          $body.= '<div class="showmore-button toggler">show more</div>';
        else  :

          $body = '<span class="init">'.$row["body"].'</span>';
        endif;
      ?> 
      <div class="bdy">
        <?php echo $body;?>
      </div>
    </div> 
    <?php if($mem_lnk!="") :?>
      <div class="mem_lnk"><?php echo $mem_lnk; ?></div>
    <?php endif; ?>
  </div>
</div>
<?php endforeach; ?>
