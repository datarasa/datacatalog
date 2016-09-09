<?PHP
/*
csvDict class - generate data dictionary from csv data
version 1.0 5/15/2015

Copyright (c) 2015, Wagon Trader

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
class csvDict{
  public $convertToBool = true;
  public $includeData = true;
  public $bool;
  public $tableName;
  public $primColumn;
  public $isAuto;
  public $workDict;
  public $dataDict;
  public $dataRows;
  /* csvDict class initialization
	usage: 	csvDict(void);

	This method is automatically called when the class is initialized.
	It sets the bool property to define boolean fields
	
	returns: void
  */
  public function __construct(){
    $this->setBool();
  }
  
  /* method: processCSV
    usage:	processCSV($csvFile[, string tableName][, bool hasHeader=true]);
    params:	csvFile = csv file to read, include full path if needed
		tableName = manually specify table name, othewise csv file name will be used
		hasHeader = does the csv file have a header row? If true then these column headers
			will be used for the column names, otherwise a generic Columnx name will be generated.

    This is the main method to read the csv file and generate the data dictionary. The working data will
    be stored in workDict property, the data dictionary will be stored in the dataDict property. If the
    includeData property is true, the data will be stored in the dataRows property.

    returns: void
  */
  public function processCSV($csvFile,$tableName='',$hasHeader = true){
    if( empty($tableName) ){
	  list($this->tableName,$junk) = explode('.',$csvFile,2);
	}else{
	  $this->tableName = $tableName;
	}
    $count = 0;
	if (($handle = fopen($csvFile, 'r')) !== FALSE) {
	  while (($data = fgetcsv($handle, 0)) !== FALSE) {
	    $num = count($data);
        for ($x=0;$x<$num;$x++) {
	      $value = trim($data[$x]);
		  if( empty($hasHeader) AND $count == 0 ){
		    $this->initColumn('Column'.$x,$x);
		    continue;
		  }elseif( $count == 0 ){
		    $value = str_replace(' ','_',$value);
		    $this->initColumn($value,$x);
		    continue;
	  	  }
		  if( is_numeric($value) ){
		    if( ctype_digit($value) ){
		      $this->workDict[$x]['int']++;
		    }else{
			  $this->workDict[$x]['float']++;
			  list($int,$dec) = explode('.',$value);
			  $int = (int)$int;
			  if( empty($largestIntValue[$x]) OR $int > $largestIntValue[$x] ){
			    $largestIntValue[$x] = $int;
			    $this->workDict[$x]['liv'] = $int;
		      }
			  $decLength = strlen($dec);
			  if( empty($largestDecLength[$x]) OR $decLength > $largestDecLength[$x] ){
			    $largestDecLength[$x] = $decLength;
			    $this->workDict[$x]['ldl'] = $decLength;
		      }
		    }
		  }else{
		    if( $this->convertToBool AND array_key_exists($value,$this->bool) ){
		      $this->workDict[$x]['bool']++;
		    }elseif( strlen($value) < 256 ){
			  $this->workDict[$x]['varchar']++;
		    }else{
			  $this->workDict[$x]['text']++;
		    }
		  }
		  $this->workDict[$x]['rows'][$count-1]['value'] = stripslashes($value);
	    }
	    $count++;
	  }
	  fclose($handle);
    }
	for($x=0;$x<count($this->workDict);$x++){
  	  $this->dataDict[$x]['column'] = $this->workDict[$x]['column'];
	  if( !empty($this->workDict[$x]['text']) ){
	    $this->dataDict[$x]['type'] = 'TEXT';
		$this->dataDict[$x]['prop'] = '';
	  }elseif( !empty($this->workDict[$x]['varchar']) ){
		$this->dataDict[$x]['type'] = 'VARCHAR';
		$this->dataDict[$x]['prop'] = '255';
	  }elseif( !empty($this->workDict[$x]['float']) ){
		$this->dataDict[$x]['type'] = 'FLOAT';
		$precision = ( $this->workDict[$x]['ldl'] > 24 ) ? 24 : $this->workDict[$x]['ldl'];
		$length = strlen($this->workDict[$x]['liv'])+$precision+1;
		$length = ( $length < 10 ) ? 10 : $length;
		$this->dataDict[$x]['prop'] = $length.','.$this->workDict[$x]['ldl'];
	  }elseif( !empty($this->workDict[$x]['int']) ){
		$this->dataDict[$x]['type'] = 'INT';
		$this->dataDict[$x]['prop'] = '11';
	  }elseif( !empty($this->workDict[$x]['bool']) ){
		$this->dataDict[$x]['type'] = 'BOOL';
		$this->dataDict[$x]['prop'] = '1';
	  }else{
		$this->dataDict[$x]['type'] = 'undefined';
		$this->dataDict[$x]['prop'] = '';
	  }
	  if( !empty($this->includeData) ){
	    $this->dataRows[$x] = $this->workDict[$x]['rows'];
	  }
    }
  }
	
  /* method: setPrimColumn
  usage:	setPrimColumn(mixed primColumn);
  params:	primColumn = id or name of column to use for primary key 

  This method sets the primColumn property for the primary key. You can specify the column name or
  specify which column in the csv is the primary key. The first field is zero (0), second is one (1)...

  returns: void
  */
  public function setPrimColumn($primColumn){
	if( is_numeric($primColumn) ){
	  $this->primColumn = $this->dataDict[$primColumn]['column'];
	}else{
	  $this->primColumn = $primColumn;
	}
  }
  
  /* method: getDisplay
  usage:	getDisplay(void);

  This method returns the human readable data dictionary

  returns: formatted dictionary
  */
  public function getDisplay(){
    $return = '<div style="margin: 10px;"><strong>'.$this->tableName.' table</strong>';
	foreach( $this->dataDict as $data ){
	  if( $data['column'] == $this->primColumn ){
	    $keyProp = 'PRIMARY KEY';
		$keyProp = ( !empty($this->isAuto) ) ? 'AUTO_INCREMENT '.$keyProp : $keyProp;
	  }else{
		$keyProp = '';
	  }
	  $type = ( $data['type'] == 'BOOL' ) ? 'INT' : $data['type'];
	  $properties = ( empty($data['prop']) ) ? '' : '('.$data['prop'].')';
	  $return .= '<div style="margin-left:10px;margin-top:6px;"><strong>'.$data['column'].'</strong><br><div style="margin-left: 20px;">'.$type.' '.$properties.' '.$keyProp.'</div></div>';
	}
	$return .= '</div>';
	return $return;
  }
	
  /* method: getTableQuery
	usage:	getTableQuery(void);
	
	This method returns the SQL query to create the database table
	
	returns: query
  */
  public function getTableQuery(){
    $count = 0;
	$return = 'CREATE TABLE `'.$this->tableName.'` (';
	foreach( $this->dataDict as $data ){
	  if( $data['column'] == $this->primColumn ){
	    $keyProp = 'PRIMARY KEY';
		$keyProp = ( !empty($this->isAuto) ) ? 'AUTO_INCREMENT '.$keyProp : $keyProp;
	  }else{
		$keyProp = '';
	  }
	  $type = ( $data['type'] == 'BOOL' ) ? 'INT' : $data['type'];
	  $properties = ( empty($data['prop']) ) ? '' : '('.$data['prop'].')';
	  $return .= ( empty($count) ) ? '' : ',';
	  $return .= '`'.$data['column'].'` '.$type.' '.$properties.' '.$keyProp;
	  $count++;
    }
	return $return;
  }
	
  /* method: getInsertQuery
	usage:	getInsertQuery(int id);
	params:	id = data row id
	
	This method returns the SQL query to insert the specified row into the table.
	Note: The row id can be obtained as the key values in dataRows[0] property 
	
	returns: query
  */
  public function getInsertQuery($id){
    $count = 0;
	$return = 'INSERT INTO `'.$this->tableName.'` SET ';
	foreach( $this->dataRows as $key=>$data ){
	  $value = ( $this->dataDict[$key]['type'] == 'BOOL' ) ? $this->bool[$data[$id]['value']] : $data[$id]['value'];
	  $return .= ( empty($count) ) ? '' : ',';
	  $return .= '`'.$this->dataDict[$key]['column'].'`="'.$this->quoteSmart($value).'"';
	  $count++;
	}
	return $return;
  }
	
  /* method: quoteSmart
	usage:	quoteSmart(string value);
	params:	value = string to be quoted
	
	This method returns an escaped string for insertion into a database table
	Note: In a production environment where the data is actually being inserted into
		a table, this method should be updated to use real string escaping
	
	returns: query
  */
  public function quoteSmart($value){
    if( !is_numeric($value) ){
	  $value = addslashes($value);
	}
	return $value;
  }
	
  /* method: setBool
	usage:	setBool(void);
	
	This method sets the bool property. The key value pairs define the text representing a boolean value and the value
	
	returns: void
  */
  protected function setBool(){
    $this->bool = array(
	  'true'=>1,
	  'false'=>0,
	   'yes'=>1,
	    'no'=>0,
		'on'=>1,
		'off'=>0,
	);
  }
	
  protected function initColumn($column,$id){
    $this->workDict[$id]['column'] = $column;
	$this->workDict[$id]['int'] = 0;
	$this->workDict[$id]['float'] = 0;
	$this->workDict[$id]['bool'] = 0;
	$this->workDict[$id]['varchar'] = 0;
	$this->workDict[$id]['text'] = 0;
  }
	
}
?>
