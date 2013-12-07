<?php /* FILEVERSION: v1.0.1b */ ?>
<?php
class login {

	//core object properties
	public $secure;
	public $root;
	public $activeSession;

	//content properties
	public $loginForm;

	public function login($secure=true){

		//determines whether or not to use secure connection for login script (should only be used for testing)
		$this->secure = $secure;

		//if secure connection is enabled than it creates the login form that directs itself to the processlogin page via https
		if($secure == true){

			$this->root = _SECURE_ROOT_;

		} else {

			$this->root = _ROOT_;
		}

		//checking if user is logged in
		$this->activeSession = processLogin::checkForSession();

		if(!$this->activeSession){
			$this->loginForm = $this->loginForm();
		}

	}

	public function loginForm(){

		//form html
		return $this->formStyle() . '
		<div class="darken-screen hidden"></div>
		<div class="login-container hidden">
			<div class="login-close"><a href="#" title="Close">X</a></div>
			<form id="login-form" method="post" name="login" action="' . $this->root . '/include/classes/processLogin.class.inc">
	            <label for="username">Username:</label>
	            <input type="text" id="username" name="username">
	            <label for="password">Password:</label>
	            <input type="password" id="password" name="password">
	            <p><a href="#" title="Forgot your password?" id="forgotPass">Forgot your password?</a></p>
	            <p><a href="#" title="Register an account" id="registerUser">Register as a new user</a></p>
	            <div id="lower">
	                <input type="submit" value="Login">
	                <div class="clearfix"></div>
	            </div><!--/ lower-->
	        </form>

	        <form id="new-user-form" class="hidden" method="post" name="newUser" action="' . $this->root . '/include/classes/processLogin.class.inc">
				<input type="hidden" name="createUser" value="createUser">
	            <label for="email">Email Address:</label>
	            <input type="text" id="email" name="email">
	            <label for="password">Password:</label>
	            <input type="password" id="password" name="password">
	            <label for="password">Verify Password:</label>
	            <input type="password" id="password2" name="password2">
	            <label for="first_name">First Name:</label>
	            <input type="text" id="first_name" name="first_name">
	            <label for="last_name">Last Name:</label>
	            <input type="text" id="last_name" name="last_name">
	            <div id="lower">
	                <input type="submit" value="Request Access">
	                <br>
	                <a href="#" title="Return to Login" class="loginReturn">Back</a>
	                <div class="clearfix"></div>
	            </div><!--/ lower-->
	        </form>
	    
			<form id="forgot-password-form" class="hidden" method="post" name="newUser" action="' . $this->root . '/include/classes/processLogin.class.inc">
				<input type="hidden" name="forgotPass" value="forgotPass">
	            <label for="email">Email Address:</label>
	            <input type="text" id="email" name="email">
	            <div id="lower">
	                <input type="submit" value="Request Temporary Password" style="margin-right: 20px;">
	                <br>
	                <a href="#" title="Return to Login" class="loginReturn">Back</a>
	                <div class="clearfix"></div>
	            </div><!--/ lower-->
	        </form>
	    </div>';
	}

