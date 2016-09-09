<?php
function http_curl_post($url, $post){
  $ch = curl_init($url);
  curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");  
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($ch, CURLOPT_POSTFIELDS,$post);
  curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1); 
  $result = curl_exec($ch);
  curl_close($ch);  // Seems like good practice
  return $result;
}

//$post_fields = json_encode($_POST["data"]);
$post_fields = $_POST["data"];
$post_url = $_POST["url"];

echo http_curl_post($post_url, $post_fields);

?>
