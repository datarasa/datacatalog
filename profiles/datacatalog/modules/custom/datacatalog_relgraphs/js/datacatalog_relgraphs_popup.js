// JavaScript Document
(function($) {
  $(document).ready(function () {  
    output = $(".graph_json").text();
    if (output!="" && output!="[]") {
      output = jQuery.parseJSON(output);
	  var data = output;
      var containerId = "body.page-user #graphContainer";
      kb = new buildGraph(data, containerId, 1);
      jQuery(".fullscreen_icon").on("click", function () {
        if (kb.isFullscreen()){
          kb.exitFullscreen();
        }
	    else{
          kb.enterFullscreen();
        }
      });
   }
   $("body.page-user #ng-lightbox .fullscreen_icon" ).on( "click", function () {
     $("body.page-user .lightbox__content").toggleClass("lightbox__content-fullscreen");
	 jQuery("svg.svg-graph").width('100%');
     jQuery("svg.svg-graph").height('100%');
   });	 
	
    //add highlight to nodes
    jQuery('.sidebar li').on('mouseover', function(e){
      kb.highlightNode(jQuery(this).attr('data'), true);
    });
    jQuery('.sidebar li').on('mouseout', function(e){
      kb.highlightNode(jQuery(this).attr('data'), false);
    });
    jQuery('#loadMore').click(function () {
      jQuery('#listUlD li.hideLi').toggle();
      var lable = 'Load more';
      if (jQuery("#loadMore").text() == 'Load more') {
        lable = 'Show Less';
      }
      jQuery("#loadMore").text(lable);
    });
	  
    $("a.fncy-lightbox").fancybox({
      maxWidth	: 800,
      maxHeight	: 600,
      fitToView	: false,
      width		: '70%',
      height		: '70%',
      autoSize	: false,
      closeClick	: false,
      openEffect	: 'none',
      closeEffect	: 'none'
    });
  });
})(jQuery);