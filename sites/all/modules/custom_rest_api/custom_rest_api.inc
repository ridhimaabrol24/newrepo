<?php

function _custom_rest_api_create($data) {
  global $user;

  unset($data->id);
  $data->uid = $user->uid;
  $data->created = time();
  $data->modified = time();

  if (!isset($data->subject)) {
    return services_error('Missing note attribute subject', 406);
  }

  if (!isset($data->note)) {
    return services_error('Missing note attribute note', 406);
  }

  custom_rest_api_write_note($data);

  return (object)array(
    'id' => <?php
// note_service.inc
/**
* Callback for creating note services.
*
* @param object $data
* @return object
*/
function _custom_rest_api_create($data) {
  global $user;

  unset($data->id);
  $data->uid = $user->uid;
  $data->created = time();
  $data->modified = time();

  if (!isset($data->subject)) {
    return services_error('Missing note attribute subject', 406);
  }

  if (!isset($data->note)) {
    return services_error('Missing note attribute note', 406);
  }

  custom_rest_api_write_note($data);

  return (object)array(
    'id' => $data->id,
    'uri' => services_service_uri(array('rest_api', $data->id)),
  );
}

// note_service.inc
/**
* Callback for updating note services.
*
* @param int $id
* @param object $data
* @return object
*/
function _custom_rest_api_update($id, $data) {
  global $user;
  $note = custom_rest_api_get_note($id);

  unset($data->created);
  $data->id = $id;
  $data->uid = $note->uid;
  $data->modified = time();

  custom_rest_api_write_note($data);
  krumo($data);
  die;
  return (object)array(
    'id' => $id,
    'uri' => services_service_uri(array('note', $id)),
  );

}
/**
* Callback for retrieving note services.
*
* @param int $id
* @return object
*/
function _custom_rest_api_retrieve($id) {
  return custom_rest_api_get_note($id);
}

/**
* Callback for deleting note services.
*
* @param int $id
* @return object
*/
function _custom_rest_api_delete($id) {
  custom_rest_api_delete_note($id);

  return (object)array(
    'id' => $id,
  );
}

function _custom_rest_api_index($page, $parameters) {
  global $user;

  $notes = array();
  $res = db_query("SELECT * FROM {note}
WHERE uid='".$user->uid."'ORDER BY modified DESC");
  foreach ($res as $note) {
    $notes[] = $note;
  }

  return $notes;
}

/**
* Access callback for the note service.
*
* @param string $op
*  The operation that's going to be performed.
* @param array $args
*  The arguments that will be passed to the callback.
* @return bool
*  Whether access is given or not.
*/

function _custom_rest_api_access($op, $args) {
  global $user;
  $access = FALSE;

  switch ($op) {
    case 'view':
      $note = custom_rest_api_get_note($args[0]);
      $access = user_access('note service view any note');
      $access = $access || $note->uid == $user->uid &&
      user_access('note service view own notes');
      break;
    case 'update':
      $note = custom_rest_api_get_note($args[0]->id);
      $access = user_access('note service edit any note');
      $access = $access || $note->uid == $user->uid &&
      user_access('note service edit own notes');
      break;
    case 'delete':
      $note = custom_rest_api_get_note($args[0]);
      $access = user_access('note service delete any note');
      $access = $access || $note->uid == $user->uid &&
      user_access('note service delete own notes');
      break;
  }
  $access = TRUE;

  return $access;
}
?>
