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
		
 class Neo4jTest {
 	
	private $client;
	private $host;
	private $port;
	private $logger;
	
	
	function __construct($host = 'localhost', $port = 7575){
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
   public function createNode($node) {
		
		$pk = $node[0];
		$index = $node[1];
		$properties = $node[2];
		
		$pkv = $properties[$pk];
	
		$labels = isset($node['labels'])? $node['labels'] : array();
		
		$indicies = array();
		$n = $this->findNodeByPK($index, $pk, $pkv);
		if($n){
		
			$n->setProperties($properties)->save();
			$this->add_labels($n, $labels);
			
			return $n;
			
		}else{
			try{
				$_node = new Node($this->client);
				$_node->setProperties($properties)->save();
				
				//add to nodeIndex;
				$type = Index::TypeNode;
				
				$indexs = new Index($this->client, $type, $index);
				$indicies[$index] = $indexs;
				
				$indexs->add($_node, $pk, $pkv);
				
				$this->add_labels($_node, $labels);
				
				return $_node;
			}catch(Exception $ex){
				return "Exception...";
			}
		}
		 
   }
   private function add_labels($_node, $labels){
		if( count($labels) > 0 ){
					
			$label_objects = array();
			foreach($labels as $label){
				$label_objects[] = $this->client->makeLabel($label);
			}
			
			$labels = $_node->addLabels($label_objects);
		}
   }
   
   public function createRelationship(){
	    $args = func_get_args();
		try{
			if( count($args) == 1){
				return $this->create_rel_and_nodes($args[0]);
			}else if(count($args) == 4){
				$source = $args[0];
				$target = $args[1];
				$type = $args[2];
				$properties = $args[3];
			
				return $source->relateTo($target, $type)->setProperties($properties)->save();
			
			}else{
				echo "Error: createRelationship expects parameter 1, or 4. ".count($args)." given in function call point";
			}
		}catch(Exception $e){
			return "CreateRelationship: ".$e->getMessage();
		}
   }
   public function create_rel_and_nodes($rel){
		$source = $this->createNode($rel['source']);
		$target = $this->createNode($rel['target']);
		
		return $source->relateTo($target, $rel['type'])->setProperties($rel['properties'])->save();
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
           	 //$this->log($e->getMessage());
             return null;
        }   
      }
       
	  //$this->log("Invalide index: $index"); 
      return null;
   }
   
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
            //$this->log($e->getMessage());
            return NULL;
        }
		
		return NULL;
   }
   
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
			$rel = array();
			//$rel['rel_prop'] = $rowItem->getProperties();
			//$rel['s_prop'] = $rowItem->getSource();
			//$rel[] = $rowItem->getTarget();*/
            return $rowItem->getProperties();
        }
		
		return $rowItem;
	}
	
}
