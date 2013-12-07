<?php /* FILEVERSION: v1.0.1b */ ?>
<?php

class breadcrumbs {


	public $currentPage;
	public $tab;
	public $baseUrl;
	public $steps;


	public function breadcrumbs(){

		//sets all base properties
		$this->createBase();
	}

	public function createBase($currentPage=null){

		//checking if a page override was submitted
		if(is_null($currentPage)){

			//if not then set the current page to the active page
			$currentPage = $_SERVER['REQUEST_URI'];
		}

		//getting root so that it can find what it needs to remove from the url to get the base values
		$rootContents = explode('/',_ROOT_);

		//removing url contents that exist in the _ROOT_ constant
		$contents = str_replace($rootContents,null,$currentPage);

		//removing any double slashes
		$contents = str_replace('//','/',$contents);

		//setting object scope property
		$this->currentPage = $contents;

		if(stripos($contents,'?') > 1){
			//separating the url body from the query
			$urHere = explode('?',$contents);
			
			//setting object scope variables
			$this->steps = explode('&',$urHere[1]);
			$this->baseUrl = $urHere[0];
			if(isset($_GET['tab'])){
				$this->tab = $_GET['tab'];	
			} else {
				$this->tab = null;
			}
		}

		//changing the steps into a usable array of values
		$this->setSteps(); 
		
	}

	public function setSteps(){

		$return = array();

		//checking if mod_rewrite was used
		if(is_null($this->steps)){

			//setting the tab manually
			$step = explode('=',$_SERVER['QUERY_STRING']);
			array_push($return,array($step[0],$step[1]));

		} else {

			foreach($this->steps as $step){
				$step = explode('=',$step);
				array_push($return,array($step[0],$step[1]));
			}
		}

		$this->steps = $return;
	}

	public function showCrumbs(){

		$return = array();
		$steps = array();

		//starting breadcrumb html
		array_push($return,'<div class="bcrumbs"><ol class="breadcrumb"><span>You are:</span>');

		foreach($this->steps as $step){

			//checking the crumb shouldn't be ignored
			$ignore = array('msg','ppg');

			if(!in_array($step[0],$ignore)){

				$urlContent = $this->currentPage;
				$urlSearch = $this->crumbConversion($step);

				//checking if null crumb value return
				if(!is_null($urlSearch[0])){

					$urlLen = stripos($urlContent, $urlSearch[1]) + strlen($urlSearch[1]);

					$href = substr($urlContent,0,$urlLen);
					
					$friendly = $urlSearch[0];

					//page fix makes sure that per page value is included on the page number click
					if(stripos($href,'pg=') > 1){
						
						if(isset($_GET['ppg'])){
							$ppg = $_GET['ppg'];
						} else {
							$ppg = 10;
						}

						$href = $href . '&ppg=' . $ppg;
					}

					$link = '<li><a href="' . _ROOT_ . $href . '">' . $friendly . '</a></li>';

					array_push($return,$link);
				}					
			}
		}

		array_push($return,'</ol></div>');

		//show the breadcrumbs
		return  implode(null,$return);

	}

	public function crumbConversion($step){

		$return = array();

		//array of friendly values to convert the url information to structure = array( name ( value => friendly ) )
		$conv = array(
			'ifnc'		=> 
				array(
					'ni'		=>	'Add / Remove Inventory',
					'vi'		=>	'View Inventory'
				),
			'pid'		=>
				array(
					'#'			=>	'Single Product Inventory',
					
				),
			'qi'		=>
				array(
					'in'		=>	'Scan In Inventory',
					'out'		=>	'Scan Out Inventory'
				),
			'mtchb'		=>
				array(
					'mpn'		=> 'MPN Match',
					'upc'		=> 'UPC Match',
					'id'		=> 'Product ID Match',
				),
			'pg'	=>
				array(
					'#'			=> 'Page ' . $step[1],
				),
			'pfnc'		=>
				array(
					'newprd'	=> 'Add New Product ',
					'mngprd'	=> 'Manage Products ',
				),	
			'mngID'	=>
				array(
					'#'			=> 'Edit Product',
				),
			'dstID'		=>
				array(
					'#'			=> 'Manage Distributor',
					'new'		=> 'Create New Distributor Account',
					'na'		=> null,
				),
			'dstfnc'	=>
				array(
					'cntct'		=> 'Manage Distributor Account Info',
					'ordrs'		=> 'Manage Distributor Orders',
				),
			'dstsubfnc'	=>
				array(
					'usrmng'	=> 'Create / Manage Associated User',
				),
			'ufnc'		=>
				array(
					'apu'		=> 'Approve Pending Users',
					'du'		=> 'Deactivate User Account',
					'uda'		=> 'User / Distributor Associations',
					'ufr'		=> 'Function Rights',
				),
			'user_id'	=>
				array(
					'#'			=> 'User Access',
				),
			'mngfrall'	=>
				array(
					'true'		=> 'Global Settings',
				),
			'prf'		=>
				array(
					'#'			=> 'Profile Rights',
					'n'			=> 'Create New Profile'
				),
			);

		//setting the function and value names (GET info from url)
		$function = $step[0];
		$value = $step[1];

		//checking if the $function value is present in the friendly array
		if(array_key_exists($function,$conv)){
			
			//what to look for in the URL
			$urlSearch = $function . '=' . $value;

			//checking if the value is a number and if so converting it to a standard symbol
			if(is_numeric($value)){

				$value = '#';
			} 

			//checking if sub array key exists
			if(array_key_exists($value,$conv[$function])){
				
				//setting the friendly name to that within the array
				$friendly = $conv[$function][$value];

			} else {

				//setting a recognizeable error
				$friendly = 'Missing Breadcrumb Value';

			}

		} else {

			//if unable to find in array then just capitalize the first letter
			$friendly = ucfirst($value);

			//what to look for in the url
			$urlSearch = $function . '=' . $value;			

		}

		//return the values		
		return array($friendly, $urlSearch);

	}
}

?>