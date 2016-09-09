<?php

 /**
  * @file: neo4jNode.php
  *
  * @created: 12/2/2013
  */
  
   use Everyman\Neo4j\Client,
	    Everyman\Neo4j\Transport,
	    Everyman\Neo4j\Node,
	    Everyman\Neo4j\Index,
	    Everyman\Neo4j\Relationship,
	    Everyman\Neo4j\Cypher,
  	    Everyman\Neo4j\Execption;
		
	  
 
	  
	  
 class Neo4j {
 	
	private $client;
	private $host;
	private $port;
	private $logger;
	
	
	function __construct($host = 'localhost', $port = 7474){
	    $this->host = $host;
	    $this->port = $port;
	    
	    //connect to neo4j server
	    $this->connect();
    }
     
     
   /**
    * connect($host, $port)
    * Connect to neo4j server.
    */
   private function connect(){
	    try{
	        $this->client = new Client($this->host, $this->port);
	        if(!$this->isLive()){
	            $this->client = NULL;
	    	}
	    }catch(Exception $e){
	    	$this->log($e->getMessage());
	        $this->client = null;
	    }
   }
    
    
   /**
    * Checks wehter Neo4j server is live or not.
    */ 
   public function isLive(){
       $status = file_get_contents("http://". $this->host . ":" . $this->port ."/?_=".time());
       
       if($status != FALSE && $status != NULL && $status != ""){
         return TRUE;
       }
         
       return FALSE;
   }
   
   
   /**
    * createNode(Neo4jNode $node)
    */
   public function createNode(Neo4jNode $node) {
   	
		if(!$node->isValid()){
			$this->log("Invalide node");
			return FALSE;
		}
   		
		$pk = $node->getPK();
		$pkv = $node->getPKV();
		$index = $node->getIndex();
		$properties = $node->getProperties();
		$labels = $node->getLabels();
		
		#find node in index
		$_node = $this->findNodeByPK($index, $pk, $pkv);
		
		if($_node){
            $_node->setProperties($properties)->save();
			
			$_labels = $this->hasLabels($labels);
			
			if($_labels){
				$labels = $_node->addLabels($_labels);
			}
            return $_node;
        }
		
		try{
			$_node = new Node($this->client);
            $_node->setProperties($properties)->save();
            
            //add to nodeIndex;
            $this->indexNode($_node, $index, $pk, $pkv);
			
			$_labels = $this->hasLabels($labels);
			
			if($_labels){
				$labels = $_node->addLabels($_labels);
			}
			
			return $_node;
		}catch(Exception $ex){
			$this->log($ex->getMessage());
			return NULL;
		}
		 
   }
   
   public function createRelationship(){
   	$args = func_get_args();
	if(count($args == 1) && $args[0] instanceof Neo4jRelationship){
		return $this->createRelationship1($args[0]);
	}else if(count($args) == 4){
		return $this->createRelationship2($args[0], $args[1], $args[2], $args[3]);	
	}
	
		$this->log("Invalid arguments passed, method createRelationship()!", Logger::ERR);
		
		return false;
   }
   
   /**
    * createRelationship(Neo4jRelationship $relationship)
    * Creates a relationship from source to target with givent properties
    * 
    */
  private function createRelationship1(Neo4jRelationship $relationship){
	
	if(!$relationship->isValid()){
		$this->log("Invalid relationship");
		return FALSE;
	}
	
	$source = $relationship->getSource();
	$target = $relationship->getTarget();
	$type = $relationship->getType();
	$properties = $relationship->getProperties();
	
	
	
	$source = $this->createNode($source);
	$target = $this->createNode($target);
	
	
	try {
				
			return $source->relateTo($target, $type)->setProperties($properties)->save();
	}catch(Exception $e){
		$this->log($e->getMessage());
		return NULL;
	}
		
	return NULL;
  }  
  
  private function createRelationship2(Node $source, Node $target, $type, $properties){
		
  	return $source->relateTo($target, $type)->setProperties($properties)->save();
  }
   
   	
	
   /**
    * findNodeByPK($index_name, $primary_key, $unique_value)
    * Finds a node in the index specified by its unique field.
    */
   public function findNodeByPK($index_name, $primary_key, $unique_value){
     $index = $this->getIndex($index_name);  
     if($index){
          try{
             return $index->findOne($primary_key, $unique_value);
          }catch(Exception $e){
           	 $this->log($e->getMessage());
             return null;
        }   
      }
       
	  $this->log("Invalide index: $index"); 
      return null;
   }
   
   
   /**
	* indexNode($index, $primary_key, $unique_name)
	* Index a Neo4j node into Neo4j index by the primary_key and unique_value
	*/
	private function indexNode($node, $index_name, $primary_key, $unique_value){
	    $index = $this->getIndex($index_name);  
	    if($index){
	        $index->add($node, $primary_key, $unique_value);
	        return true;
	    }
	    
	    return false;
	}
	
	
	
    /**
     * getIndex($name = null, $type = Index::TypeNode)
     * Return a Neo4j index of the type specfied.
     */
    private function getIndex($name = null, $type = Index::TypeNode){
        static $indicies = array();     
        
        if(!isset($name) || $name == ''){
            $this->log("Invalid index name $name!");
            return false;
        }
    
        if(isset($indicies[$name])){
            return $indicies[$name];
        }
    
        //load indices
        try{
            //load nodeIndex
            $index = new Index($this->client, $type, $name);
            $indicies[$name] = $index;
            return $index;
        }catch(Exception $e){
            $this->log($e->getMessage());
            return NULL;
        }
		
		return NULL;
   }
	
	
   /**
	* deleteIndex($index = NULL)
	* Deletes and index.
	*/
   public function deleteIndex($index_name = NULL){
   	 if(!isset($index_name) || empty($index_name)){
    	return FALSE;
     }
		
	 if($index = $this->getIndex($index_name)){
			
		try{
            return $index->delete();
        }catch(Exception $e){
            $this->log($e->getMessage());
            return FALSE;
        }
	  }
		
	  return FALSE;
    }	
   
   
  
   
   /**
     * cypherQuery($query, $params)
     * Runs a cypher query.
     */
    public function cypherQuery($query, $params=array()){
        try{
            $query = new Cypher\Query($this->client, $query, $params);
            $rs = $query->getResultSet();
            
            $output = array();
            foreach($rs as $row){
                $row_item = array();
                foreach($row as $key => $item) {
                    $row_item[$key] = $this->cypherResultFetchItems($item);
                }
                $output[] = $row_item;
            }
            return $output;
        }catch(Everyman\Neo4j\Exception $e){
            $this->log($e->getMessage(), Logger::ERR);
            return false;
        }
    }

    
    /**
     * cypherResultFetchItems($rowItem = null)
     * fetch a node, relationship or other objects properties.
     */
    private function cypherResultFetchItems($rowItem = null){
        //if its a node
        if($rowItem instanceof Node){
            return $rowItem->getProperties();
        }else if($rowItem instanceof Relationship){
            // $rel = array();
            // $rel['properties'] = $rowItem->getProperties();
            // $start = $rowItem->getStartNode();
            // $rel['source'] = $start->getProperties();
            // $end = $rowItem->getEndNode();
            // $rel['target'] = $end->getProperties();
//             
            // return $rel;
            return $rowItem;
        }

    
        return $rowItem;
    }
	
	/**
	 * @method addLabels(array(label1, label2, ...));
	 * @return object array of labels OR false 
	 */
	 private function hasLabels($labels){
	 	
	 	#if label array contains one or more labels then add them all to the node
			$_labels = array();
			
			if( count($labels) > 0 ){
				foreach($labels as $label){
					$_labels[] = $this->client->makeLabel($label);
				}
			}else{
				return false;
			}
			
			return $_labels;
			
	 }
	 
   public function setLogger(Logger $logger){
   		$this->logger = $logger;
   }
   
   private function log($log, $severity = Logger::ERR){
		if(isset($this->logger)){
			$this->logger($log, $severity);
		}else{
			print "\n". $log;
		}
	}
   private function relExists($source, $target){
   			$suid = $source->uid;
			$tuid = $target->uid;
   			$qry = "START s=node(*)  
						MATCH s-[r]->t WHERE s.uid='$suid' AND t.uid='$tuid'   
						set r.count = r.count+1      
						return r LIMIT 1";
								
   			$query = new Cypher\Query($this->client, $qry, array());
            $rs = $query->getResultSet();
			if(!empty($rs)){
				echo "<pre>".print_r($rs, true)."</pre>";
				
				return true;
			}else{
				return false;
			}
   }
 }