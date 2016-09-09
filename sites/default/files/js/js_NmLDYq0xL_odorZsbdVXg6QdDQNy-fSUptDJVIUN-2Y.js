(function ($) {

/**
 * A progressbar object. Initialized with the given id. Must be inserted into
 * the DOM afterwards through progressBar.element.
 *
 * method is the function which will perform the HTTP request to get the
 * progress bar state. Either "GET" or "POST".
 *
 * e.g. pb = new progressBar('myProgressBar');
 *      some_element.appendChild(pb.element);
 */
Drupal.progressBar = function (id, updateCallback, method, errorCallback) {
  var pb = this;
  this.id = id;
  this.method = method || 'GET';
  this.updateCallback = updateCallback;
  this.errorCallback = errorCallback;

  // The WAI-ARIA setting aria-live="polite" will announce changes after users
  // have completed their current activity and not interrupt the screen reader.
  this.element = $('<div class="progress" aria-live="polite"></div>').attr('id', id);
  this.element.html('<div class="bar"><div class="filled"></div></div>' +
                    '<div class="percentage"></div>' +
                    '<div class="message">&nbsp;</div>');
};

/**
 * Set the percentage and status message for the progressbar.
 */
Drupal.progressBar.prototype.setProgress = function (percentage, message) {
  if (percentage >= 0 && percentage <= 100) {
    $('div.filled', this.element).css('width', percentage + '%');
    $('div.percentage', this.element).html(percentage + '%');
  }
  $('div.message', this.element).html(message);
  if (this.updateCallback) {
    this.updateCallback(percentage, message, this);
  }
};

/**
 * Start monitoring progress via Ajax.
 */
Drupal.progressBar.prototype.startMonitoring = function (uri, delay) {
  this.delay = delay;
  this.uri = uri;
  this.sendPing();
};

/**
 * Stop monitoring progress via Ajax.
 */
Drupal.progressBar.prototype.stopMonitoring = function () {
  clearTimeout(this.timer);
  // This allows monitoring to be stopped from within the callback.
  this.uri = null;
};

/**
 * Request progress data from server.
 */
Drupal.progressBar.prototype.sendPing = function () {
  if (this.timer) {
    clearTimeout(this.timer);
  }
  if (this.uri) {
    var pb = this;
    // When doing a post request, you need non-null data. Otherwise a
    // HTTP 411 or HTTP 406 (with Apache mod_security) error may result.
    $.ajax({
      type: this.method,
      url: this.uri,
      data: '',
      dataType: 'json',
      success: function (progress) {
        // Display errors.
        if (progress.status == 0) {
          pb.displayError(progress.data);
          return;
        }
        // Update display.
        pb.setProgress(progress.percentage, progress.message);
        // Schedule next timer.
        pb.timer = setTimeout(function () { pb.sendPing(); }, pb.delay);
      },
      error: function (xmlhttp) {
        pb.displayError(Drupal.ajaxError(xmlhttp, pb.uri));
      }
    });
  }
};

/**
 * Display errors on the page.
 */
Drupal.progressBar.prototype.displayError = function (string) {
  var error = $('<div class="messages error"></div>').html(string);
  $(this.element).before(error).hide();

  if (this.errorCallback) {
    this.errorCallback(this);
  }
};

})(jQuery);
;
/**
 * @file
 *
 * Implement a modal form.
 *
 * @see modal.inc for documentation.
 *
 * This javascript relies on the CTools ajax responder.
 */