	public static function formJavascript(){
		if(!processLogin::checkForSession()){
			return '
			<script>
				$(\'#loginButton\').click( function() {
					$(\'.login-container\').removeClass("hidden"),
					$(\'.darken-screen\').removeClass("hidden")
				});
			</script>
			<script>
				$(\'.login-close\').click( function() {
					$(\'.login-container\').addClass("hidden"),
					$(\'.darken-screen\').addClass("hidden")
				});
			</script>			
			<script>
				$(\'.loginReturn\').click( function() {
					$(\'#login-form\').removeClass("hidden"),
					$(\'#forgot-password-form\').addClass("hidden"),
					$(\'#new-user-form\').addClass("hidden")
				});
			</script>
			<script>
				$(\'#registerUser\').click( function() {
					$(\'#login-form\').addClass("hidden"),
					$(\'#forgot-password-form\').addClass("hidden"),
					$(\'#new-user-form\').removeClass("hidden")
				});
			</script>
			<script>
				$(\'#forgotPass\').click( function() {
					$(\'#login-form\').addClass("hidden"),
					$(\'#forgot-password-form\').removeClass("hidden"),
					$(\'#new-user-form\').addClass("hidden")
				});
			</script>';
		}
	}
	public static function formStyle(){
		return '
		<style>
			.hidden {
				display: none !important;
				animation: disappear .4s linear;
			}
			.login-container {
			    position: absolute;
			    width: 325px;
			    top: 50%;
			    left: 50%;
			    margin-top: -140px;
			    margin-left: -170px;
			    background: #fff;
			    border-radius: 3px;
			    border: 1px solid #ccc;
			    box-shadow: 0 1px 2px rgba(0, 0, 0, .1);
			    animation: appear .5s linear;
  				-webkit-animation: appear .5s linear;			    
			    z-index: 1000;
			    padding-bottom: 5px;
			}
			.login-container form {
			    margin: 0 auto;
			}
			.login-container label {
			    color: #555;
			    display: inline-block;
			    margin-left: 18px;
			    padding-top: 10px;
			    font-size: 14px;
			}
			.login-container p a {
			    font-size: 11px;
			    color: #aaa;
			    float: left;
				margin: -5px 0 0 18px;
			    -webkit-transition: all .4s ease;
			    -moz-transition: all .4s ease;
			    transition: all .4s ease;
			}
			.login-container p a:hover {
			    color: #555;
			}
			.login-container input {
			    font-family: "Helvetica Neue", Helvetica, sans-serif;
			    font-size: 12px;
			    outline: none;
			}
			.login-container input[type=text],
			.login-container input[type=password] {
			    color: #777;
			    padding-left: 10px;
			    margin: 10px;
			    margin-top: 12px;
			    margin-left: 18px;
			    width: 290px;
			    height: 35px;
			    border: 1px solid #c7d0d2;
			    border-radius: 2px;
			    box-shadow: inset 0 1.5px 3px rgba(190, 190, 190, .4), 0 0 0 5px #f5f7f8;
			    -webkit-transition: all .4s ease;
			    -moz-transition: all .4s ease;
			    transition: all .4s ease;
			}
			.login-container input[type=text]:hover,
			.login-container input[type=password]:hover {
			    border: 1px solid #b6bfc0;
			    box-shadow: inset 0 1.5px 3px rgba(190, 190, 190, .7), 0 0 0 5px #f5f7f8;
			}
			.login-container input[type=text]:focus,
			.login-container input[type=password]:focus {
			    border: 1px solid #a8c9e4;
			    box-shadow: inset 0 1.5px 3px rgba(190, 190, 190, .4), 0 0 0 5px #e6f2f9;
			}
			.login-container #lower {
			    background: #ecf2f5;
			    width: 100%;
			    height: 69px;
			    margin-top: 20px;
			    box-shadow: inset 0 1px 1px #fff;
			    border-top: 1px solid #ccc;
			    border-bottom-right-radius: 3px;
			    border-bottom-left-radius: 3px;
			}
			.login-container #lower .checkbox {
				display: table-cell;
				vertical-align: text-bottom;
			} 
			.login-container input[type=checkbox] {
			    margin-left: 20px;
			    margin-top: 30px;
			}
			.login-container .check {
			    margin-left: 3px;
			    font-size: 11px;
			    color: #444;
			    text-shadow: 0 1px 0 #fff;
			}
			.login-container input[type=submit] {
			    float: right;
			    margin-top: 20px;
			    height: 30px;
			    font-size: 14px;
			    font-weight: bold;
			    color: #fff;
			    background-color: #acd6ef; /*IE fallback*/
			    background-image: -webkit-gradient(linear, left top, left bottom, from(#acd6ef), to(#6ec2e8));
			    background-image: -moz-linear-gradient(top left 90deg, #acd6ef 0%, #6ec2e8 100%);
			    background-image: linear-gradient(top left 90deg, #acd6ef 0%, #6ec2e8 100%);
			    border-radius: 30px;
			    border: 1px solid #66add6;
			    box-shadow: 0 1px 2px rgba(0, 0, 0, .3), inset 0 1px 0 rgba(255, 255, 255, .5);
			    cursor: pointer;
			}
			#new-user-form input[type=submit] {
				margin-right: 20px;
			}
			.login-container input[type=submit]:hover {
			    background-image: -webkit-gradient(linear, left top, left bottom, from(#b6e2ff), to(#6ec2e8));
			    background-image: -moz-linear-gradient(top left 90deg, #b6e2ff 0%, #6ec2e8 100%);
			    background-image: linear-gradient(top left 90deg, #b6e2ff 0%, #6ec2e8 100%);
			}
			.login-container input[type=submit]:active {
			    background-image: -webkit-gradient(linear, left top, left bottom, from(#6ec2e8), to(#b6e2ff));
			    background-image: -moz-linear-gradient(top left 90deg, #6ec2e8 0%, #b6e2ff 100%);
			    background-image: linear-gradient(top left 90deg, #6ec2e8 0%, #b6e2ff 100%);
			}
			.login-close {
				width: 18px;
				height: 18px;
				border-radius: 17px;
				background: #999;
				float: right;
				padding: 0;
				font-size: 17px;
				position: relative;
				top: -12px;
				left: 12px;
				border: 2px solid #fff;
				font-weight: bold;
			}
			.login-close:hover {
				background: red !important;
				color: #fff !important;
			}
			.login-close a {
				text-decoration: none !important;
				color: #fff !important;
				position: relative;
				left: 3px;
				top: 0;
			}
			#registerUser,
			.loginReturn {
				font-size: 10px;
				margin: 0 0 0 20px;
			}
			#registerUser {
				position: relative;
				top: -15px;
				right: 20px;
				float: right !important;
			}
		</style>';
	}
}
?>