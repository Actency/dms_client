<?php
/**
 * Hack status (based on MD5check module)
 */
function hack_dms_client_report()
{
	if (!module_exists('md5check')) {
		return array('error' => t('The md5check module is not enabled.'));
	}
	$hack = array('code' => 1);
	// Fetches an array of all active modules and looping through them
	$modules = module_list(TRUE, FALSE);
	foreach ($modules as $moduleName) {
		// Loads the module data from database
		$module = md5check_get_values_for_module($moduleName);
		// Creates a md5 hash of the modules files
		$md5 = md5check_calculate_md5_value_for_module($module);

		// If the existing module md5 hash isn't null (as never runned before) we'll check if it has changed
		// else we'll just store the new value
		if ($module->md5check !== NULL) {
			if ($md5 != $module->md5check) {
				// The value has changed as in a files content has changed - we'll report this
				watchdog('security',
						t('Security issue. Module @moduleName has changed.', array('@moduleName' => $moduleName)),
						array(),
						WATCHDOG_CRITICAL
				);
				$hack['modules'][] = $moduleName;
				// and stores the new value so we won't report the same change again
				md5check_setMD5value($module->filename, $md5);
			}
		}
		else {
			// Existing value is null - new value will be stored
			md5check_setMD5value($module->filename, $md5);
		}
	}
	return $hack;
}
