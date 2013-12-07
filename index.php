<?php /* FILEVERSION: v1.0.1b */ ?>
<?php require_once('include' . DIRECTORY_SEPARATOR . 'settings.inc'); ?>
<?php require_once('include' . DIRECTORY_SEPARATOR . 'functions.php'); ?>
<?php getClasses(); ?>
<?php

//instantiating necessary classes
$login = new login(false); //false indicating not a secure connection for testing purposes
$nav = new navigation;
$page = new adminPage;
$bcurmb = new breadcrumbs;

?>
<html>
<head>
  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">

  <title>Basic Admin Panel</title>
  <meta name="description" content="Basic Admin Panel">
  <meta name="Author" content="Brandon Thomas">
  <!-- © 2013 by Perspektive Designs -->

  <!-- START STYLE -->
  <link rel="stylesheet" href="style/bootstrap.css">
  <link rel="stylesheet" href="style/responsive.css">
  <link rel="stylesheet" href="style/admin.style.css">
  <!-- bxSlider CSS file -->
  <link rel="stylesheet" href="style/glDatePicker.flatwhite.css">
  <!-- date picker style -->
  <link rel="stylesheet" href="style/bxslider.style.css">
  <!-- END STYLE -->

  <!-- START HEAD JS -->
  <script src="//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>
  <script src="js/bootstrap.min.js"></script>
  <!-- bxSlider Javascript file -->
  <script src="js/bxslider.js"></script>
  <!-- date picker Javascript file -->
  <script src="js/glDatePicker.min.js"></script>
  <!--HTML EDITOR JS -->
  <script type="text/javascript" src="js/tinymce/tinymce.min.js"></script>
	<script type="text/javascript">
		tinymce.init({
		    selector: "#htmlTextArea",
		    plugins: "spellchecker preview save",
		    save_enablewhendirty: true,
		    browser_spellcheck: true,
    		toolbar: "bold italic underline alignleft aligncenter alignright alignjustify  bullist numlist outdent indent undo redo styleselect fontselect fontsizeselect save",
		 });
	</script>
  <!-- END HEAD JS -->
</head>

<body>
	<header>
		<?php
			//site navigation 
			echo $nav->displayNav(); 
			echo $login->loginForm;
		?>
	</header>

	<div class="main-body">
		<div class="body-container">

			<?php 

				//checks to see if the requested was a rewritten url, if not it insert it into the db
				$needle = substr($_SERVER['REQUEST_URI'],0,strpos($_SERVER['REQUEST_URI'],'?'));
				if($needle == $_SERVER['PHP_SELF']){

					global $mysqli;
					$stmt = $mysqli->query('INSERT INTO `' . _DB_NAME_ . '`.`' . _DB_PREFIX_ . 'url_rewrite` (`url`) VALUES (\'' . $_SERVER['REQUEST_URI'] . '\')');
				}
				
				if($page->checkSession()){

					echo $page->title('Management Console');
					echo $bcurmb->showCrumbs();
					echo $page->retrieveMessages();
					echo $page->adminNavigation(); 
					echo $page->adminContent();		

				} else {
					echo $page->retrieveMessages();
					echo $page->title('Welcome - Please Login');
					
				}
			?>
		
		</div> <!-- END BODY CONTAINER -->
	</div> <!-- END MAIN BODY -->
	<div class="clearfix spacer"></div>
	<footer>
		<?php 
			//adding pagify navigation to needed pages
			echo navigation::pagify(inventory::countInventory()); 
			
			//require javascript
			require_once( __DIR__ .'/include/javascript.inc');

			//include the session renew, options ([time out], [warning]{optional})
			echo sessionRenew(600,10);
		?>
	</footer>
	<?php
		//displays php info 
		/*
		if($_SERVER['REMOTE_ADDR'] == $_SERVER['SERVER_ADDR']){
			echo '<div class="internalOnly">' . phpinfo() . '</div>';
		}
		*/
	?>
</body>
</html>