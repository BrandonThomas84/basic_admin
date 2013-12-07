<?php /* FILEVERSION: v1.0.1b */ ?>
<?php 

//constructing the root variable
$root = str_replace('classes',null,__DIR__);
require_once($root  . '/settings.inc');

//require functions file
require_once($root . '/functions.php'); 

?>
<?php

class processLogin {

	//basic properties
	public $mysqli;
	public $returnMessage;

	//credential properties
	protected $username;
	protected $password;
	protected $dbPassword;
	protected $salt;
	protected $userType;
	protected $firstName;
	protected $lastName;
	protected $id;
	protected $email;
	

	public function processLogin(){

		//starting db connection for querying
		global $mysqli;
		$this->mysqli = $mysqli;

		//checking to make sure we have a secure connection
		$this->checkForSubmission();
	}

	public function checkForSubmission(){

		//checking for a form submission
		if(isset($_POST['username'])){

			$this->verifyCredentials();

			//sending back to the home page after complete with message
			$this->redirect('index.php?msg=' . $this->returnMessage);
		}

		if(isset($_POST['forgotPass'])){
			
			//changing the users password to the string used as a salt using the static users tab class
			$this->passwordRecovery();

			//redirect back to the index page once login is complete
			$this->redirect('index.php?msg=' . $this->returnMessage);

		}

		if(isset($_POST['createUser'])){

			//checking for registration request
			$this->insertNewUser($_POST['email'], $_POST['password'], $_POST['password2'], $_POST['first_name'], $_POST['last_name']);
					
			//redirect back to the index page once login is complete
			$this->redirect('index.php?msg=' . $this->returnMessage);
		}

		if(isset($_GET['logout'])){

			//kill session
			$this->logout();

			//sending back to the home page
			$this->redirect('index.php');
		}

	} 

