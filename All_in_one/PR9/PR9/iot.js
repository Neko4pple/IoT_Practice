
  1 function XHR_write(data) {
  2     var xhr = new XMLHttpRequest();
  3     xhr.open("GET","remoteC.php?" + data);
  4     xhr.send();
  5 }
  6
  7 function XHR_read(data){
  8     var xhr = new XMLHttpRequest();
  9
 10     xhr.open("GET","remoteC.php?" + data, false);
 11     xhr.send();
 12     return xhr.responseText;
 13 }
 14
 15 function repeat(){
 16     LIGHT();
 17 }
 18
 19 setInterval(function(){repeat();},500);
 20
 21 function LEDON(){
 22     XHR_write('ledOn');
 23     //document.LED.src='img/led_on.png';
 24     document.getElementById("LED_IMG_ID").src='img/led_on.png';
 25     document.getElementById("LED_ON").value="ON";
 26     document.getElementById("LED_TITLE").innerHTML="LED Turned ON";
 27     }
 28
 29 function LEDOFF(){
 30     XHR_write('ledOff');
 31     document.LED.src='img/led_off.png';
 32     document.getElementById("LED_IMG_ID").src='img/led_off.png';
 33     document.getElementById("LED_OFF").value="OFF";
 34     document.getElementById("LED_TITLE").innerHTML="LED";
 35     }
 36
 37 function LIGHT(){
 38     var value=XHR_read('light');
 39     console.log('value'+value);
 40     if(value>=1000){
 41         document.LIGHT.src='img/light_on.png';
 42     } else {
 43         document.LIGHT.src='img/light_off.png';
 44     }
 45
 46 }