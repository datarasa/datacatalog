var kb={};
function buildGraph(data,containerId,popup) {
  var isFullscreen = false;
  var links = data.links;
  var nodes = data.nodes;
  var def_width, def_height;
  // data.forEach(function(link) {
  //   link.source = nodes[link.source] || (nodes[link.source] = {name: link.source, type:link.sourceType, image:link.image, url:link.source_link});
  //   link.target = nodes[link.target] || (nodes[link.target] = {name: link.target, type:link.targetType, image:link.image, url:link.target_link});
  // });
  if(popup==1) {
    var wdth = 633;
  }else {
    var wdth = jQuery(containerId).width();
  }
  var width = wdth,
  height = jQuery(containerId).height();
  
  function onZoom (e){
    reDraw(e);
    events.zoom.notify(null, e, self);
  }

  function Event() {
    var handlers = [];
    this.subscribe = function(fn) {
      handlers.push(fn);
    };
  
    this.unsubscribe = function(fn) {
      for(var i = handlers.length - 1; i >= 0; i--) {
        if(handlers[i] === fn) {
          handlers.splice(i, 1);
        }
      }
    };
  
    this.notify = function(args, e, scope) {
      e = e || {};
      scope = scope || this;
      var returnValue;
      for(var i = 0; i < handlers.length; i++) {
        returnValue = handlers[i].call(scope, e, args);
      }
      return returnValue;
    }
  }

  var events = {
    zoom: new Event()
  };

  //zoomSlider initialization code
  jQuery("#zoom_slider").zoom_slider({
    orientation: "vertical",
    range: "min",
    min: 0.05,
    max: 1.05,
    step: 0.1,
    value: 0.25,
    change: function( event, ui ){
      if(zoomSliderOn) {
        var y = ui.value * 4;
        svg.attr("transform", "translate(" + [(jQuery('#graphContainer').width()/2)-(jQuery('#graphContainer').width()*y/2),(jQuery('#graphContainer').height()/2)-(jQuery('#graphContainer').height()*y/2)] + ")"  + " scale(" + y + ")");
      }
    }
  });
       
  //turn zoomSlider on mouseover
  jQuery("#zoom_slider").mouseover(function(e) {
    zoomSliderOn = true;
  });

  //options
  var defaults = {
    //linkColors
    linkColors: {
      person: '#DA312A',
      company : '#5C89E0',
      department : '#001C56'
    }
  };
  /**
    * reDraw()
    * re-draws graph on zoom, etc. 
  */
  function reDraw(e){
    var y, v;
    svg.attr("transform", "translate(" + e.translate + ")" + " scale(" + e.scale + ")");
    d3Translate = d3.event.translate;
    //When zoom on MouseWheel turn Off zoomSlider
    zoomSliderOn = false;
    //set zoomSlider value
    jQuery( "#slider-range-min").slider("value", d3.event.scale / 4)
  }
    
  //fade
  function fade(opacity,x){
    return function(d) {
      node.style("stroke-opacity", function(o) {
        thisOpacity = isConnected(d, o) ? 1 : opacity;
        this.setAttribute('fill-opacity', thisOpacity);
        return thisOpacity;
      });

      link.style("stroke-opacity", opacity).style("stroke-opacity", function(o) {
        return o.source === d || o.target === d ? 1 : opacity;
      });

      if(x > 0){
        text.style("fill",function(o) {
          color = "black";
          whitecolor = "white";
          if(isConnected(d, o)){   
            return whitecolor;
          }
          else{
            return color;
          }
       });
     }
     else {
       text.style("fill","white")
     }
    };
  }

  /***
   * isConnected(a, b)
   * determines wether nodes a and b are connected
  */
  function isConnected(a, b){
    //var links = data       
    //if a,b are point to the same node
    if(a.index == b.index){
      return true;
	}
   //else find
   for(i in links){
     if(links[i].source.index == a.index){
       if(links[i].target.index == b.index){
         return true;
       }
     } 
	 else if(links[i].target.index == a.index){
       if(links[i].source.index == b.index){
         return true;
       }
     }
   }
   return false;
  }

  zoom = d3.behavior.zoom()
    .translate([0,0])
    .scale(1)
    .scaleExtent([0.25,6])
    .on("zoom", function(){

      onZoom(d3.event)
    });

  fill = d3.scale.category20();

  var force = d3.layout.force()
    .nodes(d3.values(nodes))
    .links(links)
    .size([width, height])
    .linkDistance(100)
    .charge(-2500)
    .start();

  var svg = d3.select(containerId).append("svg")
    .attr("width", width)
    .attr("height", height)
    .attr("pointer-events", "all")
    .attr("class", "svg-graph")
    .append("svg:g")
    .call(zoom)
    .append("svg:g");


  //graph canvas rect
  svg.append("svg:rect")
  .attr("width", width)
  .attr("height", height)
  .attr("fill", 'transparent')
  .attr('class', 'graph-rect');

  var link = svg.selectAll(".link")
    .data(links)
    .attr("cursor", "pointer")
    .attr("class", "link")
    .enter().append("path")
    .style("stroke", function(d){return getLinkColor(d.source.type);})
    .style("stroke-width", "1").attr("stroke-opacity", "1.0")
    .attr("cursor", "pointer")
    .on("mouseover", function() { d3.select(this).style("stroke-width", "3").attr("stroke-opacity", "1.0") })
    .on("mouseout", function() { d3.select(this).style("stroke-width", "1").attr("stroke-opacity", "1.0") });

  var node = svg.selectAll(".node")
  .data(d3.values(nodes));
      
  var nodeenter = node.enter().append("g")
  .attr("class", function(d){
    return d.name == jQuery('input.ui-autocomplete-input').val() ? "node searched" : "node";
  })

  .attr("cursor", "pointer")
  .on("mouseover", fade(.2,1))
  .on("mouseout", fade(1,0))
  //.on("click", function(d) { window.location = d.url; })
  .on("click", function(d) { window.open(d.url, '_blank'); })
  .call(force.drag);
  
  
  nodeenter.append("title")
  .text(function(d) { return d.name; });

   //nodeenter.append("svg:a")
  //.attr("xlink:href", function(d){return d.url;});  // <-- reading the new "url" property

  var rect = nodeenter.append("svg:rect")
  .attr("x", function(d) { return -1 * d.name.toString().visualLength() / 2 - 5 - ((5 * d.name.toString().visualLength()) / 200); })
  .attr("y", -15)
  //.attr("rx", 10)
  .attr("width", function(d) { return d.name.toString().visualLength() + 10 + ((5 * d.name.toString().visualLength()) / 100); })
  .attr("height", 22)

  var image = nodeenter.append("image")
  .attr("xlink:href", function(d){
      //console.log(JSON.stringify(d));
    return (d.image && d.image.length > 1)? d.image : "/sites/all/modules/datacatalog_relgraphs/images/default_"+d.type+".png";
  })
  .attr("cursor", "pointer")
  .attr("x", -17)
  .attr("y", -45)
  .attr("width", 31)
  .attr("height", 32);

  var text = nodeenter.append("text")
  .attr("cursor", "pointer")
  .attr("text-anchor", "middle")
  .text(function(d) { return d.name; });

  /**
    * getLinkColor()
    * returns link color.
  */
  function getLinkColor(type){
    return (type in defaults.linkColors) ? defaults.linkColors[type] : 'black';
  }

  /**
     *@method arcPath
     *@param {boolean} arg1
     *@param{object} arg2
     *if arg1 is true arcPath is drawn from source to target e.g with arrow head pointing to target
     *if arg1 is false arcPath is drawn from target to source e.g with arrow head pointing to source
  */
  var mLinkNum = {};
  function arcPath(leftHand, d) {
    var start = leftHand ? d.source : d.target,
    end = leftHand ? d.target : d.source,
    dx = end.x - start.x,
    dy = end.y - start.y,
    dr = Math.sqrt(dx * dx + dy * dy),
    sweep = leftHand ? 0 : 1;
    // get the total link numbers between source and target node
    var lTotalLinkNum = mLinkNum[d.source.index + "," + d.target.index] || mLinkNum[d.target.index + "," + d.source.index];
    if(lTotalLinkNum > 1) {
      // if there are multiple links between these two nodes, we need generate different dr for each path
      dr = dr/(1 + (1/lTotalLinkNum) * (d.linkindex - 1));
    }  
    return  "M" + start.x + "," + start.y + "A" + dr + "," + dr + " 0 0 1," + end.x + "," + end.y + 
            "A" + dr + "," + dr + " 0 0 0," + start.x + "," + start.y; 
    //return "M" + start.x + "," + start.y + "A" + dr + "," + dr + " 0 0," + sweep + " " + end.x + "," + end.y;
  }

  force.on("tick", function() {
    link.each(function() {this.parentNode.insertBefore(this, this); });
    link.attr("d", function(d) {
      //get arcPath
      return arcPath(false, d);
    });
    node.attr("transform", function(d) { return "translate(" + d.x + "," + d.y + ")"; });
  });


  //highlight node
  this.highlightNode = function(name, on){
  
  if (on) {
      node.attr('class', function(d){
    if(d.name == name){
        return 'node node-highlight';
    }
    return (d.name == jQuery('input.ui-autocomplete-input').val()) ? 'node searched' : 'node';
      });
  }else{
      node.attr('class', function(d){
    return (d.name == jQuery('input.ui-autocomplete-input').val()) ? 'node searched' : 'node';
      });
  }
  
    }

   //enterFullscreen
   this.enterFullscreen = function(){
   if (isFullscreen) {
     return;
   }
	def_width = jQuery("#graphContainer").width();
	def_height = jQuery("#graphContainer").height();
   jQuery("#graphContainer").addClass('kb-graph-fullscreen');
      this.setResize(0,0);
      jQuery("svg.svg-graph").width(jQuery("#graphContainer").width());
      jQuery("svg.svg-graph").height(jQuery("#graphContainer").height());
      isFullscreen = true;
    }
    
   //exit fullscreen
   this.exitFullscreen = function(){
     if (!isFullscreen) {
        return;
     }
     jQuery("#graphContainer").removeClass('kb-graph-fullscreen');
     this.setResize(def_width, def_height);
     isFullscreen = false;
   }
    
   //isFullscreen
   this.isFullscreen = function(){
     return isFullscreen;
   }

   //kb setResize
   this.setResize = function(w, h){
      w = (w == 0 ) ? jQuery("#graphContainer").width() : w; 
      h = (h == 0 ) ? jQuery("#graphContainer").height() : h;
      //set graph with & height
	  jQuery("#graphContainer").width(w);
	  jQuery("#graphContainer").height(h);
      force.size([w,h]);
      d3.select(".svg-graph").attr('width', w).attr('height', h);
      d3.select(".svg-graph rect").attr('width', w).attr('height', h);
    }
}

