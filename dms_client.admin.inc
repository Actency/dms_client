<?php
/**
 * Form builder function for module settings.
 */
function dms_client_settings_form() {
	dms_client_load_includes();
	
	$form['dms_client_fieldset'] = array(
	  '#type' => 'fieldset', 
	  '#title' => t('DMS Client'), 
	  '#weight' => 5, 
	  '#collapsible' => TRUE, 
	  '#collapsed' => FALSE,
	);
	
	$form['dms_client']['dms_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret'),
    '#default_value' => variable_get('dms_client_secret', ''),
    '#description' => t('Serial key from DMS host site'),
  );
	
	//appel a toutes les fonctions implementant le hook_dms_client_admin_form()
	foreach(dms_client_get_plugins() as $plugin) {
		if (($callback = $plugin.'_dms_client_admin_form') && function_exists($callback)) {
			
			$form[$plugin.'_fieldset'] = array(
					'#type' => 'fieldset',
					'#title' => t('DMS Client'),
					'#weight' => 5,
					'#collapsible' => TRUE,
					'#collapsed' => FALSE,
			);
			
			$form[$plugin.'_fieldset'][]=call_user_func($callback);
		}
	}
	
	return system_settings_form($form);  
}