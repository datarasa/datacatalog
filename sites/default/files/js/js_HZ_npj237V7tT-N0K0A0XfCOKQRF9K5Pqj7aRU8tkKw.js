(function ($) {

Drupal.behaviors.textarea = {
  attach: function (context, settings) {
    $('.form-textarea-wrapper.resizable', context).once('textarea', function () {
      var staticOffset = null;
      var textarea = $(this).addClass('resizable-textarea').find('textarea');
      var grippie = $('<div class="grippie"></div>').mousedown(startDrag);

      grippie.insertAfter(textarea);

      function startDrag(e) {
        staticOffset = textarea.height() - e.pageY;
        textarea.css('opacity', 0.25);
        $(document).mousemove(performDrag).mouseup(endDrag);
        return false;
      }

      function performDrag(e) {
        textarea.height(Math.max(32, staticOffset + e.pageY) + 'px');
        return false;
      }

      function endDrag(e) {
        $(document).unbind('mousemove', performDrag).unbind('mouseup', endDrag);
        textarea.css('opacity', 1);
      }
    });
  }
};

})(jQuery);
;
(function ($) {

$.fn.toggleClick = function () {
    var functions = arguments
    return this.each(function () {
      var iteration = 0
      $(this).click(function () {
        functions[iteration].apply(this, arguments)
        iteration = (iteration + 1) % functions.length
      })
    })
  }

/**
 * Attach collapse behavior to the feedback form block.
 */
Drupal.behaviors.feedbackForm = {
  attach: function (context) {
    $('#block-feedback-form', context).once('feedback', function () {
      var $block = $(this);
      $block.find('span.feedback-link')
        .prepend('<span id="feedback-form-toggle">[ + ]</span> ')
        .css('cursor', 'pointer')
        .toggleClick(function () {
            Drupal.feedbackFormToggle($block, false);
          },
          function() {
            Drupal.feedbackFormToggle($block, true);
          }
        );
      $block.find('form').hide();
      $block.show();
    });
  }
};

/**
 * Re-collapse the feedback form after every successful form submission.
 */
Drupal.behaviors.feedbackFormSubmit = {
  attach: function (context) {
    var $context = $(context);
    if (!$context.is('#feedback-status-message')) {
      return;
    }
    // Collapse the form.
    $('#block-feedback-form .feedback-link').click();
    // Blend out and remove status message.
    window.setTimeout(function () {
      $context.fadeOut('slow', function () {
        $context.remove();
      });
    }, 3000);
  }
};

/**
 * Collapse or uncollapse the feedback form block.
 */
Drupal.feedbackFormToggle = function ($block, enable) {
  $block.find('form').slideToggle('medium');
  if (enable) {
    $('#feedback-form-toggle', $block).html('[ + ]');
  }
  else {
    $('#feedback-form-toggle', $block).html('[ &minus; ]');
  }
};

})(jQuery);
;
//Merged and minified: bue.popup.js, bue.markup.js, bue.preview.js, bue.imce.js, bue.misc.js
(function(b,a){BUE.popups=BUE.popups||{};BUE.popHtml='<table class="bue-popup" style="display: none;" role="dialog"><tbody class="bue-zero"><tr class="bue-zero"><td class="bue-zero"><div class="bue-popup-head clearfix"><div class="bue-popup-title"></div><button class="bue-popup-close" type="button">x</button></div><div class="bue-popup-body"><div class="bue-popup-content clearfix"></div></div></td></tr></tbody></table>';BUE.openPopup=function(f,e,d,c){return BUE.createPopup(f).open(e,d,c)};BUE.createPopup=function(i,h,f){if(BUE.popups[i]){return BUE.popups[i]}var c=BUE.$html(BUE.popHtml).appendTo("body").attr("id",i);var e=c.find(".bue-popup-title").html(h||"");var d=c.find(".bue-popup-content").html(f||"");var g=BUE.popups[i]=c[0];g.open=function(o,l,k){if(o!==undefined&&o!==null){e.html(o)}if(l!==undefined&&l!==null){d.html(l)}var m=g.bue=BUE.active,q=m.buttons[m.bindex||0];k=typeof k=="string"?{effect:k}:k;k=a.extend({effect:"show",speed:"normal",callback:g.onopen},k);k.onopen=k.onopen||k.callback;if(!k.offset&&q){var p=a(q).offset(),j=c.width(),n=Math.max(15,p.left-j/2+15);k.offset={left:n-Math.max(0,n+j-a(window).width()+15),top:p.top+15};q.pops=true}c.css(k.offset);if(k.effect=="show"){c.show();k.onopen&&k.onopen.call(g)}else{c[k.effect](k.speed,k.onopen)}g.onclose=k.onclose||false;return g};g.close=function(j){c.stop(true,true)[j||"hide"]();g.onclose&&g.onclose.call(g);return g};g.closenfocus=function(){g.close().bue.focus();return g};g.onopen=function(){if(c.css("display")!="none"){var j=c.focus().find("form");if(j.length){a(j[0].elements[0]).focus()}else{c.find("a:first").focus()}}return g};c.attr("tabindex",0);c.find(".bue-popup-close").click(g.closenfocus)[0].title=Drupal.t("Close");c.keydown(function(j){if(j.keyCode==27){g.closenfocus();return false}});c.find(".bue-popup-head").mousedown(function(l){var m={X:parseInt(c.css("left"))-l.pageX,Y:parseInt(c.css("top"))-l.pageY};var k=function(n){c.css({left:m.X+n.pageX,top:m.Y+n.pageY});return false};var j=function(n){a(document).unbind("mousemove",k).unbind("mouseup",j)};a(document).mousemove(k).mouseup(j);return false});return g};BUE.preprocess=a.extend({popup:function(j,f){if(j.index){return}var c=b.dialog=BUE.dialog=BUE.createPopup("bue-dialog");var e=function(){this.blur()};var i=c.open,d=c.close;c.open=function(p,n,m){c.esp&&c.close();var o=BUE.active;o.buttonsDisabled(true).stayClicked(true);c.esp=o.posSelection();f(o.textArea).bind("focus.bue",e);return i(p,n,m)};c.close=function(m){if(!c.esp){return c}var n=c.bue;f(n.textArea).unbind("focus.bue",e);n.buttonsDisabled(false).stayClicked(false);n==BUE.active&&n.makeSelection(c.esp.start,c.esp.end);c.esp=null;return d(m)};var g=b.quickPop=BUE.quickPop=BUE.createPopup("bue-quick-pop");var l=g.open,h=g.close,k=f(g);g.open=function(n,m){f(document).mouseup(g.close);return l(null,n,m)};g.close=function(){f(document).unbind("mouseup",g.close);return h()};k.keydown(function(o){switch(o.keyCode){case 13:setTimeout(g.closenfocus);break;case 38:case 40:var n=k.find("a"),m=n.index(document.activeElement);n.eq(m+o.keyCode-39).focus();return false}});k.find(".bue-popup-head").css({display:"none"})}},BUE.preprocess)})(BUE.instance.prototype,jQuery);(function(d,c){BUE.html=function(g,l,f){var e=f||{},h=l||"";var k="<"+g;for(var j in e){k+=e[j]==null?"":" "+j+'="'+e[j]+'"'}k+=a(g)?(" />"+h):(">"+h+"</"+g+">");return g?k:h};BUE.objHtml=function(e){return e&&e.tag?b(e.tag,e.html,e.attributes):""};BUE.input=function(g,h,f,e){return b("input","",c.extend({type:g,name:h,value:f||null},e))};BUE.selectbox=function(k,f,j,e){var j=j||{},h="";for(var g in j){h+=b("option",j[g],{value:g,selected:g==f?"selected":null})}return b("select",h,c.extend({},e,{name:k}))};BUE.table=function(j,e){for(var h,g="",f=0;h=j[f];f++){g+=h.data===undefined?BUE.trow(h):BUE.trow(h.data,h.attr)}return b("table",g,e)};BUE.trow=function(f,e){for(var j,h="",g=0;j=f[g];g++){h+=j.data===undefined?b("td",j):b("td",j.data,j.attr)}return b("tr",h,e)};BUE.regesc=function(e){return e.replace(/([\\\^\$\*\+\?\.\(\)\[\]\{\}\|\:])/g,"\\$1")};BUE.nctag=function(e){return !e||/^(img|input|hr|br|embed|param)$/.test(e)};BUE.parseHtml=function(k,g){var l=new RegExp("^<("+(g||"[a-z][a-z0-9]*")+")([^>]*)>($|((?:.|[\r\n])*)</\\1>$)");if(!(h=k.match(l))||(!h[3]&&!a(h[1]))){return null}var g=h[1],f=[],e={},h;if((f=h[2].split('"')).length>1){for(var j=0;f[j+1]!==undefined;j+=2){e[f[j].replace(/\s|\=/g,"")]=f[j+1]}}return{tag:g,attributes:e,html:h[4]}};d.insertObj=function(l,h){if(!l||!l.tag){return this}var j=this,e=l.tag,h=c.extend({cursor:null,extend:true,toggle:false},h);var k,i=j.getSelection(),f=i&&h.extend&&BUE.parseHtml(i);if(k=f&&f.tag==e){if(h.toggle){return j.replaceSelection(f.html,h.cursor)}var l={tag:e,html:typeof l.html!="string"||l.html==i?f.html:l.html,attributes:c.extend(f.attributes,l.attributes)}}if(k||a(e)||l.html){return j.replaceSelection(BUE.objHtml(l),h.cursor)}var g=b(e,"",l.attributes);return j.tagSelection(g.substr(0,g.length-e.length-3),"</"+e+">",h.cursor)};var b=BUE.html;var a=BUE.nctag})(BUE.instance.prototype,jQuery);eDefHTML=BUE.html;eDefInput=BUE.input;eDefSelectBox=BUE.selectbox;eDefTable=BUE.table;eDefRow=BUE.trow;eDefNoEnd=BUE.nctag;eDefRegEsc=BUE.regesc;eDefParseTag=BUE.parseHtml;eDefInputText=function(c,a,b){return BUE.input("text",c,a,{size:b||null})};eDefInputSubmit=function(b,a){return BUE.input("submit",b,a)};(function(b,a){b.prv=function(e){var d=this;if(d.prvOn){return d.prvHide()}var e=e===undefined?true:e;var c=d.getContent();if(e&&!(d.safeToPreview=d.safeToPreview||c.indexOf("<")==-1)){c='<div class="warning">'+Drupal.t("The preview is disabled due to previously inserted HTML code in the content. This aims to protect you from any potentially harmful code inserted by other editors or users. If you own the content, just preview an empty text to re-enable the preview.")+"</div>"}return d.prvShow(BUE.autop(c))};b.prvShow=function(d,e){var f=this;var g=a(f.textArea);var c=a(f.preview=f.preview||BUE.$html('<div class="preview bue-preview" style="display:none; overflow:auto"></div>').insertBefore(g)[0]);if(e===undefined||e){d='<div class="'+(f.textArea.name=="comment"?"comment":"node")+'"><div class="content">'+d+"</div></div>"}if(f.prvOn){c.html(d);return f}f.prvPos=f.posSelection();c.show().height(g.height()).width(g.width()).html(d);g.height(1);f.buttonsDisabled(true,f.bindex).stayClicked(true);f.prvOn=true;return f};b.prvHide=function(){var d=this;if(d.prvOn){var c=a(d.preview);a(d.textArea).height(c.height());c.hide();d.buttonsDisabled(false).stayClicked(false);d.prvOn=false;d.prvPos&&(d.makeSelection(d.prvPos.start,d.prvPos.end).prvPos=null)}return d};b.prvAjax=function(e,f){var d=this,c;if(d.prvOn){return d.prvHide()}if(!(c=a.ajaxMarkup)){return d.prvShow(Drupal.t('Preview requires <a href="http://drupal.org/project/ajax_markup">Ajax markup</a> module with proper permissions set.'))}if(e&&e.call){f=e;e=0}d.prvShow('<div class="bue-prv-loading">'+Drupal.t("Loading...")+"</div>");c(d.getContent(),e||c.getFormat(d.textArea),function(h,g,i){d.prvOn&&d.prvShow(g?h:h.replace(/\n/g,"<br />"))&&(f||Drupal.attachBehaviors)(d.preview)});return d};BUE.autop=function(d){if(d==""||!(/\n|\r/).test(d)){return d}var f=function(h,i,g){return h.replace(new RegExp(i,"g"),g)};var c=function(h,g){return d=f(d,h,g)};var e="(table|thead|tfoot|caption|colgroup|tbody|tr|td|th|div|dl|dd|dt|ul|ol|li|pre|select|form|blockquote|address|math|style|script|object|input|param|p|h[1-6])";d+="\n";c("<br />\\s*<br />","\n\n");c("(<"+e+"[^>]*>)","\n$1");c("(</"+e+">)","$1\n\n");c("\r\n|\r","\n");c("\n\n+","\n\n");c("\n?((.|\n)+?)\n\\s*\n","<p>$1</p>\n");c("\n?((.|\n)+?)$","<p>$1</p>\n");c("<p>\\s*?</p>","");c("<p>(<div[^>]*>\\s*)","$1<p>");c("<p>([^<]+)\\s*?(</(div|address|form)[^>]*>)","<p>$1</p>$2");c("<p>\\s*(</?"+e+"[^>]*>)\\s*</p>","$1");c("<p>(<li.+?)</p>","$1");c("<p><blockquote([^>]*)>","<blockquote$1><p>");c("</blockquote></p>","</p></blockquote>");c("<p>\\s*(</?"+e+"[^>]*>)","$1");c("(</?"+e+"[^>]*>)\\s*</p>","$1");c("<(script|style)(.|\n)*?</\\1>",function(g){return f(g,"\n","<PNL>")});c("(<br />)?\\s*\n","<br />\n");c("<PNL>","\n");c("(</?"+e+"[^>]*>)\\s*<br />","$1");c("<br />(\\s*</?(p|li|div|dl|dd|dt|th|pre|td|ul|ol)[^>]*>)","$1");if(d.indexOf("<pre")!=-1){c("(<pre(.|\n)*?>)((.|\n)*?)</pre>",function(j,i,h,g){return f(i,"\\\\(['\"\\\\])","$1")+f(f(f(g,"<p>","\n"),"</p>|<br />",""),"\\\\(['\"\\\\])","$1")+"</pre>"})}return c("\n</p>$","</p>")}})(BUE.instance.prototype,jQuery);eDefAutoP=BUE.autop;eDefPreview=function(){BUE.active.prv()};eDefPreviewShow=function(c,b,a){c.prvShow(b,a)};eDefPreviewHide=function(a){a.prvHide()};eDefAjaxPreview=function(){BUE.active.prvAjax()};(function(c,b){var a=c.imce=BUE.imce={};b(function(){a.url=Drupal.settings.BUE.imceURL||""});a.button=function(e,d){return a.url?'<input type="button" id="bue-imce-button" name="bue_imce_button" class="form-submit" value="'+(d||Drupal.t("Browse"))+'" onclick="BUE.imce.open(this.form.elements[\''+e+"'])\">":""};a.open=function(e){if(!a.url){return}a.ready=a.sendto=function(){},a.target=null;b.extend(a,e.focus?{target:e,ready:a.readyDefault,sendto:a.sendtoDefault}:e);if(a.pop){a.setPos();a.ready(a.win,a.pop)}else{var d=a.url+(a.url.indexOf("?")<0?"?":"&")+"app=bue|imceload@bueImceLoad|";a.pop=BUE.createPopup("bue-imce-pop",Drupal.t("File Browser"),'<iframe src="'+d+'" frameborder="0"></iframe>');a.setPos()}};a.setPos=function(){var d=b(a.pop),f=b(window),e=window.opera?window.innerHeight:f.height();a.pop.open(null,null,{offset:{left:Math.max(0,(f.width()-d.width())/2),top:f.scrollTop()+Math.max(0,(e-d.height())/2)}})};a.finish=function(d,e){a.sendto(d,e,a.pop)};a.sendtoDefault=function(f,j,d){var h=a.target,g=h.form.elements,k={alt:f.name,width:f.width,height:f.height};h.value=f.url;for(var e in k){if(g["attr_"+e]){g["attr_"+e].value=k[e]}}d.close();h.focus()};a.readyDefault=function(g,d){var e=g.imce,f=a.target&&a.target.value;f&&e.highlight(f.substr(f.lastIndexOf("/")+1));if(e.fileKeys&&!e.fileKeys.k27){e.fileKeys.k27=function(h){d.closenfocus();a.target&&a.target.focus()}}!window.opera&&!("WebkitAppearance" in document.documentElement.style)&&b(e.FLW).focus()};window.bueImceLoad=function(d){(a.win=d).imce.setSendTo(Drupal.t("Send to editor"),a.finish);a.ready(d,a.pop);if((window.opera||("WebkitAppearance" in document.documentElement.style))&&b(a.pop).is(":visible")){b(a.win.imce.FLW).one("focus",function(){a.pop.close();a.setPos()})}}})(BUE.instance.prototype,jQuery);eDefBrowseButton=function(a,c,b){return BUE.imce.button(c,b)};(function(d,c){d.wrapLines=function(h,n,m,g){var o=this,k=o.getSelection().replace(/\r\n|\r/g,"\n"),l=BUE.regesc;if(!k){return o.tagSelection(h+n,m+g)}var j,i=new RegExp("^"+l(h+n)+"((.|\n)*)"+l(m+g)+"$");if(j=k.match(i)){i=new RegExp(l(m)+"\n"+l(n),"g");return o.replaceSelection(j[1].replace(i,"\n"))}return o.replaceSelection(h+n+k.replace(/\n/g,m+"\n"+n)+m+g)};d.toggleTag=function(g,h,k){var i=this,j={tag:g,html:i.getSelection(),attributes:h};return i.insertObj(j,{cursor:k,toggle:true})};d.help=function(h){var k=this;if(!k.helpHTML){for(var l,j=[],g=0;l=k.buttons[g];g++){j[g]=[BUE.input(l.type,null,l.value||null,{"class":l.className,src:l.src||null,style:c(l).attr("style")}),l.title]}k.helpHTML=BUE.table(j,{id:"bue-help","class":"bue-"+k.tplid})}k.quickPop.open(k.helpHTML,h);return k};d.tagChooser=function(g,i){var k=this,i=c.extend({wrapEach:"li",wrapAll:"ul",applyTag:true,effect:"slideDown"},i);var l=BUE.html(i.wrapAll||"div","",{"class":"tag-chooser"}),j=b(l);var h=BUE.html(i.wrapEach,"",{"class":"choice"});var m=BUE.html("a","",{href:"#","class":"choice-link"});c.each(g,function(n,o){var p={tag:o[0],html:o[1],attributes:o[2]};b(m).html(i.applyTag?BUE.objHtml(p):p.html).click(function(){k.insertObj(c.extend(p,{html:null}));return false}).appendTo(j)[h?"wrap":"end"](h)});k.quickPop.open(j,i.effect);return k};d.tagDialog=function(w,q,h){var v=this,k=v.getSelection(),o=BUE.parseHtml(k,w)||{attributes:{}};for(var r,p="",u=[],m=0,l=0;r=q[m];m++,l++){r=e(r,o,k);if(r.type=="hidden"){p+=a(r);l--;continue}u[l]=[BUE.html("label",r.title,{"for":r.attributes.id}),a(r)];while(r.getnext&&(r=q[++m])){u[l][1]+=a(e(r,o,k))}}var g=c.extend({title:Drupal.t("Tag editor - @tag",{"@tag":w.toUpperCase()}),stitle:Drupal.t("OK"),validate:false,submit:function(n,i){return v.tgdSubmit(n,i)},effect:"show"},h);var s=BUE.table(u,{"class":"bue-tgd-table"});var j=BUE.html("div",BUE.input("submit","bue_tgd_submit",g.stitle,{"class":"form-submit"}));var t=b(BUE.html("form",s+j+p,{name:"bue_tgd_form",id:"bue-tgd-form"}));v.dialog.open(g.title,t,h);t.submit(function(){return f(w,this,g,v)});return v};d.tgdSubmit=function(g,l){var m=this,n={tag:g,html:null,attributes:{}};for(var h,k,j=0;k=l.elements[j];j++){if(k.name.substr(0,5)=="attr_"){h=k.name.substr(5);if(h=="html"){n.html=k.value}else{n.attributes[h]=k.value.replace(/\x22/g,"&quot;").replace(/>/g,"&gt;").replace(/</g,"&lt;")||null}}}return m.insertObj(n)};var b=BUE.$html;var a=function(i){var g=i.prefix||"";switch(i.type){case"select":g+=BUE.selectbox(i.fname,i.value,i.options||{},i.attributes);break;case"textarea":g+=BUE.html("textarea","\n"+i.value,i.attributes);break;default:g+=BUE.input(i.type,i.fname,i.value,i.attributes);break}return g+(i.suffix||"")};var e=function(h,i,g){h=typeof(h)=="string"?{name:h}:h;if(h.name=="html"){h.value=typeof i.html=="string"?i.html:(g||h.value||"")}h.value=Drupal.checkPlain(typeof i.attributes[h.name]=="string"?i.attributes[h.name]:(h.value||""));h.title=typeof h.title=="string"?h.title:h.name.substr(0,1).toUpperCase()+h.name.substr(1);h.fname="attr_"+h.name;h.type=h.value.indexOf("\n")>-1?"textarea":(h.type||"text");h.attributes=c.extend({name:h.fname,id:h.fname,"class":""},h.attributes);h.attributes["class"]+=" form-"+h.type;if(h.required){h.attributes["class"]+=" required";h.attributes.title=Drupal.t("This field is required.")}return h};var f=function(p,g,h,o){for(var j,m=0;j=g.elements[m];m++){if(c(j).hasClass("required")&&!j.value){return BUE.noticeRequired(j)}}var k=h.validate;if(k){try{if(!k(p,g,h,o)){return false}}catch(n){alert(n.name+": "+n.message)}}o.dialog.close();var l=h.submit;l=typeof l=="string"?window[l]:l;if(l){try{l(p,g,h,o)}catch(n){alert(n.name+": "+n.message)}}return false};BUE.noticeRequired=function(g){c(g).fadeOut("fast").fadeIn("fast",function(){c(this).focus()});return false}})(BUE.instance.prototype,jQuery);eDefSelProcessLines=eDefTagLines=function(f,e,h,g){BUE.active.wrapLines(f,e,h,g)};eDefTagger=function(e,d,f){BUE.active.toggleTag(e,d,f)};eDefHelp=function(a){BUE.active.help(a)};eDefTagDialog=function(h,g,l,k,j,i){BUE.active.tagDialog(h,g,{title:l,stitle:k,submit:j,effect:i})};eDefTagInsert=function(d,c){BUE.active.tgdSubmit(d,c)};eDefTagChooser=function(g,f,j,i,h){BUE.active.tagChooser(g,{applyTag:f,wrapEach:j,wrapAll:i,effect:h})};;
/**
* hoverIntent r6 // 2011.02.26 // jQuery 1.5.1+
* <http://cherne.net/brian/resources/jquery.hoverIntent.html>
* 
* @param  f  onMouseOver function || An object with configuration options
* @param  g  onMouseOut function  || Nothing (use configuration options object)
* @author    Brian Cherne brian(at)cherne(dot)net
*/
(function($){$.fn.hoverIntent=function(f,g){var cfg={sensitivity:7,interval:100,timeout:0};cfg=$.extend(cfg,g?{over:f,out:g}:f);var cX,cY,pX,pY;var track=function(ev){cX=ev.pageX;cY=ev.pageY};var compare=function(ev,ob){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t);if((Math.abs(pX-cX)+Math.abs(pY-cY))<cfg.sensitivity){$(ob).unbind("mousemove",track);ob.hoverIntent_s=1;return cfg.over.apply(ob,[ev])}else{pX=cX;pY=cY;ob.hoverIntent_t=setTimeout(function(){compare(ev,ob)},cfg.interval)}};var delay=function(ev,ob){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t);ob.hoverIntent_s=0;return cfg.out.apply(ob,[ev])};var handleHover=function(e){var ev=jQuery.extend({},e);var ob=this;if(ob.hoverIntent_t){ob.hoverIntent_t=clearTimeout(ob.hoverIntent_t)}if(e.type=="mouseenter"){pX=ev.pageX;pY=ev.pageY;$(ob).bind("mousemove",track);if(ob.hoverIntent_s!=1){ob.hoverIntent_t=setTimeout(function(){compare(ev,ob)},cfg.interval)}}else{$(ob).unbind("mousemove",track);if(ob.hoverIntent_s==1){ob.hoverIntent_t=setTimeout(function(){delay(ev,ob)},cfg.timeout)}}};return this.bind('mouseenter',handleHover).bind('mouseleave',handleHover)}})(jQuery);;
/*
 * sf-Touchscreen v1.3b - Provides touchscreen compatibility for the jQuery Superfish plugin.
 *
 * Developer's note:
 * Built as a part of the Superfish project for Drupal (http://drupal.org/project/superfish)
 * Found any bug? have any cool ideas? contact me right away! http://drupal.org/user/619294/contact
 *
 * jQuery version: 1.3.x or higher.
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 */

