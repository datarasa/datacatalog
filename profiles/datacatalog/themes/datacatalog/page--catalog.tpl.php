<?php if (theme_get_setting('scrolltop_display')): ?>
  <div id="toTop"><span class="glyphicon glyphicon-chevron-up"></span></div>
<?php endif; ?>

<!-- #page -->
<div id="page" class="clearfix"> 
  <!-- #main-content -->
  <div id="main-content">
    <div class="container-fluid">
      <div class="row row-eq-height row-offcanvas row-offcanvas-left nav_colpsd">
        <div class="eq-hdr-rw">
          <?php if ($logo): ?>
            <div class="logo-wrapper">
              <div id="logo"> 
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"> 
                  <img class="logo_colpsd" src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /> 
                </a> 
                <div id="menu-toggler" class="menu-toggler sidebar-toggler"> </div>
                <div class="res-toggler"> </div>
              </div>
            </div>
          <?php endif; ?>  
          <?php if ($page['header']): ?>
            <?php print render($page['header']); ?>
          <?php endif; ?>
        </div>  
        <div class="eq_rows_wrapper"> 
          <aside class="left-col sidebar-offcanvas">

            <?php if ($page['sidebar_first']): ?>

            <!--#sidebar-first-->
              <section id="sidebar-first" class="sidebar clearfix"> <?php print render($page['sidebar_first']); ?> </section>
            <!--EOF:#sidebar-first-->
            <?php endif; ?>
          </aside>
          <div class="mobi-header col-xs-12 p-0">
            <?php if ($page['header']): ?>
              <?php print render($page['header']); ?>
            <?php endif; ?>
          </div>
          <div class="main-area">
            <!-- #main -->
            <div id="main" class="clearfix"> 
              <!-- #messages-console -->
              <?php if ($messages):?>
                <div id="messages-console" class="clearfix">
                  <div class="row">
                    <div class="col-md-12"> <?php print $messages; ?> </div>
                  </div>
                </div>
              <?php endif; ?>
              <!-- EOF: #messages-console -->

              <?php if ($page['breadcrumbs']): ?>
                <?php print render($page['breadcrumbs']); ?>
              <?php endif; ?>
              
              <!-- EOF:#content-wrapper -->
              <div id="content-wrapper">
               
                <?php print render($title_prefix); ?>
                <?php if ($title): ?>
                  <h1 class="page-title"><?php print $title; ?></h1>
                <?php endif; ?>
                <?php print render($title_suffix); ?> <?php print render($page['help']); ?> 
                
                <!-- #tabs -->
                <?php if ($tabs): ?>
                  <div class="tabs"> <?php print render($tabs); ?> </div>
                <?php endif; ?>
                <!-- EOF: #tabs --> 
                
                <!-- #action links -->
                <?php if ($action_links): ?>
                  <ul class="action-links">
                    <?php print render($action_links); ?>
                  </ul>
                <?php endif; ?>
                <!-- EOF: #action links --> 
                <div class="col-md-12 col-sm-12 col-xs-12 p-0">
                  <?php
                   /*$view = views_get_view('Communities');
                     $view->set_display('Datacatalog listing');
                     $view->init_handlers();
                     $exposed_form = $view->display_handler->get_plugin('exposed_form');
                      print $exposed_form->render_exposed_form(true);*/
                  ?>

                  <?php print render($page['content']); ?> <?php print $feed_icons; ?> 
                </div>
              </div>
              <!-- EOF:#content-wrapper --> 
              
            </div>
            <!-- EOF:#main -->
            <?php if ($page['sidebar_second']): ?>
              <aside class="<?php print $second_sidebar_grid_class; ?> right-col">
                <div class="arw_sdbr_scnd"></div>
                <!--#sidebar-second-->
                <section id="sidebar-second" class="sidebar clearfix"> <?php print render($page['sidebar_second']); ?> </section>
                <!--EOF:#sidebar-second--> 
              </aside>
            <?php endif; ?>
          </div>
        </div>
      </div>
    </div>
  </div>
  <!-- EOF:#main-content -->
  
  <?php if ($page['bottom_content']): ?>
    <!-- #bottom-content -->
    <div id="bottom-content" class="clearfix">

      <div class="container-fluid"> 
      
        <!-- #bottom-content-inside -->
        <div id="bottom-content-inside" class="clearfix">
          <div class="row">
            <div class="col-md-12"> <?php print render($page['bottom_content']); ?> </div>
          </div>
        </div>
        <!-- EOF:#bottom-content-inside --> 
      
      </div>
    </div>
    <!-- EOF: #bottom-content -->
  <?php endif; ?>
</div>
<!-- EOF:#page --> 