(function ($) {
  // Make sure our objects are defined.
  Drupal.CTools = Drupal.CTools || {};
  Drupal.CTools.Modal = Drupal.CTools.Modal || {};

  /**
   * Display the modal
   *
   * @todo -- document the settings.
   */
  Drupal.CTools.Modal.show = function(choice) {
    var opts = {};

    if (choice && typeof choice == 'string' && Drupal.settings[choice]) {
      // This notation guarantees we are actually copying it.
      $.extend(true, opts, Drupal.settings[choice]);
    }
    else if (choice) {
      $.extend(true, opts, choice);
    }

    var defaults = {
      modalTheme: 'CToolsModalDialog',
      throbberTheme: 'CToolsModalThrobber',
      animation: 'show',
      animationSpeed: 'slow',
      modalSize: {
        type: 'scale',
        width: .8,
        height: .8,
        addWidth: 0,
        addHeight: 0,
        // How much to remove from the inner content to make space for the
        // theming.
        contentRight: 25,
        contentBottom: 45
      },
      modalOptions: {
        opacity: .55,
        background: '#fff'
      },
      modalClass: 'default'
    };

    var settings = {};
    $.extend(true, settings, defaults, Drupal.settings.CToolsModal, opts);

    if (Drupal.CTools.Modal.currentSettings && Drupal.CTools.Modal.currentSettings != settings) {
      Drupal.CTools.Modal.modal.remove();
      Drupal.CTools.Modal.modal = null;
    }

    Drupal.CTools.Modal.currentSettings = settings;

    var resize = function(e) {
      // When creating the modal, it actually exists only in a theoretical
      // place that is not in the DOM. But once the modal exists, it is in the
      // DOM so the context must be set appropriately.
      var context = e ? document : Drupal.CTools.Modal.modal;

      if (Drupal.CTools.Modal.currentSettings.modalSize.type == 'scale') {
        var width = $(window).width() * Drupal.CTools.Modal.currentSettings.modalSize.width;
        var height = $(window).height() * Drupal.CTools.Modal.currentSettings.modalSize.height;
      }
      else {
        var width = Drupal.CTools.Modal.currentSettings.modalSize.width;
        var height = Drupal.CTools.Modal.currentSettings.modalSize.height;
      }

      // Use the additionol pixels for creating the width and height.
      $('div.ctools-modal-content', context).css({
        'width': width + Drupal.CTools.Modal.currentSettings.modalSize.addWidth + 'px',
        'height': height + Drupal.CTools.Modal.currentSettings.modalSize.addHeight + 'px'
      });
      $('div.ctools-modal-content .modal-content', context).css({
        'width': (width - Drupal.CTools.Modal.currentSettings.modalSize.contentRight) + 'px',
        'height': (height - Drupal.CTools.Modal.currentSettings.modalSize.contentBottom) + 'px'
      });
    }

    if (!Drupal.CTools.Modal.modal) {
      Drupal.CTools.Modal.modal = $(Drupal.theme(settings.modalTheme));
      if (settings.modalSize.type == 'scale') {
        $(window).bind('resize', resize);
      }
    }
    $('body').addClass('ctools-modal-open');
    resize();

    $('span.modal-title', Drupal.CTools.Modal.modal).html(Drupal.CTools.Modal.currentSettings.loadingText);
    Drupal.CTools.Modal.modalContent(Drupal.CTools.Modal.modal, settings.modalOptions, settings.animation, settings.animationSpeed, settings.modalClass);
    $('#modalContent .modal-content').html(Drupal.theme(settings.throbberTheme)).addClass('ctools-modal-loading');

    // Position autocomplete results based on the scroll position of the modal.
    $('#modalContent .modal-content').delegate('input.form-autocomplete', 'keyup', function() {
      $('#autocomplete').css('top', $(this).position().top + $(this).outerHeight() + $(this).offsetParent().filter('#modal-content').scrollTop());
    });
  };

  /**
   * Hide the modal
   */
  Drupal.CTools.Modal.dismiss = function() {
    if (Drupal.CTools.Modal.modal) {
      Drupal.CTools.Modal.unmodalContent(Drupal.CTools.Modal.modal);
    }
  };

  /**
   * Provide the HTML to create the modal dialog.
   */
  Drupal.theme.prototype.CToolsModalDialog = function () {
    var html = ''
    html += '  <div id="ctools-modal">'
    html += '    <div class="ctools-modal-content">' // panels-modal-content
    html += '      <div class="modal-header">';
    html += '        <a class="close" href="#">';
    html +=            Drupal.CTools.Modal.currentSettings.closeText + Drupal.CTools.Modal.currentSettings.closeImage;
    html += '        </a>';
    html += '        <span id="modal-title" class="modal-title">&nbsp;</span>';
    html += '      </div>';
    html += '      <div id="modal-content" class="modal-content">';
    html += '      </div>';
    html += '    </div>';
    html += '  </div>';

    return html;
  }

  /**
   * Provide the HTML to create the throbber.
   */
  Drupal.theme.prototype.CToolsModalThrobber = function () {
    var html = '';
    html += '  <div id="modal-throbber">';
    html += '    <div class="modal-throbber-wrapper">';
    html +=        Drupal.CTools.Modal.currentSettings.throbber;
    html += '    </div>';
    html += '  </div>';

    return html;
  };

  /**
   * Figure out what settings string to use to display a modal.
   */
  Drupal.CTools.Modal.getSettings = function (object) {
    var match = $(object).attr('class').match(/ctools-modal-(\S+)/);
    if (match) {
      return match[1];
    }
  }

  /**
   * Click function for modals that can be cached.
   */
  Drupal.CTools.Modal.clickAjaxCacheLink = function () {
    Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(this));
    return Drupal.CTools.AJAX.clickAJAXCacheLink.apply(this);
  };

  /**
   * Handler to prepare the modal for the response
   */
  Drupal.CTools.Modal.clickAjaxLink = function () {
    Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(this));
    return false;
  };

  /**
   * Submit responder to do an AJAX submit on all modal forms.
   */
  Drupal.CTools.Modal.submitAjaxForm = function(e) {
    var $form = $(this);
    var url = $form.attr('action');

    setTimeout(function() { Drupal.CTools.AJAX.ajaxSubmit($form, url); }, 1);
    return false;
  }

  /**
   * Bind links that will open modals to the appropriate function.
   */
  Drupal.behaviors.ZZCToolsModal = {
    attach: function(context) {
      // Bind links
      // Note that doing so in this order means that the two classes can be
      // used together safely.
      /*
       * @todo remimplement the warm caching feature
       $('a.ctools-use-modal-cache', context).once('ctools-use-modal', function() {
         $(this).click(Drupal.CTools.Modal.clickAjaxCacheLink);
         Drupal.CTools.AJAX.warmCache.apply(this);
       });
        */

      $('area.ctools-use-modal, a.ctools-use-modal', context).once('ctools-use-modal', function() {
        var $this = $(this);
        $this.click(Drupal.CTools.Modal.clickAjaxLink);
        // Create a drupal ajax object
        var element_settings = {};
        if ($this.attr('href')) {
          element_settings.url = $this.attr('href');
          element_settings.event = 'click';
          element_settings.progress = { type: 'throbber' };
        }
        var base = $this.attr('href');
        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
      });

      // Bind buttons
      $('input.ctools-use-modal, button.ctools-use-modal', context).once('ctools-use-modal', function() {
        var $this = $(this);
        $this.click(Drupal.CTools.Modal.clickAjaxLink);
        var button = this;
        var element_settings = {};

        // AJAX submits specified in this manner automatically submit to the
        // normal form action.
        element_settings.url = Drupal.CTools.Modal.findURL(this);
        if (element_settings.url == '') {
          element_settings.url = $(this).closest('form').attr('action');
        }
        element_settings.event = 'click';
        element_settings.setClick = true;

        var base = $this.attr('id');
        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);

        // Make sure changes to settings are reflected in the URL.
        $('.' + $(button).attr('id') + '-url').change(function() {
          Drupal.ajax[base].options.url = Drupal.CTools.Modal.findURL(button);
        });
      });

      // Bind our custom event to the form submit
      $('#modal-content form', context).once('ctools-use-modal', function() {
        var $this = $(this);
        var element_settings = {};

        element_settings.url = $this.attr('action');
        element_settings.event = 'submit';
        element_settings.progress = { 'type': 'throbber' }
        var base = $this.attr('id');

        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
        Drupal.ajax[base].form = $this;

        $('input[type=submit], button', this).click(function(event) {
          Drupal.ajax[base].element = this;
          this.form.clk = this;
          // Stop autocomplete from submitting.
          if (Drupal.autocompleteSubmit && !Drupal.autocompleteSubmit()) {
            return false;
          }
          // An empty event means we were triggered via .click() and
          // in jquery 1.4 this won't trigger a submit.
          if (event.bubbles == undefined) {
            $(this.form).trigger('submit');
            return false;
          }
        });
      });

      // Bind a click handler to allow elements with the 'ctools-close-modal'
      // class to close the modal.
      $('.ctools-close-modal', context).once('ctools-close-modal')
        .click(function() {
          Drupal.CTools.Modal.dismiss();
          return false;
        });
    }
  };

  // The following are implementations of AJAX responder commands.

  /**
   * AJAX responder command to place HTML within the modal.
   */
  Drupal.CTools.Modal.modal_display = function(ajax, response, status) {
    if ($('#modalContent').length == 0) {
      Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(ajax.element));
    }
    $('#modal-title').html(response.title);
    // Simulate an actual page load by scrolling to the top after adding the
    // content. This is helpful for allowing users to see error messages at the
    // top of a form, etc.
    $('#modal-content').html(response.output).scrollTop(0);

    // Attach behaviors within a modal dialog.
    var settings = response.settings || ajax.settings || Drupal.settings;
    Drupal.attachBehaviors('#modalContent', settings);

    if ($('#modal-content').hasClass('ctools-modal-loading')) {
      $('#modal-content').removeClass('ctools-modal-loading');
    }
    else {
      // If the modal was already shown, and we are simply replacing its
      // content, then focus on the first focusable element in the modal.
      // (When first showing the modal, focus will be placed on the close
      // button by the show() function called above.)
      $('#modal-content :focusable:first').focus();
    }
  }

  /**
   * AJAX responder command to dismiss the modal.
   */
  Drupal.CTools.Modal.modal_dismiss = function(command) {
    Drupal.CTools.Modal.dismiss();
    $('link.ctools-temporary-css').remove();
  }

  /**
   * Display loading
   */
  //Drupal.CTools.AJAX.commands.modal_loading = function(command) {
  Drupal.CTools.Modal.modal_loading = function(command) {
    Drupal.CTools.Modal.modal_display({
      output: Drupal.theme(Drupal.CTools.Modal.currentSettings.throbberTheme),
      title: Drupal.CTools.Modal.currentSettings.loadingText
    });
  }

  /**
   * Find a URL for an AJAX button.
   *
   * The URL for this gadget will be composed of the values of items by
   * taking the ID of this item and adding -url and looking for that
   * class. They need to be in the form in order since we will
   * concat them all together using '/'.
   */
  Drupal.CTools.Modal.findURL = function(item) {
    var url = '';
    var url_class = '.' + $(item).attr('id') + '-url';
    $(url_class).each(
      function() {
        var $this = $(this);
        if (url && $this.val()) {
          url += '/';
        }
        url += $this.val();
      });
    return url;
  };


  /**
   * modalContent
   * @param content string to display in the content box
   * @param css obj of css attributes
   * @param animation (fadeIn, slideDown, show)
   * @param speed (valid animation speeds slow, medium, fast or # in ms)
   * @param modalClass class added to div#modalContent
   */
  Drupal.CTools.Modal.modalContent = function(content, css, animation, speed, modalClass) {
    // If our animation isn't set, make it just show/pop
    if (!animation) {
      animation = 'show';
    }
    else {
      // If our animation isn't "fadeIn" or "slideDown" then it always is show
      if (animation != 'fadeIn' && animation != 'slideDown') {
        animation = 'show';
      }
    }

    if (!speed) {
      speed = 'fast';
    }

    // Build our base attributes and allow them to be overriden
    css = jQuery.extend({
      position: 'absolute',
      left: '0px',
      margin: '0px',
      background: '#000',
      opacity: '.55'
    }, css);

    // Add opacity handling for IE.
    css.filter = 'alpha(opacity=' + (100 * css.opacity) + ')';
    content.hide();

    // If we already have modalContent, remove it.
    if ($('#modalBackdrop').length) $('#modalBackdrop').remove();
    if ($('#modalContent').length) $('#modalContent').remove();

    // position code lifted from http://www.quirksmode.org/viewport/compatibility.html
    if (self.pageYOffset) { // all except Explorer
    var wt = self.pageYOffset;
    } else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
      var wt = document.documentElement.scrollTop;
    } else if (document.body) { // all other Explorers
      var wt = document.body.scrollTop;
    }

    // Get our dimensions

    // Get the docHeight and (ugly hack) add 50 pixels to make sure we dont have a *visible* border below our div
    var docHeight = $(document).height() + 50;
    var docWidth = $(document).width();
    var winHeight = $(window).height();
    var winWidth = $(window).width();
    if( docHeight < winHeight ) docHeight = winHeight;

    // Create our divs
    $('body').append('<div id="modalBackdrop" class="backdrop-' + modalClass + '" style="z-index: 1000; display: none;"></div><div id="modalContent" class="modal-' + modalClass + '" style="z-index: 1001; position: absolute;">' + $(content).html() + '</div>');

    // Get a list of the tabbable elements in the modal content.
    var getTabbableElements = function () {
      var tabbableElements = $('#modalContent :tabbable'),
          radioButtons = tabbableElements.filter('input[type="radio"]');

      // The list of tabbable elements from jQuery is *almost* right. The
      // exception is with groups of radio buttons. The list from jQuery will
      // include all radio buttons, when in fact, only the selected radio button
      // is tabbable, and if no radio buttons in a group are selected, then only
      // the first is tabbable.
      if (radioButtons.length > 0) {
        // First, build up an index of which groups have an item selected or not.
        var anySelected = {};
        radioButtons.each(function () {
          var name = this.name;

          if (typeof anySelected[name] === 'undefined') {
            anySelected[name] = radioButtons.filter('input[name="' + name + '"]:checked').length !== 0;
          }
        });

        // Next filter out the radio buttons that aren't really tabbable.
        var found = {};
        tabbableElements = tabbableElements.filter(function () {
          var keep = true;

          if (this.type == 'radio') {
            if (anySelected[this.name]) {
              // Only keep the selected one.
              keep = this.checked;
            }
            else {
              // Only keep the first one.
              if (found[this.name]) {
                keep = false;
              }
              found[this.name] = true;
            }
          }

          return keep;
        });
      }

      return tabbableElements.get();
    };

    // Keyboard and focus event handler ensures only modal elements gain focus.
    modalEventHandler = function( event ) {
      target = null;
      if ( event ) { //Mozilla
        target = event.target;
      } else { //IE
        event = window.event;
        target = event.srcElement;
      }

      var parents = $(target).parents().get();
      for (var i = 0; i < parents.length; ++i) {
        var position = $(parents[i]).css('position');
        if (position == 'absolute' || position == 'fixed') {
          return true;
        }
      }

      if ($(target).is('#modalContent, body') || $(target).filter('*:visible').parents('#modalContent').length) {
        // Allow the event only if target is a visible child node
        // of #modalContent.
        return true;
      }
      else {
        getTabbableElements()[0].focus();
      }

      event.preventDefault();
    };
    $('body').bind( 'focus', modalEventHandler );
    $('body').bind( 'keypress', modalEventHandler );

    // Keypress handler Ensures you can only TAB to elements within the modal.
    // Based on the psuedo-code from WAI-ARIA 1.0 Authoring Practices section
    // 3.3.1 "Trapping Focus".
    modalTabTrapHandler = function (evt) {
      // We only care about the TAB key.
      if (evt.which != 9) {
        return true;
      }

      var tabbableElements = getTabbableElements(),
          firstTabbableElement = tabbableElements[0],
          lastTabbableElement = tabbableElements[tabbableElements.length - 1],
          singleTabbableElement = firstTabbableElement == lastTabbableElement,
          node = evt.target;

      // If this is the first element and the user wants to go backwards, then
      // jump to the last element.
      if (node == firstTabbableElement && evt.shiftKey) {
        if (!singleTabbableElement) {
          lastTabbableElement.focus();
        }
        return false;
      }
      // If this is the last element and the user wants to go forwards, then
      // jump to the first element.
      else if (node == lastTabbableElement && !evt.shiftKey) {
        if (!singleTabbableElement) {
          firstTabbableElement.focus();
        }
        return false;
      }
      // If this element isn't in the dialog at all, then jump to the first
      // or last element to get the user into the game.
      else if ($.inArray(node, tabbableElements) == -1) {
        // Make sure the node isn't in another modal (ie. WYSIWYG modal).
        var parents = $(node).parents().get();
        for (var i = 0; i < parents.length; ++i) {
          var position = $(parents[i]).css('position');
          if (position == 'absolute' || position == 'fixed') {
            return true;
          }
        }

        if (evt.shiftKey) {
          lastTabbableElement.focus();
        }
        else {
          firstTabbableElement.focus();
        }
      }
    };
    $('body').bind('keydown', modalTabTrapHandler);

    // Create our content div, get the dimensions, and hide it
    var modalContent = $('#modalContent').css('top','-1000px');
    var mdcTop = wt + ( winHeight / 2 ) - (  modalContent.outerHeight() / 2);
    var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);
    $('#modalBackdrop').css(css).css('top', 0).css('height', docHeight + 'px').css('width', docWidth + 'px').show();
    modalContent.css({top: mdcTop + 'px', left: mdcLeft + 'px'}).hide()[animation](speed);

    // Bind a click for closing the modalContent
    modalContentClose = function(){close(); return false;};
    $('.close').bind('click', modalContentClose);

    // Bind a keypress on escape for closing the modalContent
    modalEventEscapeCloseHandler = function(event) {
      if (event.keyCode == 27) {
        close();
        return false;
      }
    };

    $(document).bind('keydown', modalEventEscapeCloseHandler);

    // Per WAI-ARIA 1.0 Authoring Practices, initial focus should be on the
    // close button, but we should save the original focus to restore it after
    // the dialog is closed.
    var oldFocus = document.activeElement;
    $('.close').focus();

    // Close the open modal content and backdrop
    function close() {
      // Unbind the events
      $(window).unbind('resize',  modalContentResize);
      $('body').unbind( 'focus', modalEventHandler);
      $('body').unbind( 'keypress', modalEventHandler );
      $('body').unbind( 'keydown', modalTabTrapHandler );
      $('.close').unbind('click', modalContentClose);
      $('body').unbind('keypress', modalEventEscapeCloseHandler);
      $(document).trigger('CToolsDetachBehaviors', $('#modalContent'));

      // Set our animation parameters and use them
      if ( animation == 'fadeIn' ) animation = 'fadeOut';
      if ( animation == 'slideDown' ) animation = 'slideUp';
      if ( animation == 'show' ) animation = 'hide';

      // Close the content
      modalContent.hide()[animation](speed);
      $('body').removeClass('ctools-modal-open'); 
      // Remove the content
      $('#modalContent').remove();
      $('#modalBackdrop').remove();

      // Restore focus to where it was before opening the dialog
      $(oldFocus).focus();
    };

    // Move and resize the modalBackdrop and modalContent on window resize.
    modalContentResize = function(){

      // Reset the backdrop height/width to get accurate document size.
      $('#modalBackdrop').css('height', '').css('width', '');

      // Position code lifted from:
      // http://www.quirksmode.org/viewport/compatibility.html
      if (self.pageYOffset) { // all except Explorer
      var wt = self.pageYOffset;
      } else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
        var wt = document.documentElement.scrollTop;
      } else if (document.body) { // all other Explorers
        var wt = document.body.scrollTop;
      }

      // Get our heights
      var docHeight = $(document).height();
      var docWidth = $(document).width();
      var winHeight = $(window).height();
      var winWidth = $(window).width();
      if( docHeight < winHeight ) docHeight = winHeight;

      // Get where we should move content to
      var modalContent = $('#modalContent');
      var mdcTop = wt + ( winHeight / 2 ) - ( modalContent.outerHeight() / 2);
      var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);

      // Apply the changes
      $('#modalBackdrop').css('height', docHeight + 'px').css('width', docWidth + 'px').show();
      modalContent.css('top', mdcTop + 'px').css('left', mdcLeft + 'px').show();
    };
    $(window).bind('resize', modalContentResize);
  };

  /**
   * unmodalContent
   * @param content (The jQuery object to remove)
   * @param animation (fadeOut, slideUp, show)
   * @param speed (valid animation speeds slow, medium, fast or # in ms)
   */
  Drupal.CTools.Modal.unmodalContent = function(content, animation, speed)
  {
    // If our animation isn't set, make it just show/pop
    if (!animation) { var animation = 'show'; } else {
      // If our animation isn't "fade" then it always is show
      if (( animation != 'fadeOut' ) && ( animation != 'slideUp')) animation = 'show';
    }
    // Set a speed if we dont have one
    if ( !speed ) var speed = 'fast';

    // Unbind the events we bound
    $(window).unbind('resize', modalContentResize);
    $('body').unbind('focus', modalEventHandler);
    $('body').unbind('keypress', modalEventHandler);
    $('body').unbind( 'keydown', modalTabTrapHandler );
    $('.close').unbind('click', modalContentClose);
    $('body').unbind('keypress', modalEventEscapeCloseHandler);
    $(document).trigger('CToolsDetachBehaviors', $('#modalContent'));

    // jQuery magic loop through the instances and run the animations or removal.
    content.each(function(){
      if ( animation == 'fade' ) {
        $('#modalContent').fadeOut(speed, function() {
          $('#modalBackdrop').fadeOut(speed, function() {
            $(this).remove();
          });
          $(this).remove();
        });
      } else {
        if ( animation == 'slide' ) {
          $('#modalContent').slideUp(speed,function() {
            $('#modalBackdrop').slideUp(speed, function() {
              $(this).remove();
            });
            $(this).remove();
          });
        } else {
          $('#modalContent').remove();
          $('#modalBackdrop').remove();
        }
      }
    });
  };

