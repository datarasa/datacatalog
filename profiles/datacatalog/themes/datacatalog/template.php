<?php 
/**
 * Page alter.
 */

function datacatalog_page_alter($page) {
  $mobileoptimized = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' =>  'MobileOptimized',
	  'content' =>  'width'
	 )
  );
  $handheldfriendly = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' =>  'HandheldFriendly',
      'content' =>  'true'
     )
  );
  $viewport = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
	'#attributes' => array(
      'name' =>  'viewport',
      'content' =>  'width=device-width, initial-scale=1'
     )
  );
  drupal_add_html_head($mobileoptimized, 'MobileOptimized');
  drupal_add_html_head($handheldfriendly, 'HandheldFriendly');
  drupal_add_html_head($viewport, 'viewport');
}

/**
 * Preprocess variables for html.tpl.php
 */
function datacatalog_preprocess_html(&$variables) {
  //role classes
  foreach ($variables['user']->roles as $role):
    $variables['classes_array'][] = 'role-' . drupal_html_class($role);
  endforeach;
  /**
   * Add IE8 Support
   */
  drupal_add_css(path_to_theme() . '/css/ie8.css', array('group' => CSS_THEME, 'browsers' => array('IE' => '(lt IE 9)', '!IE' => FALSE), 'preprocess' => FALSE));
  /**
   * Add Graph jquery Support
   */
  drupal_add_js(path_to_theme() . '/js/jquery.show-more.js');
  drupal_add_js(path_to_theme() . '/js/pinterest.js');
  /**
   * Bootstrap CDN
   */
  if (theme_get_setting('bootstrap_css_cdn', 'datacatalog')):
    $cdn = '//maxcdn.bootstrapcdn.com/bootstrap/' . theme_get_setting('bootstrap_css_cdn', 'datacatalog')  . '/css/bootstrap.min.css';
    drupal_add_css($cdn, array('type' => 'external'));
  endif;
  if (theme_get_setting('bootstrap_js_cdn', 'datacatalog')):
    $cdn = '//maxcdn.bootstrapcdn.com/bootstrap/' . theme_get_setting('bootstrap_js_cdn', 'datacatalog')  . '/js/bootstrap.min.js';
    drupal_add_js($cdn, array('type' => 'external'));
  endif;
  
  /**
   * Javascript for sorting style 
   */
  
  drupal_add_js(drupal_get_path('module', 'datacatalog_general') . '/js/chosen/chosen.jquery.min.js');
  drupal_add_js(drupal_get_path('module', 'datacatalog_general') . '/js/datacatalog_general.js');
    
  /**
   * Add Javascript for enable/disable scrollTop action
   */
  if (theme_get_setting('scrolltop_display', 'datacatalog')):
    drupal_add_js ('jQuery(document).ready(function($) { 
	  $(window).scroll(function() {
        if($(this).scrollTop() != 0) {
		  $("#toTop").fadeIn();	
        }
        else {
          $("#toTop").fadeOut();
        }
	  });
      $("#toTop").click(function() {
        $("body,html").animate({scrollTop:0},800);
      });	
    });',
    array('type' => 'inline', 'scope' => 'header'));
  endif;
	//EOF:Javascript
}

/**
 * Override or insert variables into the html template.
 */
function datacatalog_process_html(&$vars) {
  // Hook into color.module
  if (module_exists('color')):
    _color_html_alter($vars);
  endif;
}

/**
 * Preprocess variables for page template.
 */