(function($){
  $.fn.sftouchscreen = function(options){
    options = $.extend({
      mode: 'inactive',
      breakpoint: 768,
      breakpointUnit: 'px',
      useragent: '',
      behaviour: 2,
      disableHover: false
    }, options);

    function activate(menu){
      var eventHandler = (('ontouchstart' in window) || (window.DocumentTouch && document instanceof DocumentTouch)) ? ['click touchstart','mouseup touchend'] : ['click','mouseup'];
      // Select hyperlinks from parent menu items.
      menu.find('li:has(ul)').children('a,span.nolink').each(function(){
        var item = $(this),
        parent = item.closest('li');
        if (options.disableHover){
          parent.unbind('mouseenter mouseleave');
        }
        if (options.behaviour == 2){
          if (parent.children('a.menuparent,span.nolink.menuparent').length > 0 && parent.children('ul').children('.sf-clone-parent').length == 0){
            var
            // Cloning the hyperlink of the parent menu item.
            cloneLink = parent.children('a.menuparent,span.nolink.menuparent').clone(),
            // Wrapping the hyerplinks in <li>.
            cloneLink = $('<li class="sf-clone-parent" />').html(cloneLink);
            // Removing unnecessary stuff.
            cloneLink.find('.sf-sub-indicator').remove(),
            // Adding a helper class and attaching them to the sub-menus.
            parent.children('ul').addClass('sf-has-clone-parent').prepend(cloneLink);
          }
        }
        // No .toggle() here as it's not possible to reset it.
        item.bind(eventHandler[0], function(event){
          // Already clicked?
          if (item.hasClass('sf-clicked')){
            // Depending on the preferred behaviour, either proceed to the URL.
            if (options.behaviour == 0){
              window.location = item.attr('href');
            }
            // or collapse the sub-menu.
            else if (options.behaviour == 1 || options.behaviour == 2){
              event.preventDefault();
              item.removeClass('sf-clicked');
              parent.hideSuperfishUl().find('a,span.nolink').removeClass('sf-clicked');
            }
          }
          // Prevent the default action otherwise.
          else {
            event.preventDefault();
            item.addClass('sf-clicked');
            parent.showSuperfishUl().siblings('li:has(ul)').hideSuperfishUl().find('.sf-clicked').removeClass('sf-clicked');
          }
        });
      });

      $(document).bind(eventHandler[1], function(event){
        if (menu.not(event.target) && menu.has(event.target).length === 0){
          menu.find('.sf-clicked').removeClass('sf-clicked');
          menu.find('li:has(ul)').hideSuperfishUl();
        }
      });
    }
    // Return original object to support chaining.
    // This is not necessary actually because of the way the module uses these plugins.
    for (var b = 0; b < this.length; b++) {
      var menu = $(this).eq(b),
      mode = options.mode;
      // The rest is crystal clear, isn't it? :)
      if (mode == 'always_active'){
        activate(menu);
      }
      else if (mode == 'window_width'){
        var breakpoint = (options.breakpointUnit == 'em') ? (options.breakpoint * parseFloat($('body').css('font-size'))) : options.breakpoint,
        windowWidth = window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth,
        timer;
        if ((typeof Modernizr === 'undefined' || typeof Modernizr.mq !== 'function') && windowWidth < breakpoint){
          activate(menu);
        }
        else if (typeof Modernizr !== 'undefined' && typeof Modernizr.mq === 'function' && Modernizr.mq('(max-width:' + (breakpoint - 1) + 'px)')) {
          activate(menu);
        }
        $(window).resize(function(){
          clearTimeout(timer);
          timer = setTimeout(function(){
            var windowWidth = window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth;
            if ((typeof Modernizr === 'undefined' || typeof Modernizr.mq !== 'function') && windowWidth < breakpoint){
              activate(menu);
            }
            else if (typeof Modernizr !== 'undefined' && typeof Modernizr.mq === 'function' && Modernizr.mq('(max-width:' + (breakpoint - 1) + 'px)')) {
              activate(menu);
            }
          }, 50);
        });
      }
      else if (mode == 'useragent_custom'){
        if (options.useragent != ''){
          var ua = RegExp(options.useragent, 'i');
          if (navigator.userAgent.match(ua)){
            activate(menu);
          }
        }
      }
      else if (mode == 'useragent_predefined' && navigator.userAgent.match(/(android|bb\d+|meego)|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows (ce|phone)|xda|xiino/i)){
        activate(menu);
      }
    }
    return this;
  }
})(jQuery);
;
/*
 * sf-Smallscreen v1.2b - Provides small-screen compatibility for the jQuery Superfish plugin.
 *
 * Developer's note:
 * Built as a part of the Superfish project for Drupal (http://drupal.org/project/superfish)
 * Found any bug? have any cool ideas? contact me right away! http://drupal.org/user/619294/contact
 *
 * jQuery version: 1.3.x or higher.
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
  */

