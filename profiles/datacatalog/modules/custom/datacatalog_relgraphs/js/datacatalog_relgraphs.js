// JavaScript Document
(function($) {
  $(document).ready(function () {  
    $("#searchA").autocomplete({
      source: function( request, response ) {
	    rel_type=$("#rel_type").val();	
		if (rel_type=="p_ds" || rel_type=="people_people") {
		  acr_url="/load-members";
		}
		else if (rel_type=="bp_ds") {
		  acr_url="/check-if-busns-prcs-nds-fnd";
		}
		else if (rel_type=="tg_ds" || rel_type=="tg_tg" || rel_type=="tag_people") {
		  acr_url="/check-if-tgs-fnd";
		}
        $.ajax({
		  url: acr_url,
          dataType: "json",
		  data: "srch="+request.term,
          success: function( data ) {
            if (data.length == 0) {
              data.push({
                label: "",
                value: "No results found"
              });
              $('#ui-id-1').addClass('noresults');
            }
            else{
              if ($("#ui-id-1").hasClass("noresults")) {
                $("#ui-id-1").removeClass("noresults");
              }
            }
            response($.map( data, function( item ) {
              return {
                label: item.type,
                value: item.value
              }
            }));
          }
        });
      },
      minLength: 1,
      select: function( e, ui ) {
        $("input[id='hideVal']").val(ui.item.value);
      },
      open: function( event, ui ) {
        //change width to responsive
        var widthInput = $("#searchA").width();
        $("#ui-id-1").width(widthInput + 11);
        var firstElement = $(this).data("ui-autocomplete").menu.element[0].children[0], inpt = $('#searchA'), original = inpt.val(),
		firstElementText = $(firstElement).text();
        var myarr = firstElementText.split("(");
        if (typeof myarr[0] != 'undefined') {
          var val = myarr[0];
          if (val != 'No results found.') {
            $("input[id='hideVal']").val(val);
          }
        }
        if (typeof myarr[1] != 'undefined') {
          var myarr2 = myarr[1].split(")");
        }
        if (typeof myarr2 != 'undefined') {
          var type = myarr2[0];
          $("#searchA").attr("name", type);
        }
      },
      autoFocus: true
    }).data("ui-autocomplete")._renderItem = function( ul, item ) {
      if (item.label == "No results found") {
        return $( "<li>" ).append( "<a><span class='sq-baseline'>" + item.value + "</span></a>").appendTo( ul );
      } 
	  else {
        return $( "<li>" ).append( "<a><span class='sq-baseline'>" + item.value + "</span></a>" ).appendTo( ul );
      }
    };
	
    $('#submit').click(function () {
      var char = $("#searchForm #searchA").val().replace(/ /g,'').length;
      if (char < 3) {
        $("div.search-help-block p.search-help").text("Please enter atleast 3 characters.");
        $("div.search-help-block").fadeIn();
        return false;
      }
      if ($("#ui-id-1").hasClass("noresults")) {
        $("div.search-help-block p.search-help").text("No result found for generating graph, Please change your keyword.");
        $("div.search-help-block").fadeIn();
        return false;
      }
      var myEl = $('#hideVal').val();
      $("input[id='searchA']").val(myEl);
      $("#searchForm").submit();
   })

   $("a.searchclose").click(function(){
     $("div.search-help-block").fadeOut();
   });
	
	output=$(".graph_json").text();
    if (output!="" && output!="[]") {
	  output = jQuery.parseJSON(output);
	  var data = output;
      var containerId = "#graphContainer";
      kb = new buildGraph(data, containerId, 0);
      jQuery(".fullscreen_icon").on("click", function () {
        if (kb.isFullscreen()) {
          kb.exitFullscreen();
        }
		else {
          kb.enterFullscreen();
        }
      });
    }

    //add highlight to nodes
      jQuery('.sidebar.sidebar-graph li').on('mouseover', function (e) {
        kb.highlightNode(jQuery(this).attr('data'), true);
      });
      jQuery('.sidebar.sidebar-graph li').on('mouseout', function(e) {
        kb.highlightNode(jQuery(this).attr('data'), false);
      });
	  
	  jQuery('#loadMore').click(function () {
        jQuery('#listUlD li.hideLi').toggle();
        var lable = 'Load more';
        if (jQuery("#loadMore").text() == 'Load more') {
          lable = 'Show less';
        }
        jQuery("#loadMore").text(lable);
      });
  });
})(jQuery);
