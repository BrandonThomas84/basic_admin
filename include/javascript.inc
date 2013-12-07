<?php /* FILEVERSION: v1.0.1b */ ?>
<?php /* FOOTER JAVASCRIPT INCLUDE */ ?>
<script>
	// Options http://bxslider.com/options
	$(document).ready(function(){
	  $('.bxslider').bxSlider({
	  		slideSelector: 'div.slide',
		    slideMargin: 0,
		    captions: true,
		    startSlide: 1,
		    speed: 700,
		    auto: true,
		    pause: 5000,
		    autoHover: true,
		    slideWidth: 1000,
		    randomStart: true
  		});
	});
</script>
<script>
	//closes the messages box
	$('#hideMessage').click( function() {
		$('#page-message').addClass("hidden")
	});
</script>
<script>
	//assures the page message will not display on hover after 10 seconds
	$(document).ready( function() {
		setTimeout( 
			function() {
				$('#page-message').addClass("hidden")
			},10000
		);		
	});	
</script>
<script>
	//enables movement of admin tabs
	var left = parseInt($('#admin-tabs > ul.nav').css('left'));

	$('#tab-left-button').click( function(){
			
			left = left-100;

			$('#admin-tabs > ul.nav').css({
				'position': 'relative',
				'left' : left+'px'
			});
		
	})
	$('#tab-right-button').click( function(){
			
			left = left+100;

			$('#admin-tabs > ul.nav').css({
				'position': 'relative',
				'left' : left+'px'
			});
		
	})
</script>
<script>
	//enables pasting into the inventory input from the scanner
	$(function(){
	    $("#inventoryScan").bind('paste input', function(e) {
	        this.form.submit();
	    });
	});
</script>
<script>
	//form validation for the product insert form
	$('#productFormSubmit').click(function () {
		$('#description').val(
				tinyMCE.activeEditor.getContent()
		);
		
		var x=document.forms["productManager"]["mpn"].value;
		if (x==null || x=="")
		  {
		  alert("MPN must be filled out");
		  return false;
		  }
	
		var x=document.forms["productManager"]["manufacturer"].value;
		if (x==null || x=="")
		  {
		  alert("Manufacturer must be filled out");
		  return false;
		  }

		var x=document.forms["productManager"]["qty_on_hand"].value;
		if (x==null || x=="")
		  {
		  alert("Inventory Available must be filled out");
		  return false;
		  }
	
		var x=document.forms["productManager"]["cost"].value;
		if (x==null || x=="")
		  {
		  alert("Cost must be filled out");
		  return false;
		  }
	
		var x=document.forms["productManager"]["dealer_price"].value;
		if (x==null || x=="")
		  {
		  alert("Dealer Price must be filled out");
		  return false;
		  }
	
		var x=document.forms["productManager"]["map_price"].value;
		if (x==null || x=="")
		  {
		  alert("Map Price must be filled out");
		  return false;
		  }
	
		var x=document.forms["productManager"]["prev_order"].value;
		if (x==null || x=="")
		  {
		  alert("Original Order Date must be filled out");
		  return false;
		  }
	
		var x=document.forms["productManager"]["next_order"].value;
		if (x==null || x=="")
		  {
		  alert("Next Order Date must be filled out");
		  return false;
		  }
	
		var x=document.forms["productManager"]["title"].value;
		if (x==null || x=="")
		  {
		  alert("Product Title must be filled out");
		  return false;
		  }
		

		$('#productEditor').submit();
	});
</script>
<script>
	//calendar javascript for date selectors
    $(window).load(function()
    {
        $("input[id*='mydate']").glDatePicker({
		    showAlways: false,
		    allowMonthSelect: true,
		    allowYearSelect: true,
		    prevArrow: '<',
		    nextArrow: '>',
		    cssName: 'flatwhite',
		    selectableDOW: [1, 2, 3, 4, 5]
		});
    });
</script>
<?php echo login::formJavascript(); ?>
