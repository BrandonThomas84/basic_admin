<?php /* FILEVERSION: v1.0.1b */ ?>
<?php
/** Prevent direct access */
if (basename($_SERVER['PHP_SELF']) == 'settings.inc') { 
	die('You cannot load this page directly.');
}
//change this value to TRUE to force all pages to render in https only
$REQUIRESECURE = false;

//set the directory value addition
if($REQUIRESECURE){
	
	//redirects to https if secure is forced
	if ($_SERVER["SERVER_PORT"] != 443 || $_SERVER["HTTPS"] != "on" || empty($_SERVER['HTTPS'])) {
    	$redir = "Location: https://" . $_SERVER['HTTP_HOST'] . $_SERVER['PHP_SELF'];
    	header($redir);
	}

	$s = 'https://';

} else {
	
	$s = 'http://';
}

//the admin panel folder location that will be appended to all links
$ROOTDIR = 'github/basic_admin';


//settings constants
# Site Root
define('_ROOT_',$s . $ROOTDIR);	

# Secure Site Root
define('_SECURE_ROOT_','https://' . $ROOTDIR);

# Database host name
define('_DB_SERVER_','127.0.0.1');

# Database user name
define('_DB_USER_','basic_admin');

# Database password
define('_DB_PASSWD_','A2aoF^8inf7V7H806RTtF1ae3');

# Database name
define('_DB_NAME_','manufacturer_admin');

# Database table prefix
define('_DB_PREFIX_',null);

# Max Number of Login Attempts before lockout
define('_MAX_LOGINS_ATTEMPTS_','5');

# Lockout duration in seconds
define('_LOCKOUT_DURATION_','1800');

# Company Name
define('_CO_NAME_','Energy Efficient Services');


?>