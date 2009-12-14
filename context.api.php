<?php
// $Id$

/**
 * @file
 * Hooks provided by Context.
 */

/**
 * CTools plugin API hook for Context. Note that a proper entry in
 * hook_ctools_plugin_api() must exist for this hook to be called.
 */
function hook_context_plugins() {
  $plugins = array();
  $plugins['foo_context_condition_bar'] = array(
    'handler' => array(
      'path' => drupal_get_path('module', 'foo') .'/plugins',
      'file' => 'foo_context_condition_bar.inc',
      'class' => 'foo_context_condition_bar',
      'parent' => 'context_condition',
    ),
  );
  $plugins['foo_context_reaction_baz'] = array(
    'handler' => array(
      'path' => drupal_get_path('module', 'foo') .'/plugins',
      'file' => 'foo_context_reaction_baz.inc',
      'class' => 'foo_context_reaction_baz',
      'parent' => 'context_reaction',
    ),
  );
  return $plugins;
}

/**
 * Registry hook for conditions.
 *
 * Each entry associates a condition type with the CTools plugin to be used as
 * its condition class.
 */
function hook_context_conditions() {
  return array(
    'bar' => array(
      'title' => t('Name of condition "bar"'),
      'plugin' => 'foo_context_condition_bar',
    ),
  );
}

/**
 * Alter the condition registry.
 *
 * Allows modules to alter the condition registry. Default condition plugins
 * can be replaced by custom ones declared in hook_context_plugins().
 *
 * @param $registry
 *   The condition registry, passed by reference.
 */
function hook_context_conditions_alter(&$registry) {
  if (isset($registry['bar'])) {
    $registry['bar']['plugin'] = 'custom_context_condition_bar';
  }
}

/**
 * Registry hook for conditions & reactions.
 *
 * Each entry associates a condition or reaction with the CTools plugin to be
 * used as its plugin class.
 */
function hook_context_registry() {
  return array(
    'conditions' => array(
      'bar' => array(
        'title' => t('Name of condition "bar"'),
        'plugin' => 'foo_context_condition_bar',
      ),
    ),
    'reactions' => array(
      'baz' => array(
        'title' => t('Name of reaction "baz"'),
        'plugin' => 'foo_context_reaction_baz',
      ),
    ),
  );
}

/**
 * Alter the registry.
 *
 * Allows modules to alter the registry. Default plugins can be replaced by
 * custom ones declared in hook_context_plugins().
 *
 * @param $registry
 *   The reaction registry, passed by reference.
 */
function hook_context_reactions_alter(&$registry) {
  if (isset($registry['reactions']['baz'])) {
    $registry['reactions']['baz']['plugin'] = 'custom_context_reaction_baz';
  }
}
