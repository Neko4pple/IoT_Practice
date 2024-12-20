  1 <?php
  2     if(isset($_GET['ledOn'])) {
  3
  4          $ret = shell_exec('/home/pi/JungYung/ledOn 2>&1');
  5
  6          echo $ret;
  7
  8     } else if(isset($_GET['ledOff'])) {
  9
 10          $ret = shell_exec('/home/pi/JungYung/ledOff 2>&1');
 11
 12          echo $ret;
 13
 14     } else if(isset($_GET['light'])) {
 15
 16          $ret = shell_exec('/home/pi/JungYung/light 2>&1');
 17
 18          echo $ret;
 19
 20     } else if(isset($_GET['aa'])) {
 21
 22          $ret = shell_exec('/home/pi/JungYung/aa 2>&1');
 23
 24
 25          echo $ret;
 26
 27     } else {
 28
 29          echo "This is remoteC.php. You entered wrong parameter.";
 30
 31     }
 32
 33 ?>