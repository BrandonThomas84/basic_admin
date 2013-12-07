<?php /* FILEVERSION: v1.0.1b */ ?>
<?php

class functionRights{
	
	public static function checkRights($functionName,$type='class'){

		global $mysqli;

		$user_id = $_COOKIE['usrID'];

		//get user_type
		$stmt = $mysqli->query('SELECT DISTINCT `' . _DB_PREFIX_ . 'users`.`user_type` FROM `' . _DB_NAME_ . '`.`' . _DB_PREFIX_ . 'users` WHERE `id` = ' . $user_id);
		
		$row = $stmt->fetch_array();

		$user_type = $row['user_type'];

		//if user type is admin then return true no matter function rights
		if($user_type == 'admin'){

			return true;

		} else {

			//checking if function right request type is class of method
			if($type == 'method'){

				//if we are dealing with a method then we will need to strip the method name from the called object
				$functionName = getMethod($functionName);
			}

			//preparing statement to prevent SQL injection
			$stmt = $mysqli->prepare('SELECT DISTINCT `id` FROM `' . _DB_NAME_ . '`.`' . _DB_PREFIX_ . 'function_rights` WHERE `user_id` = ? AND `function_type` = ? AND `function_name` = ?');

			//binding submitted userid to prepared query
			$stmt->bind_param('iss',$user_id, $type, $functionName);

			//executing prepared statement
			$stmt->execute();

			//store result
	    	$stmt->store_result();

			//counting number of failed attempts
			if($stmt->num_rows > 0 ){

				//return true value
				return true;

			} else {

				//return false value
				return false;

			}
		}
	}
}

?>