(function($){
  $.fn.sfsmallscreen = function(options){
    options = $.extend({
      mode: 'inactive',
      type: 'accordion',
      breakpoint: 768,
      breakpointUnit: 'px',
      useragent: '',
      title: '',
      addSelected: false,
      menuClasses: false,
      hyperlinkClasses: false,
      excludeClass_menu: '',
      excludeClass_hyperlink: '',
      includeClass_menu: '',
      includeClass_hyperlink: '',
      accordionButton: 1,
      expandText: 'Expand',
      collapseText: 'Collapse'
    }, options);

    // We need to clean up the menu from anything unnecessary.
    function refine(menu){
      var
      refined = menu.clone(),
      // Things that should not be in the small-screen menus.
      rm = refined.find('span.sf-sub-indicator, span.sf-description'),
      // This is a helper class for those who need to add extra markup that shouldn't exist
      // in the small-screen versions.
      rh = refined.find('.sf-smallscreen-remove'),
      // Mega-menus has to be removed too.
      mm = refined.find('ul.sf-megamenu');
      for (var a = 0; a < rh.length; a++){
        rh.eq(a).replaceWith(rh.eq(a).html());
      }
      for (var b = 0; b < rm.length; b++){
        rm.eq(b).remove();
      }
      if (mm.length > 0){
        mm.removeClass('sf-megamenu');
        var ol = refined.find('div.sf-megamenu-column > ol');
        for (var o = 0; o < ol.length; o++){
          ol.eq(o).replaceWith('<ul>' + ol.eq(o).html() + '</ul>');
        }
        var elements = ['div.sf-megamenu-column','.sf-megamenu-wrapper > ol','li.sf-megamenu-wrapper'];
        for (var i = 0; i < elements.length; i++){
          obj = refined.find(elements[i]);
          for (var t = 0; t < obj.length; t++){
            obj.eq(t).replaceWith(obj.eq(t).html());
          }
        }
        refined.find('.sf-megamenu-column').removeClass('sf-megamenu-column');
      }
      refined.add(refined.find('*')).css({width:''});
      return refined;
    }

    // Creating <option> elements out of the menu.
    function toSelect(menu, level){
      var
      items = '',
      childLI = $(menu).children('li');
      for (var a = 0; a < childLI.length; a++){
        var list = childLI.eq(a), parent = list.children('a, span');
        for (var b = 0; b < parent.length; b++){
          var
          item = parent.eq(b),
          path = item.is('a') ? item.attr('href') : '',
          // Class names modification.
          itemClone = item.clone(),
          classes = (options.hyperlinkClasses) ? ((options.excludeClass_hyperlink && itemClone.hasClass(options.excludeClass_hyperlink)) ? itemClone.removeClass(options.excludeClass_hyperlink).attr('class') : itemClone.attr('class')) : '',
          classes = (options.includeClass_hyperlink && !itemClone.hasClass(options.includeClass_hyperlink)) ? ((options.hyperlinkClasses) ? itemClone.addClass(options.includeClass_hyperlink).attr('class') : options.includeClass_hyperlink) : classes;
          // Retaining the active class if requested.
          if (options.addSelected && item.hasClass('active')){
            classes += ' active';
          }
          // <option> has to be disabled if the item is not a link.
          disable = item.is('span') || item.attr('href')=='#' ? ' disabled="disabled"' : '',
          // Crystal clear.
          subIndicator = 1 < level ? Array(level).join('-') + ' ' : '';
          // Preparing the <option> element.
          items += '<option value="' + path + '" class="' + classes + '"' + disable + '>' + subIndicator + $.trim(item.text()) +'</option>',
          childUL = list.find('> ul');
          // Using the function for the sub-menu of this item.
          for (var u = 0; u < childUL.length; u++){
            items += toSelect(childUL.eq(u), level + 1);
          }
        }
      }
      return items;
    }

    // Create the new version, hide the original.
    function convert(menu){
      var menuID = menu.attr('id'),
      // Creating a refined version of the menu.
      refinedMenu = refine(menu);
      // Currently the plugin provides two reactions to small screens.
      // Converting the menu to a <select> element, and converting to an accordion version of the menu.
      if (options.type == 'accordion'){
        var
        toggleID = menuID + '-toggle',
        accordionID = menuID + '-accordion';
        // Making sure the accordion does not exist.
        if ($('#' + accordionID).length == 0){
          var
          // Getting the style class.
          styleClass = menu.attr('class').split(' ').filter(function(item){
            return item.indexOf('sf-style-') > -1 ? item : '';
          }),
          // Creating the accordion.
          accordion = $(refinedMenu).attr('id', accordionID);
          // Removing unnecessary classes.
          accordion.removeClass('sf-horizontal sf-vertical sf-navbar sf-shadow sf-js-enabled');
          // Adding necessary classes.
          accordion.addClass('sf-accordion sf-hidden');
          // Removing style attributes and any unnecessary class.
          accordion.children('li').removeAttr('style').removeClass('sfHover');
          // Doing the same and making sure all the sub-menus are off-screen (hidden).
          accordion.find('ul').removeAttr('style').not('.sf-hidden').addClass('sf-hidden');
          // Creating the accordion toggle switch.
          var toggle = '<div class="sf-accordion-toggle ' + styleClass + '"><a href="#" id="' + toggleID + '"><span>' + options.title + '</span></a></div>';

          // Adding Expand\Collapse buttons if requested.
          if (options.accordionButton == 2){
            var parent = accordion.find('li.menuparent');
            for (var i = 0; i < parent.length; i++){
              parent.eq(i).prepend('<a href="#" class="sf-accordion-button">' + options.expandText + '</a>');
            }
          }
          // Inserting the according and hiding the original menu.
          menu.before(toggle).before(accordion).hide();

          var
          accordionElement = $('#' + accordionID),
          // Deciding what should be used as accordion buttons.
          buttonElement = (options.accordionButton < 2) ? 'a.menuparent,span.nolink.menuparent' : 'a.sf-accordion-button',
          button = accordionElement.find(buttonElement);

          // Attaching a click event to the toggle switch.
          $('#' + toggleID).bind('click', function(e){
            // Preventing the click.
            e.preventDefault();
            // Adding the sf-expanded class.
            $(this).toggleClass('sf-expanded');

            if (accordionElement.hasClass('sf-expanded')){
              // If the accordion is already expanded:
              // Hiding its expanded sub-menus and then the accordion itself as well.
              accordionElement.add(accordionElement.find('li.sf-expanded')).removeClass('sf-expanded')
              .end().find('ul').hide()
              // This is a bit tricky, it's the same trick that has been in use in the main plugin for sometime.
              // Basically we'll add a class that keeps the sub-menu off-screen and still visible,
              // and make it invisible and removing the class one moment before showing or hiding it.
              // This helps screen reader software access all the menu items.
              .end().hide().addClass('sf-hidden').show();
              // Changing the caption of any existing accordion buttons to 'Expand'.
              if (options.accordionButton == 2){
                accordionElement.find('a.sf-accordion-button').text(options.expandText);
              }
            }
            else {
              // But if it's collapsed,
              accordionElement.addClass('sf-expanded').hide().removeClass('sf-hidden').show();
            }
          });

          // Attaching a click event to the buttons.
          button.bind('click', function(e){
            // Making sure the buttons does not exist already.
            if ($(this).closest('li').children('ul').length > 0){
              e.preventDefault();
              // Selecting the parent menu items.
              var parent = $(this).closest('li');
              // Creating and inserting Expand\Collapse buttons to the parent menu items,
              // of course only if not already happened.
              if (options.accordionButton == 1 && parent.children('a.menuparent,span.nolink.menuparent').length > 0 && parent.children('ul').children('li.sf-clone-parent').length == 0){
                var
                // Cloning the hyperlink of the parent menu item.
                cloneLink = parent.children('a.menuparent,span.nolink.menuparent').clone(),
                // Wrapping the hyerplinks in <li>.
                cloneLink = $('<li class="sf-clone-parent" />').html(cloneLink);
                // Adding a helper class and attaching them to the sub-menus.
                parent.children('ul').addClass('sf-has-clone-parent').prepend(cloneLink);
              }
              // Once the button is clicked, collapse the sub-menu if it's expanded.
              if (parent.hasClass('sf-expanded')){
                parent.children('ul').slideUp('fast', function(){
                  // Doing the accessibility trick after hiding the sub-menu.
                  $(this).closest('li').removeClass('sf-expanded').end().addClass('sf-hidden').show();
                });
                // Changing the caption of the inserted Collapse link to 'Expand', if any is inserted.
                if (options.accordionButton == 2 && parent.children('.sf-accordion-button').length > 0){
                  parent.children('.sf-accordion-button').text(options.expandText);
                }
              }
              // Otherwise, expand the sub-menu.
              else {
                // Doing the accessibility trick and then showing the sub-menu.
                parent.children('ul').hide().removeClass('sf-hidden').slideDown('fast')
                // Changing the caption of the inserted Expand link to 'Collape', if any is inserted.
                .end().addClass('sf-expanded').children('a.sf-accordion-button').text(options.collapseText)
                // Hiding any expanded sub-menu of the same level.
                .end().siblings('li.sf-expanded').children('ul')
                .slideUp('fast', function(){
                  // Doing the accessibility trick after hiding it.
                  $(this).closest('li').removeClass('sf-expanded').end().addClass('sf-hidden').show();
                })
                // Assuming Expand\Collapse buttons do exist, resetting captions, in those hidden sub-menus.
                .parent().children('a.sf-accordion-button').text(options.expandText);
              }
            }
          });
        }
      }
      else {
        var
        // Class names modification.
        menuClone = menu.clone(), classes = (options.menuClasses) ? ((options.excludeClass_menu && menuClone.hasClass(options.excludeClass_menu)) ? menuClone.removeClass(options.excludeClass_menu).attr('class') : menuClone.attr('class')) : '',
        classes = (options.includeClass_menu && !menuClone.hasClass(options.includeClass_menu)) ? ((options.menuClasses) ? menuClone.addClass(options.includeClass_menu).attr('class') : options.includeClass_menu) : classes,
        classes = (classes) ? ' class="' + classes + '"' : '';

        // Making sure the <select> element does not exist already.
        if ($('#' + menuID + '-select').length == 0){
          // Creating the <option> elements.
          var newMenu = toSelect(refinedMenu, 1),
          // Creating the <select> element and assigning an ID and class name.
          selectList = $('<select' + classes + ' id="' + menuID + '-select"/>')
          // Attaching the title and the items to the <select> element.
          .html('<option>' + options.title + '</option>' + newMenu)
          // Attaching an event then.
          .change(function(){
            // Except for the first option that is the menu title and not a real menu item.
            if ($('option:selected', this).index()){
              window.location = selectList.val();
            }
          });
          // Applying the addSelected option to it.
          if (options.addSelected){
            selectList.find('.active').attr('selected', !0);
          }
          // Finally inserting the <select> element into the document then hiding the original menu.
          menu.before(selectList).hide();
        }
      }
    }

    // Turn everything back to normal.
    function turnBack(menu){
      var
      id = '#' + menu.attr('id');
      // Removing the small screen version.
      $(id + '-' + options.type).remove();
      // Removing the accordion toggle switch as well.
      if (options.type == 'accordion'){
        $(id + '-toggle').parent('div').remove();
      }
      // Crystal clear!
      $(id).show();
    }

    // Return original object to support chaining.
    // Although this is unnecessary because of the way the module uses these plugins.
    for (var s = 0; s < this.length; s++){
      var
      menu = $(this).eq(s),
      mode = options.mode;
      // The rest is crystal clear, isn't it? :)
      if (mode == 'always_active'){
        convert(menu);
      }
      else if (mode == 'window_width'){
        var breakpoint = (options.breakpointUnit == 'em') ? (options.breakpoint * parseFloat($('body').css('font-size'))) : options.breakpoint,
        windowWidth = window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth,
        timer;
        if ((typeof Modernizr === 'undefined' || typeof Modernizr.mq !== 'function') && windowWidth < breakpoint){
          convert(menu);
        }
        else if (typeof Modernizr !== 'undefined' && typeof Modernizr.mq === 'function' && Modernizr.mq('(max-width:' + (breakpoint - 1) + 'px)')) {
          convert(menu);
        }
        $(window).resize(function(){
          clearTimeout(timer);
          timer = setTimeout(function(){
            var windowWidth = window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth;
            if ((typeof Modernizr === 'undefined' || typeof Modernizr.mq !== 'function') && windowWidth < breakpoint){
              convert(menu);
            }
            else if (typeof Modernizr !== 'undefined' && typeof Modernizr.mq === 'function' && Modernizr.mq('(max-width:' + (breakpoint - 1) + 'px)')) {
              convert(menu);
            }
            else {
              turnBack(menu);
            }
          }, 50);
        });
      }
      else if (mode == 'useragent_custom'){
        if (options.useragent != ''){
          var ua = RegExp(options.useragent, 'i');
          if (navigator.userAgent.match(ua)){
            convert(menu);
          }
        }
      }
      else if (mode == 'useragent_predefined' && navigator.userAgent.match(/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od|ad)|iris|kindle|lge |maemo|midp|mmp|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows (ce|phone)|xda|xiino/i)){
        convert(menu);
      }
    }
    return this;
  }
})(jQuery);
;
/*
 * Supposition v0.2 - an optional enhancer for Superfish jQuery menu widget.
 *
 * Copyright (c) 2008 Joel Birch - based mostly on work by Jesse Klaasse and credit goes largely to him.
 * Special thanks to Karl Swedberg for valuable input.
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 */
/*
 * This is not the original jQuery Supposition plugin.
 * Please refer to the README for more information.
 */