jQuery( document ).ready(function() {
  //Add ruler if not already added.
  if(jQuery('#ruler').length == 0){
    console.log("Creating span#ruler for node visualLength calculations!");
    jQuery("#block-system-main").append("<span id='ruler' style='visibility: hidden; white-space: nowrap;'></span>");
  }
  else{
    console.log("#ruler already exists, it may cause disturbance if its visible!");
  }
  String.prototype.visualLength = function() {
    var ruler = document.getElementById("ruler");
    ruler.innerHTML = this;
    return ruler.offsetWidth;
  }
});


//. neo4j data parser methods...
function idIndex(a,id) {
  for (var i=0;i<a.length;i++) 
  {if (a[i].id == id) return i;}
  return null;
}  

function convertNeo4jDataToD3(data){
    var nodes=[], links=[], node_ids=[], related=[];
   // console.log(JSON.stringify(data.results[0]));
//    if(JSON.stringify(data.results[0].data.length) != 0){
//        console.log('data' + data.results[0].data.length);
//       jQuery('.no-relationship').css('display', 'none');
//    }else{
//        console.log('no data');
//       jQuery('.no-relationship').css('display', 'block');
//    } 
    data.results[0].data.forEach(function (row) {
      row.graph.nodes.forEach(function (n) {
          //console.log(JSON.stringify(n));
         //if (idIndex(nodes,n.id) == null)
                var name = "";
                var title = "";
                var url = ""; 
	        var type = ""; 	
//         if(n.properties.entity_type == 'node' && n.properties.bundle == 'business_process'){  
//           return true;
//         }
         if(n.properties.type != 'tags' || n.properties.type != 'user'){
            var name = n.properties.title;
            var title = n.properties.title;
            var type = n.properties.type;
            var url = '/' + n.properties.url;
         }
         if(n.properties.type == 'tags' || n.properties.type == 'user'){
            var name = n.properties.name;
            var title = n.properties.name;
            var type = n.properties.type;
            var url = '/' + n.properties.url;
         }
         if(jQuery.inArray(n.id, node_ids) == -1){
            nodes.push({id:n.id,name:name,title:title,type:type,url:url}); 
            related.push({title:title, type:n.properties.type, url:url}); 
            node_ids.push(n.id);
          }
      
        });
        links = links.concat( row.graph.relationships.map(function(r) {
//            if (idIndex(nodes,r.endNode) == null){
//               return true;
//           }
              return {source:idIndex(nodes,r.startNode),target:idIndex(nodes,r.endNode),type:r.type, value:1};
            
        })); 
    });
    var markup = '';
    related.forEach(function (rel) {
        if(rel.type == 'source' && rel.title != ''){
          markup +='<li data="'+ rel.title +'"><a href="'+ rel.url +'" target="_blank">'+ rel.title +'</a></li>';  
          //console.log(markup);
        }    
    });
    jQuery("ul#listUlD").html(markup);
    graph = {nodes:nodes, links:links};
    return graph;
};
jQuery(document).ready(function(){
jQuery('.toggle-link a').on('click',function(e){
	e.preventDefault();
	if(jQuery(this).text() == 'Select All'){
		var parent_id = jQuery(this).parent().parent().attr('id');
		jQuery('#'+parent_id).find('input:checkbox').prop('checked',true);
		jQuery(this).text('Select None');
	}else{
		 var parent_id = jQuery(this).parent().parent().attr('id');
		 jQuery('#'+parent_id).find('input:checkbox').prop('checked', false);
		 jQuery(this).text('Select All');
	}	
});
});