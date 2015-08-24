<?php
/**
 * Statistics (users count, nodes count, lang, etc.)
 */
function statistics_dms_client_report() {
	// Lang
	$statistics['languages'] = language_list('enabled');
	$statistics['language_default'] = language_default();
	// Users count
	$statistics['users'] = db_select('users', 'u')->countQuery()->execute()->fetchField();
	// Nodes count
	$statistics['nodes']['published'] = db_select('node', 'n')->condition('n.status', 1)->countQuery()->execute()->fetchField();
	$statistics['nodes']['unpublished'] = db_select('node', 'n')->condition('n.status', 0)->countQuery()->execute()->fetchField();
	return $statistics;
}