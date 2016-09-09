(function($) {
$(document).ready(function () {
	if($("#placeholder").length) {
    $.plot("#placeholder", [{
    data: [[0,50],[150,100],[180,90], [275,148],[380,55],[475,120]],
    color: "#f45f73",
    lines: {
        fill: true,
        lineWidth: 3,
        fillColor: {
            colors: [{ opacity: 0 }, { opacity: 0.5 } ]
        }
    },
    points: {
        show: true,
        fillColor: '#fff'
    }
}], 
    
    {
    series: {
        lines: {
            show: true,
            fill: true
        }
    },
    grid: {
        hoverable: true,
        clickable: true,
        backgroundColor: '#fff',
        color: '#d8d8d8',
        show: true,
        markings: [
            { yaxis: { from: 0, to: 200 }, color: ""}
        ],
        markingsLineWidth: 6
    },
    yaxis: {
        show: true,
        min:0,
        max:200
    },
    xaxis: {
        show: true,
        min: 0,
        max: 600
    }
});
	}
});
})(jQuery);