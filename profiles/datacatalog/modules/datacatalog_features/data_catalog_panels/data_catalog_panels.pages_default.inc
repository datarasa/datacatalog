<?php
/**
 * @file
 * data_catalog_panels.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function data_catalog_panels_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_2b271847-e638-4511-8ad3-42cd09fa3f3a';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'Wiki node page',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'book',
          'settings' => array(
            'book' => array(
              'any' => 'any',
              143 => 0,
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'book' => 'book',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible:source_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'source_left' => NULL,
      'source_bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '56320d9a-a788-4730-b9e4-d37132f847e8';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-a47284b6-8632-451e-aace-6bb34e35d21b';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'book_explorer-book_explorer';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'a47284b6-8632-451e-aace-6bb34e35d21b';
    $display->content['new-a47284b6-8632-451e-aace-6bb34e35d21b'] = $pane;
    $display->panels['center'][0] = 'new-a47284b6-8632-451e-aace-6bb34e35d21b';
    $pane = new stdClass();
    $pane->pid = 'new-1d7b9cc4-a066-4b75-8f21-eadd89b8df45';
    $pane->panel = 'source_left';
    $pane->type = 'block';
    $pane->subtype = 'datacatalog_blocks-contextual_dropdown_links';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 3,
              1 => 4,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'wiki-edit',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '1d7b9cc4-a066-4b75-8f21-eadd89b8df45';
    $display->content['new-1d7b9cc4-a066-4b75-8f21-eadd89b8df45'] = $pane;
    $display->panels['source_left'][0] = 'new-1d7b9cc4-a066-4b75-8f21-eadd89b8df45';
    $pane = new stdClass();
    $pane->pid = 'new-f9e3181c-255e-4ca5-886d-38f6355a11d4';
    $pane->panel = 'source_left';
    $pane->type = 'views';
    $pane->subtype = 'wiki_page';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '1',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block',
      'context' => array(
        0 => '',
      ),
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'f9e3181c-255e-4ca5-886d-38f6355a11d4';
    $display->content['new-f9e3181c-255e-4ca5-886d-38f6355a11d4'] = $pane;
    $display->panels['source_left'][1] = 'new-f9e3181c-255e-4ca5-886d-38f6355a11d4';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_2b271847-e638-4511-8ad3-42cd09fa3f3a'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_2da4416f-f554-4acb-ad4b-336f97ce1982';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 2;
  $handler->conf = array(
    'title' => 'source page',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'source' => 'source',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'path_visibility',
          'settings' => array(
            'visibility_setting' => '1',
            'paths' => 'source/*',
          ),
          'context' => 'empty',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
          1 => 1,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
          1 => 'source_right',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'source left',
        'width' => 74.489577875753355,
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
        'hide_empty' => 0,
      ),
      'source_right' => array(
        'type' => 'region',
        'title' => 'source right',
        'width' => '25.51042212424665',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
        'hide_empty' => 1,
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'bottom',
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      'bottom' => array(
        'type' => 'region',
        'title' => 'bottom',
        'width' => 100,
        'width_type' => '%',
        'parent' => '1',
        'class' => '',
        'hide_empty' => 0,
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => array(),
      'left' => NULL,
      'right' => NULL,
      'source_left' => NULL,
      'source_bottom' => NULL,
      'source_right' => array(),
      'bottom' => array(),
      'center' => array(),
    ),
    'source_right' => array(
      'style' => 'stylizer',
    ),
    'style' => 'stylizer',
    'center' => array(
      'style' => 'stylizer',
    ),
    'bottom' => array(
      'style' => 'stylizer',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'd35ab83e-53b9-4f83-b0ef-328918e60369';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0bfb1b53-e4f0-4d0c-95dc-d1dde2e3d57b';
    $pane->panel = 'bottom';
    $pane->type = 'views';
    $pane->subtype = 'metadata_fields_view';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'context' => array(
        0 => 'argument_entity_id:node_1.nid',
      ),
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0bfb1b53-e4f0-4d0c-95dc-d1dde2e3d57b';
    $display->content['new-0bfb1b53-e4f0-4d0c-95dc-d1dde2e3d57b'] = $pane;
    $display->panels['bottom'][0] = 'new-0bfb1b53-e4f0-4d0c-95dc-d1dde2e3d57b';
    $pane = new stdClass();
    $pane->pid = 'new-08dbca06-ba65-45ba-8876-c7fd3a784609';
    $pane->panel = 'bottom';
    $pane->type = 'node_comment_wrapper';
    $pane->subtype = 'node_comment_wrapper';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'mode' => '1',
      'comments_per_page' => '50',
      'context' => 'argument_entity_id:node_1',
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '08dbca06-ba65-45ba-8876-c7fd3a784609';
    $display->content['new-08dbca06-ba65-45ba-8876-c7fd3a784609'] = $pane;
    $display->panels['bottom'][1] = 'new-08dbca06-ba65-45ba-8876-c7fd3a784609';
    $pane = new stdClass();
    $pane->pid = 'new-0a7925b5-3caf-4322-b4a1-725fe90d9f92';
    $pane->panel = 'center';
    $pane->type = 'node_title';
    $pane->subtype = 'node_title';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'link' => 0,
      'markup' => 'h1',
      'id' => '',
      'class' => 'page-title',
      'context' => 'argument_entity_id:node_1',
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(),
      'style' => 'stylizer',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0a7925b5-3caf-4322-b4a1-725fe90d9f92';
    $display->content['new-0a7925b5-3caf-4322-b4a1-725fe90d9f92'] = $pane;
    $display->panels['center'][0] = 'new-0a7925b5-3caf-4322-b4a1-725fe90d9f92';
    $pane = new stdClass();
    $pane->pid = 'new-3e018267-ad8d-4ff3-ac16-de4d09c9ced2';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'trim_length' => '300',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(),
      'style' => 'stylizer',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'inner',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '3e018267-ad8d-4ff3-ac16-de4d09c9ced2';
    $display->content['new-3e018267-ad8d-4ff3-ac16-de4d09c9ced2'] = $pane;
    $display->panels['center'][1] = 'new-3e018267-ad8d-4ff3-ac16-de4d09c9ced2';
    $pane = new stdClass();
    $pane->pid = 'new-527ae42d-0c64-429d-bdbc-4e2cf32a4726';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_tags_term';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
      'formatter' => 'taxonomy_term_reference_link',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(),
      'style' => 'stylizer',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'inner',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '527ae42d-0c64-429d-bdbc-4e2cf32a4726';
    $display->content['new-527ae42d-0c64-429d-bdbc-4e2cf32a4726'] = $pane;
    $display->panels['center'][2] = 'new-527ae42d-0c64-429d-bdbc-4e2cf32a4726';
    $pane = new stdClass();
    $pane->pid = 'new-86191076-09ee-4bb3-99a8-4396e6d946e5';
    $pane->panel = 'center';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:og_group_ref';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'inline',
      'formatter' => 'entityreference_label',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'link' => 1,
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(),
      'style' => 'stylizer',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'inner',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '86191076-09ee-4bb3-99a8-4396e6d946e5';
    $display->content['new-86191076-09ee-4bb3-99a8-4396e6d946e5'] = $pane;
    $display->panels['center'][3] = 'new-86191076-09ee-4bb3-99a8-4396e6d946e5';
    $pane = new stdClass();
    $pane->pid = 'new-df570043-694f-4942-b5d8-688dbdb8ab8c';
    $pane->panel = 'source_right';
    $pane->type = 'block';
    $pane->subtype = 'datacatalog_blocks-contextual_dropdown_links';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(),
      'style' => 'stylizer',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'right-pane-contextual-links',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'df570043-694f-4942-b5d8-688dbdb8ab8c';
    $display->content['new-df570043-694f-4942-b5d8-688dbdb8ab8c'] = $pane;
    $display->panels['source_right'][0] = 'new-df570043-694f-4942-b5d8-688dbdb8ab8c';
    $pane = new stdClass();
    $pane->pid = 'new-49459fca-c291-4804-b275-83f00cfd60b7';
    $pane->panel = 'source_right';
    $pane->type = 'block';
    $pane->subtype = 'datacatalog_blocks-node_page_subscrptn_button';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(),
      'style' => 'stylizer',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'right-pane-custom-button',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '49459fca-c291-4804-b275-83f00cfd60b7';
    $display->content['new-49459fca-c291-4804-b275-83f00cfd60b7'] = $pane;
    $display->panels['source_right'][1] = 'new-49459fca-c291-4804-b275-83f00cfd60b7';
    $pane = new stdClass();
    $pane->pid = 'new-c67e6b09-1ae9-49e9-a979-e32ef85ea0e3';
    $pane->panel = 'source_right';
    $pane->type = 'block';
    $pane->subtype = 'block-2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'c67e6b09-1ae9-49e9-a979-e32ef85ea0e3';
    $display->content['new-c67e6b09-1ae9-49e9-a979-e32ef85ea0e3'] = $pane;
    $display->panels['source_right'][2] = 'new-c67e6b09-1ae9-49e9-a979-e32ef85ea0e3';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_2da4416f-f554-4acb-ad4b-336f97ce1982'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_54c6bdeb-133d-4bbc-9bee-ebedae1eb47f';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'OG panel Group Page',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'og_is_node_group',
          'settings' => NULL,
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'c7ca486f-5651-4b23-9b96-08fc09b40b39';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-2291a527-4055-4b99-974c-1d1862abf5ef';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'quicktabs-community_page';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '2291a527-4055-4b99-974c-1d1862abf5ef';
    $display->content['new-2291a527-4055-4b99-974c-1d1862abf5ef'] = $pane;
    $display->panels['center'][0] = 'new-2291a527-4055-4b99-974c-1d1862abf5ef';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_54c6bdeb-133d-4bbc-9bee-ebedae1eb47f'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function data_catalog_panels_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'communities_page';
  $page->task = 'page';
  $page->admin_title = 'Communities Page';
  $page->admin_description = '';
  $page->path = 'communities';
  $page->access = array(
    'logic' => 'and',
    'plugins' => array(
      0 => array(
        'name' => 'role',
        'settings' => array(
          'rids' => array(
            0 => 2,
          ),
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_communities_page__panel_context_df4669f4-9c60-49e4-9652-a1b6b74e7674';
  $handler->task = 'page';
  $handler->subtask = 'communities_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '9970c63d-68ed-4750-8508-18b0d48aa763';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-9ce3848a-a49d-4e41-8113-026f3786dd52';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'block-1';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 4,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '<none>',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '9ce3848a-a49d-4e41-8113-026f3786dd52';
    $display->content['new-9ce3848a-a49d-4e41-8113-026f3786dd52'] = $pane;
    $display->panels['center'][0] = 'new-9ce3848a-a49d-4e41-8113-026f3786dd52';
    $pane = new stdClass();
    $pane->pid = 'new-c3591781-a4ad-46e0-9a1f-1bd9384c6c70';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'quicktabs-communities_page';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'c3591781-a4ad-46e0-9a1f-1bd9384c6c70';
    $display->content['new-c3591781-a4ad-46e0-9a1f-1bd9384c6c70'] = $pane;
    $display->panels['center'][1] = 'new-c3591781-a4ad-46e0-9a1f-1bd9384c6c70';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-c3591781-a4ad-46e0-9a1f-1bd9384c6c70';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['communities_page'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'dashboard';
  $page->task = 'page';
  $page->admin_title = 'Dashboard';
  $page->admin_description = '';
  $page->path = 'dashboard';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'role',
        'settings' => array(
          'rids' => array(
            0 => 2,
          ),
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_dashboard__panel';
  $handler->task = 'page';
  $handler->subtask = 'dashboard';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Dashboard',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
    'access' => array(
      'plugins' => array(),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible:dashboard_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'left' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Dashboard';
  $display->uuid = '2065e9aa-3289-4624-a3e1-bfb3b5b24299';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0efaa55e-eaa6-42a8-874a-60b4d97792ba';
    $pane->panel = 'center';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'activity title',
      'title' => '',
      'body' => '<span class="activity-title">Activity</span>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0efaa55e-eaa6-42a8-874a-60b4d97792ba';
    $display->content['new-0efaa55e-eaa6-42a8-874a-60b4d97792ba'] = $pane;
    $display->panels['center'][0] = 'new-0efaa55e-eaa6-42a8-874a-60b4d97792ba';
    $pane = new stdClass();
    $pane->pid = 'new-1effa515-0e27-42be-85ba-047f6ec2468a';
    $pane->panel = 'center';
    $pane->type = 'views';
    $pane->subtype = 'communities_recent_activity';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '9',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'override_title' => 1,
      'override_title_text' => '<none>',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '1effa515-0e27-42be-85ba-047f6ec2468a';
    $display->content['new-1effa515-0e27-42be-85ba-047f6ec2468a'] = $pane;
    $display->panels['center'][1] = 'new-1effa515-0e27-42be-85ba-047f6ec2468a';
    $pane = new stdClass();
    $pane->pid = 'new-4ebc97a6-3f7d-4e31-8578-a625855ab7ef';
    $pane->panel = 'left';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Users Title',
      'title' => '',
      'body' => '<h4 class="dash-block-title">Users per Month</h4>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '4ebc97a6-3f7d-4e31-8578-a625855ab7ef';
    $display->content['new-4ebc97a6-3f7d-4e31-8578-a625855ab7ef'] = $pane;
    $display->panels['left'][0] = 'new-4ebc97a6-3f7d-4e31-8578-a625855ab7ef';
    $pane = new stdClass();
    $pane->pid = 'new-e6818cba-cebc-409c-80cc-bcff2931ed5a';
    $pane->panel = 'left';
    $pane->type = 'block';
    $pane->subtype = 'block-11';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '<none>',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'e6818cba-cebc-409c-80cc-bcff2931ed5a';
    $display->content['new-e6818cba-cebc-409c-80cc-bcff2931ed5a'] = $pane;
    $display->panels['left'][1] = 'new-e6818cba-cebc-409c-80cc-bcff2931ed5a';
    $pane = new stdClass();
    $pane->pid = 'new-64c7a09a-357d-406d-b848-42111ab0a868';
    $pane->panel = 'left';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Separator',
      'title' => '',
      'body' => '<div class="panel-separator" style="height:40px;"></div>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '64c7a09a-357d-406d-b848-42111ab0a868';
    $display->content['new-64c7a09a-357d-406d-b848-42111ab0a868'] = $pane;
    $display->panels['left'][2] = 'new-64c7a09a-357d-406d-b848-42111ab0a868';
    $pane = new stdClass();
    $pane->pid = 'new-667fa1d9-ae22-42f0-9207-f2747942b32e';
    $pane->panel = 'left';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Sources Title',
      'title' => '',
      'body' => '<h4 class="dash-block-title">Sources per Month</h4>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '667fa1d9-ae22-42f0-9207-f2747942b32e';
    $display->content['new-667fa1d9-ae22-42f0-9207-f2747942b32e'] = $pane;
    $display->panels['left'][3] = 'new-667fa1d9-ae22-42f0-9207-f2747942b32e';
    $pane = new stdClass();
    $pane->pid = 'new-e5d53b2f-0aa1-41bb-a5c7-4043504ae711';
    $pane->panel = 'left';
    $pane->type = 'block';
    $pane->subtype = 'block-12';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '<none>',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = 'e5d53b2f-0aa1-41bb-a5c7-4043504ae711';
    $display->content['new-e5d53b2f-0aa1-41bb-a5c7-4043504ae711'] = $pane;
    $display->panels['left'][4] = 'new-e5d53b2f-0aa1-41bb-a5c7-4043504ae711';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-e6818cba-cebc-409c-80cc-bcff2931ed5a';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['dashboard'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'dashboard_page';
  $page->task = 'page';
  $page->admin_title = 'Dashboard Page';
  $page->admin_description = 'use as front dashboard page';
  $page->path = 'dashboard';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_dashboard_page__panel';
  $handler->task = 'page';
  $handler->subtask = 'dashboard_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 2,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
          1 => 'front_right_region_',
        ),
        'parent' => 'main',
        'class' => 'col-md-12  col-sm-12 col-xs-12',
        'hide_empty' => 0,
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Main Region',
        'width' => '60.92896174863388',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => 'front-main-region col-md-7  col-sm-7 col-xs-12',
        'hide_empty' => 0,
      ),
      'front_right_region_' => array(
        'type' => 'region',
        'title' => 'Front Right Region ',
        'width' => '39.07103825136612',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => 'front-right-region col-md-5  col-sm-5 col-xs-12',
        'hide_empty' => 0,
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'front_right_region_' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'd5be0239-18d3-446f-acaa-d3973b8cdd64';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-19c43eaf-6f2b-4c42-a0b3-6a0e2f3ff293';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'datacatalog_blocks-datacatalog_views_comments';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '19c43eaf-6f2b-4c42-a0b3-6a0e2f3ff293';
    $display->content['new-19c43eaf-6f2b-4c42-a0b3-6a0e2f3ff293'] = $pane;
    $display->panels['center'][0] = 'new-19c43eaf-6f2b-4c42-a0b3-6a0e2f3ff293';
    $pane = new stdClass();
    $pane->pid = 'new-087c74ea-0d98-4291-8303-066193ab12b4';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'datacatalog_blocks-datacatalog_dataitems_members';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '087c74ea-0d98-4291-8303-066193ab12b4';
    $display->content['new-087c74ea-0d98-4291-8303-066193ab12b4'] = $pane;
    $display->panels['center'][1] = 'new-087c74ea-0d98-4291-8303-066193ab12b4';
    $pane = new stdClass();
    $pane->pid = 'new-882d9614-2384-4911-87d8-a03e6b9e16be';
    $pane->panel = 'front_right_region_';
    $pane->type = 'block';
    $pane->subtype = 'datacatalog_blocks-datacatalog_total_members';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Total Members',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-md-6  col-sm-6 col-xs-12',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '882d9614-2384-4911-87d8-a03e6b9e16be';
    $display->content['new-882d9614-2384-4911-87d8-a03e6b9e16be'] = $pane;
    $display->panels['front_right_region_'][0] = 'new-882d9614-2384-4911-87d8-a03e6b9e16be';
    $pane = new stdClass();
    $pane->pid = 'new-f6a1b92a-e285-430f-8be5-f0b090aa3810';
    $pane->panel = 'front_right_region_';
    $pane->type = 'block';
    $pane->subtype = 'datacatalog_blocks-datacatalog_total_posts';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Total Posts',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-md-6  col-sm-6 col-xs-12',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'f6a1b92a-e285-430f-8be5-f0b090aa3810';
    $display->content['new-f6a1b92a-e285-430f-8be5-f0b090aa3810'] = $pane;
    $display->panels['front_right_region_'][1] = 'new-f6a1b92a-e285-430f-8be5-f0b090aa3810';
    $pane = new stdClass();
    $pane->pid = 'new-e7a99e5d-6400-4f42-947f-d26a8932f50a';
    $pane->panel = 'front_right_region_';
    $pane->type = 'block';
    $pane->subtype = 'datacatalog_blocks-datacatalog_dataitems_by_week';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-md-12  col-sm-12 col-xs-12',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'e7a99e5d-6400-4f42-947f-d26a8932f50a';
    $display->content['new-e7a99e5d-6400-4f42-947f-d26a8932f50a'] = $pane;
    $display->panels['front_right_region_'][2] = 'new-e7a99e5d-6400-4f42-947f-d26a8932f50a';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-087c74ea-0d98-4291-8303-066193ab12b4';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['dashboard_page'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'my_communities_page';
  $page->task = 'page';
  $page->admin_title = 'My Communities Page';
  $page->admin_description = '';
  $page->path = 'my-communities';
  $page->access = array(
    'logic' => 'and',
    'plugins' => array(
      0 => array(
        'name' => 'role',
        'settings' => array(
          'rids' => array(
            0 => 2,
          ),
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_my_communities_page__panel_context_9235e33b-e2e8-4a3a-b9f4-0a01d280921b';
  $handler->task = 'page';
  $handler->subtask = 'my_communities_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '9970c63d-68ed-4750-8508-18b0d48aa763';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-52453eb1-9b94-4836-92c6-912ef7345e65';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'quicktabs-my_communities_page';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '52453eb1-9b94-4836-92c6-912ef7345e65';
    $display->content['new-52453eb1-9b94-4836-92c6-912ef7345e65'] = $pane;
    $display->panels['center'][0] = 'new-52453eb1-9b94-4836-92c6-912ef7345e65';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['my_communities_page'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'owners_lookup';
  $page->task = 'page';
  $page->admin_title = 'Owners Lookup';
  $page->admin_description = '';
  $page->path = 'owners';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'role',
        'settings' => array(
          'rids' => array(
            0 => 2,
          ),
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_owners_lookup__panel';
  $handler->task = 'page';
  $handler->subtask = 'owners_lookup';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '8a2572e8-3670-41a7-8781-801ff7358b3a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-b2164911-22db-4c4e-8a4a-d4e840786429';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'quicktabs-owners_lookup';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'b2164911-22db-4c4e-8a4a-d4e840786429';
    $display->content['new-b2164911-22db-4c4e-8a4a-d4e840786429'] = $pane;
    $display->panels['center'][0] = 'new-b2164911-22db-4c4e-8a4a-d4e840786429';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['owners_lookup'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'wiki';
  $page->task = 'page';
  $page->admin_title = 'wiki';
  $page->admin_description = '';
  $page->path = 'wiki/introduction-general-wiki';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_wiki__panel';
  $handler->task = 'page';
  $handler->subtask = 'wiki';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'wiki-page',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
    'access' => array(
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible:source_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'source_left' => NULL,
      'source_bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '9ac01fe8-2402-4264-8b19-3eff993ec414';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-c66970fb-2a8d-45d4-aa7c-7b936f06c3fe';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'book_explorer-book_explorer';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array(
      'method' => '0',
      'settings' => array(),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'c66970fb-2a8d-45d4-aa7c-7b936f06c3fe';
    $display->content['new-c66970fb-2a8d-45d4-aa7c-7b936f06c3fe'] = $pane;
    $display->panels['center'][0] = 'new-c66970fb-2a8d-45d4-aa7c-7b936f06c3fe';
    $pane = new stdClass();
    $pane->pid = 'new-276bb5a9-6bd9-4bfb-9218-cf71750026a0';
    $pane->panel = 'source_left';
    $pane->type = 'views';
    $pane->subtype = 'wiki';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '1',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'page',
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '276bb5a9-6bd9-4bfb-9218-cf71750026a0';
    $display->content['new-276bb5a9-6bd9-4bfb-9218-cf71750026a0'] = $pane;
    $display->panels['source_left'][0] = 'new-276bb5a9-6bd9-4bfb-9218-cf71750026a0';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['wiki'] = $page;

  return $pages;

}