function datacatalog_preprocess_page(&$vars) {
 
  /**
   * insert variables into page template.
   */
  if ($vars['page']['sidebar_first'] && $vars['page']['sidebar_second']): 
    $vars['first_sidebar_grid_class'] = 'col-md-2 col-sm-3 col-xs-12 p-r-0 p-l-0';
    $vars['second_sidebar_grid_class'] = 'col-md-2 col-sm-3 col-xs-12 p-r-10';
    $vars['main_grid_class'] = 'col-md-10 col-sm-9 col-xs-12 p-0';
   
  elseif ($vars['page']['sidebar_first'] || $vars['page']['sidebar_second']):
    $vars['first_sidebar_grid_class'] = 'col-md-2  col-sm-3 col-xs-12 p-r-0 p-l-0';

    $vars['second_sidebar_grid_class'] = 'col-md-2  col-sm-3 col-xs-12 p-r-10 p-l-0';
    $vars['main_grid_class'] = 'col-md-12 col-sm-12 col-xs-12 p-0';	
   
  else:
    $vars['main_grid_class'] = 'col-md-12';			
  endif;
  
  if ($vars['page']['header_top_left'] && $vars['page']['header_top_right']): 
    $vars['header_top_left_grid_class'] = 'col-md-8';
    $vars['header_top_right_grid_class'] = 'col-md-4';
  
  elseif ($vars['page']['header_top_right'] || $vars['page']['header_top_left']):
    $vars['header_top_left_grid_class'] = 'col-md-12';
    $vars['header_top_right_grid_class'] = 'col-md-12';		
  endif;
  /**
   * Add Javascript
   */
  if ($vars['page']['pre_header_first'] || $vars['page']['pre_header_second'] || $vars['page']['pre_header_third']): 
	drupal_add_js('
	  function hidePreHeader() {
	    jQuery(".toggle-control").html("<a href=\"javascript:showPreHeader()\"><span class=\"glyphicon glyphicon-plus\"></span></a>");
	    jQuery("#pre-header-inside").slideUp("fast");
	  }
	  function showPreHeader() {
	    jQuery(".toggle-control").html("<a href=\"javascript:hidePreHeader()\"><span class=\"glyphicon glyphicon-minus\"></span></a>");
	    jQuery("#pre-header-inside").slideDown("fast");
	  }
	  ',
	array('type' => 'inline', 'scope' => 'footer', 'weight' => 3));
  endif;
  /* drupal_add_js('function(){
     var elem = document.createElement("img");
     elem.setAttribute("src", "http://datacatalog-dev.datarasa.org/sites/all/themes/datacatalog/images/psd_arrows.png");
     elem.setAttribute("alt", "arrows");
     document.getElementsByClassName("views-field-title").appendChild(elem);
     }',array('type' => 'inline', 'scope' => 'footer', 'weight' => 4));*/
   drupal_add_js(path_to_theme() . '/js/limit.js');
  
   //EOF:Javascript
   if (!empty($vars['node']) && !empty($vars['node']->type) && $vars['node']->type == "source" ):
     drupal_add_js(drupal_get_path('module', 'datacatalog_subscription') . '/js/datacatalog_subscription.js');
   endif;
   if (!empty($vars['node']) && !empty($vars['node']->type) && $vars['node']->type == "book" ):
     $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
   endif;
   global $user;
   if (arg(0)=="user" and $user->uid ):
     drupal_add_css(path_to_theme() . '/css/jquery.fancybox.css');
     drupal_add_js(path_to_theme() . '/js/jquery.fancybox.js');
     drupal_set_title('User Profile');   
   endif;
   $book_found=check_if_any_node_found("book");
   if (arg(0) == "node" and arg(1) == "add" and arg(2) == "book" and $book_found >= 1 ):
     $link = drupal_get_path_alias('user/' . $user->uid);	
	 drupal_goto($link);
   endif;
  
   if ((arg(0) == 'group' && arg(5) == 'add-user') || (arg(0) == 'group' && arg(4) == 'people')):
     $current_title = drupal_get_title();
     $new_title = str_replace('People in group', 'People in community', $current_title);
     drupal_set_title($new_title);
   endif;
   if (arg(0) == 'group' && arg(4) == 'people'):
     $vars['page']['content']['system_main']['main']['#markup'] = str_replace('Group overview','Community overview',$vars['page']['content']['system_main']['main']['#markup']);
     $vars['page']['content']['system_main']['main']['#markup'] = str_replace('Group manager','Community manager',$vars['page']['content']['system_main']['main']['#markup']);
   endif;
}

/**
 * Override or insert variables into the page template.
 */
function datacatalog_process_page(&$variables) {
  // Hook into color.module.
  if (module_exists('color')):
    _color_page_alter($variables);
  endif;
}
/**
 * Preprocess variables for block.tpl.php
 */
function datacatalog_preprocess_block(&$variables) {
  $variables['classes_array'][] = 'clearfix';
}

/**
 * Override theme_breadrumb().
 *
 * Print breadcrumbs as a list, with separators.
 */
function datacatalog_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
    if (!empty($breadcrumb)):
      $breadcrumb[] = drupal_get_title();
      $breadcrumbs = '<ol class="breadcrumb">';
      $count = count($breadcrumb) - 1;
        foreach ($breadcrumb as $key => $value):
          $breadcrumbs .= '<li>' . $value . '</li>';
        endforeach;
      $breadcrumbs .= '</ol>';
      return $breadcrumbs;
    endif;
}

function datacatalog_preprocess_views_view(&$vars) {
  $view = &$vars['view'];
  // Make sure it's the correct view
  if ($view->name == 'communities_es' or $view->name == 'Communities' or $view->name == 'group_title' or $view->name == 'og_members_admin'):
    drupal_add_js(drupal_get_path('module', 'datacatalog_subscription') . '/js/datacatalog_subscription.js');
  endif;

  if ($view->name == 'og_members_admin'):
    drupal_add_library('system', 'ui');
    drupal_add_library('system', 'ui.dialog');
  endif;

}
function datacatalog_menu_link(array $variables) {
  $book_found = check_if_any_node_found("book");
  if ($variables['element']['#href'] == 'node/add/book' and $book_found >= 1):
    $variables['element']['#attributes']['style'][] = 'display:none';
  endif;
  return theme_menu_link($variables);
}
/**
 * implements hook_form_alter().
 */
function datacatalog_form_alter(&$form, &$form_state, $form_id)
{
  switch($form_id)
  {
    case 'user_login':
    case 'user_login_block':
      $form['actions']['links'] = array(
        array('#markup' => '<a class="forget-link" href="/user/password/">Forgot your password?</a>'),
        '#weight' => 100,
      );
      break;
  }
}
