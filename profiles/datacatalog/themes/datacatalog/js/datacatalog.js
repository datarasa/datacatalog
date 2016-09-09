(function($) {
  $(document).ready(function(){
    $('.view-Communities.view-display-id-page .view-content').pinterest_grid({
      no_columns: 3,
      padding_x: 5,
      padding_y: 5,
      margin_bottom: 50,
      single_column_breakpoint: 700
    });
	$('.view-communities-es.view-display-id-page .view-content').pinterest_grid({
      no_columns: 3,
      padding_x: 6,
      padding_y: 6,
      margin_bottom: 50,
      single_column_breakpoint: 700
    });
	$('.view-my-communities-es.view-display-id-page_1 .view-content').pinterest_grid({
      no_columns: 3,
      padding_x: 6,
      padding_y: 6,
      margin_bottom: 50, 
      single_column_breakpoint: 700
    });

    $( ".mem_lnk" ).each(function( index ) {
      if($(this).text() == "" || $(".mem_lnk").text().length == 5) {
        $(this).remove();
      }
    });
    function getRows(selector) {
      var height = $(selector).height();
      var line_height = $(selector).css('line-height');
      line_height = parseFloat(line_height)
      var rows = height / line_height;
      return Math.round(rows);
    }
	
    $(document).on("click",".showmore-button",function(e){  
      $(this).siblings(".rest").toggle();
	if($(this).text()=="show more") {
	  $(this).text("show less");
	}
        else {
	  $(this).text("show more");
	}
    });
	
    
	$("body.page-user .view .item-list ul.pager li a").addClass('load-more');	
	/*$( ".load-more" ).on( "click", function(event) {
		$('.view-content .odd').addClass('abs');
		$('.view-content .even').addClass('abs');
		//$('.view-user-profile-wiki-tab-es table:not(:first-of-type) .del-wiki').addClass('del-wiki2');
	});*/
    $('[data-toggle="tooltip"]').tooltip();  
    
    if($(".tree li.active-li").parents(".cmnty").length) { 
      cmnty_title = $(".tree li.active-li").parents(".cmnty").children().find("div.slctd > a").html();
      cmnty_href = $(".tree li.active-li").parents(".cmnty").children().find("div.slctd > a").attr("href");
      $(".cstm_brdcrmbs ul li:nth-child(2)").after('<li><a href="'+cmnty_href+'">'+cmnty_title+'</a></li>'); 
    }
	
    $("body.not-logged-in.page-user #main").prepend('<div class="col-md-12 p-0"><div id="logo"> <a rel="home" title="Home" href="/"> <img alt="Home" src="http://datacatalog-dev.datarasa.org/sites/default/files/login_logo.png" class="logo_colpsd"></a> </div> </div>');
		  
    $('.menu-toggler').click(function () {
      $('.row-offcanvas').toggleClass('nav_colpsd nav_uncolpsd');
        //$("div.main-area").toggleClass('nav-width-compnstr');
	$(".row-offcanvas-left.nav_uncolpsd #block-menu-block-3 .menu-block-wrapper ul > li ul,.row-offcanvas-left.nav_uncolpsd #dataItemsTree > ul.tree ul").hide();
	$(".row-offcanvas-left.nav_uncolpsd #sidebar-first #block-menu-block-3 a.reltnships").removeClass("slctd");
	if($(".row-offcanvas-left #sidebar-first #block-menu-block-3 a.reltnships i").hasClass('glyphicon-menu-down')) {
	  $(".row-offcanvas-left #sidebar-first #block-menu-block-3 a.reltnships i").removeClass('glyphicon-menu-down');
	  $(".row-offcanvas-left #sidebar-first #block-menu-block-3 a.reltnships i").addClass('glyphicon-menu-left');
	}
	if($(".row-offcanvas-left.nav_uncolpsd .tree i").hasClass('glyphicon-menu-down')) {
	  $(".row-offcanvas-left.nav_uncolpsd .tree div").removeClass("slctd");
	  $(".row-offcanvas-left.nav_uncolpsd .tree i").removeClass('glyphicon-menu-down');
	  $(".row-offcanvas-left.nav_uncolpsd .tree i").addClass('glyphicon-menu-left');
	}
	$(".row-offcanvas-left.nav_uncolpsd .tree li").removeClass("open");
	$(".row-offcanvas-left.nav_uncolpsd .tree div").removeClass("slctd");
    });
	
    $("#edit-field-metadata-fields").before("<div id='custom-meta-lable'><label>Metadata fields</label></div>");
    
    if(!$(".node-type-source .field-type-field-collection.field-label-above .field-items .field-item").length) {
      $(".field-type-field-collection.field-label-above .field-label").hide();
    }
    $("body.page-node-add-group .page-title").text('Create Community');
    $("body.page-node-edit.node-type-group .page-title em").text('Edit Community');
	
	//
    url=window.location.href;
    s_grph_pg = url.indexOf("relationship"); 
    if(s_grph_pg!=-1) {
      $("#block-menu-block-3 a.reltnships").addClass("slctd");
      $("#block-menu-block-3 a.reltnships").append('<i class="indicator glyphicon glyphicon-menu-down"></i>');	
      $("#block-menu-block-3 ul.menu li ul").show();
    } else {
      $("#block-menu-block-3 a.reltnships").append('<i class="indicator glyphicon glyphicon-menu-left"></i>');	
    }
    $("#block-menu-block-3 a.reltnships").removeClass("active").removeAttr("href").css({"cursor":"pointer"});
	
    $(".row-offcanvas-left.nav_colpsd ul.menu li a.reltnships").click(function(){
      $(this).siblings("ul.menu").toggle();
      $(this).toggleClass("slctd");
      $(this).children("i").toggleClass( 'glyphicon-menu-left glyphicon-menu-down' );
    });
    $(document).on('mouseenter','.row-offcanvas-left.nav_uncolpsd #block-menu-block-3 .menu-block-wrapper ul > li', function (event) {
      $(this).children("ul.menu").stop( true, true ).fadeToggle();
      $(this).children("a.reltnships").toggleClass("slctd");
      $(this).children().find("i").toggleClass( 'glyphicon-menu-left glyphicon-menu-right' );
    }).on('mouseleave','.row-offcanvas-left.nav_uncolpsd #block-menu-block-3 .menu-block-wrapper ul > li',  function(){
      $(this).children("ul.menu").stop( true, true ).fadeToggle();
      $(this).children("a.reltnships").toggleClass("slctd");
      $(this).children().find("i").toggleClass( 'glyphicon-menu-left glyphicon-menu-right' );
    });	
	
    $(document).on('mouseenter','.row-offcanvas-left.nav_uncolpsd #dataItemsTree > ul.tree > li', function (event) {
      $(this).children("ul").stop( true, true ).fadeToggle();
      $(this).toggleClass("slctd");
      $(this).children().find("a").toggleClass("slctd");
      $(this).children().find("i").toggleClass( 'glyphicon-menu-left glyphicon-menu-right' );
    }).on('mouseleave','.row-offcanvas-left.nav_uncolpsd #dataItemsTree > ul.tree > li',  function(){
      $(this).children("ul").stop( true, true ).fadeToggle();
      $(this).toggleClass("slctd");
      $(this).children().find("a").toggleClass("slctd");
      $(this).children().find("i").toggleClass( 'glyphicon-menu-left glyphicon-menu-right' );
    });		

    $("#edit-field-csv-file-und-0-upload-button").attr('value', 'Import');


    $('body.node-type-source .panels-flexible-region-new-center .inner').wrapAll( '<div class="src-clps" />');
	
    $('body.node-type-source .panels-flexible-region-new-center .src-clps').showMore({
      minheight: 59,
      animationspeed: 250
    });
    $('#showmore-').addClass('more');

    $('body.node-type-group #block-system-main article').showMore({
      minheight: 59,
      animationspeed: 250
    });
    if($('body.node-type-group #block-system-main article .field-name-body,body.node-type-source #block-system-main .src-clps .field-name-body').length>0) {
      body_rows = getRows('body.node-type-group #block-system-main article .field-name-body,body.node-type-source #block-system-main .src-clps .field-name-body');
	if(body_rows == 1) {
	  rd_mr_cls = "rd_mr_tp_mrg_"+body_rows;
	}
	else if(body_rows == 2) {
	  rd_mr_cls = "rd_mr_tp_mrg_"+body_rows;
	  $("body.node-type-group .field-name-field-owners").addClass("ownr_mrg_btm");
	  $("body.node-type-source .showmore-cont > .src-clps .field-name-og-group-ref").addClass("cmnty_mrg_btm");
	}
	else if(body_rows >= 3) {
	  rd_mr_cls = "rd_mr_tp_mrg_3";
	} 
      $("body.node-type-group .showmore-button,body.node-type-source .showmore-button").addClass(rd_mr_cls);
    }

    if($("ul#contextual-tabs .dropdown-menu").has("li").length == 0) {
      $("ul#contextual-tabs").css("display","none");
      $(".node-type-source #main .right-pane-custom-button").css("margin-bottom","5px");
    };
	
    $(".page-node-revisions .field-name-field-metadata-fields table").removeClass("field-collection-view-final");
    $(".page-node-revisions .field-name-field-metadata-fields table").removeClass("sticky-enabled");
    $(".page-node-revisions .field-name-field-metadata-fields table").addClass("views-table");
	
    $(".ng-lightbox").on("contextmenu",function(e){
      return false;
    });
    $("body.node-type-group .view-community-wiki .view-content").addClass("wiki-links");
    $("body.node-type-group .view-community-wiki .view-footer .view-content").removeClass("wiki-links");
	$("body.node-type-group .view-community-wiki-es .view-content").addClass("wiki-links");
    $("body.node-type-group .view-community-wiki-es .view-footer .view-content").removeClass("wiki-links");
    $('.wiki-links .wiki-list').wrapAll( '<div class="wiki-wrapper" />');
  //$('.wiki-links').prepend('<div class="links-header">Wiki Pages</div>');
    $('body.page-catalog .view-Communities .view-filters .views-exposed-widgets').prepend('<div class="browse-header">Browse By:</div>');
    $('.mobi-header .block-superfish ul li a.menuparent').append('<span class="sf-sub-indicator sub-ind"> »</span>'); 
    $('.wiki-list li div span a').click(function(e) {
      $('.wiki-list li div span a.active').removeClass('active'); 
      $(this).addClass('active');
      $("#jquery_ajax_load_target").prepend('<br>');
      e.preventDefault();
    });
    $('body.page-relationship-console .sidebar-graph .form-group h2 a').addClass('exp-link');
    $('body.page-relationship-console .sidebar-graph .form-group h2 a').click(function(e) {
      $('body.page-relationship-console .sidebar-graph .form-group h2 a').removeClass('expended');
      $(this).addClass('expended');
      e.preventDefault();
    });
    $('body.page-relationship-console .sidebar-graph .form-group h2 a').wrap( '<span class="fieldset-legend" />'); 
	  
    var XX = 450;
    $('.bdy .init').filter(function() {
      return $(this).text().length < XX;
    }).addClass('short');
    $(".short").siblings("div.toggler").css( "display", "none" );
    
	var YY = 160; 
    $('body.node-type-source .src-clps .field-name-body .field-item').filter(function() {
      return $(this).text().length < YY;
    }).parents('.src-clps').addClass('short-cont');
    $(".short-cont").siblings("div.showmore-button").css( "display", "none" );
    $('.pager-load-more a').click(function(e) { 
      $('.toggler').addClass('more')
    });
	
    $('body.not-logged-in #messages-console .col-md-12').addClass('welcome-notice');
	/*$('.add-src-comm').prepend("<span class='glyphicon glyphicon-plus'></span>"); 
	$('.import-src-comm').prepend("<span class='glyphicon glyphicon-import'></span>");
	$('.add-bus-pro').prepend("<span class='glyphicon glyphicon-plus'></span>");
	$('.add-wiki-page').prepend("<span class='glyphicon glyphicon-plus'></span>");*/
	
	$('view-filters .form-submit').on("click", function(event){
	});
	$('.node-form .form-actions input[type="submit"]').focusout(function () {
	  if ($(".node-form .form-actions input[type='submit']").val() == 'Delete') {
	    $(".node-form .form-actions input[type='submit']").addClass('del');
	  } 
	});
	//$('form#node-delete-confirm ').parents('#modal-content').addClass('delete-confirm'); 
    
	
	/*$( ".del-wiki" ).on( "click", function(event) {
	  $('body.page-user').removeClass('full-ng'); 
	  $('.ctools-modal-content').addClass('del-conf');
	});*/
	$('.modal-header a.close').on( "click", function(event) {
	  $('.ctools-modal-content').removeClass('del-conf');
	  /*$('body').removeClass('modal-open')*/;
	});
	$('.ctools-use-modal').on("click", function(event) {
		/*$("body").addClass("modal-open");*/
	});
	$('#contextual-tabs li a').on("contextmenu",function(e){
        //alert('right click disabled');
        return false;
    });
	if ($("div.showmore-button").length){ 
	     $('.showmore-cont').addClass('long');
	 } 
	else {
		$('.showmore-cont').addClass('short');
	}
	$("div.ctools-modal-content.wiki-edit .modal-title em").addClass("wiki");
	$('#block-user-login div.form-item-name').append('<div class="description">Enter your Data Catalog username.</div>');
	$('#block-user-login div.form-item-pass').append('<div class="description">Enter the password that accompanies your username.</div>'); 

    function isEmpty( el ){
      return !$.trim(el.html())
    }
    if (isEmpty($('#quicktabs-tabpage-community_page-3'))) {
      $('#quicktabs-tabpage-community_page-3').append('<div class="view-empty"><p>No results found</p></div>');
    }
	$('body.node-type-source .view-empty').parents('.view-metadata-fields-view').addClass('empty-meta');
	
  });	// document ready close
  Drupal.behaviors.datacatalog_gen = {
    attach: function (context, settings) {
      $("#source-node-form .form-actions .form-submit:first-child").addClass("src-submit");
      $("#source-node-form #sourceid .field-name-field-business-process .ief-entity-table").addClass("bus-table");
      $("#source-node-form #sourceid #edit-field-business-process-und-actions-ief-add").addClass("add-bus-pro");
      $("#source-node-form #sourceid #edit-field-business-process-und-actions-ief-add-existing").addClass("add-bus-pro");
	  $(".del-comm.ctools-use-modal").removeClass("ctools-use-modal"); 
/*      $(".src-submit").on( "click", function(event) {
        var isValid = true;
        var $myDiv = $('.bus-table');
        if ( !$myDiv.length ){
          isValid = false;
          $('#fillIn').remove();
          if (!($('#fillIn').length)){
            $('#source-node-form #edit-field-business-process-und-actions').prepend("<p id='fillIn'>Business Process field is required</p>");
          }
          $("#source-node-form").submit(function(e){
            if ( $('#fillIn').length==0 ){
              $('#source-node-form #edit-field-business-process-und-form .fieldset-wrapper').prepend("<p id='fillIn'>Business Process field is required, Please click on 'Add Business Process' button.</p>");
		    }
            e.preventDefault();
          });
        }
        else {
          $('#fillIn').remove();
          isValid = true;
          $('#source-node-form').submit( function(e){
            e.preventDefault();
            $(this).unbind('submit').submit()
          });
        }
      });*/
      //Adding class to submit button
      $("#ng-lightbox .node-form .form-actions .form-submit:first-child").addClass("submit-btn");
      $( ".submit-btn" ).on( "click", function(event) {
        $('div.lightbox__overlay ').addClass('consistent');
      });
      $('body.page-catalog .view-Communities.jquery-once-3-processed .views-row .pd-wrpr .colpsd').showMore({
        minheight: 39,
        animationspeed: 250
      });
    
      $('.view-my-communities.view-display-id-page .view-content').pinterest_grid({
        no_columns: 3,
        padding_x: 5,
        padding_y: 5,
        margin_bottom: 50,
        single_column_breakpoint: 700
      });
	  $( ".edit-src" ).on( "click", function(event) {
        //alert( "Edit now?" );  // jQuery 1.7+
        //event.preventDefault();
        //$(".lightbox__content").css("width", "95%");
        $('body.page-user').addClass('full-ng');
      });
	  $( ".edit-bus-pro" ).on( "click", function(event) {
	    $('body.page-user').addClass('full-ng');
	  });
	  $( ".edit-comm" ).on( "click", function(event) {
	    $('body.page-user').addClass('full-ng');
	  });
	  $( ".edit-wiki" ).on( "click", function(event) {
	    $('body.page-user').addClass('full-ng');
	    $('.ctools-modal-content').addClass('wiki-edit');
	  });
      $( "#edit-btn" ).on( "click", function(event) {
        $('body.page-user').removeClass('full-ng');
      });	
      $( "#email-btn" ).on( "click", function(event) { 
        $('body.page-user').removeClass('full-ng');
      });	
      $(".lightbox__header").click(function() {
        $('body.page-user').removeClass('full-ng');
      });
	  $(".modal-header a").click(function(){
	    $('body.page-user').removeClass('full-ng');
	  });
	  $( ".del-comm" ).on( "click", function(event) {
	    $('body.page-user').removeClass('full-ng'); 
	    $('.ctools-modal-content').addClass('del-conf');
	    $('.ctools-modal-content').addClass('del-conf-comm');
	  });
	  $( ".del-src" ).on( "click", function(event) {
	    $('body.page-user').removeClass('full-ng'); 
	    $('.ctools-modal-content').addClass('del-conf');
	  });
	  $( ".del-bus-pro" ).on( "click", function(event) {
	    $('body.page-user').removeClass('full-ng'); 
	    $('.ctools-modal-content').addClass('del-conf');
	  });
	  $( ".del-wiki" ).on( "click", function(event) {
	    $('body.page-user').removeClass('full-ng'); 
	    $('.ctools-modal-content').addClass('del-conf');
	  });
	  $( ".delete-src-link" ).on( "click", function(event) {
		$('body.page-user').removeClass('full-ng');   
		$('#modalContent').addClass('half-modal');  
	    $('.ctools-modal-content').addClass('del-conf');
	  });
	  $(".database-src-comm").on("click", function(event) {
        $('.ctools-modal-content').addClass('db-conn-wiz');
	  });
	  
	  $("div.modal-header #modal-title").text(function(index, currentText) {
         return currentText.substr(0, 70);
      }); 

      
      /*Communities*/ 
	  $("body.page-communities .view-display-id-page .view-content .odd").css("position","absolute");	
      $("body.page-communities .view-display-id-page .view-content .even").css("position","absolute");
      $("body.page-my-communities .view-display-id-page .view-content .odd").css("position","absolute");	
      $("body.page-my-communities .view-display-id-page .view-content .even").css("position","absolute");
	  $("body.page-my-communities .view-my-communities-es.view-display-id-page_1 .view-content .odd").css("position","absolute");	
      $("body.page-my-communities .view-my-communities-es.view-display-id-page_1 .view-content .even").css("position","absolute");
	  /*end communities*/

    }
  };	
  $(document).ready(function(){
    $(window).ready( function () {
      if ($(window).width() <= 1024) {
        $(".nav_colpsd").removeClass("nav_colpsd nav_uncolpsd").addClass("resp");
        $(".block-superfish .sf-menu.sf-style-blue li.menuparent ul").addClass("sf-sub");
          
        $.fn.clickToggle = function(func1, func2) {
           var funcs = [func1, func2];
           this.data('toggleclicked', 0);
           this.click(function() {
             var data = $(this).data();
             var tc = data.toggleclicked;
             $.proxy(funcs[tc], this)();
             data.toggleclicked = (tc + 1) % 2;
           });
           return this;
        };
	
        $('.menu-toggler').clickToggle(function() {
          $('.row-offcanvas').removeClass('resp');
          $('.row-offcanvas').removeClass('nav_uncolpsd');
          $('.left-col').addClass('navbar-collapse collapse in');
          $('.mobi-header .block-superfish').addClass('navbar-collapse collapse in');
          $(".mobi-header .block-superfish").css("display","block");
          $("#superfish-1").slideDown(200);
          $("#sidebar-first").slideDown(200);
        }, function() {
          $('.row-offcanvas').addClass('resp');
          $('.left-col').removeClass('navbar-collapse collapse in');
          $('.mobi-header .block-superfish').removeClass('navbar-collapse collapse in');
          $(".mobi-header .block-superfish").css("display","none");
          $("#superfish-1").slideUp("slow");
          $("#sidebar-first").slideUp("slow");
        });
        $('.dropdown-toggle').clickToggle(function(){
          $('.navbar-user').addClass('open');
          $('li.btn-group').addClass('open');
        }, function(){
          $('.navbar-user').removeClass('open');
          $('li.btn-group').removeClass('open');
        });
        $('.sub-ind').clickToggle(function(){
          $('.sf-sub').addClass('open');
        }, function(){
          $('.sf-sub').removeClass('open');
        });
	     
      }
    });
  });
  
  Drupal.behaviors.ajaxComments = {
    attach: function(context, settings) {
    // @hack - comments arent being rendered inside of this
      $('.ajax-comment-wrapper').appendTo('.comment-wrap');
    // Responds to submission of new comment by the user.
      if ($(context).hasClass('ajax-comment-wrapper')) {
        commentNumber = $(context).attr("id").split('-');
        // Scroll to the comment reply inserted by ajax_command.
        ajaxCommentsScrollReply(commentNumber[2])
      }
      // Scroll to the comment reply form when reply is clicked.
      $("a.ajax-comment-reply:not(clicked)").click(function() {
        commentNumber = $(this).attr("id").split('-');
        //ajaxCommentsScrollForm(commentNumber[1]);
	    ajaxCommentsScrollReply(commentNumber[1]);
        // Don't let people reply over and over.
        $(this).hide();
       });
       // Hide comment form if cancel is clicked.
      $("a.ajax-comments-reply-cancel").click(function(e) {
        commentForm = $(this).attr("href");
        // Hide comment form.
        $(commentForm).hide();
        commentNumber = $(this).attr("id").split('-');
        // This needs to be unbound because the ajax_command callback is still
        // attached to it. We want to show the form that is already hidden
        // instead of calling for a new one.
        $('a#reply-' + commentNumber[3]).show();
      });
    }
  };
  /**
   * Scrolls user to comment reply form.
   */
  function ajaxCommentsScrollForm(commentNumber) {
    pos = $('#comment-wrapper-' + commentNumber).offset();
    height = propHelper($('#comment-wrapper-' + commentNumber + ' .topicdetails-dl>.topicdetails-dd>.discussbox>.inner'), "scrollHeight");
    // Scroll to comment reply form.

    $('html, body').animate({ scrollTop: pos.top + height}, 'fast');
  }
  /**
   * Scrolls user to comment that has been added to page.
   */
  function ajaxCommentsScrollReply(commentNumber) {
    formSize = propHelper($('.comment-form'), "scrollHeight");
    pos = $('#comment-wrapper-' + commentNumber).offset();
    // Scroll to comment reply.
    $('html, body').animate({ scrollTop: pos.top - formSize}, 'slow');
  }
  /**
   * Helper function to retrieve object properties.
   *
   * Works with jquery below and above version 1.6
   *
   */
  function propHelper(e, p) {
    if ($.isFunction($.prop)) {
      return e.prop(p);
    }
    else {
      return e.attr(p);
    }
  } 
})(jQuery);		// (function($) close
