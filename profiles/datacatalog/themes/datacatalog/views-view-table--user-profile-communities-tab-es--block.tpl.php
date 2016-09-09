<?php
global $user;
?>
<table <?php if ($classes): print 'class="'. $classes . '" '; endif; ?><?php print $attributes; ?>>
  <?php if (!empty($title) || !empty($caption)): ?>
    <caption><?php print $caption . $title; ?></caption>
  <?php endif; ?>
  <?php if (!empty($header)): ?>
    <thead>
      <tr>
        <?php foreach ($header as $field => $label):
		  if ($field == "author"): 
		    $show_td = 0;
          elseif ($field == "nid_1" and !in_array('community admin', $user->roles)):
		    $show_td = 0;
		  elseif ($field == "nid_1" and in_array('community admin', $user->roles)): 
		    $show_td = 1;
		    $content = count_pend_members($content);
          elseif ($field == "nothing_2" and !in_array('community admin', $user->roles) ):
            $show_td = 0;   
          else:
            $show_td = 1;  
          endif;		
          if ($show_td == 1): 
        ?>
         <th <?php if ($header_classes[$field]): print 'class="'. $header_classes[$field] . '" '; endif; ?>>
           <?php print $label; ?>
         </th>
        <?php endif;			
		 endforeach; ?>
      </tr>
    </thead>
  <?php endif; ?>
    <tbody>
      <?php foreach ($rows as $row_count => $row): ?>
        <tr <?php if ($row_classes[$row_count]): print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  endif; ?>>
          <?php foreach ($row as $field => $content): 
		    if ($field == "author"):
			  $cmm_auth = $content;
			endif;
			
		    if ($field == "author"):
			  $show_td = 0;
			elseif ($field == "nid_1" and !in_array('community admin', $user->roles)):
		      $show_td = 0;
		    elseif ($field == "nid_1" and in_array('community admin', $user->roles)): 
		      $show_td = 1;
		      $content = count_pend_members($content);	 
		    elseif ($field == "nothing_2" and !in_array('community admin', $user->roles) ):
		      $show_td = 0;   
		    elseif ($field == "nothing_2" and in_array('community admin', $user->roles) and $user->uid != $cmm_auth):
              $title = "<div style='text-align:left;'>Community is created by another user.</div>";
              $content = '<div class="label label-sm label-info" data-html="true" data-toggle="tooltip" data-placement="bottom" title="'.$title.'">Info!</div>';
		    else:
			  $show_td = 1;  
		    endif;
		    if($show_td == 1):
		  ?>
          <td <?php if ($field_classes[$field][$row_count]): print 'class="' . $field_classes[$field][$row_count] . '" '; endif; ?>
		    <?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
            <?php print $content; ?>
          </td>
        <?php 
		  endif;
		  endforeach; ?>
        </tr>
      <?php endforeach; ?>
   </tbody>
</table>
