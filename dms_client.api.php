<?php

/**
 * @file
 * Hooks for dms_client module.
 */

/**
 * Alter the report before sending him back.
 *
 * @param array $report
 *   The report data after all callbacks were called.
 */
function hook_dms_client_report_alter(&$report) {
  // Alter any report result...
}

/**
 * Alter the list of modes to generate the reports.
 *
 * @param array $modes
 *   All available modes.
 */
function hook_dms_client_report_modes_alter(&$modes) {
  // Alter any mode, add a new one...
}

/**
 * Alter the list of tasks to generate the reports.
 *
 * @param array $tasks
 *   All available tasks.
 */
function hook_dms_client_report_tasks_alter(&$tasks) {
  // Alter any task, add a new one...
}

/**
 * Alter the list of available actions.
 *
 * @param array $actions
 *   All available actions.
 */
function hook_dms_client_actions_alter(&$actions) {
  // Alter any action, add a new one...
}