$(function() {
  Drupal.ajax.prototype.commands.modal_display = Drupal.CTools.Modal.modal_display;
  Drupal.ajax.prototype.commands.modal_dismiss = Drupal.CTools.Modal.modal_dismiss;
});

})(jQuery);
;
/**
* @file
* Javascript, modifications of DOM.
*
* Manipulates links to include jquery load funciton
*/

(function ($) {
  Drupal.behaviors.jquery_ajax_load = {
    attach: function (context, settings) {
      jQuery.ajaxSetup ({
      // Disable caching of AJAX responses
        cache: false
      });

      var trigger = Drupal.settings.jquery_ajax_load.trigger;
      var target = Drupal.settings.jquery_ajax_load.target;
      // Puede ser más de un valor, hay que usar foreach()
      $(trigger).once(function() {
        var html_string = $(this).attr( 'href' );
        // Hay que validar si la ruta trae la URL del sitio
        $(this).attr( 'href' , target );
        var data_target = $(this).attr( 'data-target' );
        if (typeof data_target === 'undefined' ) {
          data_target = target;
        }
        else {
          data_target = '#' + data_target;
        }
        $(this).click(function(evt) {
          evt.preventDefault();
          jquery_ajax_load_load($(this), data_target, html_string);
        });
      });
      $(trigger).removeClass(trigger);
    }
  };  

// Handles link calls
  function jquery_ajax_load_load(el, target, url) {
    var module_path = Drupal.settings.jquery_ajax_load.module_path;
    var toggle = Drupal.settings.jquery_ajax_load.toggle;
    var base_path = Drupal.settings.jquery_ajax_load.base_path;
    var animation = Drupal.settings.jquery_ajax_load.animation;
    if( toggle && $(el).hasClass( "jquery_ajax_load_open" ) ) {
      $(el).removeClass( "jquery_ajax_load_open" );
      if ( animation ) {
        $(target).hide('slow', function() {
          $(target).empty();
        });
      }
      else {
        $(target).empty();
      }
    }
    else {
      var loading_html = Drupal.t('Loading'); 
      loading_html += '... <img src="/';
      loading_html += module_path;
      loading_html += '/jquery_ajax_load_loading.gif">';
      $(target).html(loading_html);
      $(target).load(base_path + 'jquery_ajax_load/get' + url, function( response, status, xhr ) {
        if ( status == "error" ) {
          var msg = "Sorry but there was an error: ";
          $(target).html( msg + xhr.status + " " + xhr.statusText );
        }
        else {
          if ( animation ) {
            $(target).hide();
            $(target).show('slow')
          }
//        Drupal.attachBehaviors(target);
        }
      });
      $(el).addClass( "jquery_ajax_load_open" );
    }
  }
}(jQuery));
;
(function($) {

var BUE = window.BUE = window.BUE || {preset: {}, templates: {}, instances: [], preprocess: {}, postprocess: {}, nameSelectors: {}};

// Get editor settings from Drupal.settings and process preset textareas.
Drupal.behaviors.BUE = {attach: function(context, settings) {
  var set = settings.BUE, tpls = BUE.templates, pset = BUE.preset, names = BUE.nameSelectors, i, E, T;
  if (set) {
    $.each(set.templates, function (id, tpl) {
      tpls[id] = tpls[id] || $.extend({}, tpl);
    });
    $.extend(pset, set.preset);
    set.templates = {};
    set.preset = {};
  }
  // Process nameSelector=>templateID pairs
  for (i in names) {
    if (T = $(i, context)[0]) {
      BUE.processTextarea(T, names[i]);
    }
  }
  // Process preset textareaID=>templateID pairs
  for (i in pset) {
    if (T = $('#' + i, context)[0]) {
      if (E = BUE.processTextarea(T, pset[i])) {
        // Textareas IDs are not preserved in ajax forms. We store the selectors based on the field name.
        if (E.textArea.name) {
          names['textarea[name="' + E.textArea.name + '"]'] = pset[i];
          delete pset[i];
        }
      }
    }
  }
  // Fix enter key on textfields triggering button click.
  $('input:text', context).bind('keydown.bue', BUE.eFixEnter);
}};

// Integrate editor template into textarea T
BUE.processTextarea = function (T, tplid) {
  if (!T || !BUE.templates[tplid] || !(T = $(T).filter('textarea')[0])) return false;
  // Check visibility on the element-level only.
  if (T.style.display == 'none' || T.style.visibility == 'hidden') return false;
  if (T.bue) return T.bue;
  var E = new BUE.instance(T, tplid);
  !BUE.active || BUE.active.textArea.disabled ? E.activate() : E.accesskeys(false);
  // Pre&post process.
  for (var i in BUE.preprocess) BUE.preprocess[i](E, $);
  for (var i in BUE.postprocess) BUE.postprocess[i](E, $);
  return E;
};

// Create an editor instance
BUE.instance = function (T, tplid) {
  var i = BUE.instances.length, E = T.bue = BUE.instances[i] = this;
  E.index = i;
  E.textArea = T;
  E.tplid = tplid;
  E.tpl = BUE.templates[tplid];
  E.bindex = null;
  E.safeToPreview = T.value.indexOf('<') == -1;
  E.UI = BUE.$html(BUE.theme(tplid).replace(/\%n/g, i)).insertBefore(T).bind('keydown.bue', BUE.eUIKeydown);
  E.buttons = $('.bue-button', E.UI).each(function(i, B) {
    var arr = B.id.split('-');
    $($.extend(B, {eindex: arr[1], bid: arr[3], bindex: i})).bind('click.bue', BUE.eButtonClick);
  }).get();
  $(T).bind('focus.bue', BUE.eTextareaFocus);
};

// Execute button's click event
BUE.buttonClick = function (eindex, bindex) { try {
  var E = BUE.instances[eindex].activate();
  var domB = E.buttons[bindex];
  var tplB = E.tpl.buttons[domB.bid];
  var content = tplB[1];
  E.bindex = bindex;
  E.dialog.close();
  if (tplB[4]) {
    tplB[4](E, $);
  }
  else if (content) {
    var arr = content.split('%TEXT%');
    if (arr.length == 2) E.tagSelection(arr[0], arr[1]);
    else E.replaceSelection(arr.length == 1 ? content : arr.join(E.getSelection()), 'end');
  }
  !(domB.pops || domB.stayClicked) && E.focus();
  } catch (e) {alert(e.name +': '+ e.message);}
  return false;
};

// Return html for editor templates.
BUE.theme = function (tplid) {
  var tpl = BUE.templates[tplid] || {html: ''}, html = '', sprite;
  if (typeof tpl.html == 'string') return tpl.html;
  // Load sprite
  if (sprite = tpl.sprite) {
    var surl = (new Image()).src = sprite.url, sunit = sprite.unit, sx1 = sprite.x1;
    $(document.body).append('<style type="text/css" media="all">.bue-'+ tplid +' .bue-sprite-button {background-image: url('+ surl +'); width: '+ sunit +'px; height: '+ sunit +'px;}</style>');
  }
  var title, content, icon, key, func,
  style = document.documentElement.style,
  access = ('MozAppearance' in style) && 'Shift + Alt' || (('ActiveXObject' in window) || ('WebkitAppearance' in style)) && 'Alt';
  // Create html for buttons. B(0-title, 1-content, 2-icon or caption, 3-accesskey) and 4-function for js buttons
  for (var B, isimg, src, type, btype, attr, alt, i = 0, s = 0; B = tpl.buttons[i]; i++) {
    // Empty button.
    if (B.length == 0) {
      s++;
      continue;
    }
    title = B[0], content = B[1], icon = B[2], key = B[3], func = null;
    // Set button function
    if (content.substr(0, 3) == 'js:') {
      func = B[4] = new Function('E', '$', content.substr(3));
    }
    isimg = (/\.(png|gif|jpg)$/i).test(icon);
    // Theme button.
    if (title.substr(0, 4) == 'tpl:') {
      html += func ? (func(null, $) || '') : content;
      html += icon ? ('<span class="separator">'+ (isimg ? '<img src="'+ tpl.iconpath +'/'+ icon +'" />' : icon) +'</span>') : '';
      continue;
    }
    // Text button
    if (!isimg) {
      type = 'button', btype = 'text', attr = 'value="'+ icon +'"';
    }
    else {
      type = 'image';
      // Sprite button
      if (sprite) {
        btype = 'sprite', attr = 'src="'+ sx1 +'" style="background-position: -'+ (s * sunit) +'px 0;"';
        s++;
      }
      // Image button
      else {
        btype = 'image', attr = 'src="'+ tpl.iconpath +'/'+ icon +'"';
      }
    }
    alt = title + (key ? '('+ key +')' : '');
    title += access && key ? ' ('+ access +' + '+ key +')' : '';
    html += '<input type="'+ type +'" alt="'+ alt +'" title="'+ title +'" accesskey="'+ key +'" id="bue-%n-button-'+ i +'" class="bue-button bue-'+ btype +'-button editor-'+ btype +'-button" '+ attr +' tabindex="'+ (i ? -1 : 0) +'" />';
  }
  return tpl.html = '<div class="bue-ui bue-'+ tplid +' editor-container clearfix" id="bue-ui-%n" role="toolbar">'+ html +'</div>';
};

// Cross browser selection handling. 0-1=All, 2=IE, 3=Opera
BUE.mode = document.createElement('textarea').setSelectionRange ? (window.opera ? 3 : 1) : (document.selection && document.selection.createRange ? 2 : 0);

// New line standardization. At least make them represented by a single char.
BUE.text = BUE.processText = BUE.mode < 2 ? function (s) {return s.toString()} : function (s) {return s.toString().replace(/\r\n/g, '\n')};

// Create selection in a textarea
BUE.selMake = BUE.mode == 2 ? function (T, start, end) {
  var range = T.createTextRange();
  range.collapse();
  range.moveEnd('character', end);
  range.moveStart('character', start);
  range.select();
} :
BUE.mode == 3 ? function (T, start, end) {
  var text = BUE.text(T.value), i = text.substring(0, start).split('\n').length, j = text.substring(start, end).split('\n').length;
  T.setSelectionRange(start + i -1 , end + i + j - 2);
} :
BUE.mode == 1 ? function (T, start, end) {
  T.setSelectionRange(start, end);
} :
function (T, start, end) {};

// Return the selection coordinates in a textarea
BUE.selPos = BUE.mode == 2 ? function (T) {
  T.focus();
  var orange = document.selection.createRange(), range = orange.duplicate();
  range.moveToElementText(T);
  range.setEndPoint('EndToEnd', orange);
  var otext = orange.text, olen = otext.length, prelen = range.text.length - olen;
  var start = prelen - (T.value.substr(0, prelen).split('\r\n').length - 1);
  start && range.moveStart('character', start);
  for (; range.compareEndPoints('StartToStart', orange) < 0; start++) {
    range.moveStart('character', 1);
  }
  var end = start + olen - (otext.split('\r\n').length - 1);
  for (; range.compareEndPoints('EndToStart', orange) > 0; end++) {
    range.moveEnd('character', -1);
    if (range.text.length != olen) break;
  }
  return {start: start, end: end};
} :
BUE.mode == 3 ? function (T) {
  var start = T.selectionStart || 0, end = T.selectionEnd || 0, val = T.value;
  var i = val.substring(0, start).split('\r\n').length, j = val.substring(start, end).split('\r\n').length;
  return {start: start - i + 1, end: end - i - j + 2};
} :
function (T) {
  return {start: T.selectionStart || 0, end: T.selectionEnd || 0}
};

// Enter key fixer for text fields
BUE.eFixEnter = function(e) {
  e.keyCode == 13 && (BUE.enterKeyTime = new Date());
};

// Button click handler
BUE.eButtonClick = function(e) {
  return !(BUE.enterKeyTime && new Date() - BUE.enterKeyTime < 500) && BUE.buttonClick(this.eindex, this.bindex);
};

// Textarea focus handler
BUE.eTextareaFocus = function(e) {
  this.bue && !this.bue.dialog.esp && this.bue.activate();
};

// UI keydown handler
BUE.eUIKeydown = function(e) {
  if (e.keyCode != 37 && e.keyCode != 39) return;
  var len, E = BUE.instances[this.id.split('-').pop()];
  if (E && (len = E.buttons.length)) {
    var A = document.activeElement, i = Math.max(-1, (A && A.eindex == E.index ? A.bindex : -1) + e.keyCode - 38) + len;
    E.buttons[i % len].focus();
  }
};

// Html 2 jquery. Faster than $(html)
BUE.$html = function(s){
  var div = document.createElement('div');
  div.innerHTML = s;
  return $(div.childNodes);
};

// Backward compatibility.
window.editor = window.editor || BUE;

})(jQuery);


