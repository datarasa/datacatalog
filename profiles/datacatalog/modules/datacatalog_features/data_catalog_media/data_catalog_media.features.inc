<?php
/**
 * @file
 * data_catalog_media.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function data_catalog_media_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function data_catalog_media_image_default_styles() {
  $styles = array();

  // Exported image style: activity_stream_user_image.
  $styles['activity_stream_user_image'] = array(
    'label' => 'Activity Stream user image',
    'effects' => array(
      8 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 72,
          'height' => 72,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: community_image_listing_page.
  $styles['community_image_listing_page'] = array(
    'label' => 'Community image community page',
    'effects' => array(
      6 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 70,
          'height' => 70,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: community_thumb.
  $styles['community_thumb'] = array(
    'label' => 'community_thumb',
    'effects' => array(
      11 => array(
        'name' => 'image_resize',
        'data' => array(
          'width' => 69,
          'height' => 68,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: experts_image_listing_page.
  $styles['experts_image_listing_page'] = array(
    'label' => 'Experts image listing page',
    'effects' => array(
      7 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 155,
          'height' => 155,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: experts_image_right_side_bar.
  $styles['experts_image_right_side_bar'] = array(
    'label' => 'Experts image right side bar',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 34,
          'height' => 34,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: group_author_dp_community_page.
  $styles['group_author_dp_community_page'] = array(
    'label' => 'Community author dp community page',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 50,
          'height' => 50,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: large.
  $styles['large'] = array(
    'label' => 'Large (480x480)',
    'effects' => array(
      0 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 480,
          'height' => 480,
          'upscale' => 0,
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: medium.
  $styles['medium'] = array(
    'label' => 'Medium (220x220)',
    'effects' => array(
      0 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 220,
          'height' => 220,
          'upscale' => 1,
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: thumbnail.
  $styles['thumbnail'] = array(
    'label' => 'Thumbnail (100x100)',
    'effects' => array(
      0 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 100,
          'height' => 100,
          'upscale' => 1,
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: top_right_user_prof_pic.
  $styles['top_right_user_prof_pic'] = array(
    'label' => 'top_right_user_prof_pic',
    'effects' => array(
      12 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 33,
          'height' => 33,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: user_pic__on__profile_view_page.
  $styles['user_pic__on__profile_view_page'] = array(
    'label' => 'user pic. on  profile view page',
    'effects' => array(
      5 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 98,
          'height' => 98,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
