<?php
// $Id$

/**
 * Expose node content as a context condition.
 */
class context_condition_content extends context_condition {
  /**
   * Allow admins to provide a section title, section subtitle and section class.
   */
  function condition_form($context) {
    $form = parent::condition_form($context);
    unset($form['#default_value']);
    unset($form['#options']);

    $values = $this->fetch_from_context($context);

    if (module_exists('content')) {
      foreach (content_fields() as $field) {
        if ($options = content_allowed_values($field)) {
          $form[$field['field_name']] = array(
            '#title' => check_plain($field['widget']['label'] .' - '. $field['field_name']),
            '#type' => 'checkboxes',
            '#default_value' => $values['values'],
          );

          foreach ($options as $key => $value) {
            $form[$field['field_name']]['#options'][$field['field_name'] . ':' . $key] = $value;
          }
        }
      }
    }

    return $form;
  }

  /**
   * Condition form submit handler.
   */
  function condition_form_submit($values) {
    $flat = array();

    foreach($values as $field) {
      foreach($field as $value) {
        if ($value !== 0) {
          $flat[$value] = $value;
        }
      }
    }

    return $flat;
  }

  function execute($node, $op) {
    if ($this->condition_used()) {
      foreach ($this->get_contexts() as $context) {
        $values = $this->fetch_from_context($context, 'values');
        foreach (content_fields() as $field) {
          if (!empty($node->$field['field_name']) && $options = content_allowed_values($field)) {
            foreach ($node->$field['field_name'] as $item) {
              if (in_array($field['field_name'] . ':' . $item['value'], $values)) {
                $this->condition_met($context, $field['field_name'] . ':' . $item['value']);
              }
            }
          }
        }
      }
    }
  }
}
