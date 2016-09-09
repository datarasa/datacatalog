window.onload = function () {
  if(jQuery("#sources-members").length) {
    jQuery.getJSON("datacatalog-blocks/get-members-sources", function (result) {
      CanvasJS.addColorSet("hbarscolor",
      [
        "#59D573",
        "#5099DD",
      ]);
      var chart1 = new CanvasJS.Chart("sources-members", {
        colorSet: "hbarscolor",
        animationEnabled: true,
        axisX: {
          interval: 1,
          gridThickness: 0,
        },
        axisY2: {
          interlacedColor: "#fff",
          gridColor: "#ccc"
        },
        data: [
          {
            type: "bar",
            axisYType: "secondary",
            dataPoints: result
          }
        ]
      });
      chart1.render();
    });
  }
  if(jQuery("#sources-byweekchart").length) {
    jQuery.getJSON("datacatalog-blocks/get-members-sources-by-week", function(result) {
      var chart = new CanvasJS.Chart("sources-byweekchart",
      {
        colorSet: "hbarscolor",
        theme: "theme1",
        animationEnabled: true,
        toolTip: {
          shared: true
        },
        axisY: {
          title: "Sources & Members"
        },
        axisY2: {
          title: "Members"
        },
        data: [
          {
             type: "column",
             name: "Sources",
             legendText: "Sources",
             showInLegend: true,
             dataPoints: result['sources']
           },
           {
             type: "column",
             name: "Members",
             legendText: "Members",
             showInLegend: true,
             dataPoints: result['members']
           }
        ],
        legend: {
          cursor: "pointer",
          itemclick: function (e) {
            if (typeof (e.dataSeries.visible) === "undefined" || e.dataSeries.visible) {
              e.dataSeries.visible = false;
            }else {
              e.dataSeries.visible = true;
            }
            chart.render();
          }
        },
      });
      chart.render();
    });
  }
  if(jQuery("#sources-views-comments").length) {
    jQuery.getJSON("datacatalog-blocks/get-views-comments", function (result) {
      var cdps = [];
      jQuery.each(result['comments'], function (i, item) {
        var rdate = item.x;
        var cdate = new Date(rdate);
        cdps.push({x: cdate, y: item.y});
      });
      var vdps = [];
      jQuery.each(result['views'], function (i, item) {
        var rdate = item.x;
        var cdate = new Date(rdate);
        vdps.push({x: cdate, y: item.y});
      });
      var chart2 = new CanvasJS.Chart("sources-views-comments",
      {
        animationEnabled: true,
        axisX: {
          gridColor: "Silver",
          tickColor: "silver",
          valueFormatString: "DD/MMM"
        },
        toolTip: {
          shared: true
        },
        theme: "theme2",
        axisY: {
          gridColor: "Silver",
          tickColor: "silver"
        },
        legend: {
          verticalAlign: "center",
          horizontalAlign: "right"
        },
        data: [
          {
            type: "line",
            showInLegend: true,
            lineThickness: 2,
            name: "Views",
            markerType: "square",
            color: "#0088cc",
            dataPoints: vdps
          },
          {
            type: "line",
            showInLegend: true,
            name: "Comments",
            color: "#fd9807",
            lineThickness: 2,
            dataPoints: cdps
           }
        ],
        legend:{
          cursor: "pointer",
          itemclick: function (e) {
            if(typeof (e.dataSeries.visible) === "undefined" || e.dataSeries.visible) {
              e.dataSeries.visible = false;
            }else {
              e.dataSeries.visible = true;
            }
            chart2.render();
          }
        }
      });
      chart2.render();
    });
  }
  if (jQuery("#placeholder").length) {
    jQuery.getJSON("datacatalog-blocks/get-members-by-month", function (result) {
      var d1 = result['data'];
      var d2 = result['data'];
      var girds = [];
      jQuery.each(d2, function (i, item) {
        girds.push({color: '#d8d8d8', lineWidth: 1, xaxis: {from: item[0], to: item[0]}});
      });
      var data1 = [
        {
		  label: "Trend", 
		  data: d1, 
		  points: {
		    symbol: "circle", fillColor: "#fff", radius: 4
		  }, 
		  color: '#f45f73', 
		  lines: {
            fill: true,
            lineWidth: 1,
            fillColor: {
              colors: [
			    {
			       opacity: 0
			    }, 
			    {
			       opacity: 0.5
			    }
			  ]
            }
          }
		},
      ];
      jQuery.plot(jQuery("#placeholder"), data1, {
        xaxis: {
          min: (new Date(result['min'])).getTime(),
          max: (new Date(result['max'])).getTime(),
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
          min: 0,
          max: result['members_count'],
          axisLabel: '',
          axisLabelUseCanvas: true,
          axisLabelFontSizePixels: 12,
          axisLabelFontFamily: 'Verdana, Arial, Helvetica, Tahoma, sans-serif',
          axisLabelPadding: 0
        },
        series: {
          lines: {show: true},
          points: {
            radius: 3,
            show: true,
            fill: true
          },
        },
        grid: {
          hoverable: true,
          borderWidth: 0,
          markings: girds
        },
        legend: {
          labelBoxBorderColor: "none",
          position: "right"
        }
      });
    });
    var previousPoint1 = null;
    jQuery("#placeholder").bind("plothover", function (event, pos, item) {
      if (item) {
        if ((previousPoint1 != item.dataIndex) || (previousLabel != item.series.label)) {
          previousPoint1 = item.dataIndex;
          previousLabel = item.series.label;
          jQuery("#flot-tooltip").remove();
          var x = convertToDate(item.datapoint[0]),
          y = item.datapoint[1];
          z = item.series.color;
          showTooltip(item.pageX, item.pageY, "<b>" + "" + "</b><br /> " + "Users"+ " : <span class='user-nos'>" + y + "</span>", z);
        }
      } else {
        jQuery("#flot-tooltip").remove();
        previousPoint1 = null;
      }
    });
  }
  if (jQuery("#sourceholder").length) {
    jQuery.getJSON("datacatalog-blocks/get-sources-by-month", function (result) {
      var d3 = result['data'];
      var d4 = result['data'];
      var girds = [];
      jQuery.each(d4, function (i, item) {
        girds.push({ color: '#d8d8d8', lineWidth: 1, xaxis: {from: item[0], to: item[0]}});
      });
      var data2 = [
        {
		   label: "Trend", 
		   data: d3, 
		   points: {
		     symbol: "circle", 
			 fillColor: "#fff" , 
			 radius:4
		   }, 
		   color: '#3c90cf', 
		   lines: {
             fill: true,
             lineWidth: 1,
             fillColor: {
               colors: [{opacity: 0}, {opacity: 0.5}]
             }
            }
	     },
       ];
       jQuery.plot(jQuery("#sourceholder"), data2, {
         xaxis: {
           min: (new Date(result['min'])).getTime(),
           max: (new Date(result['max'])).getTime(),
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
           min: 0,
           max: result['source_count'], //200,
           axisLabel: '',
           axisLabelUseCanvas: true,
           axisLabelFontSizePixels: 12,
           axisLabelFontFamily: 'Verdana, Arial, Helvetica, Tahoma, sans-serif',
           axisLabelPadding: 0
         },
         series: {
           lines: {show: true},
           points: {
             radius: 3,
             show: true,
             fill: true
           },
         },
         grid: {
           hoverable: true,
           borderWidth: 0,
           markings: girds
         },
         legend: {
           labelBoxBorderColor: "none",
           position: "right"
         }
       });
     });
     var previousPoint2 = null;
     jQuery("#sourceholder").bind("plothover", function (event, pos, item) {
       if (item) {
         if ((previousPoint2 != item.dataIndex) || (previousLabel != item.series.label)) {
           previousPoint2 = item.dataIndex;
           previousLabel = item.series.label;
           jQuery("#source-tooltip").remove();
           var x = convertToDate(item.datapoint[0]),
           y = item.datapoint[1];
           z = item.series.color;
           showTooltip(item.pageX, item.pageY, "<b>" + ""+ "</b><br /> " + "Sources"+ " : <span class='source-nos'>" + y + "</span>", z);
         }
       } else {
         jQuery("#source-tooltip").remove();
         previousPoint2 = null;
       }
    });
  }
}

function showTooltip(x, y, contents, z) {
  jQuery('<div id="flot-tooltip">' + contents + '</div>').css({
    top: y - 80 ,
    left: x,
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


    
   