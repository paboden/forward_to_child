<?php
global $language;
$lang = ($language->language == 'en') ? '' : '_' . $language->language;
$lang_name = ($language->language == 'en') ? '' : ' - ' . $language->name;


$plugin = array(
  'single' => TRUE,  // Just do this one, it is needed.
  'title' => t('Forward to Child') . $lang_name,  // Title to show up on the pane screen.
  'description' => t('Forward to Child menu item link'), // Description to show up on the pane screen.
  'category' => 'Widgets', // Category to place this pane in.
  'edit form' => 'forward_to_child_pane_edit_form', // A function that will return the settings form for the pane.
  'render callback' => 'forward_to_child_pane_render', // A function that will return the renderable content.
  'admin info' => 'forward_to_child_pane_admin_info', // A function that will return the information displayed on the admin screen (optional).
  'defaults' => array(
    'ftc_pane_prefix' . $lang => '',
    'ftc_pane_suffix' . $lang => '',
  )
);

/**
 * Set the Forward to Child pane admin info.
 */
function forward_to_child_pane_admin_info($subtype, $conf, $contexts) {
  $block = new stdClass;
  $block->title = (isset($conf['override_title'])) ? $conf['override_title_text'] : t('Forward to Child link');
  $block->content = t('Creating a link forward to the first child of this page. Current page must be in a menu for this to be active.');

  return $block;
}

/**
 * Create the Forward to Child pane edit form.
 */
function forward_to_child_pane_edit_form($form, $form_state) {
  global $language;
  $lang = ($language->language == 'en') ? '' : '_' . $language->language;
  $lang_name = ($language->language == 'en') ? '' : ' - ' . $language->name;

  $conf = $form_state['conf'];

dpm($form_state);
  $form['ftc_pane_prefix' . $lang] = array(
    '#type' => 'textfield',
    '#title' => t('Link Prefix') . $lang_name,
    '#default_value' => $conf['ftc_pane_prefix' . $lang] ? $conf['ftc_pane_prefix' . $lang] : '',
  );
  // Suffix to display after the parent item link
  $form['ftc_pane_suffix' . $lang] = array(
    '#type' => 'textfield',
    '#title' => t('Link Suffix') . $lang_name,
    '#default_value' => $conf['ftc_pane_suffix' . $lang] ? $conf['ftc_pane_suffix' . $lang] : '',
  );

  return $form;
}

/**
 * Save the Forward to Child pane edit form.
 */
function forward_to_child_pane_edit_form_submit($form, $form_state) {
  global $language;
  $lang = ($language->language == 'en') ? '' : '_' . $language->language;

  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
  //foreach (array('ftc_pane_prefix' . $lang, 'ftc_pane_suffix' . $lang) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }

  return $form;
}

/**
 * Run-time rendering of the Forward to Child pane (content type)
 */
function forward_to_child_pane_render($subtype, $conf, $context = NULL) {
  global $language;
  $lang = ($language->language == 'en') ? '' : '_' . $language->language;
  $lang_name = ($language->language == 'en') ? '' : ' - ' . $language->name;

  $block = new stdClass();
  $block->module = 'forward_to_child';
  $block->title = '';

  $prefix = (!empty($conf['ftc_pane_prefix' . $lang])) ? $conf['ftc_pane_prefix' . $lang] . ' ' : '';
  $suffix = (!empty($conf['ftc_pane_suffix' . $lang])) ? ' ' . $conf['ftc_pane_suffix' . $lang] : '';

  $child_link_item = get_child_link_item();
  if (!empty($child_link_item)) {
    $forward_to_child_item = l($prefix . $child_link_item['link_title'] . $suffix, $child_link_item['link_path'], array($child_link_item['localized_options']));
  }
  else {
    $forward_to_child_item = NULL;
  }

  $content = array(
    '#attributes' => array('class' => array('forward-to-child-link')),
    '#markup' => $forward_to_child_item,
  );
  $block->content = $content;

  return $block;
}