<?php

/**
 * Form builder function for module settings.
 */
function dms_client_settings_form() {
  $form = array();

  $form['dms_client'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuration'),
    '#description' => t('DMS configuration to link this site to the main server.') . '<br/><b>TODO: ' . t('reinforce security of this module using SSL.') . '</b>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['dms_client']['dms_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret'),
    '#required' => TRUE,
    '#default_value' => variable_get('dms_client_secret', ''),
    '#description' => t('Generated token copied from the DMS server.') . '<br/><b>' . t('It will be sent as a parameter in each request.') . '</b>'
  );

  $form['dms_client']['dms_client_allowed_ips'] = array(
    '#type' => 'textarea',
    '#title' => t('Allowed IPs'),
    '#required' => TRUE,
    '#default_value' => variable_get('dms_client_allowed_ips', ''),
    '#description' => t('Only requests coming from one of these IPs will be authorized.') . '<br/><b>' . t('Enter one IP per line.') . '</b>'
  );

  $form['dms_client']['dms_client_dev_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Developer mode'),
    '#default_value' => variable_get('dms_client_dev_mode', ''),
    '#description' => t('In this mode, IP restriction is bypassed.'),
  );

  return system_settings_form($form);
}