(function($){
  $.fn.supposition = function(){
    var $w = $(window), /*do this once instead of every onBeforeShow call*/
    _offset = function(dir) {
      return window[dir == 'y' ? 'pageYOffset' : 'pageXOffset']
      || document.documentElement && document.documentElement[dir=='y' ? 'scrollTop' : 'scrollLeft']
      || document.body[dir=='y' ? 'scrollTop' : 'scrollLeft'];
    },
    onHide = function(){
      this.css({bottom:''});
    },
    onBeforeShow = function(){
      this.each(function(){
        var $u = $(this);
        $u.css('display','block');
        var $mul = $u.closest('.sf-menu'),
        level = $u.parents('ul').length,
        menuWidth = $u.width(),
        menuParentWidth = $u.closest('li').outerWidth(true),
        menuParentLeft = $u.closest('li').offset().left,
        totalRight = $w.width() + _offset('x'),
        menuRight = $u.offset().left + menuWidth,
        exactMenuWidth = (menuRight > (menuParentWidth + menuParentLeft)) ? menuWidth - (menuRight - (menuParentWidth + menuParentLeft)) : menuWidth;
        if ($u.parents('.sf-js-enabled').hasClass('rtl')) {
          if (menuParentLeft < exactMenuWidth) {
            if (($mul.hasClass('sf-horizontal') && level == 1) || ($mul.hasClass('sf-navbar') && level == 2)){
              $u.css({left:0,right:'auto'});
            }
            else {
              $u.css({left:menuParentWidth + 'px',right:'auto'});
            }
          }
        }
        else {
          if (menuRight > totalRight && menuParentLeft > menuWidth) {
            if (($mul.hasClass('sf-horizontal') && level == 1) || ($mul.hasClass('sf-navbar') && level == 2)){
              $u.css({right:0,left:'auto'});
            }
            else {
              $u.css({right:menuParentWidth + 'px',left:'auto'});
            }
          }
        }
        var windowHeight = $w.height(),
        offsetTop = $u.offset().top,
        menuParentShadow = ($mul.hasClass('sf-shadow') && $u.css('padding-bottom').length > 0) ? parseInt($u.css('padding-bottom').slice(0,-2)) : 0,
        menuParentHeight = ($mul.hasClass('sf-vertical')) ? '-' + menuParentShadow : $u.parent().outerHeight(true) - menuParentShadow,
        menuHeight = $u.height(),
        baseline = windowHeight + _offset('y');
        var expandUp = ((offsetTop + menuHeight > baseline) && (offsetTop > menuHeight));
        if (expandUp) {
          $u.css({bottom:menuParentHeight + 'px',top:'auto'});
        }
        $u.css('display','none');
      });
    };

    return this.each(function() {
      var o = $.fn.superfish.o[this.serial]; /* get this menu's options */

      /* if callbacks already set, store them */
      var _onBeforeShow = o.onBeforeShow,
      _onHide = o.onHide;

      $.extend($.fn.superfish.o[this.serial],{
        onBeforeShow: function() {
          onBeforeShow.call(this); /* fire our Supposition callback */
          _onBeforeShow.call(this); /* fire stored callbacks */
        },
        onHide: function() {
          onHide.call(this); /* fire our Supposition callback */
          _onHide.call(this); /* fire stored callbacks */
        }
      });
    });
  };
})(jQuery);;
/*
 * Superfish v1.4.8 - jQuery menu widget
 * Copyright (c) 2008 Joel Birch
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 *
 * CHANGELOG: http://users.tpg.com.au/j_birch/plugins/superfish/changelog.txt
 */
