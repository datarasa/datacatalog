<table <?php if ($classes): print 'class="' . $classes . '" '; endif; ?><?php print $attributes; ?>>
  <?php if (!empty($title) || !empty($caption)) : ?>
    <caption><?php print $caption . $title; ?></caption>
  <?php endif; ?>
  <?php if (!empty($header)) : ?>
    <thead>
      <tr>
        <?php foreach ($header as $field => $label): 
	      if($field != "og_group_ref") :	
		?>
            <th <?php if ($header_classes[$field]): print 'class="' . $header_classes[$field] . '" '; endif; ?>>
              <?php print $label; ?>
            </th>
        <?php
	       endif;
		 endforeach; ?>
      </tr>
    </thead>
  <?php endif; ?>
  <tbody>
    <?php foreach ($rows as $row_count => $row): ?>
      <tr <?php if ($row_classes[$row_count]): print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  endif; ?>>
        <?php foreach ($row as $field => $content): 
		  if ($field == "og_group_ref"):
		    $communities=$content;
		  endif;
		  if ($field == "nothing" and str_replace(' ', '', $content)=="|"):
		    $content = "<div style='text-align:left;'>To manage Source you need to resubscribe atleast in one of the following Communities:<br><strong>".$communities."</strong></div>";
			$content = '<div class="label label-sm label-info" data-html="true" data-toggle="tooltip" data-placement="bottom" title="'.$content.'">Info!</div>';
			$class = "";
		  else:
		    $class="";  
		  endif;
		  if($field != "og_group_ref") :
        ?>
          <td <?php if ($field_classes[$field][$row_count]): print 'class="'. $field_classes[$field][$row_count] .' '.$class.'" '; endif; ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
            <?php echo $content; ?>
          </td>
        <?php 
		  endif;
		endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>