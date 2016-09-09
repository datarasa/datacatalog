<?php
$members = og_get_group_members_properties(45, array(), 'members__1', 'node');
print_r($members);
$documentCounter = 1;
$linksArr[$documentCounter]['value'] = 'abc';
$linksArr[$documentCounter]['type']  = 'person'; 
$documentCounter++;
echo json_encode($linksArr);