/*
 * This is not the original jQuery Superfish plugin.
 * Please refer to the README for more information.
 */

(function($){
  $.fn.superfish = function(op){
    var sf = $.fn.superfish,
      c = sf.c,
      $arrow = $(['<span class="',c.arrowClass,'"> &#187;</span>'].join('')),
      over = function(){
        var $$ = $(this), menu = getMenu($$);
        clearTimeout(menu.sfTimer);
        $$.showSuperfishUl().siblings().hideSuperfishUl();
      },
      out = function(){
        var $$ = $(this), menu = getMenu($$), o = sf.op;
        clearTimeout(menu.sfTimer);
        menu.sfTimer=setTimeout(function(){
          if ($$.children('.sf-clicked').length == 0){
            o.retainPath=($.inArray($$[0],o.$path)>-1);
            $$.hideSuperfishUl();
            if (o.$path.length && $$.parents(['li.',o.hoverClass].join('')).length<1){over.call(o.$path);}
          }
        },o.delay);
      },
      getMenu = function($menu){
        var menu = $menu.parents(['ul.',c.menuClass,':first'].join(''))[0];
        sf.op = sf.o[menu.serial];
        return menu;
      },
      addArrow = function($a){ $a.addClass(c.anchorClass).append($arrow.clone()); };

    return this.each(function() {
      var s = this.serial = sf.o.length;
      var o = $.extend({},sf.defaults,op);
      o.$path = $('li.'+o.pathClass,this).slice(0,o.pathLevels),
      p = o.$path;
      for (var l = 0; l < p.length; l++){
        p.eq(l).addClass([o.hoverClass,c.bcClass].join(' ')).filter('li:has(ul)').removeClass(o.pathClass);
      }
      sf.o[s] = sf.op = o;

      $('li:has(ul)',this)[($.fn.hoverIntent && !o.disableHI) ? 'hoverIntent' : 'hover'](over,out).each(function() {
        if (o.autoArrows) addArrow( $(this).children('a:first-child, span.nolink:first-child') );
      })
      .not('.'+c.bcClass)
        .hideSuperfishUl();

      var $a = $('a, span.nolink',this);
      $a.each(function(i){
        var $li = $a.eq(i).parents('li');
        $a.eq(i).focus(function(){over.call($li);}).blur(function(){out.call($li);});
      });
      o.onInit.call(this);

    }).each(function() {
      var menuClasses = [c.menuClass],
      addShadow = true;
      if ($.browser !== undefined){
        if ($.browser.msie && $.browser.version < 7){
          addShadow = false;
        }
      }
      if (sf.op.dropShadows && addShadow){
        menuClasses.push(c.shadowClass);
      }
      $(this).addClass(menuClasses.join(' '));
    });
  };

  var sf = $.fn.superfish;
  sf.o = [];
  sf.op = {};
  sf.IE7fix = function(){
    var o = sf.op;
    if ($.browser !== undefined){
      if ($.browser.msie && $.browser.version > 6 && o.dropShadows && o.animation.opacity != undefined) {
        this.toggleClass(sf.c.shadowClass+'-off');
      }
    }
  };
  sf.c = {
    bcClass: 'sf-breadcrumb',
    menuClass: 'sf-js-enabled',
    anchorClass: 'sf-with-ul',
    arrowClass: 'sf-sub-indicator',
    shadowClass: 'sf-shadow'
  };
  sf.defaults = {
    hoverClass: 'sfHover',
    pathClass: 'overideThisToUse',
    pathLevels: 1,
    delay: 800,
    animation: {opacity:'show'},
    speed: 'fast',
    autoArrows: true,
    dropShadows: true,
    disableHI: false, // true disables hoverIntent detection
    onInit: function(){}, // callback functions
    onBeforeShow: function(){},
    onShow: function(){},
    onHide: function(){}
  };
  $.fn.extend({
    hideSuperfishUl : function(){
      var o = sf.op,
        not = (o.retainPath===true) ? o.$path : '';
      o.retainPath = false;
      var $ul = $(['li.',o.hoverClass].join(''),this).add(this).not(not).removeClass(o.hoverClass)
          .children('ul').addClass('sf-hidden');
      o.onHide.call($ul);
      return this;
    },
    showSuperfishUl : function(){
      var o = sf.op,
        sh = sf.c.shadowClass+'-off',
        $ul = this.addClass(o.hoverClass)
          .children('ul.sf-hidden').hide().removeClass('sf-hidden');
      sf.IE7fix.call($ul);
      o.onBeforeShow.call($ul);
      $ul.animate(o.animation,o.speed,function(){ sf.IE7fix.call($ul); o.onShow.call($ul); });
      return this;
    }
  });
})(jQuery);;
/*
 * Supersubs v0.4b - jQuery plugin
 * Copyright (c) 2013 Joel Birch
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 *
 * This plugin automatically adjusts submenu widths of suckerfish-style menus to that of
 * their longest list item children. If you use this, please expect bugs and report them
 * to the jQuery Google Group with the word 'Superfish' in the subject line.
 *
 */
