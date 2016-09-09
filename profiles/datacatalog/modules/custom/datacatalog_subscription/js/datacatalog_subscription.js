(function($) {
  $(document).ready(function (){
    $( '.mem_lnk' ).on( 'click', 'a.og_custom', function () {
      var slctr = $(this);
      var data = slctr.attr('data').split('_');	
      var action = data[0];
      var gid = data[1];
      $.ajax({
        type: "POST",
        url: "/og_cstm_subscrptn",
        data: {action: action, gid: gid}, 
        success: function(res){
          if(res == 'subscribe') {
            slctr.parent().html('<span id="pndng_aprvl">Pending request...</span>');
          }else if(res == 'delete') {
			if( $(".view-group-content-es .view-header").length > 0 ) {
			  $(".view-group-content-es .view-header").html('<div class="alert alert-info" id="subscribe-community-msg"><strong>Info!</strong> Please subscribe in the community to add source.</div>');	  
			}
            slctr.parent().html('<a class="og_custom" style="cursor:pointer;" data="subscribe_'+gid+'">Subscribe</a>');
          }
        }
      }); 
    });  
	 
    $( '.mem_lnk' ).on( 'click', 'a.node_custom,a.node_custom_src_pg', function () {  
      var slctr = $(this);
	  slctr_class = slctr.attr('class');
      if(slctr_class == 'node_custom_src_pg') {
	    unsub_btn = 'Unsubscribe';
	    sub_btn = 'Subscribe';
	  }else {
	    unsub_btn = '<img alt="Subscribe" title="Unsubscribe" src="/sites/all/themes/datacatalog/images/subscribe.png">';
	    sub_btn = '<img alt="Unsubscribe" title="Subscribe" src="/sites/all/themes/datacatalog/images/subscribe-new.png">';
	  }
	  var data = slctr.attr('data').split('_');
      var action = data[0];
      var nid = data[1];
      slctr.removeClass('node_custom');
      $.ajax({
        type: "POST",
        url: "/nd_cstm_subscrptn",
        data: {action: action, nid: nid}, 
        success: function(res){
          if(res == 'sub') {
            slctr.parent().html('<a class="'+slctr_class+'" style="cursor:pointer;" data="unsub_'+nid+'">'+unsub_btn+'</a>');
          }else if(res == 'unsub') {
            slctr.parent().html('<a class="'+slctr_class+'" style="cursor:pointer;" data="sub_'+nid+'">'+sub_btn+'</a>');
          }
        }
     });
    });  
	
   	var og_cstm_gadmin_subscrptn = function(slctr, action, gid, uid) {
	  $.ajax({
        type: "POST",
        url: "/og_cstm_subscrptn",
        data: {action: action, gid: gid, uid: uid}, 
        success: function(res){
          if(res == 'approve') {
            slctr.parent().html('Active |');
          }else if(res == 'delete') {
            slctr.parent().parent().parent().remove();
          }
        }
      }); 
    }

    var del_confirmation = function(slctr, action, gid, uid) {
      $( "#dialog-confirm" ).dialog({
        resizable: false,
        modal: true,
        buttons: {
          "Yes": function() {
			og_cstm_gadmin_subscrptn(slctr, action, gid, uid);
			$( this ).dialog( "close" );
          },
          Cancel: function() {
            $( this ).dialog( "close" );
          }
        }
      });
    }
	
    $( '.mem_lnk' ).on( 'click', 'a.og_custom_gadmin', function () {  
      var slctr = $(this);
      var data = slctr.attr('data').split('_');	
      var gid = data[1];
      var uid = data[2];
      var action = data[0];

	  if(action == "delete") {
	    del_confirmation(slctr, action, gid, uid);
	  }else 
	  {
		og_cstm_gadmin_subscrptn(slctr, action, gid, uid);
	  } 
    });  

  });	
})(jQuery);		
