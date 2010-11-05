<?php
// $Id$

/**
 * Expose node content as a context condition.
 */
class context_condition_content extends context_condition {
  function condition_values() {
    $values = array();
    if (module_exists('content')) {
      foreach (content_fields() as $field) {
        $field_values = array();
        $field_values[$field['field_name']] = check_plain($field['widget']['label'] .' - '. $field['field_name']);
        if ($options = content_allowed_values($field)) {
          foreach ($options as $key => $value) {
            $field_values[$field['field_name'] . ':' . $key] = check_plain("-- {$value}");
          }
          
          $values += $field_values;
        }
      }
    }
    
    return $values;
  }

  function execute($node, $op) {
    if ($this->condition_used()) {
      foreach ($this->get_contexts() as $context) {
        $values = $this->fetch_from_context($context, 'values');
        foreach (content_fields() as $field) {
          // If field exists.
          if (!empty($node->$field['field_name']) && in_array($field['field_name'], $values)) {
            $this->condition_met($context, $field['field_name']);
          }

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
