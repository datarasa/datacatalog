var d1 = [[1262304000000, 50], [1264982400000, 100], [1267401600000, 95], [1270080000000, 148], [1272672000000, 53], [1275350400000, 110], [1277942400000, 50], [1280620800000, 100], [1283299200000, 110], [1285891200000, 120], [1288569600000, 100], [1291161600000, 90]];
 
var data1 = [
    {label: "Trend",  data: d1, points: { symbol: "circle", fillColor: "#fff" , radius:4}, color: '#f45f73',lines: {
        fill: true,
        lineWidth: 1,
        fillColor: {
            colors: [{ opacity: 0 }, { opacity: 0.5 } ]
        }
    }},
    
];
 (function($) {
$(document).ready(function () {
	if($("#placeholder").length) {
    $.plot($("#placeholder"), data1, {
        xaxis: {
            min: (new Date(2009, 11, 18)).getTime(),
            max: (new Date(2010, 11, 15)).getTime(),
            mode: "time",
            tickSize: [1, "month"],
            monthNames: ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"],
            tickLength: 0,
            axisLabel: '',
            axisLabelUseCanvas: true,
            axisLabelFontSizePixels: 12,
            axisLabelFontFamily: 'Verdana, Arial, Helvetica, Tahoma, sans-serif',
            axisLabelPadding: 5
        },
        yaxis: {
            min:0,
            max:200,
            axisLabel: '',
            axisLabelUseCanvas: true,
            axisLabelFontSizePixels: 12,
            axisLabelFontFamily: 'Verdana, Arial, Helvetica, Tahoma, sans-serif',
            axisLabelPadding: 0
        },
        series: {
            lines: { show: true },
            points: {
                radius: 3,
                show: true,
                fill: true
            },
        },
        grid: {
            hoverable: true,
            borderWidth: 0,
			markings: [
      { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1262304000000, to: 1262304000000 } },
      { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1264982400000, to: 1264982400000 } },
      { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1267401600000, to: 1267401600000 } },
	  { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1270080000000, to: 1270080000000 } },
	  { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1272672000000, to: 1272672000000 } },
	  { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1275350400000, to: 1275350400000 } },
	  { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1277942400000, to: 1277942400000 } },
	  { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1280620800000, to: 1280620800000 } },
	  { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1283299200000, to: 1283299200000 } },
	  { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1285891200000, to: 1285891200000 } },
	  { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1288569600000, to: 1288569600000 } },
	  { color: '#d8d8d8', lineWidth: 1, xaxis: { from: 1291161600000, to: 1291161600000 } }
    ]
        },
        legend: {
            labelBoxBorderColor: "none",
                position: "right"
        }
    });
	}
 
    function showTooltip(x, y, contents, z) {
        $('<div id="flot-tooltip">' + contents + '</div>').css({
            top: y - 30,
            left: x - 135,
            'border-color': z,
        }).appendTo("body").fadeIn(200);
    }
 
    function getMonthName(numericMonth) {
        var monthArray = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];
        var alphaMonth = monthArray[numericMonth];
 
        return alphaMonth;
    }
 
    function convertToDate(timestamp) {
        var newDate = new Date(timestamp);
        var dateString = newDate.getMonth();
        var monthName = getMonthName(dateString);
 
        return monthName;
    }
 
    var previousPoint = null;
 
    $("#placeholder").bind("plothover", function (event, pos, item) {
        if (item) {
            if ((previousPoint != item.dataIndex) || (previousLabel != item.series.label)) {
                previousPoint = item.dataIndex;
                previousLabel = item.series.label;
 
                $("#flot-tooltip").remove();
 
                var x = convertToDate(item.datapoint[0]),
                y = item.datapoint[1];
                z = item.series.color;
 
                /*showTooltip(item.pageX, item.pageY,
                    "<b>" + item.series.label + "</b><br /> " + x + " = " + y + "users",
                    z);*/
				showTooltip(item.pageX, item.pageY,
                    /*"<b>" + item.series.label + "</b><br /> " + "Users"+ " : <span class='user-nos'>" + y + "</span>",
                    z);	*/
					"<b>" + "" + "</b><br /> " + "Users"+ " : <span class='user-nos'>" + y + "</span>",
                    z);
            }
        } else {
            $("#flot-tooltip").remove();
            previousPoint = null;
        }
	
    });
});
})(jQuery);