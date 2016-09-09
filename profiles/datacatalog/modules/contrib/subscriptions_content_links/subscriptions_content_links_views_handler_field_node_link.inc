<?php   
 class subscriptions_content_links_views_handler_field_node_link extends views_handler_field {
   function construct() {
     parent::construct();
     $this->additional_fields['nid'] = 'nid';
     $this->additional_fields['type'] = 'type';
     $this->additional_fields['status'] = 'status';
     $this->additional_fields['uid'] = 'uid';
   }
 
   function option_definition() {
     $options = parent::option_definition();
     $options['subscribe'] =
     $options['unsubscribe'] = array('default' => '', 'translatable' => TRUE);
 
     return $options;
   }
 
   function options_form(&$form, &$form_state) {
     parent::options_form($form, $form_state);
     $form['subscribe'] = array(
       '#type' => 'textfield',
       '#title' => t('Text to display for subscribing'),
       '#default_value' => $this->options['subscribe'],
     );
     $form['unsubscribe'] = array(
       '#type' => 'textfield',
       '#title' => t('Text to display for unsubscribing'),
       '#default_value' => $this->options['unsubscribe'],
     );
   }
 
 
   function query() {
     $this->ensure_my_table();
     $this->add_additional_fields();
   }
 
   function render($values) {
     // ensure user has access to edit this node.
     $node = new stdClass();
     $node->nid = $values->{$this->aliases['nid']};
     $node->type = $values->{$this->aliases['type']};
     $node->status = $values->{$this->aliases['status']};
     $node->uid = $values->{$this->aliases['uid']};
 
     $options = array('query' => drupal_get_destination());
 
     if (_subscriptions_content_links_subscribe_access($node)) {
       $op = 'subscribe';
     }
 
     if (_subscriptions_content_links_unsubscribe_access($node)) {
       $op = 'unsubscribe';
     }
 
     if (isset($op)) {
       $options['attributes'] = array('class' => array('subscriptions_content_links-link', 'subscriptions_content_links-' . $op));
       return l(empty($this->options[$op]) ? t($op) : $this->options[$op],
         "node/$node->nid/$op/". drupal_get_token(), $options);
     }
   }
 }