<?php /* FILEVERSION: v1.0.1b */ ?>
<?php

//OO code linking
$mysqli = new mysqli(_DB_SERVER_,_DB_USER_,_DB_PASSWD_,_DB_NAME_);
	if (!$mysqli){die("Could not connect to MySQLi: " . mysql_error());}
?>