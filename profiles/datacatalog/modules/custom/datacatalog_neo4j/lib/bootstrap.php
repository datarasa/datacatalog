<?php

 /**
  * @file: bootstrap.php
  * 
  * @created: 12/2/2013
  */
  
/*
  spl_autoload_register(function ($className) {
  $libPath = dirname(__FILE__).DIRECTORY_SEPARATOR;
  $classFile = str_replace('\\',DIRECTORY_SEPARATOR,$className).'.php';
  $classPath = $libPath.$classFile;
  echo $classPath;
  if (file_exists($classPath)) {
      require($classPath);
  }
});
*/  
  require("neo4jphp.phar");
  //require_once 'neo4j_node.php';
  //require_once 'neo4j_relationship.php';
  //require_once 'neo4j.php';
  require_once 'neo4jtest.php';
  require_once 'logger.php';
  
  
  #set time limit
  set_time_limit(0);
  
  
  
  
  
  
 