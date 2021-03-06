<?php

/**
 * Creates/returns a form to configure the btp variables.
 *
 * @param array $form
 * @param array $form_state
 * @return array
 */
function forward_to_child_settings($form, &$form_state) {
  global $language;
  $lang = ($language->language == 'en') ? '' : '_' . $language->language;
  $lang_name = ($language->language == 'en') ? '' : ' - ' . $language->native;

  $number_of_ftc_blocks = variable_get('ftc_number_of_forward_to_child_blocks' . $lang, 1);
  $form['ftc_number_of_forward_to_child_blocks' . $lang] = array(
    '#type' => 'select',
    '#title' => t('Number of available blocks') . $lang_name,
    '#default_value' => $number_of_ftc_blocks,
    '#options' => drupal_map_assoc(range(1, 10)),
    '#description' => t('This will enable multiple "Forward to Child" link blocks. Each block has its own configurable settings. '),
  );

  $enable_ftc_panel_pane = variable_get('ftc_enable_panel_pane' . $lang, TRUE);
  $form['ftc_enable_panel_pane' . $lang] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable panel pane') . $lang_name,
    '#default_value' => $enable_ftc_panel_pane,
    '#description' => t('This will enable a panel pane.'),
  );

  $enable_ftc_page_variable = variable_get('ftc_enable_page_variable' . $lang, TRUE);
  $form['ftc_enable_page_variable' . $lang] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable page.tpl.php variable') . $lang_name,
    '#default_value' => $enable_ftc_page_variable,
    '#description' => t('This will enable a <em>\$forward_to_child_link</em> variable for use in your own page.tpl.php.'),
  );

  return system_settings_form($form);
}
