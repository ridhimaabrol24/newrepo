<?php

  print render($my_view_html);

if (isset($node_content)) {
  print render($node_content['field_image1']);
  print render($node_content['field_event_date']);
}
?>
