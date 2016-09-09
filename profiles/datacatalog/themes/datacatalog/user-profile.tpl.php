<?php
/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */
?>

<div class="profile"<?php print $attributes; ?>>
 <?php 
   global $user;
   $user_id = $user->uid;
   $user_info = user_load(arg(1));
   $pro_desc = $user_info->field_profile_description['und'][0]['value'];
   $pro_company = $user_info->field_profile_company['und'][0]['value'];
   $pro_position = $user_info->field_profile_position['und'][0]['value'];
   if($user_info->picture->uri!=""):
     $pic_uri=$user_info->picture->uri;
   else:
     $pic_uri='public://pictures/user-default.png';
   endif;  
 ?>
  <div class="col-md-11 col-sm-9 col-xs-12 p-0">
    <div id="pro-pic" class="col-md-2 col-sm-2 col-xs-12 p-0">
      <?php echo theme('image_style', array('path' => $pic_uri, 'style_name' => 'user_pic__on__profile_view_page'));; ?>
    </div>
    <div id="details" class="col-md-10 col-sm-10 col-xs-12 p-0">
      <div id="usr-name"><?php echo $user_info->name ?></div>
      <div id="position"><?php echo $pro_position; ?></div>
      <div id="company"><?php echo $pro_company; ?></div>
      <div id="usr-email"><a href="mailto:<?php echo $user_info->mail;?>"><?php echo $user_info->mail ?></a></div>
      <div id="profile-description">
        <?php echo $pro_desc; ?>
      </div>
    </div>
  </div>
  <div class="col-md-1 col-sm-3 col-xs-12 p-0">
    <div id="profile-send-mail">
  
      <?php if ($user_id == arg(1) || in_array('administrator', $user->roles)):?>
        <a id="edit-btn" href="/user/<?php echo arg(1); ?>/edit/nojs" class="ng-lightbox ctools-use-modal pro-btn">Edit</a> 
      <?php elseif ($user_id != arg(1) || in_array('administrator', $user->roles)):?>  
        <a id="email-btn" href="/user/<?php echo $user_info->uid; ?>/contact/nojs" class="ng-lightbox ctools-use-modal pro-btn">Email</a>
      <?php endif;?>
    </div>
  </div>
</div> 
<div id="block-quicktabs-user-profile-page" class="block block-quicktabs clearfix">
  <div class="content">
    <?php
    $block = module_invoke('quicktabs', 'block_view', 'user_profile_page');
     print render($block);
    ?>
  </div>
</div>