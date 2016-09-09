<?php
include 'XMetaClient.php';

$authParams = array();
$authParams["db_host"] = "localhost"; 
$authParams["db_port"] =  3306;
$authParams["db_user"] = "root";
$authParams["db_pass"] = "devservzulu001";
$authParams["db_type"] = "mysql";
//$authParams["db"] = "dcatdev";
$xMetaClient = new XMetaClient("localhost", "8181");
try{
  $xMetaClient->authenticate( $authParams );
}catch(Exception $ex){

  echo "<pre>".print_r( $ex, true)."</pre>";
  exit;
}



//$availableRoutes = $xMetaClient->listAvailableRoutes();
$databases = $xMetaClient->showDataBases();
$tables = $xMetaClient->showTables("dcatdev");
$columns = $xMetaClient->showColumns("employee", "admins");
$showColumnWithType = $xMetaClient->showColumnWithType("employee", "admins");
$getColumnType = $xMetaClient->getColumnType("employee", "admins", "id");
$getColumnLength = $xMetaClient->getColumnLength("employee", "admins", "id");
$getColumnAtPos = $xMetaClient->getColumnAtPos("employee", "admins", 1);
$getPrimaryKey = $xMetaClient->getPrimaryKey("employee", "admins");
$getForeignKey = $xMetaClient->getForeignKey("employee", "booking_steps");
$getForeignKeyRefTables = $xMetaClient->getForeignKeyRefTables("employee", "booking_steps");
$getIndexes = $xMetaClient->getIndexes("employee", "admins");
$getAllIndexesAndRefTables = $xMetaClient->getAllIndexesAndRefTables("employee", "admins");
$databaseExists = $xMetaClient->databaseExists("employee");
$tableExists = $xMetaClient->tableExists("employee", "admins");
$columnExists = $xMetaClient->columnExists("employee", "admins", "id");
$supportedFeatures = $xMetaClient->supportedFeatures("outer_join");// group_by, outer_join, union, union_all
$getDatabaseInfo = $xMetaClient->getDatabaseInfo();
$getDatabaseDriverInfo = $xMetaClient->getDatabaseDriverInfo();

echo "<pre>".print_r($databases, true)."</pre>";
?>
