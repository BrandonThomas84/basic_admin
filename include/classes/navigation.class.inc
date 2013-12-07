<?php /* FILEVERSION: v1.0.1b */ ?>
<?php

class navigation {

	//used to make sure links are always pointing to the correct location
	public $root;
	public $level;

	public $sessionButton;
	public $sessionButtonID;
	public $sessionHref;
	public $myAccountButton;

	//user properties
	public $userID;
	public $email;
	public $firstName;
	public $lastName;
	public $middleInitial;

	public function navigation(){

		//seets object properties to be used
		$this->setProperties();
	}

	public function setProperties(){

		//if the user is logged in already
		if(processLogin::checkForSession()){

			//session button variables
			$this->sessionButton = 'Logout';
			$this->sessionButtonID = 'logoutButton';
			$this->sessionHref = _ROOT_ . '/include/classes/processLogin.class.inc?logout=true';
			$this->myAccountButton = '
				<li class="dropdown">
		          	<a href="#" class="dropdown-toggle" data-toggle="dropdown">My Account<b class="caret"></b></a>
					<ul class="dropdown-menu">
			            <li class="dropdown-header"><strong>Account Tools:</strong></li>
			            <li class="divider"></li>
			            <li><a href="#" title="Image 1">Manage Account</a></li>
			            <li><a href="#" title="Image 2">My Orders</a></li>
			        </ul>
			    </li>';

		} else {

			//more session button variables
			$this->sessionButton = 'Login';
			$this->sessionButtonID = 'loginButton';
			$this->sessionHref = '#';
			$this->myAccountButton = null;

		}
	}

	public function displayNav(){

 
		$html = '
		<div class="navbar navbar-inverse navbar-static-top main-nav">
		    <div class="navbar-header">
			  <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target=".navbar-collapse">
	            <span class="icon-bar"></span>
	            <span class="icon-bar"></span>
	            <span class="icon-bar"></span>
	          </button>
		      <a class="navbar-brand" href="' . _ROOT_ . '/home">EES Admin Area</a>
		    </div>
		    <div class="navbar-collapse collapse" style="margin-left: 40px;">
		      <ul class="nav navbar-nav">
		        <li><a href="' . _ROOT_ . '/home">Home</a></li>
		        <li><a href="http://www.energyefficientservices.com/" title="Visit EES public site" target="_blank">Public Site</a></li>
		        ' . $this->myAccountButton . '
		        <li><a href="' . $this->sessionHref . '" title="' . $this->sessionButton . '" id="' . $this->sessionButtonID . '">' . $this->sessionButton . '</a></li>
		      </ul>
		    </div>
		</div>';

		return $html;
	}

	public static function pagify($totalValues){

		//setting default display call (whether or not to show the page navigation)
		$display = false;
		$displayOn = array('ifnc' => 'vi');

		//check each array key to see if a get value is in the url
		foreach($displayOn as $display){

			//verify that the necessary value is set and that it is equalt to the accepted array value
			if(isset($_GET[array_search($display,$displayOn)]) && $display == $_GET[array_search($display,$displayOn)]){
			
				$display = true;

			} else {

				$display = false;
			}	
		}

		//if page is one listed in acceptable array
		if($display == true){
			global $mysqli;
			$return = array();
			$url = $_SERVER['PHP_SELF'] . '?' . $_SERVER['QUERY_STRING'];


			//checking if a page number is set
			if(!isset($_GET['pg'])){

				$page = 1;
				$pgLoc = null;

			} else {

				$page = $_GET['pg'];
				$pgLoc = stripos($url,'pg=');
			}

			//checking if a per page amount is set
			if(!isset($_GET['ppg'])){

				$perPage = 10;
				$ppgLoc = null;

			} else {

				$perPage = $_GET['ppg'];
				$ppgLoc = stripos($url,'ppg=');
			}

			//identifying which value comes first in the url
			$startStrip = min($ppgLoc,$pgLoc) -1 ;
			$url = substr($url,0,$startStrip);
			

			//getting total pages
			$pages = $totalValues / $perPage;
			$pages = ceil($pages);

			//checking if on first page
			if(($page - 1) <= 0){

				$left = '<li class="disabled"><a href="#">&laquo;</a></li>';
			} else {

				$left = '<li><a href="' . $url . '&pg=' . ($page - 1) . '&ppg=' . $perPage . '">&laquo;</a></li>';
			}

			//checking if on last page
			if(($page + 1) > $pages){

				$right = '<li class="disabled"><a href="#">&raquo;</a></li>';	
				 
				
			} else {
				
				$right = '<li><a href="' . $url . '&pg=' . ($page + 1) . '&ppg=' . $perPage . '">&raquo;</a></li>';
			}

			//creating individual page number links
			for($i=-2; $i<3; $i++){
				
				//page number
				$value = $page + $i;

				//checking if page to be printed is too low or too high to display
				if($value > 0 && $value < $pages+1){

					if($page == $value){
						$active = ' class="active" ';
					} else {
						$active = null;
					}

					//adding pages to pagify array
					$value = '<li' .$active .'><a href="' . $url . '&pg=' . $value . '&ppg=' . $perPage . '">' . $value . '</a></li>';

				} else {
					if($page > 3){
						$value = '<li class="disabled"><a href="#">..</a></li>';	
					} else {
						$value = null;
					}
					
				}

				array_push($return,$value);	
				

			}

			//adding left and right controls to array
			array_unshift($return,$left);
			array_push($return,$right);

			$return = implode(null,$return);
			return '
			
			<div class="row-fluid footer">
				<div class="span6 pagination pagination-small">
					<p>Page Number</p>
					<ul>' . $return . '</ul>
				</div>
				<div class="span6 pagination pagination-small">
					<p>Results Per Page</p>
					<form method="get" name="perpage">
						<input type="hidden" name="tab" value="' . $_GET['tab'] . '">
						<input type="hidden" name="ifnc" value="' . $_GET['ifnc'] . '">
						<input type="hidden" name="pg" value="' . $page . '">
						<select name="ppg" onChange="this.form.submit()" style="height: 26px;width: 100px;">
							<option value="1"' . checkForSelected(1,$perPage) . '>1</option>
							<option value="10"' . checkForSelected(10,$perPage) . '>10</option>
							<option value="25"' . checkForSelected(25,$perPage) . '>25</option>
							<option value="50"' . checkForSelected(50,$perPage) . '>50</option>
							<option value="100"' . checkForSelected(100,$perPage) . '>100</option>
						</select>
					</form>
				</div>
			</div>';
		}
			
	}
	
}

?>