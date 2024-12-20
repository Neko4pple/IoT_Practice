function XHR_write(data) {
    var xhr = new XMLHttpRequest();
    xhr.open("GET","remoteC.php?" + data);
    xhr.send();
}

function XHR_read(data){
    var xhr = new XMLHttpRequest();

    xhr.open("GET","remoteC.php?" + data, false);
    xhr.send();
    return xhr.responseText;
}

function repeat(){
    LIGHT();
}

setInterval(function(){repeat();},500);

function LEDON(){
    XHR_write('ledOn');
    //document.LED.src='img/led_on.png';
    document.getElementById("LED_IMG_ID").src='img/led_on.png';
    document.getElementById("LED_ON").value="ON";
    document.getElementById("LED_OFF").value="OFF";
    document.getElementById("LED_TITLE").innerHTML="LED Turned ON";
    }
     
function LEDOFF(){
    XHR_write('ledOff');
    document.LED.src='img/led_off.png';
    document.getElementById("LED_IMG_ID").src='img/led_off.png';
    document.getElementById("LED_ON").value="ON";
    document.getElementById("LED_OFF").value="OFF";
    document.getElementById("LED_TITLE").innerHTML="LED";
    }
     
function LIGHT(){
    var val=XHR_read('light');
    console.log('value'+val);
    if(val>=1000){
        document.LIGHT.src='img/light_on.png';
    } else {
        document.LIGHT.src='img/light_off.png';
    }

}