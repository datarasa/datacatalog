<?php
set_time_limit ( 0 ); 
define('DRUPAL_ROOT', realpath("../"));
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
require_once DRUPAL_ROOT . '/ajax/includes/bootStrap.php';
if ( isset($_POST['query_id']) && !empty($_POST['query_id']) ) {
  $query_id_Parts = explode("_", $_POST['query_id']);
  $query_id = $query_id_Parts[0];
  $posted_time = $query_id_Parts[1]; 
  $search_query = db_select('shell_search_filters', 'ssf')
  ->fields('ssf', array('search_filters'))
  ->condition('id', array($query_id),'=')
  ->condition('posted_time', array($posted_time),'=')
  ->orderBy('posted_time', 'DESC')
  ->range(0,1)
  ->execute(); 
  if ( $search_query->rowCount() < 1) {
  	$alerts['type'] = 'error';
  	$alerts['message'] = 'Wrong parameters passed';
  	echo json_encode($alerts);
  	exit;
  }
  $row = $search_query->fetchAssoc();
  $filters = unserialize(base64_decode($row['search_filters']));
  $navysbir = (isset($filters['navysbir']) && !empty($filters['navysbir'])) ? "true": "false";
  $dod = (isset($filters['dod']) && !empty($filters['dod'])) ? "true": "false";
  $doe = (isset($filters['doe']) && !empty($filters['doe'])) ? "true": "false";
  $nasa = (isset($filters['nasa']) && !empty($filters['nasa'])) ? "true": "false";
  $docs = (isset($filters['document']) && !empty($filters['document'])) ? "true": "false";
  // combinedFilters query
  $queryToSearch = $filters['Query']; 
  if ( $navysbir == "true" || $dod == "true" || $doe == "true" || $nasa =="true" || $docs == "true") {   
    $resultData = "";
    $htmlRow = "";
    $row_id = 0;
    if($navysbir == "true" || $dod == "true" || $doe == "true" || $nasa =="true"){
      function __autoload_elastica ($class) {
        $path = str_replace('\\', '/', $class);
        if (file_exists(dirname(__FILE__) ."/" . $path . '.php')) {
          require_once(dirname(__FILE__) ."/" . $path . '.php');
        }
      }
      spl_autoload_register('__autoload_elastica');
      require_once DRUPAL_ROOT . '/ajax/includes/es-ip-conf.php';
      if ( $navysbir == "true"){
        // advanced options
        $SBIR_TYPE = 'NAVY';
        $PHASE = (isset($filters['PHASE']) && !empty($filters['PHASE'])) ? $filters['PHASE']: "";
        $FIRM_DUNS = (isset($filters['FIRM_DUNS']) && !empty($filters['FIRM_DUNS'])) ? $filters['FIRM_DUNS']: "";
        $FIRM_NAME = (isset($filters['FIRM_NAME']) && !empty($filters['FIRM_NAME'])) ? $filters['FIRM_NAME']: "";
        $FIRM_ZIP = (isset($filters['FIRM_ZIP']) && !empty($filters['FIRM_ZIP'])) ? $filters['FIRM_ZIP']: "";
        $FIRM_STATE = (isset($filters['FIRM_STATE']) && !empty($filters['FIRM_STATE'])) ? $filters['FIRM_STATE']: "";
        $TOPIC_NUMBER = (isset($filters['TOPIC_NUMBER']) && !empty($filters['TOPIC_NUMBER'])) ? $filters['TOPIC_NUMBER']: "";
        $TPOC = (isset($filters['TPOC']) && !empty($filters['TPOC'])) ? $filters['TPOC']: "";
        $AWARD_FISCAL_YEAR = ( isset($filters['AWARD_FISCAL_YEAR']) && !empty($filters['AWARD_FISCAL_YEAR']) ) ? $filters['AWARD_FISCAL_YEAR']: "";
        $CONTRACT_NUMBER = (isset($filters['CONTRACT_NUMBER']) && !empty($filters['CONTRACT_NUMBER'])) ? $filters['CONTRACT_NUMBER']: "";
        $KEYWORDS = (isset($filters['KEYWORDS']) && !empty($filters['KEYWORDS'])) ? $filters['KEYWORDS']: "";
        $MAX_RESULTS = (isset($filters['maxResults']) && !empty($filters['maxResults'])) ? $filters['maxResults']: 10; 
        $mUseAwardDate = (isset($filters['mUseAwardDate']) && !empty($filters['mUseAwardDate'])) ? $filters['mUseAwardDate']: "";
        $start_date = "";
        $end_date = "";
        if ( $mUseAwardDate )  {	
      	  $start_date = !empty($filters['start-date']) ? strtotime($filters['start-date']) : '';
      	  $end_date = !empty($filters['end-date']) ? strtotime($filters['end-date']) : '';
        }
      
        $sort = (isset($filters['sort']) && !empty($filters['sort'])) ? $filters['sort']: "date";
        $start = (isset($filters['start']) && !empty($filters['start'])) ? $filters['start']: "1";
        
        if($sort == 'date'){
          $sOrder = "start_date";
          $sOrderAD ="desc";
        }else if($sort == 'title'){
          $sOrder = "titleSort";
          $sOrderAD ="asc";
        }
        if ( isset($_POST['doctype']) && !empty($_POST['doctype']) && $_POST['doctype'] != "All"  ) {
		  $DOCUMENT_TYPE = $_POST['doctype']; 
		}else{
		  $DOCUMENT_TYPE = ""; 
		}
        $queryToSearch = strtolower($queryToSearch);
        if ($queryToSearch != "" || $PHASE != "" || $FIRM_DUNS != "" || $FIRM_NAME != "" || $FIRM_ZIP != "" 
            || $FIRM_STATE != "" || $TOPIC_NUMBER != "" || $TPOC != "" || $AWARD_FISCAL_YEAR != "" 
            || $CONTRACT_NUMBER != "" || $KEYWORDS != "" || $mUseAwardDate || $DOCUMENT_TYPE != ""){
      	  $mainQuery = new Elastica\Query\Bool();
          /**** Global search Query ****/
      	  if($queryToSearch != ""){
            $globalQuery = new Elastica\Query\QueryString();
            $globalQuery->setDefaultOperator('AND');
            $globalQuery->setFields(array('porposaltitle','description'));
            $globalQuery->setQuery($queryToSearch);
            $mainQuery ->addShould($globalQuery);
      	  }
           /******* Start Date filter *******/
          if ( $start_date != ""){	
        	$rangeStartDateParam = array();
        	$rangeStartDateParam["from"] = $start_date;
        	$dateYearRange = new Elastica\Query\Range();
        	$dateYearRange->addField('start_date',$rangeStartDateParam);
        	$mainQuery->addMust($dateYearRange);
          }
       	   /******* End Date range filter *******/
          if ( $end_date != ""){
        	$rangeEndDateParam = array();
        	$rangeEndDateParam["to"] = $end_date;
        	$dateEndRange = new Elastica\Query\Range();
            $dateEndRange->addField('end_date',$rangeEndDateParam);
        	$mainQuery->addMust($dateEndRange);
          }
          /**** Phase search Query ****/	
       	  if($PHASE != ""){
        	$phaseQuery = new Elastica\Query\Term();
        	$phaseQuery->setTerm('phase', $PHASE);
        	$mainQuery ->addMust($phaseQuery);
          }
          /**** Topic Number search Query ****/	
          if($TOPIC_NUMBER != ""){
        	$topicQuery = new Elastica\Query\Term();
        	$topicQuery->setTerm('topic_number', $TOPIC_NUMBER);
        	$mainQuery ->addMust($topicQuery);
          }
          /**** Firm Duns search Query ****/		
       	  if($FIRM_DUNS != ""){
        	$dunsQuery = new Elastica\Query\Term();
        	$dunsQuery->setTerm('duns', $FIRM_DUNS);
        	$mainQuery ->addMust($dunsQuery);
          }
          /**** Firm Name search Query ****/	
      	  if($FIRM_NAME != ""){
            $firmQuery = new Elastica\Query\QueryString();
            $firmQuery->setDefaultOperator('AND');
            $firmQuery->setFields(array('firmName'));
            $firmQuery->setQuery($FIRM_NAME);
            $mainQuery ->addMust($firmQuery);
      	  }
          /**** Firm Zipcode search Query ****/		
          if($FIRM_ZIP != ""){
            $zipQuery = new Elastica\Query\Term();
        	$zipQuery->setTerm('zipcode', $FIRM_ZIP);
        	$mainQuery ->addMust($zipQuery);
          }
          /**** Firm State Code search Query ****/		
          if($FIRM_STATE != ""){
        	$stateQuery = new Elastica\Query\Term();
        	$stateQuery->setTerm('statecode', $FIRM_STATE);
        	$mainQuery ->addMust($stateQuery);
          }
       	  /**** Contract Number search Query ****/
          if($CONTRACT_NUMBER != ""){
        	$contractQuery = new Elastica\Query\Term();
        	$contractQuery->setTerm('contract_number', $CONTRACT_NUMBER);
        	$mainQuery ->addMust($contractQuery);
          }
          if($DOCUMENT_TYPE != ""){
	        $docQuery = new Elastica\Query\Term();
	        $docQuery->setTerm('document_type', $DOCUMENT_TYPE);
	        $mainQuery ->addMust($docQuery);
	      }
          /**** Firm Contract Number search Query ****/
          $sbirTypeQuery = new Elastica\Query\Term();
          $sbirTypeQuery->setTerm('sbir_type', $SBIR_TYPE);
          $mainQuery ->addMust($sbirTypeQuery);	
      	  $mainQuery->setMinimumNumberShouldMatch(1);
        }else{
          $mainQuery = new Elastica\Query\Term();
          $mainQuery->setTerm('sbir_type', $SBIR_TYPE);
        }
        $query = new Elastica\Query();
      	$query->setSort(array($sOrder => array('order' => $sOrderAD)));
        $query->setSize($MAX_RESULTS);
        $query->setFrom(0);
        $query->setQuery($mainQuery);
        /*** New string location field search ***/
        $resultSet = $elasticaType->search($query);
        $size =  $resultSet->getTotalHits();
        $resultsNS = $resultSet->getResults();	
        if(!empty($resultsNS)){
          foreach($resultsNS as $result){
            $result = $result->getData();
            $listingTitle = $result['porposaltitle'];
            $listingURL = '/sbirdetail/'.$result['unique_id'];
            $summary = strip_tags($result['description']);
            $summary1 = str_replace('ABSTRACT:', '', $summary);
            $summary = trim($summary1);
            $summaryAll = $summary;
            $pos = strpos($summary, ' ', 500);
            if ($pos !== false) {
              $summary = substr($summary, 0, $pos);
              $summary .= '...';
            }
            $topicNumber = $result['topic_number'];
            $firmName = $result['firmName'];
            $phase = $result['phase'];
            $award_start_date = isset($result['start_date']) ? @date('m/d/Y',$result['start_date']) : '';
            $award_end_date = isset($result['start_date']) ? @date('m/d/Y',$result['end_date']) : '';
            $TRL = $result['trl'];
            $source = $result['sbir_type'];
            $year = isset($result['year']) ? $result['year'] : '';
            $resultData[$row_id] = array(
              "listingURL" => $listingURL,
              "listingTitle" => $listingTitle,
              "summary" => $summary,
              "summaryAll" => $summaryAll,
              "topicNumber" => $topicNumber,
              "firmName" => $firmName,
              "source" => $source,
              "phase" => $phase,
              "award_start_date" => $award_start_date,
              "award_end_date" => $award_end_date,
              "TRL" => $TRL,
              "Year" => $year,
              "type" => 'navy'
            );
            $row_id ++;
          }
        }      
      } //End Navy Results
      /*****DOD Resutls*****/
      if ( $dod == "true" ) {
        // advanced options
        $SBIR_TYPE = 'DOD';
        $PHASE = (isset($filters['PHASE_DOD']) && !empty($filters['PHASE_DOD'])) ? $filters['PHASE_DOD']: "";
        $FIRM_DUNS = (isset($filters['FIRM_DUNS_DOD']) && !empty($filters['FIRM_DUNS_DOD'])) ? $filters['FIRM_DUNS_DOD']: "";
        $FIRM_NAME = (isset($filters['FIRM_NAME_DOD']) && !empty($filters['FIRM_NAME_DOD'])) ? $filters['FIRM_NAME_DOD']: "";
        $FIRM_ZIP = (isset($filters['FIRM_ZIP_DOD']) && !empty($filters['FIRM_ZIP_DOD'])) ? $filters['FIRM_ZIP_DOD']: "";
        $FIRM_STATE = (isset($filters['FIRM_STATE_DOD']) && !empty($filters['FIRM_STATE_DOD'])) ? $filters['FIRM_STATE_DOD']: "";
        $TOPIC_NUMBER = (isset($filters['TOPIC_NUMBER_DOD']) && !empty($filters['TOPIC_NUMBER_DOD'])) ? $filters['TOPIC_NUMBER_DOD']: "";
        $CONTRACT_NUMBER = (isset($filters['CONTRACT_NUMBER_DOD']) && !empty($filters['CONTRACT_NUMBER_DOD'])) ? $filters['CONTRACT_NUMBER_DOD']: "";
        $MAX_RESULTS = (isset($filters['maxResults_DOD']) && !empty($filters['maxResults_DOD'])) ? $filters['maxResults_DOD']: 10;
        $start_date = !empty($filters['dodfrom']) ? $filters['dodfrom'] : '';
        $end_date = !empty($filters['dodto']) ? $filters['dodto'] : '';
        $sort = (isset($filters['sort_DOD']) && !empty($filters['sort_DOD'])) ? $filters['sort_DOD']: "date";
        $start = (isset($filters['start']) && !empty($filters['start'])) ? $filters['start']: "1";
        if($sort == 'date'){
          $sOrder = "year";
          $sOrderAD ="desc";
        }else if($sort == 'title'){
          $sOrder = "titleSort";
          $sOrderAD ="asc";
        }
        $queryToSearch = strtolower($queryToSearch);
        if ($queryToSearch != "" || $PHASE != "" || $FIRM_DUNS != "" || $FIRM_NAME != "" || $FIRM_ZIP != ""
            || $FIRM_STATE != "" || $TOPIC_NUMBER != "" || $CONTRACT_NUMBER != "" || $start_date != "" || $end_date != "" ){
          $mainQuery = new Elastica\Query\Bool();
          /**** Global search Query ****/
          if($queryToSearch != ""){
            $globalQuery = new Elastica\Query\QueryString();
            $globalQuery->setDefaultOperator('AND');
            $globalQuery->setFields(array('porposaltitle','description'));
            $globalQuery->setQuery($queryToSearch);
            $mainQuery ->addShould($globalQuery);
          }
          /******* Year Range filter *******/
          if ( $start_date != "" || $end_date != ""){
            $rangeYearParam = array();
            if($start_date != ""){
              $rangeYearParam["from"] = $start_date;
            }
            if($end_date != ""){
              $rangeYearParam["to"] = $end_date;
            }
            $dateYearRange = new Elastica\Query\Range();
            $dateYearRange->addField('year',$rangeYearParam);
            $mainQuery->addMust($dateYearRange);
          }
          /**** Phase search Query ****/
          if($PHASE != ""){
            $phaseQuery = new Elastica\Query\Term();
            $phaseQuery->setTerm('phase', $PHASE);
            $mainQuery ->addMust($phaseQuery);
          }
          /**** Topic Number search Query ****/
          if($TOPIC_NUMBER != ""){
            $topicQuery = new Elastica\Query\Term();
            $topicQuery->setTerm('topic_number', $TOPIC_NUMBER);
            $mainQuery ->addMust($topicQuery);
          }
          /**** Firm Duns search Query ****/
          if($FIRM_DUNS != ""){
            $dunsQuery = new Elastica\Query\Term();
            $dunsQuery->setTerm('duns', $FIRM_DUNS);
            $mainQuery ->addMust($dunsQuery);
          }
          /**** Firm Name search Query ****/
          if($FIRM_NAME != ""){
            $firmQuery = new Elastica\Query\QueryString();
            $firmQuery->setDefaultOperator('AND');
            $firmQuery->setFields(array('firmName'));
            $firmQuery->setQuery($FIRM_NAME);
            $mainQuery ->addMust($firmQuery);
          }
          /**** Firm Zipcode search Query ****/
          if($FIRM_ZIP != ""){
            $zipQuery = new Elastica\Query\Term();
            $zipQuery->setTerm('zipcode', $FIRM_ZIP);
            $mainQuery ->addMust($zipQuery);
          }
          /**** Firm State Code search Query ****/
          if($FIRM_STATE != ""){
            $stateQuery = new Elastica\Query\Term();
            $stateQuery->setTerm('statecode', $FIRM_STATE);
            $mainQuery ->addMust($stateQuery);
          }
          /**** Contract Number search Query ****/
          if($CONTRACT_NUMBER != ""){
            $contractQuery = new Elastica\Query\Term();
            $contractQuery->setTerm('contract_number', $CONTRACT_NUMBER);
            $mainQuery ->addMust($contractQuery);
          }
          $sbirTypeQuery = new Elastica\Query\Term();
          $sbirTypeQuery->setTerm('sbir_type', $SBIR_TYPE);
          $mainQuery ->addMust($sbirTypeQuery);
          $mainQuery->setMinimumNumberShouldMatch(1);
        }
        else{
          $mainQuery = new Elastica\Query\Term();
          $mainQuery->setTerm('sbir_type', $SBIR_TYPE);
        }
        $query = new Elastica\Query();
        $query->setSort(array($sOrder => array('order' => $sOrderAD)));
        $query->setSize($MAX_RESULTS);
        $query->setFrom(0);
        $query->setQuery($mainQuery);
        $resultSet = $elasticaType->search($query);
        $size =  $resultSet->getTotalHits();
        $resultsDOD = $resultSet->getResults();
        if(!empty($resultsDOD)){
          foreach($resultsDOD as $resultDOD){
            $resultDOD = $resultDOD->getData();
            $listingTitle = $resultDOD['porposaltitle'];
            $listingURL = '/sbirdetail/'.$resultDOD['unique_id'];
            $summary = strip_tags($resultDOD['description']);
            $summary1 = str_replace('Abstract', '', $summary);
            $summary1 = str_replace('ABSTRACT:', '', $summary1);      
            $summary = trim($summary1);
            $summaryAll = $summary;
            $pos = strpos($summary, ' ', 500);
            if ($pos !== false) {
              $summary = substr($summary, 0, $pos);
              $summary .= '...';
            }
            $topicNumber = isset($resultDOD['topic_number']) ? $resultDOD['topic_number'] : '';
            $firmName = isset($resultDOD['firmName']) ? $resultDOD['firmName'] : '';
            $phase = isset($resultDOD['phase']) ? $resultDOD['phase'] : '';
            $award_start_date = isset($resultDOD['start_date']) ? @date('m/d/Y',$resultDOD['start_date']) : '';
            $award_end_date = isset($resultDOD['start_date']) ? @date('m/d/Y',$resultDOD['end_date']) : '';
            $TRL = isset($resultDOD['trl']) ? $resultDOD['trl'] : '';
            $source = $resultDOD['sbir_type'];
            $year = isset($resultDOD['year']) ? $resultDOD['year'] : '';
            $resultData[$row_id] = array(
              "listingURL" => $listingURL,
              "listingTitle" => $listingTitle,
              "summary" => $summary,
              "summaryAll" => $summaryAll,
              "topicNumber" => $topicNumber,
              "firmName" => $firmName,
              "source" => $source,
              "phase" => $phase,
              "award_start_date" => $award_start_date,
              "award_end_date" => $award_end_date,
              "TRL" => $TRL,
              "Year" => $year,
              "type" => 'dod'
            );
            $row_id ++;
          }
        }        
      }//End DOD Results
      /*****DOE Resutls*****/
      if ( $doe == "true" ) {   
        // advanced options
        $SBIR_TYPE = 'DOE';
        $PHASE = (isset($filters['PHASE_DOE']) && !empty($filters['PHASE_DOE'])) ? $filters['PHASE_DOE']: "";
        $FIRM_DUNS = (isset($filters['FIRM_DUNS_DOE']) && !empty($filters['FIRM_DUNS_DOE'])) ? $filters['FIRM_DUNS_DOE']: "";
        $FIRM_NAME = (isset($filters['FIRM_NAME_DOE']) && !empty($filters['FIRM_NAME_DOE'])) ? $filters['FIRM_NAME_DOE']: "";
        $FIRM_ZIP = (isset($filters['FIRM_ZIP_DOE']) && !empty($filters['FIRM_ZIP_DOE'])) ? $filters['FIRM_ZIP_DOE']: "";
        $FIRM_STATE = (isset($filters['FIRM_STATE_DOE']) && !empty($filters['FIRM_STATE_DOE'])) ? $filters['FIRM_STATE_DOE']: "";
        $TOPIC_NUMBER = (isset($filters['TOPIC_NUMBER_DOE']) && !empty($filters['TOPIC_NUMBER_DOE'])) ? $filters['TOPIC_NUMBER_DOE']: "";
        $CONTRACT_NUMBER = (isset($filters['CONTRACT_NUMBER_DOE']) && !empty($filters['CONTRACT_NUMBER_DOE'])) ? $filters['CONTRACT_NUMBER_DOE']: "";
        $MAX_RESULTS = (isset($filters['maxResults_DOE']) && !empty($filters['maxResults_DOE'])) ? $filters['maxResults_DOE']: 10;
        $start_date = !empty($filters['doefrom']) ? $filters['doefrom'] : '';
        $end_date = !empty($filters['doeto']) ? $filters['doeto'] : '';
        $sort = (isset($filters['sort_DOE']) && !empty($filters['sort_DOE'])) ? $filters['sort_DOE']: "date";
        $start = (isset($filters['start']) && !empty($filters['start'])) ? $filters['start']: "1";
        if($sort == 'date'){
          $sOrder = "year";
          $sOrderAD ="desc";
        }else if($sort == 'title'){
          $sOrder = "titleSort";
          $sOrderAD ="asc";
        }
        $queryToSearch = strtolower($queryToSearch);
        if ($queryToSearch != "" || $PHASE != "" || $FIRM_DUNS != "" || $FIRM_NAME != "" || $FIRM_ZIP != ""
            || $FIRM_STATE != "" || $TOPIC_NUMBER != "" || $CONTRACT_NUMBER != "" || $start_date != "" || $end_date != "" ){
          $mainQuery = new Elastica\Query\Bool();
          /**** Global search Query ****/
          if($queryToSearch != ""){
            $globalQuery = new Elastica\Query\QueryString();
            $globalQuery->setDefaultOperator('AND');
            $globalQuery->setFields(array('porposaltitle','description'));
            $globalQuery->setQuery($queryToSearch);
            $mainQuery ->addShould($globalQuery);
          }
          /******* Year Range filter *******/
          if ( $start_date != "" || $end_date != ""){
            $rangeYearParam = array();
            if($start_date != ""){
              $rangeYearParam["from"] = $start_date;
            }
            if($end_date != ""){
              $rangeYearParam["to"] = $end_date;
            }
            $dateYearRange = new Elastica\Query\Range();
            $dateYearRange->addField('year',$rangeYearParam);
            $mainQuery->addMust($dateYearRange);
          }
          /**** Phase search Query ****/
          if($PHASE != ""){
            $phaseQuery = new Elastica\Query\Term();
            $phaseQuery->setTerm('phase', $PHASE);
            $mainQuery ->addMust($phaseQuery);
          }
          /**** Topic Number search Query ****/
          if($TOPIC_NUMBER != ""){
            $topicQuery = new Elastica\Query\Term();
            $topicQuery->setTerm('topic_number', $TOPIC_NUMBER);
            $mainQuery ->addMust($topicQuery);
          }
          /**** Firm Duns search Query ****/
          if($FIRM_DUNS != ""){
            $dunsQuery = new Elastica\Query\Term();
            $dunsQuery->setTerm('duns', $FIRM_DUNS);
            $mainQuery ->addMust($dunsQuery);
          }
          /**** Firm Name search Query ****/
          if($FIRM_NAME != ""){
            $firmQuery = new Elastica\Query\QueryString();
            $firmQuery->setDefaultOperator('AND');
            $firmQuery->setFields(array('firmName'));
            $firmQuery->setQuery($FIRM_NAME);
            $mainQuery ->addMust($firmQuery);
          }
          /**** Firm Zipcode search Query ****/
          if($FIRM_ZIP != ""){
            $zipQuery = new Elastica\Query\Term();
            $zipQuery->setTerm('zipcode', $FIRM_ZIP);
            $mainQuery ->addMust($zipQuery);
          }
          /**** Firm State Code search Query ****/
          if($FIRM_STATE != ""){
            $stateQuery = new Elastica\Query\Term();
            $stateQuery->setTerm('statecode', $FIRM_STATE);
            $mainQuery ->addMust($stateQuery);
          }
          /**** Contract Number search Query ****/
          if($CONTRACT_NUMBER != ""){
            $contractQuery = new Elastica\Query\Term();
            $contractQuery->setTerm('contract_number', $CONTRACT_NUMBER);
            $mainQuery ->addMust($contractQuery);
          }
          $sbirTypeQuery = new Elastica\Query\Term();
          $sbirTypeQuery->setTerm('sbir_type', $SBIR_TYPE);
          $mainQuery ->addMust($sbirTypeQuery);
          $mainQuery->setMinimumNumberShouldMatch(1);
        }
        else{
          $mainQuery = new Elastica\Query\Term();
          $mainQuery->setTerm('sbir_type', $SBIR_TYPE);
        }
        $query = new Elastica\Query();
        $query->setSort(array($sOrder => array('order' => $sOrderAD)));
        $query->setSize($MAX_RESULTS);
        $query->setFrom(0);
        // $query->setFields($aColumns);
        $query->setQuery($mainQuery);
        $resultSet = $elasticaType->search($query);
        $size =  $resultSet->getTotalHits();
        $resultsDOE = $resultSet->getResults();        
        if(!empty($resultsDOE)){
          foreach($resultsDOE as $resultDOE){
            $resultDOE = $resultDOE->getData();
            $listingTitle = $resultDOE['porposaltitle'];
            $listingURL = '/sbirdetail/'.$resultDOE['unique_id'];
            $summary = strip_tags($resultDOE['description']);
            $summary1 = str_replace('Abstract', '', $summary);
            $summary1 = str_replace('ABSTRACT:', '', $summary1);
            $summary = trim($summary1);
            $summaryAll = $summary;
            $pos = strpos($summary, ' ', 500);
            if ($pos !== false) {
              $summary = substr($summary, 0, $pos);
              $summary .= '...';
            }
            $topicNumber = isset($resultDOE['topic_number']) ? $resultDOE['topic_number'] : '';
            $firmName = isset($resultDOE['firmName']) ? $resultDOE['firmName'] : '';
            $phase = isset($resultDOE['phase']) ? $resultDOE['phase'] : '';
            $award_start_date = isset($resultDOE['start_date']) ? @date('m/d/Y',$resultDOE['start_date']) : '';
            $award_end_date = isset($resultDOE['start_date']) ? @date('m/d/Y',$resultDOE['end_date']) : '';
            $TRL = isset($resultDOE['trl']) ? $resultDOE['trl'] : '';
            $source = $resultDOE['sbir_type'];
            $year = isset($resultDOE['year']) ? $resultDOE['year'] : '';
             
            $resultData[$row_id] = array(
              "listingURL" => $listingURL,
              "listingTitle" => $listingTitle,
              "summary" => $summary,
              "summaryAll" => $summaryAll,
              "topicNumber" => $topicNumber,
              "firmName" => $firmName,
              "source" => $source,
              "phase" => $phase,
              "award_start_date" => $award_start_date,
              "award_end_date" => $award_end_date,
              "TRL" => $TRL,
              "Year" => $year,
              "type" => 'doe'
            );
             
            $row_id ++;
          }
        }
        
      }//End DOE Results
      /*****NASA Resutls*****/
      if ( $nasa == "true" ) {      
        // advanced options
        $SBIR_TYPE = 'NASA';
        $FIRM_NAME = (isset($filters['FIRM_NAME_NASA']) && !empty($filters['FIRM_NAME_NASA'])) ? $filters['FIRM_NAME_NASA']: "";
        $FIRM_STATE = (isset($filters['FIRM_STATE_NASA']) && !empty($filters['FIRM_STATE_NASA'])) ? $filters['FIRM_STATE_NASA']: "";
        $MAX_RESULTS = (isset($filters['maxResults_NASA']) && !empty($filters['maxResults_NASA'])) ? $filters['maxResults_NASA']: 10;
        $start_date = !empty($filters['nasafrom']) ? $filters['nasafrom'] : '';
        $end_date = !empty($filters['nasato']) ? $filters['nasato'] : '';
        $sort = (isset($filters['sort_NASA']) && !empty($filters['sort_NASA'])) ? $filters['sort_NASA']: "date";
        $start = (isset($filters['start']) && !empty($filters['start'])) ? $filters['start']: "1";
        if($sort == 'date'){
          $sOrder = "year";
          $sOrderAD ="desc";
        }else if($sort == 'title'){
          $sOrder = "titleSort";
          $sOrderAD ="asc";
        }
        $queryToSearch = strtolower($queryToSearch);
        if ($queryToSearch != "" || $FIRM_NAME != "" || $FIRM_STATE != ""
            || $start_date != "" || $end_date != "" ){
          $mainQuery = new Elastica\Query\Bool();
          /**** Global search Query ****/
          if($queryToSearch != ""){
            $globalQuery = new Elastica\Query\QueryString();
            $globalQuery->setDefaultOperator('AND');
            $globalQuery->setFields(array('porposaltitle','description'));
            $globalQuery->setQuery($queryToSearch);
            $mainQuery ->addShould($globalQuery);
          }
          /******* Year Range filter *******/
          if ( $start_date != "" || $end_date != ""){
            $rangeYearParam = array();
            if($start_date != ""){
              $rangeYearParam["from"] = $start_date;
            }
            if($end_date != ""){
              $rangeYearParam["to"] = $end_date;
            }
            $dateYearRange = new Elastica\Query\Range();
            $dateYearRange->addField('year',$rangeYearParam);
            $mainQuery->addMust($dateYearRange);
          }
          /**** Firm Name search Query ****/
          if($FIRM_NAME != ""){
            $firmQuery = new Elastica\Query\QueryString();
            $firmQuery->setDefaultOperator('AND');
            $firmQuery->setFields(array('firmName'));
            $firmQuery->setQuery($FIRM_NAME);
            $mainQuery ->addMust($firmQuery);
          }
          /**** Firm State Code search Query ****/
          if($FIRM_STATE != ""){
            $stateQuery = new Elastica\Query\Term();
            $stateQuery->setTerm('statecode', $FIRM_STATE);
            $mainQuery ->addMust($stateQuery);
          }
          $sbirTypeQuery = new Elastica\Query\Term();
          $sbirTypeQuery->setTerm('sbir_type', $SBIR_TYPE);
          $mainQuery ->addMust($sbirTypeQuery);
          $mainQuery->setMinimumNumberShouldMatch(1);
        }
        else{
          $mainQuery = new Elastica\Query\Term();
          $mainQuery->setTerm('sbir_type', $SBIR_TYPE);
        }
        
        $query = new Elastica\Query();
        $query->setSort(array($sOrder => array('order' => $sOrderAD)));
        $query->setSize($MAX_RESULTS);
        $query->setFrom(0);
        $query->setQuery($mainQuery);
        $resultSet = $elasticaType->search($query);
        $size =  $resultSet->getTotalHits();
        $resultsNASA = $resultSet->getResults();
        if(!empty($resultsNASA)){
          foreach($resultsNASA as $resultNASA){
            $resultNASA = $resultNASA->getData();
            $listingTitle = $resultNASA['porposaltitle'];
            $listingURL = '/sbirdetail/'.$resultNASA['unique_id'];;
            $summary = strip_tags($resultNASA['description']);
            $summary1 = str_replace('Abstract', '', $summary);
            $summary1 = str_replace('ABSTRACT:', '', $summary1);
            $summary = trim($summary1);
            $summaryAll = $summary;
            $pos = strpos($summary, ' ', 500);
            if ($pos !== false) {
              $summary = substr($summary, 0, $pos);
              $summary .= '...';
            }
            $topicNumber = isset($resultNASA['topic_number']) ? $resultNASA['topic_number'] : '';
            $firmName = isset($resultNASA['firmName']) ? $resultNASA['firmName'] : '';
            $phase = isset($resultNASA['phase']) ? $resultNASA['phase'] : '';
            $award_start_date = isset($resultNASA['start_date']) ? @date('m/d/Y',$resultNASA['start_date']) : '';
            $award_end_date = isset($resultNASA['start_date']) ? @date('m/d/Y',$resultNASA['end_date']) : '';
            $TRL = isset($resultNASA['trl']) ? $resultNASA['trl'] : '';
            $source = $resultNASA['sbir_type'];
            $year = isset($resultNASA['year']) ? $resultNASA['year'] : '';
            $resultData[$row_id] = array(
              "listingURL" => $listingURL,
              "listingTitle" => $listingTitle,
              "summary" => $summary,
              "summaryAll" => $summaryAll,
              "topicNumber" => $topicNumber,
              "firmName" => $firmName,
              "source" => $source,
              "phase" => $phase,
              "award_start_date" => $award_start_date,
              "award_end_date" => $award_end_date,
              "TRL" => $TRL,
              "Year" => $year,
              "type" => 'nasa'
            );
            $row_id ++;
          }
        }                
      }//End NASA Results      
    }
    /*****Documetns Resutls*****/
  	if ( $docs == "true" ) {  	
  	  global $base_url;
      $baseURL = str_replace('ajax','',$base_url);
      $docQuery = !empty($queryToSearch) ? $queryToSearch : '*';
      $docs_json =  file_get_contents($baseURL.'docs-search-json?qry='.$docQuery.'&query_id='.$_POST['query_id']);
      $deco_jsdoc = json_decode($docs_json, true);
      foreach($deco_jsdoc['nodes'] as $node_doc){
        $nodes_data = node_load($node_doc['node']['nid']);
        $node_doc_url = drupal_get_path_alias('node/'.$node_doc['node']['nid']);
        $summary = $nodes_data->body['und'][0]['value'];
        $pos = strpos($summary, ' ', 500);
        if ($pos !== false) {
          $summary = substr($summary, 0, $pos);
          $summary .= '...';
        }
        
        $resultData[$row_id] =array(
          "listingURL" => '/'.$node_doc_url,
          "listingTitle" => $nodes_data->title,
          "summary" => $summary,
          "summaryAll" => $nodes_data->body['und'][0]['value'],
          "topicNumber" => '',
          "firmName" => '',
          "source" => 'Crowdsensing',
          "phase" => '',
          "award_start_date" => '',
          "award_end_date" => '',
          "TRL" => '' ,
          "Year" => '',
          "type" => 'doc'
		
        );
        $row_id ++;
      }
  	}//End documents Results
    if(!empty($resultData)){
      /*****Carrots Cluster Building*****/
      require_once DRUPAL_ROOT . '/ajax/includes/Carrot2.php';
	  $processor = new Carrot2Processor();
	  $job = new Carrot2Job();
	  $algorithm = "lingo";
	  // add documents in cluster
	  foreach ($resultData as $resultDoc ) {
	    $doc = $resultDoc['listingTitle'] . " " . $resultDoc['summaryAll'] . " " . $resultDoc['firmName'];
		$job->addDocument($doc);
	  }
      function displayCluster(Carrot2Cluster $cluster, &$d3_json_array) {
	    $temp = array();
		if(preg_match('/(Other Topics)/i', $cluster->getLabel())){
		  return;
		}
		$temp['name'] = $cluster->getLabel();
		$temp['size'] = $cluster->size();
		$temp['ids'] = $cluster->getDocumentIds();
		if (count($cluster->getSubclusters()) > 0) {
		  $temp['subclusters'] = $cluster->getSubclusters();
		  foreach ($cluster->getSubclusters() as $subcluster) {
		    displayCluster($subcluster);
		  }
		}else{
		  $temp['subclusters'] = 0;
		}
		$d3_json_array[] = $temp; 					
	  } 			
	  $job->setAlgorithm($algorithm);
	  $job->setAttributes(array (
        'LingoClusteringAlgorithm.desiredClusterCountBase' => 30, 
	    'dcs.output.format' => 'JSON', 
	    'TermDocumentMatrixBuilder.termWeighting' => 'org.carrot2.text.vsm.LogTfIdfTermWeighting',
	    'TermDocumentMatrixReducer.factorizationFactory' => 'org.carrot2.matrix.factorization.PartialSingularValueDecompositionFactory',
	    'DocumentAssigner.minClusterSize' => '2',
	    'CaseNormalizer.dfThreshold' => '1',
	  ));
	  $result = $processor->cluster($job);		 						
	  $clusters = $result->getClusters(); 			
      $d3_json_array = array();			
      if (count($clusters) > 0){ 				
        foreach ($clusters as $cluster){
	      displayCluster($cluster, $d3_json_array);
	    }
	  }
	  $d3_json = array();
	  foreach($d3_json_array as $cluster){
	    $d3_json[] = array("label" => $cluster['name'], "weight" => $cluster['size'], "ids" => $cluster['ids']);
	  }	
	  $alerts['type'] = 'data';
	  $alerts['dataArr'] = $resultData;
      $alerts['d3_json_Arr'] = $d3_json;	
      echo json_encode($alerts);
      exit;
    }else{
	  $alerts['type'] = 'error';
	  $alerts['message'] = "No Clusters Found, please try again with new search Criteria.";
	  echo json_encode($alerts);
	  exit;
    } //End Carrot Cluster
  }else {		
    $alerts['type'] = 'error';
	$alerts['message'] = "No site selected, please try again.";
	echo json_encode($alerts);
	exit; 		
  }
}