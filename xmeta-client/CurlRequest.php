<?php
class CurlRequest{

  function getRequest($url, $headers = array()){

    $curlHandler = curl_init();  

    curl_setopt($curlHandler,CURLOPT_URL,$url);
    curl_setopt($curlHandler,CURLOPT_RETURNTRANSFER,true);
    curl_setopt($curlHandler,CURLOPT_HTTPHEADER,$headers); 
    $result=curl_exec($curlHandler);
    curl_close($curlHandler);
    if($result == "Unauthorized")
      throw new Exception(" Access Denied "); 
    return $result;
  }
  
  function postRequest($url, $data){

    $data_string = json_encode($data);                                                                                   

    $curlHandler = curl_init($url);                                                                      
    curl_setopt($curlHandler, CURLOPT_CUSTOMREQUEST, "POST");                                                                     
    curl_setopt($curlHandler, CURLOPT_POSTFIELDS, $data_string);                                                                  
    curl_setopt($curlHandler, CURLOPT_RETURNTRANSFER, true);                                                                      
    curl_setopt($curlHandler, CURLOPT_HTTPHEADER, array(                                                                          
      'Content-Type: application/json',                                                                                
      'Content-Length: ' . strlen($data_string))                                                                       
    );       
    $result = curl_exec($curlHandler);
    curl_close($curlHandler);
    if($result == "Unauthorized")
     throw new InvalidArgumentException("Invalid Arguments"); 
   return $result;
 }

}
?>