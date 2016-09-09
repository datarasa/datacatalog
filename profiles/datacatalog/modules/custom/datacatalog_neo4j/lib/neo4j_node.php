<?php

 /**
  * @file: neo3j_node.php
  * 
  * A Holder class for a node.
  * 
  * @creaetd: 12/2/2013
  */
  
  
  class Neo4jNode {
  	
	#primary key of the node
	private $pkey;
	
	#index of the node
	private $index;
	
	#node properties
	private $properties;
	
	#node labels
	private $labels;
	
	#constuctor
	public function __construct($pKey, $index, $properties, $labels = array()) {
		$this->pkey = $pKey;
		$this->index = $index;
		$this->properties = $properties;
		$this->labels = $labels;
    }
	
	function getPK(){
		return $this->pkey;
	}
	
	function getPKV(){
		return isset($this->properties[$this->pkey]) ? $this->properties[$this->pkey] : NULL;
	}
	
	function getIndex(){
		return $this->index;
	}
	
	function getProperties(){
		return $this->properties;
	}
	function getLabels(){
		return $this->labels;
	}
	
	function isValid(){
		return (isset($this->pkey) && isset($this->properties[$this->pkey]) && !empty($this->properties[$this->pkey]));
	}
	
  }
 