// Bueditor instance methods
(function(E) {

// Focus on editor textarea.
E.focus = function () {
  this.textArea.focus();
  return this;
};

// Return textarea content
E.getContent = function () {
  return BUE.text(this.textArea.value);
};

// Set textarea content
E.setContent = function (content) {
  var T = this.textArea, st = T.scrollTop;
  T.value = content;
  T.scrollTop = st;
  return this;
};

// Return selected text
E.getSelection = function () {
  var pos = this.posSelection();
  return this.getContent().substring(pos.start, pos.end);
};

// Replace selected text
E.replaceSelection = function (txt, cursor) {
  var E = this, pos = E.posSelection(), content = E.getContent(), txt = BUE.text(txt);
  var end = cursor == 'start' ? pos.start : pos.start+txt.length, start = cursor == 'end' ? end : pos.start;
  E.setContent(content.substr(0, pos.start) + txt + content.substr(pos.end));
  return E.makeSelection(start, end);
};

// Wrap selected text.
E.tagSelection = function (left, right, cursor) {
  var E = this, pos = E.posSelection(), content = E.getContent();
  var left = BUE.text(left), right = BUE.text(right), llen = left.length;
  var end = cursor == 'start' ? pos.start+llen : pos.end+llen, start = cursor == 'end' ? end : pos.start+llen;
  E.setContent(content.substr(0, pos.start) + left + content.substring(pos.start, pos.end) + right + content.substr(pos.end));
  return E.makeSelection(start, end);
};

// Make a new selection
E.makeSelection = function (start, end) {
  var E = this;
  if (end === undefined || end < start) end = start;
  BUE.selMake(E.textArea, start, end);
  E.dialog.esp && (E.dialog.esp = {start: start, end: end}) || E.focus();
  return E;
};

// Return selection coordinates.
E.posSelection = function () {
  return this.dialog.esp || BUE.selPos(this.textArea);
};

// Enable/disable editor buttons
E.buttonsDisabled = function (state, bindex) {
  for (var B, i=0; B = this.buttons[i]; i++) {
    B.disabled = i == bindex ? !state : state;
  }
  return this;
};

// Make active/custom button stay clicked
E.stayClicked = function (state, bindex) {
  var B = this.buttons[bindex === undefined ? this.bindex : bindex];
  B && jQuery(B)[state ? 'addClass' : 'removeClass']('stay-clicked') && (B.stayClicked = state || false);
  return this;
};

// Enable/disable button accesskeys
E.accesskeys = function (state) {
  for (var B, i=0; B = this.buttons[i]; i++) {
    B.accessKey = state ? this.tpl.buttons[B.bid][3] : '';
  }
  return this;
};

// Activate editor and make it BUE.active
E.activate = function() {
  var E = this, A = BUE.active || null;
  if (E == A) return E;
  A && A.accesskeys(false) && E.accesskeys(true);
  return BUE.active = E;
};

// Reserve dialog and quickPop
var pop = E.dialog = E.quickPop = BUE.dialog = BUE.quickPop = {};
pop.open = pop.close = function(){};

})(BUE.instance.prototype);;
(function($) {

//get markup after processing the input by the format.
//The "callback" is called with 3 parameters: output, status(true|false), xmlHttpRequest
$.ajaxMarkup = function(input, format, callback) {
  //check if callback exists.
  if (!$.isFunction(callback)) {
    return;
  }
  //check input
  var input = $.trim(input);
  if (!input) {//return empty output for empty input.
    return callback('', true);
  }
  //check cache
  var hash = $.ajaxMarkup.hash, cache = $.ajaxMarkup.cache;
  var cid = format + ':' + hash(input);
  if (cache[cid] !== undefined) {
    return callback(cache[cid], true);
  }
  //check required parameters for ajax request.
  if (!$.ajaxMarkup.url || !$.ajaxMarkup.token) {
    return callback(Drupal.t('Some required parameters are missing for an ajax request.'), false);
  }
  //request filtered output.
  var output = '', status = false;
  $.ajax({
    url: $.ajaxMarkup.url,
    data: {input: input, format: format, token: $.ajaxMarkup.token},
    type: 'POST',
    dataType: 'json',
    success: function(response) {
      output = cache[cid] = response.output || '';
      status = true;
    },
    error: function(request) {
      output = Drupal.ajaxError(request, this.url);
    },
    complete: function(request) {
      callback.call(this, output, status, request);
    }
  });
};

//store recent output
$.ajaxMarkup.cache = {};

//string hashing used for creating cache ids. Prof. Daniel J. Bernstein's algorithm.
$.ajaxMarkup.hash = function(str) {
  for(var c, i = 0, h = 5381; c = str.charCodeAt(i); i++) {
    h = (h << 5) + h + c;
  }
  return h & 0x7FFFFFFF;
};

//Helper function to find the input format of a given textarea. defaults to 0 when there is no format.
$.ajaxMarkup.getFormat = function(selector) {
  var T = $(selector)[0];
  if (!T || T.tagName != 'TEXTAREA') {
    return 0;
  }
  var i, format = 0, name = T.name || '';
  if ((i = name.indexOf('[value]')) > 0) {//fields
    format = $(T.form.elements[name.substring(0, i) + '[format]']).val() || 0;
  }
  return format;
};

//set dynamic parameters(url & token).
$(document).ready(function() {
  $.extend($.ajaxMarkup, Drupal.settings.ajaxMarkup);
});

})(jQuery);;
//Merged and minified: bue.popup.js, bue.markup.js, bue.preview.js, bue.imce.js, bue.misc.js
(function(b,a){BUE.popups=BUE.popups||{};BUE.popHtml='<table class="bue-popup" style="display: none;" role="dialog"><tbody class="bue-zero"><tr class="bue-zero"><td class="bue-zero"><div class="bue-popup-head clearfix"><div class="bue-popup-title"></div><button class="bue-popup-close" type="button">x</button></div><div class="bue-popup-body"><div class="bue-popup-content clearfix"></div></div></td></tr></tbody></table>';BUE.openPopup=function(f,e,d,c){return BUE.createPopup(f).open(e,d,c)};BUE.createPopup=function(i,h,f){if(BUE.popups[i]){return BUE.popups[i]}var c=BUE.$html(BUE.popHtml).appendTo("body").attr("id",i);var e=c.find(".bue-popup-title").html(h||"");var d=c.find(".bue-popup-content").html(f||"");var g=BUE.popups[i]=c[0];g.open=function(o,l,k){if(o!==undefined&&o!==null){e.html(o)}if(l!==undefined&&l!==null){d.html(l)}var m=g.bue=BUE.active,q=m.buttons[m.bindex||0];k=typeof k=="string"?{effect:k}:k;k=a.extend({effect:"show",speed:"normal",callback:g.onopen},k);k.onopen=k.onopen||k.callback;if(!k.offset&&q){var p=a(q).offset(),j=c.width(),n=Math.max(15,p.left-j/2+15);k.offset={left:n-Math.max(0,n+j-a(window).width()+15),top:p.top+15};q.pops=true}c.css(k.offset);if(k.effect=="show"){c.show();k.onopen&&k.onopen.call(g)}else{c[k.effect](k.speed,k.onopen)}g.onclose=k.onclose||false;return g};g.close=function(j){c.stop(true,true)[j||"hide"]();g.onclose&&g.onclose.call(g);return g};g.closenfocus=function(){g.close().bue.focus();return g};g.onopen=function(){if(c.css("display")!="none"){var j=c.focus().find("form");if(j.length){a(j[0].elements[0]).focus()}else{c.find("a:first").focus()}}return g};c.attr("tabindex",0);c.find(".bue-popup-close").click(g.closenfocus)[0].title=Drupal.t("Close");c.keydown(function(j){if(j.keyCode==27){g.closenfocus();return false}});c.find(".bue-popup-head").mousedown(function(l){var m={X:parseInt(c.css("left"))-l.pageX,Y:parseInt(c.css("top"))-l.pageY};var k=function(n){c.css({left:m.X+n.pageX,top:m.Y+n.pageY});return false};var j=function(n){a(document).unbind("mousemove",k).unbind("mouseup",j)};a(document).mousemove(k).mouseup(j);return false});return g};BUE.preprocess=a.extend({popup:function(j,f){if(j.index){return}var c=b.dialog=BUE.dialog=BUE.createPopup("bue-dialog");var e=function(){this.blur()};var i=c.open,d=c.close;c.open=function(p,n,m){c.esp&&c.close();var o=BUE.active;o.buttonsDisabled(true).stayClicked(true);c.esp=o.posSelection();f(o.textArea).bind("focus.bue",e);return i(p,n,m)};c.close=function(m){if(!c.esp){return c}var n=c.bue;f(n.textArea).unbind("focus.bue",e);n.buttonsDisabled(false).stayClicked(false);n==BUE.active&&n.makeSelection(c.esp.start,c.esp.end);c.esp=null;return d(m)};var g=b.quickPop=BUE.quickPop=BUE.createPopup("bue-quick-pop");var l=g.open,h=g.close,k=f(g);g.open=function(n,m){f(document).mouseup(g.close);return l(null,n,m)};g.close=function(){f(document).unbind("mouseup",g.close);return h()};k.keydown(function(o){switch(o.keyCode){case 13:setTimeout(g.closenfocus);break;case 38:case 40:var n=k.find("a"),m=n.index(document.activeElement);n.eq(m+o.keyCode-39).focus();return false}});k.find(".bue-popup-head").css({display:"none"})}},BUE.preprocess)})(BUE.instance.prototype,jQuery);(function(d,c){BUE.html=function(g,l,f){var e=f||{},h=l||"";var k="<"+g;for(var j in e){k+=e[j]==null?"":" "+j+'="'+e[j]+'"'}k+=a(g)?(" />"+h):(">"+h+"</"+g+">");return g?k:h};BUE.objHtml=function(e){return e&&e.tag?b(e.tag,e.html,e.attributes):""};BUE.input=function(g,h,f,e){return b("input","",c.extend({type:g,name:h,value:f||null},e))};BUE.selectbox=function(k,f,j,e){var j=j||{},h="";for(var g in j){h+=b("option",j[g],{value:g,selected:g==f?"selected":null})}return b("select",h,c.extend({},e,{name:k}))};BUE.table=function(j,e){for(var h,g="",f=0;h=j[f];f++){g+=h.data===undefined?BUE.trow(h):BUE.trow(h.data,h.attr)}return b("table",g,e)};BUE.trow=function(f,e){for(var j,h="",g=0;j=f[g];g++){h+=j.data===undefined?b("td",j):b("td",j.data,j.attr)}return b("tr",h,e)};BUE.regesc=function(e){return e.replace(/([\\\^\$\*\+\?\.\(\)\[\]\{\}\|\:])/g,"\\$1")};BUE.nctag=function(e){return !e||/^(img|input|hr|br|embed|param)$/.test(e)};BUE.parseHtml=function(k,g){var l=new RegExp("^<("+(g||"[a-z][a-z0-9]*")+")([^>]*)>($|((?:.|[\r\n])*)</\\1>$)");if(!(h=k.match(l))||(!h[3]&&!a(h[1]))){return null}var g=h[1],f=[],e={},h;if((f=h[2].split('"')).length>1){for(var j=0;f[j+1]!==undefined;j+=2){e[f[j].replace(/\s|\=/g,"")]=f[j+1]}}return{tag:g,attributes:e,html:h[4]}};d.insertObj=function(l,h){if(!l||!l.tag){return this}var j=this,e=l.tag,h=c.extend({cursor:null,extend:true,toggle:false},h);var k,i=j.getSelection(),f=i&&h.extend&&BUE.parseHtml(i);if(k=f&&f.tag==e){if(h.toggle){return j.replaceSelection(f.html,h.cursor)}var l={tag:e,html:typeof l.html!="string"||l.html==i?f.html:l.html,attributes:c.extend(f.attributes,l.attributes)}}if(k||a(e)||l.html){return j.replaceSelection(BUE.objHtml(l),h.cursor)}var g=b(e,"",l.attributes);return j.tagSelection(g.substr(0,g.length-e.length-3),"</"+e+">",h.cursor)};var b=BUE.html;var a=BUE.nctag})(BUE.instance.prototype,jQuery);eDefHTML=BUE.html;eDefInput=BUE.input;eDefSelectBox=BUE.selectbox;eDefTable=BUE.table;eDefRow=BUE.trow;eDefNoEnd=BUE.nctag;eDefRegEsc=BUE.regesc;eDefParseTag=BUE.parseHtml;eDefInputText=function(c,a,b){return BUE.input("text",c,a,{size:b||null})};eDefInputSubmit=function(b,a){return BUE.input("submit",b,a)};(function(b,a){b.prv=function(e){var d=this;if(d.prvOn){return d.prvHide()}var e=e===undefined?true:e;var c=d.getContent();if(e&&!(d.safeToPreview=d.safeToPreview||c.indexOf("<")==-1)){c='<div class="warning">'+Drupal.t("The preview is disabled due to previously inserted HTML code in the content. This aims to protect you from any potentially harmful code inserted by other editors or users. If you own the content, just preview an empty text to re-enable the preview.")+"</div>"}return d.prvShow(BUE.autop(c))};b.prvShow=function(d,e){var f=this;var g=a(f.textArea);var c=a(f.preview=f.preview||BUE.$html('<div class="preview bue-preview" style="display:none; overflow:auto"></div>').insertBefore(g)[0]);if(e===undefined||e){d='<div class="'+(f.textArea.name=="comment"?"comment":"node")+'"><div class="content">'+d+"</div></div>"}if(f.prvOn){c.html(d);return f}f.prvPos=f.posSelection();c.show().height(g.height()).width(g.width()).html(d);g.height(1);f.buttonsDisabled(true,f.bindex).stayClicked(true);f.prvOn=true;return f};b.prvHide=function(){var d=this;if(d.prvOn){var c=a(d.preview);a(d.textArea).height(c.height());c.hide();d.buttonsDisabled(false).stayClicked(false);d.prvOn=false;d.prvPos&&(d.makeSelection(d.prvPos.start,d.prvPos.end).prvPos=null)}return d};b.prvAjax=function(e,f){var d=this,c;if(d.prvOn){return d.prvHide()}if(!(c=a.ajaxMarkup)){return d.prvShow(Drupal.t('Preview requires <a href="http://drupal.org/project/ajax_markup">Ajax markup</a> module with proper permissions set.'))}if(e&&e.call){f=e;e=0}d.prvShow('<div class="bue-prv-loading">'+Drupal.t("Loading...")+"</div>");c(d.getContent(),e||c.getFormat(d.textArea),function(h,g,i){d.prvOn&&d.prvShow(g?h:h.replace(/\n/g,"<br />"))&&(f||Drupal.attachBehaviors)(d.preview)});return d};BUE.autop=function(d){if(d==""||!(/\n|\r/).test(d)){return d}var f=function(h,i,g){return h.replace(new RegExp(i,"g"),g)};var c=function(h,g){return d=f(d,h,g)};var e="(table|thead|tfoot|caption|colgroup|tbody|tr|td|th|div|dl|dd|dt|ul|ol|li|pre|select|form|blockquote|address|math|style|script|object|input|param|p|h[1-6])";d+="\n";c("<br />\\s*<br />","\n\n");c("(<"+e+"[^>]*>)","\n$1");c("(</"+e+">)","$1\n\n");c("\r\n|\r","\n");c("\n\n+","\n\n");c("\n?((.|\n)+?)\n\\s*\n","<p>$1</p>\n");c("\n?((.|\n)+?)$","<p>$1</p>\n");c("<p>\\s*?</p>","");c("<p>(<div[^>]*>\\s*)","$1<p>");c("<p>([^<]+)\\s*?(</(div|address|form)[^>]*>)","<p>$1</p>$2");c("<p>\\s*(</?"+e+"[^>]*>)\\s*</p>","$1");c("<p>(<li.+?)</p>","$1");c("<p><blockquote([^>]*)>","<blockquote$1><p>");c("</blockquote></p>","</p></blockquote>");c("<p>\\s*(</?"+e+"[^>]*>)","$1");c("(</?"+e+"[^>]*>)\\s*</p>","$1");c("<(script|style)(.|\n)*?</\\1>",function(g){return f(g,"\n","<PNL>")});c("(<br />)?\\s*\n","<br />\n");c("<PNL>","\n");c("(</?"+e+"[^>]*>)\\s*<br />","$1");c("<br />(\\s*</?(p|li|div|dl|dd|dt|th|pre|td|ul|ol)[^>]*>)","$1");if(d.indexOf("<pre")!=-1){c("(<pre(.|\n)*?>)((.|\n)*?)</pre>",function(j,i,h,g){return f(i,"\\\\(['\"\\\\])","$1")+f(f(f(g,"<p>","\n"),"</p>|<br />",""),"\\\\(['\"\\\\])","$1")+"</pre>"})}return c("\n</p>$","</p>")}})(BUE.instance.prototype,jQuery);eDefAutoP=BUE.autop;eDefPreview=function(){BUE.active.prv()};eDefPreviewShow=function(c,b,a){c.prvShow(b,a)};eDefPreviewHide=function(a){a.prvHide()};eDefAjaxPreview=function(){BUE.active.prvAjax()};(function(c,b){var a=c.imce=BUE.imce={};b(function(){a.url=Drupal.settings.BUE.imceURL||""});a.button=function(e,d){return a.url?'<input type="button" id="bue-imce-button" name="bue_imce_button" class="form-submit" value="'+(d||Drupal.t("Browse"))+'" onclick="BUE.imce.open(this.form.elements[\''+e+"'])\">":""};a.open=function(e){if(!a.url){return}a.ready=a.sendto=function(){},a.target=null;b.extend(a,e.focus?{target:e,ready:a.readyDefault,sendto:a.sendtoDefault}:e);if(a.pop){a.setPos();a.ready(a.win,a.pop)}else{var d=a.url+(a.url.indexOf("?")<0?"?":"&")+"app=bue|imceload@bueImceLoad|";a.pop=BUE.createPopup("bue-imce-pop",Drupal.t("File Browser"),'<iframe src="'+d+'" frameborder="0"></iframe>');a.setPos()}};a.setPos=function(){var d=b(a.pop),f=b(window),e=window.opera?window.innerHeight:f.height();a.pop.open(null,null,{offset:{left:Math.max(0,(f.width()-d.width())/2),top:f.scrollTop()+Math.max(0,(e-d.height())/2)}})};a.finish=function(d,e){a.sendto(d,e,a.pop)};a.sendtoDefault=function(f,j,d){var h=a.target,g=h.form.elements,k={alt:f.name,width:f.width,height:f.height};h.value=f.url;for(var e in k){if(g["attr_"+e]){g["attr_"+e].value=k[e]}}d.close();h.focus()};a.readyDefault=function(g,d){var e=g.imce,f=a.target&&a.target.value;f&&e.highlight(f.substr(f.lastIndexOf("/")+1));if(e.fileKeys&&!e.fileKeys.k27){e.fileKeys.k27=function(h){d.closenfocus();a.target&&a.target.focus()}}!window.opera&&!("WebkitAppearance" in document.documentElement.style)&&b(e.FLW).focus()};window.bueImceLoad=function(d){(a.win=d).imce.setSendTo(Drupal.t("Send to editor"),a.finish);a.ready(d,a.pop);if((window.opera||("WebkitAppearance" in document.documentElement.style))&&b(a.pop).is(":visible")){b(a.win.imce.FLW).one("focus",function(){a.pop.close();a.setPos()})}}})(BUE.instance.prototype,jQuery);eDefBrowseButton=function(a,c,b){return BUE.imce.button(c,b)};(function(d,c){d.wrapLines=function(h,n,m,g){var o=this,k=o.getSelection().replace(/\r\n|\r/g,"\n"),l=BUE.regesc;if(!k){return o.tagSelection(h+n,m+g)}var j,i=new RegExp("^"+l(h+n)+"((.|\n)*)"+l(m+g)+"$");if(j=k.match(i)){i=new RegExp(l(m)+"\n"+l(n),"g");return o.replaceSelection(j[1].replace(i,"\n"))}return o.replaceSelection(h+n+k.replace(/\n/g,m+"\n"+n)+m+g)};d.toggleTag=function(g,h,k){var i=this,j={tag:g,html:i.getSelection(),attributes:h};return i.insertObj(j,{cursor:k,toggle:true})};d.help=function(h){var k=this;if(!k.helpHTML){for(var l,j=[],g=0;l=k.buttons[g];g++){j[g]=[BUE.input(l.type,null,l.value||null,{"class":l.className,src:l.src||null,style:c(l).attr("style")}),l.title]}k.helpHTML=BUE.table(j,{id:"bue-help","class":"bue-"+k.tplid})}k.quickPop.open(k.helpHTML,h);return k};d.tagChooser=function(g,i){var k=this,i=c.extend({wrapEach:"li",wrapAll:"ul",applyTag:true,effect:"slideDown"},i);var l=BUE.html(i.wrapAll||"div","",{"class":"tag-chooser"}),j=b(l);var h=BUE.html(i.wrapEach,"",{"class":"choice"});var m=BUE.html("a","",{href:"#","class":"choice-link"});c.each(g,function(n,o){var p={tag:o[0],html:o[1],attributes:o[2]};b(m).html(i.applyTag?BUE.objHtml(p):p.html).click(function(){k.insertObj(c.extend(p,{html:null}));return false}).appendTo(j)[h?"wrap":"end"](h)});k.quickPop.open(j,i.effect);return k};d.tagDialog=function(w,q,h){var v=this,k=v.getSelection(),o=BUE.parseHtml(k,w)||{attributes:{}};for(var r,p="",u=[],m=0,l=0;r=q[m];m++,l++){r=e(r,o,k);if(r.type=="hidden"){p+=a(r);l--;continue}u[l]=[BUE.html("label",r.title,{"for":r.attributes.id}),a(r)];while(r.getnext&&(r=q[++m])){u[l][1]+=a(e(r,o,k))}}var g=c.extend({title:Drupal.t("Tag editor - @tag",{"@tag":w.toUpperCase()}),stitle:Drupal.t("OK"),validate:false,submit:function(n,i){return v.tgdSubmit(n,i)},effect:"show"},h);var s=BUE.table(u,{"class":"bue-tgd-table"});var j=BUE.html("div",BUE.input("submit","bue_tgd_submit",g.stitle,{"class":"form-submit"}));var t=b(BUE.html("form",s+j+p,{name:"bue_tgd_form",id:"bue-tgd-form"}));v.dialog.open(g.title,t,h);t.submit(function(){return f(w,this,g,v)});return v};d.tgdSubmit=function(g,l){var m=this,n={tag:g,html:null,attributes:{}};for(var h,k,j=0;k=l.elements[j];j++){if(k.name.substr(0,5)=="attr_"){h=k.name.substr(5);if(h=="html"){n.html=k.value}else{n.attributes[h]=k.value.replace(/\x22/g,"&quot;").replace(/>/g,"&gt;").replace(/</g,"&lt;")||null}}}return m.insertObj(n)};var b=BUE.$html;var a=function(i){var g=i.prefix||"";switch(i.type){case"select":g+=BUE.selectbox(i.fname,i.value,i.options||{},i.attributes);break;case"textarea":g+=BUE.html("textarea","\n"+i.value,i.attributes);break;default:g+=BUE.input(i.type,i.fname,i.value,i.attributes);break}return g+(i.suffix||"")};var e=function(h,i,g){h=typeof(h)=="string"?{name:h}:h;if(h.name=="html"){h.value=typeof i.html=="string"?i.html:(g||h.value||"")}h.value=Drupal.checkPlain(typeof i.attributes[h.name]=="string"?i.attributes[h.name]:(h.value||""));h.title=typeof h.title=="string"?h.title:h.name.substr(0,1).toUpperCase()+h.name.substr(1);h.fname="attr_"+h.name;h.type=h.value.indexOf("\n")>-1?"textarea":(h.type||"text");h.attributes=c.extend({name:h.fname,id:h.fname,"class":""},h.attributes);h.attributes["class"]+=" form-"+h.type;if(h.required){h.attributes["class"]+=" required";h.attributes.title=Drupal.t("This field is required.")}return h};var f=function(p,g,h,o){for(var j,m=0;j=g.elements[m];m++){if(c(j).hasClass("required")&&!j.value){return BUE.noticeRequired(j)}}var k=h.validate;if(k){try{if(!k(p,g,h,o)){return false}}catch(n){alert(n.name+": "+n.message)}}o.dialog.close();var l=h.submit;l=typeof l=="string"?window[l]:l;if(l){try{l(p,g,h,o)}catch(n){alert(n.name+": "+n.message)}}return false};BUE.noticeRequired=function(g){c(g).fadeOut("fast").fadeIn("fast",function(){c(this).focus()});return false}})(BUE.instance.prototype,jQuery);eDefSelProcessLines=eDefTagLines=function(f,e,h,g){BUE.active.wrapLines(f,e,h,g)};eDefTagger=function(e,d,f){BUE.active.toggleTag(e,d,f)};eDefHelp=function(a){BUE.active.help(a)};eDefTagDialog=function(h,g,l,k,j,i){BUE.active.tagDialog(h,g,{title:l,stitle:k,submit:j,effect:i})};eDefTagInsert=function(d,c){BUE.active.tgdSubmit(d,c)};eDefTagChooser=function(g,f,j,i,h){BUE.active.tagChooser(g,{applyTag:f,wrapEach:j,wrapAll:i,effect:h})};;
