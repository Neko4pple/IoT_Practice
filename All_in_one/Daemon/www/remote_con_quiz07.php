<?php
	if(isset($_GET['lightLog'])){
              $value = shell_exec("/home/pi/JungYung/php_lightLog 2>&1");
              echo $value;
       } else if(isset($_GET['soundLog'])) {
              $value = shell_exec("/home/pi/JungYung/php_soundLog 2>&1");
              echo $value;
       } else if(isset($_GET['touchAlert'])){
              $value = shell_exec("/home/pi/JungYung/php_touchAlert 2>&1");
              echo $value;
	} else {
              echo "No Such Argument!!! by Neko4pp1e.";
       }
?>
