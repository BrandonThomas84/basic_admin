<?php /* FILEVERSION: v1.0.1b */ ?>
<?php

class adminPage {

	//construct
	public function adminPage(){

		$this->checkGlobalSubmissions();

	}

	//check for submissions from the sub tabs
	public function checkGlobalSubmissions(){

		//checking if the checkSubmission method has been created in the subsequent class
		if(method_exists($_GET['tab'],'checkSubmission')){
			$_GET['tab']::checkSubmission();
		}
		
	}

	//check for active logged in session
	public function checkSession(){

		if(isset($_COOKIE['sessionID'])){

			return true;
		} else {
			return false;
		}
	}

	//returns the formatted page title
	public function title($title){

		return '<h1>' . $title . '</h1>';
	}

	//retrieving message for display
	public function retrieveMessages(){

		//adding returned messages to the body
		$messages = new messaging;

		//get messaging
		return $messages->showMessages();
	}

	//gets the tab information from the database
	public static function displayOrder(){

		//starting mysqli
		global $mysqli;
		$return = array();

		$stmt = $mysqli->query('SELECT DISTINCT `tab_name` FROM `' . _DB_NAME_ . '`.`' . _DB_PREFIX_ . 'admin_tabs` WHERE `active` = 1 ORDER BY `order` ASC');

		while($row = $stmt->fetch_array()){

			array_push($return, $row['tab_name']);
		}

		return $return;

	}	

	//control the tabs for navigation
	public function adminNavigation(){

		//return array
		$returnArray = array();

		//array used to configure the display order
		$displayOrderArray = array();
		$displayValueArray = array();

		//getting all tabs in the tabs folder
		$tabArray = $this->displayOrder();

		//processing array of tabs
		foreach($tabArray as $tab){

			//instantiating the tab class to get the display number
			$class = new $tab;

			//adding key to the order array
			array_push($displayOrderArray, array_search($tab,$tabArray));

			//adding value to the value array
			array_push($displayValueArray, $class->navTab);
		}
		
		$display = array_combine($displayOrderArray,$displayValueArray);

		//reordering array by the displayOrder value
		ksort($display);

		//adding tabs to return array
		for($i=0;$i<count($display);$i++){

			array_push($returnArray, $display[$i]);
		}

		//adding the ul html to the beginning of the array
		array_unshift($returnArray, '
			<div class="tab-container">
				<div class="tab-controls">
					<div id="tab-left">
						<a id="tab-left-button" href="#"><span class="tab-nav-left"><</span></a>
					</div>
					<div id="tab-right">
						<a id="tab-right-button" href="#"><span class="tab-nav-right">></span></a>
					</div>
				</div>
				<div id="admin-tabs">
					<ul class="nav nav-tabs">');

		//adding closing html to the array
		array_push($returnArray, '
					</ul>
				</div>
				<div class="clearfix"></div>
			</div>');

		//imploding array
		$returnArray = implode(null,$returnArray);

		return $returnArray;
	}

	//method grabs the content to be displayed on each of the tabs
	public function adminContent(){

		//return array
		$returnArray = array();
		$tabArray = $this->displayOrder();

		//processing array of admin tabs
		foreach($tabArray as $tab){		

			//default active status
			$active = null;	
			
			//checking if active tab is set and if so applying an active setting
			if(isset($_GET['tab'])){

				//if active tab is current array tab
				if($_GET['tab'] == strtolower($tab)){

					//instantiating the class
					$class = new $tab;

					//setting the page content to the link to return to the tab home and the pageBody content from the called class
					$content = $class->tabHome . $class->pageBody;		

					//writing menu html
					$html = '
					<div class="tab-pane fade in active" id="' . $tab . '">
						<div class="container">
							<div class="well">
								' . $content . '
							</div>
						</div>
					</div>';

					array_push($returnArray,$html);

				} 
			} 		

		}

		//adding the ul html to the beginning of the array
		array_unshift($returnArray, '<div class="tab-content">');

		//adding closing html to the array
		array_push($returnArray, '</div>');

		//imploding array
		$returnArray = implode(null,$returnArray);

		return $returnArray;
	}
}

?>