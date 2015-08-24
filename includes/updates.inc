<?php
/**
 * Updates status (see /modules/update/update.manager.inc)
 *
 * @param $check
 *   If true, only returns a boolean whether there are system status errors.
 */
function updates_dms_client_report($check = FALSE) {
	$available = update_get_available(TRUE);
	if (empty($available)) {
		return array('error' => t('There was a problem getting update information. Try again later.'));
	}

	// This will be a nested array. The first key is the kind of project, which
	// can be either 'enabled', 'disabled', 'manual' (projects which require
	// manual updates, such as core). Then, each subarray is an array of
	// projects of that type, indexed by project short name, and containing an
	// array of data for cells in that project's row in the appropriate table.
	$projects = array();

	module_load_include('inc', 'update', 'update.compare');
	$project_data = update_calculate_project_data($available);

	foreach ($project_data as $name => $project) {
		// Filter out projects which are up to date already.
		if ($project['status'] == UPDATE_CURRENT) {
			continue;
		}
		// The project name to display can vary based on the info we have.
		if (!empty($project['title'])) {
			if (!empty($project['link'])) {
				$project_name = l($project['title'], $project['link']);
			}
			else {
				$project_name = check_plain($project['title']);
			}
		}
		elseif (!empty($project['info']['name'])) {
			$project_name = check_plain($project['info']['name']);
		}
		else {
			$project_name = check_plain($name);
		}
		if ($project['project_type'] == 'theme' || $project['project_type'] == 'theme-disabled') {
			$project_name .= ' ' . t('(Theme)');
		}

		if (empty($project['recommended'])) {
			// If we don't know what to recommend they upgrade to, we should skip
			// the project entirely.
			continue;
		}

		$recommended_release = $project['releases'][$project['recommended']];
		$recommended_version = $recommended_release['version'] . ' ' . l(t('(Release notes)'), $recommended_release['release_link'], array('attributes' => array('title' => t('Release notes for @project_title', array('@project_title' => $project['title'])))));
		if ($recommended_release['version_major'] != $project['existing_major']) {
			$recommended_version .= '<div title="Major upgrade warning" class="update-major-version-warning">' . t('This update is a major version update which means that it may not be backwards compatible with your currently running version.  It is recommended that you read the release notes and proceed at your own risk.') . '</div>';
		}

		// Create an entry for this project.
		$entry = array(
				'title' => $project_name,
				'installed_version' => $project['existing_version'],
				'recommended_version' => $recommended_version,
		);

		switch ($project['status']) {
			case UPDATE_NOT_SECURE:
			case UPDATE_REVOKED:
				$entry['title'] .= ' ' . t('(Security update)');
				$type = 'security';
				break;

			case UPDATE_NOT_SUPPORTED:
				$type = 'unsupported';
				$entry['title'] .= ' ' . t('(Unsupported)');
				break;

			case UPDATE_UNKNOWN:
			case UPDATE_NOT_FETCHED:
			case UPDATE_NOT_CHECKED:
			case UPDATE_NOT_CURRENT:
				$type = 'recommended';
				break;

			default:
				// Jump out of the switch and onto the next project in foreach.
				continue 2;
		}
		if ($name != 'drupal') {
			$projects[$type][$name] = $entry;
		} else {
			$entry['type'] = $type;
			$projects[$name] = $entry;
		}
	}

	if (empty($projects)) {
		return array('uptodate' => t('All of your projects are up to date.'));
	}
	return $projects;
}
