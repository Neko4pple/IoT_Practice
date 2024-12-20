<?php
	if(isset($_GET['US'])){
                $value = shell_exec("/home/pi/JungYung/PHP_US 2>&1");
                echo $value;
	}else if(isset($_GET['LASERON'])){
                $value = shell_exec("/home/pi/JungYung/PHP_LASERON 2>&1");
                echo $value;
	}else if(isset($_GET['LASEROFF'])){
                $value = shell_exec("/home/pi/JungYung/PHP_LASEROFF 2>&1");
                echo $value;
        }
?>
