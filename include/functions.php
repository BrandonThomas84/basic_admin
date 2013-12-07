<?php /* FILEVERSION: v1.0.1b */ ?>
<?php

$mysqli = new mysqli(_DB_SERVER_,_DB_USER_,_DB_PASSWD_,_DB_NAME_);

//if in the root then redirect to a tabbed page with a fix for the login script and homepage
if(!isset($_GET['tab']) && (strlen(str_replace('processLogin.class.inc',null,$_SERVER['PHP_SELF'])) == strlen($_SERVER['PHP_SELF']))){

	//check if there is a message so it can be maintained
	if(isset($_GET['msg'])){
		$message = '&msg=' . $_GET['msg'];
	} else {
		$message = null;
	}

	header('Location: ' . $_SERVER['PHP_SELF'] . '?tab=home' . $message);
	
} 

function sessionRenew($sessionTimeOut=10,$giveWarning=null){

	if(!is_null($giveWarning)){
		
		//number of seconds before timeout to show warning message
		$warning = $giveWarning;

	} else {
		$warning = -1;
	}
	

	//check is user is logged in before returning the javascript that 
	if(isset($_COOKIE['sessionID'])) {

	    return '
		<script>
			$(document).ready( function() {		
				setTimeout( 
					function() {
						parent.window.location = "' . _ROOT_ . '/include/classes/processLogin.class.inc?logout=true"
					},' . $sessionTimeOut . '000
				);	
			});
		</script>
	    <script>
			$(document).ready( function() {		
				setTimeout( 
					function() {
					  if (confirm("WARNING:\nYou\'re session is about to expire due to lack of activity.\nClick \'OK\' to extend your session.")==true)

					    return parent.window.location.reload();

					  else

					    return parent.window.location = "' . _ROOT_ . '/include/classes/processLogin.class.inc?logout=true"

					},' . ( $sessionTimeOut - $warning ) . '000
				);
			});	
		</script>';
	}
}
/*
<script>
			$(document).ready( function() {		
				setTimeout( 
					function() {
					  if (confirm("You\'re session is about to end due to lack of activity. Click \'OK\' to extend your session.")==true)

					    return parent.window.location.reload();

					  else

					    return parent.window.location.href ("' . _ROOT_ . '/include/classes/processLogin.class.inc?logout=true");

					},' . ( $sessionTimeOut - $warning ) . '000
				);	
			});	
		</script>
		*/

function getClasses(){

	//file and location array
	$return = array();
	$directories = array();
	
	//file directory to look in
	$directory = __DIR__ . '/classes';

	//add to list of directories
	array_push($directories,$directory);

	//file directory to look in
	$directory = __DIR__ . '/classes/tabs';

	//add to list of directories
	array_push($directories,$directory);

	//scan directory
	$fileList = scanDirectory($directories);

	//manually requiring home to be sure that it is called before all other tabs
	require_once(__DIR__ . '/classes/tabs/home.tab');
	
	//get files
	foreach($fileList as $file){
			
		//requiring the classes
		require_once($file[0] . '/' . $file[1]);

	}
}

function scanDirectory($directory,$returnArray=array()){

	//array values to ignore
	$noShow = array('.','..','tabs');

	//if array of directories is submitted then it will cycle through each of them
	foreach($directory as $dir){

		//file name array
		$fileArray = scandir($dir);

		//adding files to array
		foreach($fileArray as $file){

			//checking if files are told to be ignored
			if(!in_array($file,$noShow)){

				//adding file and location to return array
				array_push($returnArray,array($dir,$file));
			}

		}
	}

	//returning array
	return $returnArray;
}

//strips method names down to just the method value for checking against the database
function getMethod($method){

	return substr($method,(stripos($method,'::')+2), (strlen($method) - (stripos($method,'::'))));
}

//checks for matching and returns form control status indicators based on the type used
function checkForSelected($needle,$haystack,$type='s'){

	if($needle == $haystack){

		if($type == 's'){

			return ' SELECTED ';

		} elseif($type =='c'){

			return ' CHECKED ';
			
		}
		
	}
}



?>