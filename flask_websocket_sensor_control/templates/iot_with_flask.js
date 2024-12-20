function measurement_start() {
     console.log('start...');
     measurementCnt = document.getElementById("measurementCnt");
     socket.emit('measurement_start', {iterations: parseInt(measurementCnt.value)});
}
function do_led_chkbox_onclick(led, label)
{
	 var xmlhttp=new XMLHttpRequest();
    xmlhttp.onreadystatechange=function() {
 	    if (xmlhttp.readyState==4 && xmlhttp.status==200) {
		    label.innerHTML=xmlhttp.responseText;
	    }
	 }
    xmlhttp.open("GET","led1/"+led.checked, true)
	 xmlhttp.send();
}
window.onload = function() {
	var led=document.getElementById("tLed");
	var label=document.getElementById("tLedLabel");
	led.checked=false;
	do_led_chkbox_onclick(led, label);
};
var socket = io.connect('http://' + document.domain + ':' + location.port);
socket.on('connect', function() {
     console.log('Websocket connected!');
});
socket.on('msg_from_server', function(msg) {
     console.log(msg);
	  var logArea = document.getElementById("log"); 
	  if(msg==null) { 
       logArea.textContent='';
     } else { 
       logArea.textContent='light value='+msg.lightVal+'\n'+logArea.textContent;     }
});
