<?php
include 'CurlRequest.php';
class XMetaClient{

  public $curlRequest;
  public $token;
  public $baseUrl;

  const AUTH_ROUTE = "auth";
  const ALL_ROUTES_ROUTE = "xmeta/api/v1/";
  const SHOW_DATABASES_ROUTE = "xmeta/api/v1/list/db";
  const SHOW_TABLES_ROUTE = "xmeta/api/v1/list/table/";
  const SHOW_COLUMNS_ROUTE = "xmeta/api/v1/list/column/";
  const SHOW_COLUMNS_WITH_TYPE_ROUTE = "xmeta/api/v1/list/columnWithType/";
  const GET_COLUMN_TYPE_ROUTE = "xmeta/api/v1/get/columnType/";
  const GET_COLUMN_LENGTH_ROUTE = "xmeta/api/v1/get/columnLength/";
  const GET_COLUMN_AT_POS_ROUTE = "xmeta/api/v1/get/columnAtPos/";
  const GET_PRIMARY_KEY_ROUTE = "xmeta/api/v1/get/primaryKey/";
  const GET_FOREIGN_KEY_ROUTE = "xmeta/api/v1/get/foreignKey/";
  const GET_FOREIGN_KEY_REF_TABLE_ROUTE = "xmeta/api/v1/get/foreignKeysRefTable/";
  const GET_INDEXES_ROUTE = "xmeta/api/v1/get/indexes/";
  const GET_ALL_INDEX_REF_TABLE_ROUTE = "xmeta/api/v1/get/allIdxRefTable/";
  const DATABASE_EXISTS_ROUTE = "xmeta/api/v1/exists/db/";
  const TABLE_EXISTS_ROUTE = "xmeta/api/v1/exists/table/";
  const COLUMN_EXISTS_ROUTE = "xmeta/api/v1/exists/column/";
  const SUPPORT_FEATURES_ROUTE = "xmeta/api/v1/get/supports/";
  const GET_DATABASE_INFO_ROUTE = "xmeta/api/v1/info/db/";
  const GET_DATABASE_DRIVER_INFO_ROUTE = "xmeta/api/v1/info/dbdriver/";

  function __construct($host, $port){
    $this->baseUrl = "http://" . $host . ":" .$port."/";
    $this->curlRequest = new CurlRequest();
  }

  function setToken($token){
   $this->token = $token;
 }

 function getToken(){
  return $this->token;
}

function authenticate($authParams){

 $result= $this->curlRequest->postRequest($this->baseUrl.self::AUTH_ROUTE, $authParams); 
 $result = json_decode($result, true);
 $this->setToken($result['result']['token']);
}

function listAvailableRoutes(){
  $header = array('Authorization:bearer '. $this->getToken());
  $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::ALL_ROUTES_ROUTE, $header), true);
  return $result['result'];
}

function showDataBases(){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::SHOW_DATABASES_ROUTE, $header), true);
 return  $result['result'];
}

function showTables($database){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::SHOW_TABLES_ROUTE.$database, $header), true);
 return  $result['result'];
}

function showColumns($database, $table){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::SHOW_COLUMNS_ROUTE.$database."/".$table, $header), true);
 return  $result['result'];
}

function showColumnWithType($database, $table){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::SHOW_COLUMNS_WITH_TYPE_ROUTE.$database."/".$table, $header), true);
 return  $result['result'];
}

function getColumnType($database, $table, $column){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::GET_COLUMN_TYPE_ROUTE.$database."/".$table."/".$column, $header), true);
 return  $result['result'];
}

function getColumnLength($database, $table, $column){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::GET_COLUMN_LENGTH_ROUTE.$database."/".$table."/".$column, $header), true);
 return  $result['result'];
}

function getColumnAtPos($database, $table, $columnIndex){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::GET_COLUMN_AT_POS_ROUTE.$database."/".$table."/".$columnIndex, $header), true);
 return  $result['result'];
}

function getPrimaryKey($database, $table){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::GET_PRIMARY_KEY_ROUTE.$database."/".$table, $header), true);
 return  $result['result'];
}

function getForeignKey($database, $table){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::GET_FOREIGN_KEY_ROUTE.$database."/".$table, $header), true);
 return  $result['result'];
}

function getForeignKeyRefTables($database, $table){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::GET_FOREIGN_KEY_REF_TABLE_ROUTE.$database."/".$table, $header), true);
 return  $result['result'];
}

function getIndexes($database, $table){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::GET_INDEXES_ROUTE.$database."/".$table, $header), true);
 return  $result['result'];
}

function getAllIndexesAndRefTables($database, $table){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::GET_ALL_INDEX_REF_TABLE_ROUTE.$database."/".$table, $header), true);
 return  $result['result'];
}

function databaseExists($database){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::DATABASE_EXISTS_ROUTE.$database, $header), true);
 return  $result['result'];
}

function tableExists($database, $table){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::TABLE_EXISTS_ROUTE.$database."/".$table, $header), true);
 return  $result['result'];
}

function columnExists($database, $table, $column){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::COLUMN_EXISTS_ROUTE.$database."/".$table."/".$column, $header), true);
 return  $result['result'];
}

function supportedFeatures($feature){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::SUPPORT_FEATURES_ROUTE.$feature, $header), true);
 return  $result['result'];
}

function getDatabaseInfo(){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::GET_DATABASE_INFO_ROUTE, $header), true);
 return  $result['result'];
}

function getDatabaseDriverInfo(){
 $header = array('Authorization:bearer '. $this->getToken());
 $result = json_decode($this->curlRequest->getRequest($this->baseUrl.self::GET_DATABASE_DRIVER_INFO_ROUTE, $header), true);
 return  $result['result'];
}
}

?>