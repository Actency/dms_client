<?php
/**
 * Features status (see /sites/all/modules/contrib/features/features.admin.inc)
 */
function features_dms_client_report() {
	
	if (!module_exists('features')) {
		return array('error' => t('The features module is not enabled.'));
	}

	$features = features_get_features();

	if ( empty($features) ) {
		return array('nofeatures' => t('No Features were found.'));
	}

	$form = array('#features' => $features);
	return $form;
}