/*
 * This is not the original jQuery Supersubs plugin.
 * Please refer to the README for more information.
 */

(function($){ // $ will refer to jQuery within this closure
  $.fn.supersubs = function(options){
    var opts = $.extend({}, $.fn.supersubs.defaults, options);
    // return original object to support chaining
    // Although this is unnecessary due to the way the module uses these plugins.
    for (var a = 0; a < this.length; a++) {
      // cache selections
      var $$ = $(this).eq(a),
      // support metadata
      o = $.meta ? $.extend({}, opts, $$.data()) : opts;
      // Jump one level if it's a "NavBar"
      if ($$.hasClass('sf-navbar')) {
        $$ = $$.children('li').children('ul');
      }
      // cache all ul elements
      var $ULs = $$.find('ul'),
      // get the font size of menu.
      // .css('fontSize') returns various results cross-browser, so measure an em dash instead
      fontsize = $('<li id="menu-fontsize">&#8212;</li>'),
      size = fontsize.attr('style','padding:0;position:absolute;top:-99999em;width:auto;')
      .appendTo($$)[0].clientWidth; //clientWidth is faster than width()
      // remove em dash
      fontsize.remove();

      // loop through each ul in menu
      for (var b = 0; b < $ULs.length; b++) {
        var
        // cache this ul
        $ul = $ULs.eq(b);
        // If a multi-column sub-menu, and only if correctly configured.
        if (o.megamenu && $ul.hasClass('sf-megamenu') && $ul.find('.sf-megamenu-column').length > 0){
          // Look through each column.
          var $column = $ul.find('div.sf-megamenu-column > ol'),
          // Overall width.
          mwWidth = 0;
          for (var d = 0; d < $column.length; d++){
            resize($column.eq(d));
            // New column width, in pixels.
            var colWidth = $column.width();
            // Just a trick to convert em unit to px.
            $column.css({width:colWidth})
            // Making column parents the same size.
            .parents('.sf-megamenu-column').css({width:colWidth});
            // Overall width.
            mwWidth += parseInt(colWidth);
          }
          // Resizing the columns container too.
          $ul.add($ul.find('li.sf-megamenu-wrapper, li.sf-megamenu-wrapper > ol')).css({width:mwWidth});
        }
        else {
          resize($ul);
        }
      }
    }
    function resize($ul){
      var
      // get all (li) children of this ul
      $LIs = $ul.children(),
      // get all anchor grand-children
      $As = $LIs.children('a');
      // force content to one line and save current float property
      $LIs.css('white-space','nowrap');
      // remove width restrictions and floats so elements remain vertically stacked
      $ul.add($LIs).add($As).css({float:'none',width:'auto'});
      // this ul will now be shrink-wrapped to longest li due to position:absolute
      // so save its width as ems.
      var emWidth = $ul.get(0).clientWidth / size;
      // add more width to ensure lines don't turn over at certain sizes in various browsers
      emWidth += o.extraWidth;
      // restrict to at least minWidth and at most maxWidth
      if (emWidth > o.maxWidth) {emWidth = o.maxWidth;}
      else if (emWidth < o.minWidth) {emWidth = o.minWidth;}
      emWidth += 'em';
      // set ul to width in ems
      $ul.css({width:emWidth});
      // restore li floats to avoid IE bugs
      // set li width to full width of this ul
      // revert white-space to normal
      $LIs.add($As).css({float:'',width:'',whiteSpace:''});
      // update offset position of descendant ul to reflect new width of parent.
      // set it to 100% in case it isn't already set to this in the CSS
      for (var c = 0; c < $LIs.length; c++) {
        var $childUl = $LIs.eq(c).children('ul');
        var offsetDirection = $childUl.css('left') !== undefined ? 'left' : 'right';
        $childUl.css(offsetDirection,'100%');
      }
    }
    return this;
  };
  // expose defaults
  $.fn.supersubs.defaults = {
    megamenu: true, // define width for multi-column sub-menus and their columns.
    minWidth: 12, // requires em unit.
    maxWidth: 27, // requires em unit.
    extraWidth: 1 // extra width can ensure lines don't sometimes turn over due to slight browser differences in how they round-off values
  };
})(jQuery); // plugin code ends
;
/**
 * @file
 * The Superfish Drupal Behavior to apply the Superfish jQuery plugin to lists.
 */

(function ($) {
  Drupal.behaviors.superfish = {
    attach: function (context, settings) {
      // Take a look at each list to apply Superfish to.
      $.each(settings.superfish || {}, function(index, options) {
        // Process all Superfish lists.
        $('#superfish-' + options.id, context).once('superfish', function() {
          var list = $(this);

          // Check if we are to apply the Supersubs plug-in to it.
          if (options.plugins || false) {
            if (options.plugins.supersubs || false) {
              list.supersubs(options.plugins.supersubs);
            }
          }

          // Apply Superfish to the list.
          list.superfish(options.sf);

          // Check if we are to apply any other plug-in to it.
          if (options.plugins || false) {
            if (options.plugins.touchscreen || false) {
              list.sftouchscreen(options.plugins.touchscreen);
            }
            if (options.plugins.smallscreen || false) {
              list.sfsmallscreen(options.plugins.smallscreen);
            }
            if (options.plugins.automaticwidth || false) {
              list.sfautomaticwidth();
            }
            if (options.plugins.supposition || false) {
              list.supposition();
            }
            if (options.plugins.bgiframe || false) {
              list.find('ul').bgIframe({opacity:false});
            }
          }
        });
      });
    }
  };
})(jQuery);;
