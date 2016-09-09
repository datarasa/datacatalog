(function($){
  $.fn.zoom_slider = function(options) {
	//create zoom slider structure
    this.addClass('slider-container');
    this.append( "<div class='ui-icon ui-icon-circle-plus zoom_in'></div>" )
    .append("<div id='slider-range-min'></div>")
    .append("<div class='ui-icon ui-icon-circle-minus zoom_out'>");
	//initializing zoom_slider
    $( "#slider-range-min" ).slider(options);
	//adding and handling zoom_in click event
    $('.zoom_in').on('click', function (evt) {
      zoom = $( "#slider-range-min" ).slider("value");
      zoom += options.step;
      if ( zoom > options.max ) { return; }
        $( "#slider-range-min" ).slider("value", zoom);
    });
    //adding and handling zoom_out click event
    $('.zoom_out').on('click', function (evt) {
      zoom = $( "#slider-range-min" ).slider("value");
      zoom -= options.step;
      zoom = zoom.toFixed(2);
      if( zoom < options.min ){ return; }
        $( "#slider-range-min" ).slider("value", zoom);
      });
    return this;
  };
}(jQuery));