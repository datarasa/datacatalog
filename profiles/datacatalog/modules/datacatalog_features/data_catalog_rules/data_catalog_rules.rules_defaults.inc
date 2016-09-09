<?php
/**
 * @file
 * data_catalog_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function data_catalog_rules_default_rules_configuration() {
  $items = array();
  $items['rules_business_process_created'] = entity_import('rules_config', '{ "rules_business_process_created" : {
      "LABEL" : "Business process created",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "php", "rules" ],
      "ON" : { "node_insert--business_process" : { "bundle" : "business_process" } },
      "DO" : [
        { "php_eval" : { "code" : "\\u003C?php\\r\\ndrupal_set_message(\\u0027Business process saved sucessfully\\u0027);\\r\\ndrupal_goto($_SERVER[\\u0027HTTP_REFERER\\u0027]);\\r\\n\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_business_process_updated'] = entity_import('rules_config', '{ "rules_business_process_updated" : {
      "LABEL" : "Business process updated",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "php", "rules" ],
      "ON" : { "node_update--business_process" : { "bundle" : "business_process" } },
      "DO" : [
        { "php_eval" : { "code" : "\\u003C?php\\r\\ndrupal_set_message(\\u0027Business process updated sucessfully\\u0027);\\r\\ndrupal_goto($_SERVER[\\u0027HTTP_REFERER\\u0027]);\\r\\n\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_community_notification_after_content_post'] = entity_import('rules_config', '{ "rules_community_notification_after_content_post" : {
      "LABEL" : "Community notification after content post",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "og", "rules" ],
      "ON" : { "node_insert--source" : { "bundle" : "source" } },
      "IF" : [ { "og_entity_is_group_content" : { "entity" : [ "node" ] } } ],
      "DO" : [
        { "og_get_members" : {
            "USING" : { "group_content" : [ "node" ] },
            "PROVIDE" : { "group_members" : { "group_members" : "Fetch a List of group members" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "group-members" ] },
            "ITEM" : { "list_grp_members_emails" : "Get list of group members and their email ids" },
            "DO" : [
              { "mail" : {
                  "to" : "[list-grp-members-emails:mail]",
                  "subject" : "Notification:  [node:title-raw] posted in [node:ogname-raw]",
                  "message" : "[node:site-url]\\r\\n[node:title]\\r\\n[node:author-name]\\r\\n[node:ogname]\\r\\n[node:nid]\\r\\n[node:ogalias]\\r\\n[node:og-id]\\r\\n[node:field_mybodyfield-formatted]",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_notification_on_membership_approval'] = entity_import('rules_config', '{ "rules_notification_on_membership_approval" : {
      "LABEL" : "Notification on Membership Approval",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_approved" : [] },
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : "[account:mail]",
            "subject" : "Notification: Membership Approval",
            "message" : "[account:name],\\r\\n\\r\\nYour membership request was approved for the Community \\u0022[group:title] ([group:url])\\u0022.\\r\\n\\r\\nPlease log-in and start adding \\u0022Sources\\u0022 within the Community or become an active Community member.\\r\\n\\r\\nThanks,\\r\\n\\r\\nData Catalog Team.",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_notification_on_membership_block'] = entity_import('rules_config', '{ "rules_notification_on_membership_block" : {
      "LABEL" : "Notification on Membership Block",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_blocked" : [] },
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : "[account:mail]",
            "subject" : "Notification: Your Membership blocked",
            "message" : "Your membership request was blocked for \\u0022[group:title] ([group:url])\\u0022\\r\\n\\r\\nThanks,\\r\\n\\r\\nData Catalog Team.",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_notification_on_user_removed_from_group'] = entity_import('rules_config', '{ "rules_notification_on_user_removed_from_group" : {
      "LABEL" : "Notification on Member Removed from Group",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_delete" : [] },
      "DO" : [
        { "mail" : {
            "to" : "[account:mail]",
            "subject" : "xyz",
            "message" : "xyz",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_og_member_active'] = entity_import('rules_config', '{ "rules_og_member_active" : {
      "LABEL" : "OG member subscribe (Active)",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your membership request was approved for \\u0027[group:title]\\u0027\\r\\n",
            "message" : "[account:name],\\r\\n\\r\\nYou are now a member in the group \\u0027[group:title]\\u0027 located at [group:url]"
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] joined [group:title]",
            "message" : "[group:author:name],\\r\\n\\r\\n[account:name] joined [group:title] in [group:url]"
          }
        }
      ]
    }
  }');
  $items['rules_og_member_pending'] = entity_import('rules_config', '{ "rules_og_member_pending" : {
      "LABEL" : "OG member subscribe (Pending)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "2" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your membership request for \\u0027[group:title]\\u0027",
            "message" : "[account:name],\\r\\n\\r\\nYour membership request for Community \\u0022[group:title] ([group:url])\\u0022 is sent for approval to Community Admin, you will be informed shortly.\\r\\n\\r\\nOnce you get the Community membership, you will be able to add Source in the Community. Add Source button will be available under Community Source tab.\\r\\n\\r\\nThanks,\\r\\n\\r\\n[site:name] Team.",
            "language" : [ "" ]
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] membership request [group:title]",
            "message" : "[group:author:name],\\r\\n\\r\\n[account:name] has requested membership for Community \\u0022[group:title] ([group:url])\\u0022. You can manage membership from here [site:login-url].\\r\\n\\r\\n\\r\\nThanks,\\r\\n\\r\\nData Catalog Team",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_og_new_content'] = entity_import('rules_config', '{ "rules_og_new_content" : {
      "LABEL" : "OG new content notification",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "og", "rules" ],
      "ON" : { "node_insert" : [] },
      "IF" : [ { "og_entity_is_group_content" : { "entity" : [ "node" ] } } ],
      "DO" : [
        { "og_get_members" : {
            "USING" : { "group_content" : [ "node" ] },
            "PROVIDE" : { "group_members" : { "group_members" : "List of group members" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "group-members" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "mail" : {
                  "to" : [ "list-item:mail" ],
                  "subject" : "New source in community",
                  "message" : "Hello [list-item:name],\\r\\n\\r\\nThere is a new source \\u0022[node:title]\\u0022 has been added to one of your subscribed communities.\\r\\n\\r\\nThanks,\\r\\n\\r\\nData Catalog Team.\\r\\n",
                  "from" : [ "" ],
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_redirect_user_profile_view_mode_after_editing'] = entity_import('rules_config', '{ "rules_redirect_user_profile_view_mode_after_editing" : {
      "LABEL" : "Redirect user profile view mode after editing",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "hybridauth", "rules" ],
      "ON" : { "user_update" : [] },
      "IF" : [
        { "NOT hybridauth_user_created_hybridauth" : { "account" : [ "account" ] } }
      ],
      "DO" : [ { "redirect" : { "url" : "user" } } ]
    }
  }');
  $items['rules_sync_es_indexes'] = entity_import('rules_config', '{ "rules_sync_es_indexes" : {
      "LABEL" : "sync es indexes",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "php", "rules" ],
      "ON" : { "node_update--source" : { "bundle" : "source" } },
      "DO" : [
        { "php_eval" : { "code" : "$search_api_index = search_api_index_load(\\u0027messages\\u0027);\\r\\n$search_api_index-\\u003Ereindex();\\r\\nsearch_api_index_items($search_api_index, -1);" } }
      ]
    }
  }');
  $items['rules_test'] = entity_import('rules_config', '{ "rules_test" : {
      "LABEL" : "test",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--source" : { "bundle" : "source" } },
      "DO" : []
    }
  }');
  $items['rules_user_login_redirect'] = entity_import('rules_config', '{ "rules_user_login_redirect" : {
      "LABEL" : "user login redirect",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "php", "rules" ],
      "ON" : { "user_login" : [] },
      "IF" : [ { "php_eval" : { "code" : "return arg(1) == \\u0027reset\\u0027;" } } ],
      "DO" : [ { "redirect" : { "url" : "[site:url]" } } ]
    }
  }');
  $items['taxonomy_deep_index_rebuild'] = entity_import('rules_config', '{ "taxonomy_deep_index_rebuild" : {
      "LABEL" : "Rebuild taxonomy deep index",
      "PLUGIN" : "action set",
      "OWNER" : "rules",
      "REQUIRES" : [ "taxonomy_deep_index" ],
      "USES VARIABLES" : { "node" : { "type" : "node", "label" : "Content" } },
      "ACTION SET" : [ { "taxonomy_deep_index_rebuild" : { "node" : [ "node" ] } } ]
    }
  }');
  return $items;
}