	public function checkHTTPS(){
		// If page requires SSL, and we're not in SSL mode, 
		// redirect to the SSL version of the page
		if($_SERVER["HTTPS"] != "on") {
		   header("HTTP/1.1 301 Moved Permanently");
		   header("Location: https://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI']);
		   exit();
		}
	}

	public function verifyCredentials(){

		//form submitted username value
		$username = $_POST['username'];

		//form submitted password value
		$password = $_POST['password'];	

		//preparing ststement prevents sql injection
		$stmt = $this->mysqli->prepare('SELECT `id`, `email`, `password`, `pwd_salt`, `first_name`, `last_name`, `user_type` FROM `' . _DB_NAME_ . '`.`' . _DB_PREFIX_ . 'users` WHERE email = ? AND `user_type` NOT IN (\'refused\',\'pending approval\')');


		if(!$stmt){

			$this->returnMessage = 'invalidUser';

			$this->redirect('index.php?msg=' . $this->returnMessage);
		}

		//binding submitted username to prepared query
		$stmt->bind_param('s',$username);

		//executing prepared statement
		$stmt->execute();

		//store result
    	$stmt->store_result();

		//checking if user exists
		if($stmt->num_rows == 0){

			//setting the return message to cannot locate username
			$this->returnMessage = 'invalidUser';

		} else {

			//binding results
			$stmt->bind_result($this->id, $this->email, $this->dbPassword, $this->salt, $this->firstName, $this->lastName, $this->userType);

			//fecthing bound data
			$stmt->fetch();

			//checking for successive failed attempts to prevent a brute force attack
			if($this->checkBruteForce($this->id) == true){

				//setting the return message as a brute force lockout
				$this->returnMessage = 'passwordLockout';

			} else {

				//verifying the submitted password matches the salted DB passsword
				if($this->dbPassword !== md5($password . $this->salt)){

					//adding a failed attempt record to the login attempts table 
					$this->addAttemptValue($this->id);

					//setting the return message
					$this->returnMessage = 'incorrectPasssword';

				} else {

					//setting session cookies
					setcookie('sessionID', $this->generateRandomSalt(12), 0, '/');
					setcookie('usr', $this->email, 0, '/');
					setcookie('frstnm', $this->firstName, 0, '/');
					setcookie('lstnm', $this->lastName, 0, '/');
					setcookie('usrtyp', $this->userType, 0, '/');
					setcookie('usrID', $this->id, 0, '/');

					//successful login message
					$this->returnMessage = 'loginSuccess';
				}
			} 
		}
	}

	public function checkBruteForce($user_id){

		//preparing ststement prevents sql injection
		$stmt = $this->mysqli->prepare('SELECT DISTINCT `id` FROM `' . _DB_NAME_ . '`.`' . _DB_PREFIX_ . 'login_attempts` WHERE `user_id` = ? AND `datetime` > (CURRENT_TIMESTAMP-' . _LOCKOUT_DURATION_ . ')');

		//binding submitted userid to prepared query
		$stmt->bind_param('i',$user_id);

		//executing prepared statement
		$stmt->execute();
		$stmt->store_result();

		//counting number of failed attempts
		if($stmt->num_rows > 5){

			//return true value
			return true;

		} else {

			//return false value
			return false;

		}
	}

	public function addAttemptValue($user_id){

		//get user IP address
		$user_ip = $_SERVER['REMOTE_ADDR'];

		//preparing ststement prevents sql injection
		$stmt = $this->mysqli->prepare('INSERT INTO `' . _DB_NAME_ . '`.`' . _DB_PREFIX_ . 'login_attempts` (`user_id`,`user_ip`) VALUES (?,?)'); 

		$stmt->bind_param('is',$user_id,$user_ip);
		$stmt->execute();
		$stmt->close();


	}

	public function passwordRecovery(){

		$email = $_POST['email'];

		if($this->checkExistingUser($email) <= 0){

			//if user doesnt exist in the database return an error message
			$this->returnMessage = 'invalidUser';

		} else {

			$this->returnMessage = 'pssRecovSuccess';
		}
	}

	public function generateRandomSalt($length=25){

		//return array
		$salt = array();

		//aray of available characters that salt will be generated from
		$characterArray = array('1','2','3','4','5','6','7','8','9','10','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','!','@','#','$','%','^','&','(',')','_');

		//adding a single random character up to the specified length to the return array
		for($i = 0; $i < $length; $i++){
			
			//generating random number equal to a character in the array
			$character = rand(0,71);

			//adding that random character to the array
			array_push($salt,$characterArray[$character]);
		}

		//returning salt to a string
		$salt = implode('',$salt);

		//returning the randomized salt
		return $salt;

	}

	public function insertNewUser($email, $password, $password2, $first_name, $last_name, $middle_initial=null, $user_type='pending approval'){

		//if there is a user in the database return the error message
		if($this->checkExistingUser($email) > 0){

			$stmt = $this->mysqli->query('UPDATE `' . _DB_NAME_ . '`.`' . _DB_PREFIX_ . 'users` SET `user_type` = \'pending approval\' WHERE `email` = \'' . $email . '\'');
			
			//return duplicate user error message
			$this->returnMessage = 'dplctUsr';

		} else {

			//check if submitted passwords match
			if($password !== $password2){

				//return password error
				$this->returnMessage = 'passwordMatch';

			} else {

				$stmt = $this->mysqli->prepare('INSERT INTO `' . _DB_NAME_ . '`.`' . _DB_PREFIX_ . 'users` (`email`, `password`, `pwd_salt`, `first_name`, `last_name`, `middle_initial`, `user_type`) VALUES (?,?,?,?,?,?,?)');

				//setting salt value
				$salt =  $this->generateRandomSalt();

				//preparing the password for insertion into the database by adding the salt and hashing with MD5
				$password = md5($password . $salt);

				//binding submitted information to prepared query
				$stmt->bind_param('sssssss',$email, $password, $salt, $first_name, $last_name, $middle_initial, $user_type);

				//executing prepared statement
				$stmt->execute();

				//setting return message
				$this->returnMessage = 'newUserSuccess';
			}
		}
	}

	public function redirect($location = null, $success = 1,$test = 1){

		//Optional variables of test and success allow you to use this method with variable conditions
		if($test == $success) {
		   header("Location: " . _ROOT_ . '/' . $location);
		}

	}

	public static function checkForSession(){

		if(isset($_COOKIE['sessionID'])){

			return true;

		} else {

			return false;

		}
	}

	public function logout(){

		//expiring session cookies
		setcookie('sessionID','',time()-100, '/');
		setcookie('usr','',time()-100, '/');
		setcookie('frstnm','',time()-100, '/');
		setcookie('lstnm','',time()-100, '/');
		setcookie('usrtyp','',time()-100, '/');
		setcookie('PHPSESSID','',time()-100, '/');
		setcookie('usrID','',time()-100, '/');

		//ending session
		session_destroy();
	
	}

	public function checkExistingUser($email){
		//check if user is already registered
		$stmt = $this->mysqli->prepare('SELECT * FROM `' . _DB_NAME_ . '`.`' . _DB_PREFIX_ . 'users` WHERE `email` = ?');

		//binding submitted information to prepared query
		$stmt->bind_param('s',$email);

		//executing prepared statement
		$stmt->execute();
		$stmt->store_result();

		return $stmt->num_rows;
	}
}

new processLogin;

?>