<?php
/**
 * Form builder function for module settings.
 */
function dms_client_settings_form() {
  $form['dms_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret'),
    '#default_value' => variable_get('dms_client_secret', ''),
    '#description' => t('Serial key from DMS host site'),
  );
  return system_settings_form($form);
}