<?php
/**
 * @file
 * data_catalog_search_api.features.inc
 */

/**
 * Implements hook_default_search_api_index().
 */
function data_catalog_search_api_default_search_api_index() {
  $items = array();
  $items['business_processes'] = entity_import('search_api_index', '{
    "name" : "business processes",
    "machine_name" : "business_processes",
    "description" : null,
    "server" : "datacatalog_es",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "business_process" ] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "number_of_shards" : "4",
      "number_of_replicas" : "0",
      "fields" : {
        "author" : { "type" : "integer", "entity_type" : "user" },
        "changed" : { "type" : "date" },
        "created" : { "type" : "date" },
        "edit_url" : { "type" : "uri" },
        "is_new" : { "type" : "boolean" },
        "language" : { "type" : "string" },
        "nid" : { "type" : "integer" },
        "og_group_ref" : { "type" : "integer", "entity_type" : "node" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "title" : { "type" : "text" },
        "type" : { "type" : "string" },
        "url" : { "type" : "uri" },
        "vid" : { "type" : "integer" }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  $items['communities'] = entity_import('search_api_index', '{
    "name" : "communities",
    "machine_name" : "communities",
    "description" : null,
    "server" : "datacatalog_es",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "group" ] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "number_of_shards" : "4",
      "number_of_replicas" : "0",
      "fields" : {
        "author" : { "type" : "integer", "entity_type" : "user" },
        "changed" : { "type" : "date" },
        "created" : { "type" : "date" },
        "edit_url" : { "type" : "uri" },
        "field_cmnty_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_owners" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "user" },
        "group_group" : { "type" : "boolean" },
        "is_new" : { "type" : "boolean" },
        "language" : { "type" : "string" },
        "members__1" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "user" },
        "members__1:created" : { "type" : "list\\u003Cdate\\u003E" },
        "members__1:edit_url" : { "type" : "list\\u003Curi\\u003E" },
        "members__1:field_profile_company" : { "type" : "list\\u003Ctext\\u003E" },
        "members__1:field_profile_position" : { "type" : "list\\u003Ctext\\u003E" },
        "members__1:name" : { "type" : "list\\u003Ctext\\u003E" },
        "members__1:status" : { "type" : "list\\u003Cinteger\\u003E" },
        "members__1:theme" : { "type" : "list\\u003Ctext\\u003E" },
        "members__1:uid" : { "type" : "list\\u003Cinteger\\u003E" },
        "members__1:url" : { "type" : "list\\u003Curi\\u003E" },
        "members__2" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "user" },
        "members__2:status" : { "type" : "list\\u003Cinteger\\u003E" },
        "members__2:uid" : { "type" : "list\\u003Cinteger\\u003E" },
        "members__3" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "user" },
        "nid" : { "type" : "integer" },
        "og_group_ref__og_membership" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "og_membership" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "title" : { "type" : "text" },
        "url" : { "type" : "uri" },
        "vid" : { "type" : "integer" }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  $items['messages'] = entity_import('search_api_index', '{
    "name" : "Messages",
    "machine_name" : "messages",
    "description" : null,
    "server" : "datacatalog_es",
    "item_type" : "message",
    "options" : {
      "datasource" : { "bundles" : [ "example_create_comment", "example_og_post_in_group" ] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "number_of_shards" : "1",
      "number_of_replicas" : "0",
      "fields" : {
        "field_comment_ref" : { "type" : "integer", "entity_type" : "comment" },
        "field_node_groups_ref" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_node_ref" : { "type" : "integer", "entity_type" : "node" },
        "field_node_ref:nid" : { "type" : "integer" },
        "field_node_ref:title" : { "type" : "text" },
        "field_published" : { "type" : "boolean" },
        "language" : { "type" : "text" },
        "mid" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "text" : { "type" : "text" },
        "timestamp" : { "type" : "date" },
        "type" : { "type" : "string", "entity_type" : "message_type" },
        "user" : { "type" : "integer", "entity_type" : "user" }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  $items['sources'] = entity_import('search_api_index', '{
    "name" : "sources",
    "machine_name" : "sources",
    "description" : null,
    "server" : "datacatalog_es",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "source" ] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "number_of_shards" : "4",
      "number_of_replicas" : "0",
      "fields" : {
        "author" : { "type" : "integer", "entity_type" : "user" },
        "changed" : { "type" : "date" },
        "comments" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "comment" },
        "comments:author" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "user" },
        "comments:comment_body:value" : { "type" : "list\\u003Ctext\\u003E" },
        "comments:node" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "created" : { "type" : "date" },
        "edit_url" : { "type" : "uri" },
        "field_business_process" : { "type" : "integer", "entity_type" : "node" },
        "field_business_process:author" : { "type" : "integer", "entity_type" : "user" },
        "field_business_process:body:value" : { "type" : "text" },
        "field_business_process:created" : { "type" : "date" },
        "field_business_process:status" : { "type" : "integer" },
        "field_business_process:title" : { "type" : "text" },
        "field_owners" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "user" },
        "field_subscribed_" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "user" },
        "field_tags_term" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "is_new" : { "type" : "boolean" },
        "language" : { "type" : "string" },
        "nid" : { "type" : "integer" },
        "og_group_ref" : { "type" : "integer", "entity_type" : "node" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "title" : { "type" : "text" },
        "type" : { "type" : "string" },
        "url" : { "type" : "uri" },
        "vid" : { "type" : "integer" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "field_business_process:title" : true,
              "field_business_process:body:value" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_business_process:title" : true,
              "field_business_process:body:value" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_business_process:title" : true,
              "field_business_process:body:value" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_business_process:title" : true,
              "field_business_process:body:value" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  $items['users'] = entity_import('search_api_index', '{
    "name" : "users",
    "machine_name" : "users",
    "description" : null,
    "server" : "datacatalog_es",
    "item_type" : "user",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "50",
      "number_of_shards" : "4",
      "number_of_replicas" : "0",
      "fields" : {
        "created" : { "type" : "date" },
        "edit_url" : { "type" : "uri" },
        "field_profile_description" : { "type" : "text" },
        "mail" : { "type" : "text" },
        "name" : { "type" : "text" },
        "og_membership__1:created" : { "type" : "list\\u003Cdate\\u003E" },
        "roles" : { "type" : "list\\u003Cinteger\\u003E" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "uid" : { "type" : "integer" },
        "url" : { "type" : "uri" }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  $items['wiki'] = entity_import('search_api_index', '{
    "name" : "wiki",
    "machine_name" : "wiki",
    "description" : null,
    "server" : "datacatalog_es",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "book" ] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "number_of_shards" : "4",
      "number_of_replicas" : "0",
      "fields" : {
        "author" : { "type" : "integer", "entity_type" : "user" },
        "changed" : { "type" : "date" },
        "created" : { "type" : "date" },
        "edit_url" : { "type" : "uri" },
        "field_community_refrence" : { "type" : "integer", "entity_type" : "node" },
        "is_new" : { "type" : "boolean" },
        "language" : { "type" : "string" },
        "nid" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "title" : { "type" : "text" },
        "type" : { "type" : "string" },
        "url" : { "type" : "uri" },
        "vid" : { "type" : "integer" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : { "title" : true } }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : { "title" : true },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : { "title" : true },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : { "title" : true },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function data_catalog_search_api_default_search_api_server() {
  $items = array();
  $items['datacatalog_es'] = entity_import('search_api_server', '{
    "name" : "Datacatalog ES",
    "machine_name" : "datacatalog_es",
    "description" : "",
    "class" : "search_api_elasticsearch_elastica_service",
    "options" : {
      "0" : {
        "host" : "127.0.0.1",
        "port" : "9200",
        "headers" : { "http_user" : "" },
        "path" : "",
        "url" : "",
        "transport" : "Http",
        "persistent" : 1,
        "timeout" : "300",
        "log" : false,
        "retryOnConflict" : "0"
      },
      "facet_limit" : ""
    },
    "enabled" : "1",
    "rdf_mapping" : []
  }');
  return $items;
}
