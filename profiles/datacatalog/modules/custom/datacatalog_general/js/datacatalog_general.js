(function ($) {
  Drupal.behaviors.datacatalog_general = {
    attach: function (context, settings) {
      $('.view-display-id-page #edit-sort-by option, .view-display-id-page_1 #edit-sort-by option', context).once('datacatalog_general', function () {
        $(this).removeAttr('selected');
      });
      $('.view-display-id-page #edit-sort-by, .view-display-id-page_1 #edit-sort-by').attr('width', '145');
      $('.view-display-id-page #edit-sort-by, .view-display-id-page_1 #edit-sort-by').chosen({disable_search_threshold:10, placeholder_text_single: "Community Sort"});
      $('select.form-select').chosen({disable_search_threshold:10});
      $('.view-display-id-page .btn-default').attr('title', 'Community Sort');
	}
  };
})(jQuery);	
