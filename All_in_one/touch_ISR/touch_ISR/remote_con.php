<?php
	if(isset($_GET['touchAlert'])){
                $value = shell_exec("/home/pi/JungYung/php_touchAlert 2>&1");
                echo $value;
	} else {
                echo "No Such Argument!!! by ksaehwa.";
          }
?>
