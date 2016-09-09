<?php
/**
 * @file
 * data_catalog_blocks.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function data_catalog_blocks_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-add_community_link_block'] = array(
    'cache' => -1,
    'css_class' => 'add-community-link',
    'custom' => 0,
    'machine_name' => 'add_community_link_block',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'communities',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => -30,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['block-source_csv_info'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'machine_name' => 'source_csv_info',
    'module' => 'block',
    'node_types' => array(
      0 => 'source',
    ),
    'pages' => 'source/*',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => -29,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['block-source_graph'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'machine_name' => 'source_graph',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(
      'authenticated user' => 2,
    ),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Sources Per Month',
    'visibility' => 1,
  );

  $export['block-source_metadata'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'machine_name' => 'source_metadata',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['block-user_graph'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'machine_name' => 'user_graph',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(
      'authenticated user' => 2,
    ),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Users Per Month',
    'visibility' => 1,
  );

  $export['datacatalog_blocks-contextual_dropdown_links'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'contextual_dropdown_links',
    'module' => 'datacatalog_blocks',
    'node_types' => array(
      0 => 'source',
    ),
    'pages' => 'user',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => -35,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['datacatalog_blocks-custom_user_dropdown'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'custom_user_dropdown',
    'module' => 'datacatalog_blocks',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'authenticated user' => 2,
    ),
    'themes' => array(
      'datacatalog' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  $export['datacatalog_blocks-datacatalog_meta_data'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'datacatalog_meta_data',
    'module' => 'datacatalog_blocks',
    'node_types' => array(
      0 => 'source',
    ),
    'pages' => 'source/*',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['datacatalog_blocks-node_page_subscrptn_button'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'node_page_subscrptn_button',
    'module' => 'datacatalog_blocks',
    'node_types' => array(
      0 => 'source',
    ),
    'pages' => '<?php
	  if(arg(1)!="add" and arg(2)!="edit" and arg(2)!="revisions" and arg(2)!="delete") {
            return TRUE;
         }

?>',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => -36,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 2,
  );

  $export['hybridauth-hybridauth'] = array(
    'cache' => 8,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'hybridauth',
    'module' => 'hybridauth',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['quicktabs-communities_page'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'communities_page',
    'module' => 'quicktabs',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['quicktabs-community_page'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'community_page',
    'module' => 'quicktabs',
    'node_types' => array(),
    'pages' => '<?php
$node = node_load(arg(1));
if((arg(0)=="node" && $node->type==\'group\' && arg(2)!="edit") && (arg(0)=="node" && $node->type==\'group\' && arg(2)!="delete"))
  return TRUE;

?>',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'datacatalog',
        'weight' => -33,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 2,
  );

  $export['quicktabs-my_communities_page'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'my_communities_page',
    'module' => 'quicktabs',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['quicktabs-owners_lookup'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'owners_lookup',
    'module' => 'quicktabs',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['quicktabs-user_profile_page'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'user_profile_page',
    'module' => 'quicktabs',
    'node_types' => array(),
    'pages' => '<?php
global $user;
if(arg(0)=="user" and $user->uid!="" and arg(2)!="edit"  ) {
  return TRUE;
}
?>',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 2,
  );

  $export['quicktabs-user_profile_source_sub_tabs'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'user_profile_source_sub_tabs',
    'module' => 'quicktabs',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['search-form'] = array(
    'cache' => -1,
    'css_class' => 'col-md-3 col-sm-5 col-xs-5 p-0 ',
    'custom' => 0,
    'delta' => 'form',
    'module' => 'search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'datacatalog',
        'weight' => -40,
      ),
      'seven' => array(
        'region' => 'dashboard_inactive',
        'status' => 1,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  $export['superfish-1'] = array(
    'cache' => -1,
    'css_class' => 'col-md-7',
    'custom' => 0,
    'delta' => 1,
    'module' => 'superfish',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'datacatalog',
        'weight' => -41,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  $export['system-main'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'main',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'datacatalog',
        'weight' => -34,
      ),
      'seven' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-10b37c8a95b304085fb5fe5d7dfe907e'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => '10b37c8a95b304085fb5fe5d7dfe907e',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-46fcbcdca4ce77fc0bdd873ae7148031'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => '46fcbcdca4ce77fc0bdd873ae7148031',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-6caefb35b53fb4ef10c2eccaea57dfe0'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => '6caefb35b53fb4ef10c2eccaea57dfe0',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-81ca1c4235078c6583acf90f7b1be2b2'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => '81ca1c4235078c6583acf90f7b1be2b2',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-8f12e2385a005c2a6de1b6fc275baf55'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => '8f12e2385a005c2a6de1b6fc275baf55',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-community_wiki_es-block'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => 'community_wiki_es-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-d48df7a19235dcd8063bb1e96e6314e3'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => 'd48df7a19235dcd8063bb1e96e6314e3',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-df89a5337e23dfc851798033e9b79505'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => 'df89a5337e23dfc851798033e9b79505',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-f20e31d90aff2e85304b0251bdec8dc3'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => 'f20e31d90aff2e85304b0251bdec8dc3',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-group_content_es-block'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => 'group_content_es-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-group_title-block'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'group_title-block',
    'module' => 'views',
    'node_types' => array(
      0 => 'group',
    ),
    'pages' => '<?php
if(arg(2)!="delete" and arg(2)!="edit") {
  return true;
}

?>',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'datacatalog',
        'weight' => -36,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 2,
  );

  $export['views-owners_es-block'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => 'owners_es-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-owners_es-block_1'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => 'owners_es-block_1',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  $export['views-user_profile_wiki_tab_es-block'] = array(
    'cache' => -1,
    'css_class' => '',
    'delta' => 'user_profile_wiki_tab_es-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'datacatalog' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'datacatalog',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
  );

  return $export;
}
