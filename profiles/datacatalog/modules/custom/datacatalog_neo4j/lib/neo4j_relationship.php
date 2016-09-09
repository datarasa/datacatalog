<?php

 /**
  * @file: node_relationship.php
  * 
  * 
  * @created: 12/2/2013
  */
  
  
  class Neo4jRelationship {
  	
	private $source;
	private $target;
	private $type;
	private $properties;
	
	
	public function __construct(Neo4jNode $source, Neo4jNode $target, $type, $properties) {
		$this->source = $source;
		$this->target = $target;
		$this->type = $type;
		$this->properties = $properties;
	}
	
	
	public function isValid(){
		return  ($this->source->isValid() && $this->target->isValid() &&  !empty($this->type));
	}
	
	
	public function getSource(){
		return $this->source;
	}
	
	public function getTarget(){
		return $this->target;
	}
	
	public function getType(){
		return $this->type;
	}
	
	
	public function getProperties(){
		return $this->properties;
	}
	
	
  }
 