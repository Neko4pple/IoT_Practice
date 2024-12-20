<?php

    if(isset($_GET['ledOn'])) {

         $ret = shell_exec('/home/pi/JungYung/ledOn 2>&1');

         echo $ret;

    } else if(isset($_GET['ledOff'])) {

         $ret = shell_exec('/home/pi/JungYung/ledOff 2>&1');

         echo $ret;

    } else if(isset($_GET['light'])) {

         $ret = shell_exec('/home/pi/JungYung/light 2>&1');

         echo $ret;

    } else if(isset($_GET['aa'])) {

         $ret = shell_exec('/home/pi/JungYung/aa 2>&1');

         echo $ret;

    } else {

         echo "This is remoteC.php. You entered wrong parameter.";

    }   

?>