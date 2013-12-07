<?php /* FILEVERSION: v1.0.1b */ ?>
<?php
class messaging {

	public $messageExists;
	public $messageBody;
	public $messageType;

	public function messaging(){

		//checking if msg ID has been submitted
		if(isset($_GET['msg'])){

			//sets the default retrieval status
			$this->messageExists = true;

			$message = $_GET['msg'];
		
			//canned messages with message types
			$messages = array(
				'invalidUser'				=>		array('User does not exist. Please check your username and try again','error'),
				'passwordLockout' 			=> 		array('You\'ve been locked out of your account as a result of too many failed attempts. You\'re account will be inaccessible for ' . ( _LOCKOUT_DURATION_ / 60 ) . ' minutes.','error'),
				'incorrectPasssword'		=>		array('Incorrect Password. Please try again.','error'),
				'passwordMatch'				=>		array('Passwords do not match.','warning'),
				'loginSuccess'				=>		array('Welcome back ' . @$_COOKIE['frstnm'] . '!','success'),
				'newUserSuccess'			=>		array('Thank you for requesting a user account. You will receive an email from us once your account has been approved.','success'),
				'inventorySuccess'			=>		array('The inventory value updated','success'),
				'invalidProduct'			=>		array('The product scanned was not recognized by the system','error'),
				'updatedInventory'			=>		array('The inventory value has been updated for the scanned product','success'),
				'addedInventory'			=>		array('The inventory value has been added for the scanned product','warning'),
				'wrongFileType'				=>		array('You must convert inventory files to CSV format before uploading','error'),
				'successfulUpload'			=>		array('Your file was successfully uploaded','success'),
				'newPrdSuc'					=>		array('Successfully added a new product, You may make changes below.','success'),
				'addedNewDistrib'			=>		array('You have successfully created a new distributor and can make changes below','success'),
				'updatedDistribSuccess'		=>		array('You have successfully edited this distributor','success'),
				'addNewDistribError'		=>		array('Unable to insert the new distributor account','error'),
				'updatedDistribError'		=>		array('Unable to insert the new distributor account','error'),
				'dplctUsr'					=>		array('The email address you have entered matches an existing account. We have added your request for a new user account to our queue, please expect contact shortly."','error'),
				'newUserFail'				=>		array('There was an error while trying to create your user account. Please try again.','error'),
				'userApproveSuccess'		=>		array('You have successfully approved this user for access. Please be sure to associate them with a distributor or manually adjust their function rights. ','success'),
				'userRefuseSuccess'			=>		array('You have successfully refused access to this user.','success'),
				'userUpdateFail'			=>		array('There was an error while trying to update this user record.','error'),
				'userDeactivateSuccess'		=>		array('You have successfully deactivated this users account. They will no longer be able to login.','success'),
				'userUserAssocSuccess'		=>		array('You have successfully updated the association for this user','success'),
				'userUserAssocFail'			=>		array('There was an error while trying to update the association for this user','error'),
				'newProfileSuccess'			=>		array('You have successfully created a new function rights profile','success'),
				'editProfileSuccess'			=>		array('You have successfully edited this function rights profile','success'),
				'profileRemoved'			=>		array('The requested profile and all associated function rights have been deleted.','warning'),
				'profileRemoveDeny'			=>		array('You may not remove any of the core profiles: [ admin ], [power user ], [ customer ], [ basic ], [ pending approval ], [ guest ]','error'),
				
			);

			//check for existing canned messages
			if(array_key_exists($message,$messages)){

				//check if canned message was used
				$this->returnMessage = $messages[$message][0];

				$this->messageType = $messages[$message][1];

				$this->messageSound = $messages[$message][1];
				
			} else {

				//message equals the submitted content
				$this->returnMessage = $message;

				$this->messageType = 'info';
			}
		} else {

			//if therte is no message set then it sets null values
			$this->messageExists = false;
			$this->returnMessage = null;
			$this->messageType = null;
		}
	}

	public function showMessages(){

		if($this->messageExists){
			return '
			<div id="page-message" class="alert alert-' . $this->messageType . '">
				<div class="close">
					<a id="hideMessage" href="#" title="close">X</a>
				</div>
				<div class="message-body">
					<p>' . $this->returnMessage . '</p>
				</div>
			</div>' . $this->messageSound($this->messageType);
		}		
	}

	public function messageSound($type){

		//messages that receive sounds
		$sounds = array(
			'invalidProduct',
			'updatedInventory',
			'addedInventory'
			);

		//checking if the sound submitted is one within the accepted sounds array
		if(in_array($_GET['msg'],$sounds)){

			return '
			<audio autoplay>
			  	<source src="horse.ogg" type="audio/ogg">
			  	<source src="' . _ROOT_ . '/assets/audio/' . $type . '.mp3" type="audio/mpeg">
				Your browser does not support the audio element.
			</audio>';
		}
	}
}
?>