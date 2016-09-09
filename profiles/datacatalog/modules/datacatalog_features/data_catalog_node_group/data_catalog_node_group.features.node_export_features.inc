<?php
/**
 * @file
 * data_catalog_node_group.features.node_export_features.inc
 */

/**
 * Implements hook_node_export_features_default().
 */
function data_catalog_node_group_node_export_features_default() {
  $node_export = array(
  'code_string' => 'array(
  (object) array(
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Twitter is an online social networking service that enables users to send and read short 140-character messages called "tweets". Registered users can read and post tweets, but those who are unregistered can only read them.\',
            \'summary\' => \'\',
            \'format\' => \'markdown\',
            \'safe_value\' => "<p>Twitter is an online social networking service that enables users to send and read short 140-character messages called \\"tweets\\". Registered users can read and post tweets, but those who are unregistered can only read them.</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'changed\' => NULL,
      \'cid\' => \'0\',
      \'comment\' => \'1\',
      \'comment_count\' => \'0\',
      \'created\' => NULL,
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'field_cmnty_tags\' => array(
        \'und\' => array(
          array(
            \'tid\' => \'52\',
          ),
          array(
            \'tid\' => \'299\',
          ),
          array(
            \'tid\' => \'59\',
          ),
        ),
      ),
      \'field_group_image\' => array(
        \'und\' => array(
          array(
            \'fid\' => \'663\',
            \'uid\' => \'3\',
            \'filename\' => \'twitterlogo_1x.png\',
            \'uri\' => \'public://twitterlogo_1x.png\',
            \'filemime\' => \'image/png\',
            \'filesize\' => \'5721\',
            \'status\' => \'1\',
            \'timestamp\' => \'1463550577\',
            \'uuid\' => \'b1ee58ce-5d67-40a5-97c8-7cac89e80767\',
            \'rdf_mapping\' => array(),
            \'alt\' => \'\',
            \'title\' => \'\',
            \'width\' => \'400\',
            \'height\' => \'300\',
          ),
        ),
      ),
      \'field_owners\' => array(
        \'und\' => array(
          array(
            \'uid\' => \'14\',
          ),
          array(
            \'uid\' => \'53\',
          ),
          array(
            \'uid\' => \'4\',
          ),
        ),
      ),
      \'files\' => array(),
      \'group_group\' => array(
        \'und\' => array(
          array(
            \'value\' => \'1\',
          ),
        ),
      ),
      \'language\' => \'und\',
      \'last_comment_name\' => NULL,
      \'last_comment_timestamp\' => NULL,
      \'last_comment_uid\' => \'3\',
      \'log\' => \'\',
      \'menu\' => NULL,
      \'name\' => \'admin\',
      \'nid\' => NULL,
      \'node_export_book\' => array(
        \'weight\' => 0,
        \'#is_root\' => FALSE,
      ),
      \'node_export_drupal_version\' => \'7\',
      \'path\' => NULL,
      \'picture\' => \'0\',
      \'promote\' => \'0\',
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'revision_timestamp\' => NULL,
      \'revision_uid\' => \'1\',
      \'status\' => \'1\',
      \'sticky\' => \'0\',
      \'subscriptions_notify\' => TRUE,
      \'title\' => \'Twitter\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'type\' => \'group\',
      \'uid\' => \'1\',
      \'uuid\' => \'07c073f8-fe48-42cb-af29-ae5ef7ee5589\',
      \'vid\' => NULL,
      \'vuuid\' => \'3e9e5502-57e9-4323-9a0f-e31ee5221e19\',
    ),
  (object) array(
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "Social network analysis (SNA) is the process of investigating social structures through the use of network and graph theories.  It characterizes networked structures in terms of nodes (individual actors, people, or things within the network) and the ties or edges (relationships or interactions) that connect them. Examples of social structures commonly visualized through social network analysis include social media networks, friendship and acquaintance networks, collaboration graphs, kinship, and disease transmission.  These networks are often visualized through sociograms in which nodes are represented as points and ties are represented as lines.\\r\\n\\r\\nSocial network analysis [SNA] is the mapping and measuring of relationships and flows between people, groups, organizations, computers, URLs, and other connected information/knowledge entities. The nodes in the network are the people and groups while the links show relationships or flows between the nodes. SNA provides both a visual and a mathematical analysis of human relationships. Management consultants use this methodology with their business clients and call it Organizational Network Analysis [ONA]. \\r\\n\\r\\nTo understand networks and their participants, we evaluate the location of actors in the network. Measuring the network location is finding the centrality of a node. These measures give us insight into the various roles and groupings in a network -- who are the connectors, mavens, leaders, bridges, isolates, where are the clusters and who is in them, who is in the core of the network, and who is on the periphery?\\r\\n\\r\\nWe look at a social network -- the \\"Kite Network\\" above -- developed by David Krackhardt, a leading researcher in social networks. Two nodes are connected if they regularly talk to each other, or interact in some way. Andre regularly interacts with Carol, but not with Ike. Therefore Andre and Carol are connected, but there is no link drawn between Andre and Ike. This network effectively shows the distinction between the three most popular individual centrality measures: Degree Centrality, Betweenness Centrality, and Closeness Centrality.\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'markdown\',
            \'safe_value\' => "<p>Social network analysis (SNA) is the process of investigating social structures through the use of network and graph theories.  It characterizes networked structures in terms of nodes (individual actors, people, or things within the network) and the ties or edges (relationships or interactions) that connect them. Examples of social structures commonly visualized through social network analysis include social media networks, friendship and acquaintance networks, collaboration graphs, kinship, and disease transmission.  These networks are often visualized through sociograms in which nodes are represented as points and ties are represented as lines.</p>\\n\\n<p>Social network analysis [SNA] is the mapping and measuring of relationships and flows between people, groups, organizations, computers, URLs, and other connected information/knowledge entities. The nodes in the network are the people and groups while the links show relationships or flows between the nodes. SNA provides both a visual and a mathematical analysis of human relationships. Management consultants use this methodology with their business clients and call it Organizational Network Analysis [ONA].</p>\\n\\n<p>To understand networks and their participants, we evaluate the location of actors in the network. Measuring the network location is finding the centrality of a node. These measures give us insight into the various roles and groupings in a network -- who are the connectors, mavens, leaders, bridges, isolates, where are the clusters and who is in them, who is in the core of the network, and who is on the periphery?</p>\\n\\n<p>We look at a social network -- the \\"Kite Network\\" above -- developed by David Krackhardt, a leading researcher in social networks. Two nodes are connected if they regularly talk to each other, or interact in some way. Andre regularly interacts with Carol, but not with Ike. Therefore Andre and Carol are connected, but there is no link drawn between Andre and Ike. This network effectively shows the distinction between the three most popular individual centrality measures: Degree Centrality, Betweenness Centrality, and Closeness Centrality.</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'changed\' => NULL,
      \'cid\' => \'0\',
      \'comment\' => \'1\',
      \'comment_count\' => \'0\',
      \'created\' => NULL,
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'field_cmnty_tags\' => array(
        \'und\' => array(
          array(
            \'tid\' => \'51\',
          ),
          array(
            \'tid\' => \'52\',
          ),
          array(
            \'tid\' => \'53\',
          ),
          array(
            \'tid\' => \'67\',
          ),
          array(
            \'tid\' => \'68\',
          ),
        ),
      ),
      \'field_group_image\' => array(
        \'und\' => array(
          array(
            \'fid\' => \'169\',
            \'uid\' => \'3\',
            \'filename\' => \'7.png\',
            \'uri\' => \'public://7.png\',
            \'filemime\' => \'image/png\',
            \'filesize\' => \'3710\',
            \'status\' => \'1\',
            \'timestamp\' => \'1453984755\',
            \'uuid\' => \'2f17a4f8-37f3-49c9-9708-26b34b6fb8f3\',
            \'rdf_mapping\' => array(),
            \'alt\' => \'\',
            \'title\' => \'\',
            \'width\' => \'69\',
            \'height\' => \'68\',
          ),
        ),
      ),
      \'field_owners\' => array(
        \'und\' => array(
          array(
            \'uid\' => \'4\',
          ),
          array(
            \'uid\' => \'14\',
          ),
          array(
            \'uid\' => \'53\',
          ),
        ),
      ),
      \'files\' => array(),
      \'group_group\' => array(
        \'und\' => array(
          array(
            \'value\' => \'1\',
          ),
        ),
      ),
      \'language\' => \'und\',
      \'last_comment_name\' => NULL,
      \'last_comment_timestamp\' => NULL,
      \'last_comment_uid\' => \'3\',
      \'log\' => \'\',
      \'menu\' => NULL,
      \'name\' => \'admin\',
      \'nid\' => NULL,
      \'node_export_book\' => array(
        \'weight\' => 0,
        \'#is_root\' => FALSE,
      ),
      \'node_export_drupal_version\' => \'7\',
      \'path\' => NULL,
      \'picture\' => \'0\',
      \'promote\' => \'0\',
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'revision_timestamp\' => NULL,
      \'revision_uid\' => \'1\',
      \'status\' => \'1\',
      \'sticky\' => \'0\',
      \'subscriptions_notify\' => TRUE,
      \'title\' => \'Social Network Analysis\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'type\' => \'group\',
      \'uid\' => \'1\',
      \'uuid\' => \'4cec466f-a331-45bc-803a-426bcc8fb555\',
      \'vid\' => NULL,
      \'vuuid\' => \'fefed26e-ad50-47cf-a3b5-81824aacb05a\',
    ),
  (object) array(
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Gnip, Inc. was a social media API aggregation company. Headquartered in Boulder, Colorado, it provided data from dozens of social media websites via a single API.\',
            \'summary\' => \'\',
            \'format\' => \'markdown\',
            \'safe_value\' => "<p>Gnip, Inc. was a social media API aggregation company. Headquartered in Boulder, Colorado, it provided data from dozens of social media websites via a single API.</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'changed\' => NULL,
      \'cid\' => \'0\',
      \'comment\' => \'1\',
      \'comment_count\' => \'0\',
      \'created\' => NULL,
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'field_cmnty_tags\' => array(
        \'und\' => array(
          array(
            \'tid\' => \'372\',
          ),
        ),
      ),
      \'field_group_image\' => array(
        \'und\' => array(
          array(
            \'fid\' => \'759\',
            \'uid\' => \'3\',
            \'filename\' => \'Gnip-Logo.jpg\',
            \'uri\' => \'public://Gnip-Logo.jpg\',
            \'filemime\' => \'image/jpeg\',
            \'filesize\' => \'38425\',
            \'status\' => \'1\',
            \'timestamp\' => \'1464086873\',
            \'uuid\' => \'ae51cbec-edf4-4a5e-92ed-3f755eccb44f\',
            \'rdf_mapping\' => array(),
            \'alt\' => \'\',
            \'title\' => \'\',
            \'width\' => \'431\',
            \'height\' => \'305\',
          ),
        ),
      ),
      \'field_owners\' => array(
        \'und\' => array(
          array(
            \'uid\' => \'53\',
          ),
          array(
            \'uid\' => \'14\',
          ),
          array(
            \'uid\' => \'4\',
          ),
        ),
      ),
      \'files\' => array(),
      \'group_group\' => array(
        \'und\' => array(
          array(
            \'value\' => \'1\',
          ),
        ),
      ),
      \'language\' => \'und\',
      \'last_comment_name\' => NULL,
      \'last_comment_timestamp\' => NULL,
      \'last_comment_uid\' => \'3\',
      \'log\' => \'\',
      \'menu\' => NULL,
      \'name\' => \'admin\',
      \'nid\' => NULL,
      \'node_export_book\' => array(
        \'weight\' => 0,
        \'#is_root\' => FALSE,
      ),
      \'node_export_drupal_version\' => \'7\',
      \'path\' => NULL,
      \'picture\' => \'0\',
      \'promote\' => \'0\',
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'revision_timestamp\' => NULL,
      \'revision_uid\' => \'1\',
      \'status\' => \'1\',
      \'sticky\' => \'0\',
      \'subscriptions_notify\' => TRUE,
      \'title\' => \'Gnip\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'type\' => \'group\',
      \'uid\' => \'1\',
      \'uuid\' => \'94f201e2-4a4e-4c65-8e98-72a41ef1403f\',
      \'vid\' => NULL,
      \'vuuid\' => \'a19e0f98-0aaf-40c8-8717-8c200a857580\',
    ),
  (object) array(
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Facebook is a corporation and an online social networking service headquartered in Menlo Park, California, in the United States.\',
            \'summary\' => \'\',
            \'format\' => \'markdown\',
            \'safe_value\' => "<p>Facebook is a corporation and an online social networking service headquartered in Menlo Park, California, in the United States.</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'changed\' => NULL,
      \'cid\' => \'0\',
      \'comment\' => \'1\',
      \'comment_count\' => \'0\',
      \'created\' => NULL,
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'field_cmnty_tags\' => array(
        \'und\' => array(
          array(
            \'tid\' => \'297\',
          ),
          array(
            \'tid\' => \'59\',
          ),
          array(
            \'tid\' => \'51\',
          ),
        ),
      ),
      \'field_group_image\' => array(
        \'und\' => array(
          array(
            \'fid\' => \'655\',
            \'uid\' => \'3\',
            \'filename\' => \'24aaffa670e634a7da9a087bfa83abe6_200x200.png\',
            \'uri\' => \'public://24aaffa670e634a7da9a087bfa83abe6_200x200.png\',
            \'filemime\' => \'image/png\',
            \'filesize\' => \'6982\',
            \'status\' => \'1\',
            \'timestamp\' => \'1463484404\',
            \'uuid\' => \'507f2c10-4c4a-4cdb-8eb9-01de89678812\',
            \'rdf_mapping\' => array(),
            \'alt\' => \'\',
            \'title\' => \'\',
            \'width\' => \'200\',
            \'height\' => \'200\',
          ),
        ),
      ),
      \'field_owners\' => array(
        \'und\' => array(
          array(
            \'uid\' => \'53\',
          ),
          array(
            \'uid\' => \'14\',
          ),
          array(
            \'uid\' => \'4\',
          ),
        ),
      ),
      \'files\' => array(),
      \'group_group\' => array(
        \'und\' => array(
          array(
            \'value\' => \'1\',
          ),
        ),
      ),
      \'language\' => \'und\',
      \'last_comment_name\' => NULL,
      \'last_comment_timestamp\' => NULL,
      \'last_comment_uid\' => \'3\',
      \'log\' => \'\',
      \'menu\' => NULL,
      \'name\' => \'admin\',
      \'nid\' => NULL,
      \'node_export_book\' => array(
        \'weight\' => 0,
        \'#is_root\' => FALSE,
      ),
      \'node_export_drupal_version\' => \'7\',
      \'path\' => NULL,
      \'picture\' => \'0\',
      \'promote\' => \'0\',
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'revision_timestamp\' => NULL,
      \'revision_uid\' => \'1\',
      \'status\' => \'1\',
      \'sticky\' => \'0\',
      \'subscriptions_notify\' => TRUE,
      \'title\' => \'Facebook\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'type\' => \'group\',
      \'uid\' => \'1\',
      \'uuid\' => \'b127f5c8-41c2-4d42-b55b-53496acd119b\',
      \'vid\' => NULL,
      \'vuuid\' => \'6866f2e5-436c-4e4e-a5cc-30a1ea87f659\',
    ),
  (object) array(
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => " The World Bank\'s Open Data initiative is intended to provide all users with access to World Bank data, according to the Open Data Terms of Use. The data catalog is a listing of available World Bank datasets, including databases, pre-formatted tables, reports, and other resources. ",
            \'summary\' => \'\',
            \'format\' => \'markdown\',
            \'safe_value\' => "<p>The World Bank\'s Open Data initiative is intended to provide all users with access to World Bank data, according to the Open Data Terms of Use. The data catalog is a listing of available World Bank datasets, including databases, pre-formatted tables, reports, and other resources.</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'changed\' => NULL,
      \'cid\' => \'0\',
      \'comment\' => \'1\',
      \'comment_count\' => \'0\',
      \'created\' => NULL,
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'field_cmnty_tags\' => array(
        \'und\' => array(
          array(
            \'tid\' => \'273\',
          ),
        ),
      ),
      \'field_group_image\' => array(
        \'und\' => array(
          array(
            \'fid\' => \'598\',
            \'uid\' => \'3\',
            \'filename\' => \'world-bank-logo.png\',
            \'uri\' => \'public://world-bank-logo.png\',
            \'filemime\' => \'image/png\',
            \'filesize\' => \'4248\',
            \'status\' => \'1\',
            \'timestamp\' => \'1463126794\',
            \'uuid\' => \'bc17b71a-7df1-41a3-a81d-0d2148c7bbe1\',
            \'rdf_mapping\' => array(),
            \'alt\' => \'\',
            \'title\' => \'\',
            \'width\' => \'69\',
            \'height\' => \'69\',
          ),
        ),
      ),
      \'field_owners\' => array(
        \'und\' => array(
          array(
            \'uid\' => \'4\',
          ),
          array(
            \'uid\' => \'14\',
          ),
          array(
            \'uid\' => \'53\',
          ),
        ),
      ),
      \'files\' => array(),
      \'group_group\' => array(
        \'und\' => array(
          array(
            \'value\' => \'1\',
          ),
        ),
      ),
      \'language\' => \'und\',
      \'last_comment_name\' => NULL,
      \'last_comment_timestamp\' => NULL,
      \'last_comment_uid\' => \'3\',
      \'log\' => \'\',
      \'menu\' => NULL,
      \'name\' => \'admin\',
      \'nid\' => NULL,
      \'node_export_book\' => array(
        \'weight\' => 0,
        \'#is_root\' => FALSE,
      ),
      \'node_export_drupal_version\' => \'7\',
      \'path\' => NULL,
      \'picture\' => \'0\',
      \'promote\' => \'0\',
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'revision_timestamp\' => NULL,
      \'revision_uid\' => \'1\',
      \'status\' => \'1\',
      \'sticky\' => \'0\',
      \'subscriptions_notify\' => TRUE,
      \'title\' => \'World Bank\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'type\' => \'group\',
      \'uid\' => \'1\',
      \'uuid\' => \'cfca81f0-aaad-4bf0-b026-39cf5d777da4\',
      \'vid\' => NULL,
      \'vuuid\' => \'370b50fc-6846-413c-984a-c50b9f7e3e77\',
    ),
  (object) array(
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'Translate data into action with the privacy-first Human Data platform.\',
            \'summary\' => \'\',
            \'format\' => \'markdown\',
            \'safe_value\' => "<p>Translate data into action with the privacy-first Human Data platform.</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'changed\' => NULL,
      \'cid\' => \'0\',
      \'comment\' => \'1\',
      \'comment_count\' => \'0\',
      \'created\' => NULL,
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'field_cmnty_tags\' => array(
        \'und\' => array(
          array(
            \'tid\' => \'339\',
          ),
        ),
      ),
      \'field_group_image\' => array(
        \'und\' => array(
          array(
            \'fid\' => \'740\',
            \'uid\' => \'3\',
            \'filename\' => \'dataswift 4.png\',
            \'uri\' => \'public://dataswift 4.png\',
            \'filemime\' => \'image/png\',
            \'filesize\' => \'4054\',
            \'status\' => \'1\',
            \'timestamp\' => \'1463999831\',
            \'uuid\' => \'98a1be88-70b0-4422-a3db-f3c65bd36793\',
            \'rdf_mapping\' => array(),
            \'alt\' => \'\',
            \'title\' => \'\',
            \'width\' => \'69\',
            \'height\' => \'69\',
          ),
        ),
      ),
      \'field_owners\' => array(
        \'und\' => array(
          array(
            \'uid\' => \'14\',
          ),
          array(
            \'uid\' => \'53\',
          ),
          array(
            \'uid\' => \'4\',
          ),
        ),
      ),
      \'files\' => array(),
      \'group_group\' => array(
        \'und\' => array(
          array(
            \'value\' => \'1\',
          ),
        ),
      ),
      \'language\' => \'und\',
      \'last_comment_name\' => NULL,
      \'last_comment_timestamp\' => NULL,
      \'last_comment_uid\' => \'3\',
      \'log\' => \'\',
      \'menu\' => NULL,
      \'name\' => \'admin\',
      \'nid\' => NULL,
      \'node_export_book\' => array(
        \'weight\' => 0,
        \'#is_root\' => FALSE,
      ),
      \'node_export_drupal_version\' => \'7\',
      \'path\' => NULL,
      \'picture\' => \'0\',
      \'promote\' => \'0\',
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'revision_timestamp\' => NULL,
      \'revision_uid\' => \'1\',
      \'status\' => \'1\',
      \'sticky\' => \'0\',
      \'subscriptions_notify\' => TRUE,
      \'title\' => \'Datasift\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'type\' => \'group\',
      \'uid\' => \'1\',
      \'uuid\' => \'e6e2cc22-22f5-4ca4-8379-dbab30510da1\',
      \'vid\' => NULL,
      \'vuuid\' => \'3b102acb-fbee-4928-9a73-89f5f18ed666\',
    ),
)',
);
  return $node_export;
}
