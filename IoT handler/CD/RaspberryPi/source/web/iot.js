function XHR_write(data){
        var xhr = new XMLHttpRequest();

        xhr.open("GET","remote_con.php?" + data);
        xhr.send();
}

function XHR_read(data){
        var xhr = new XMLHttpRequest();

        xhr.open("GET","remote_con.php?" + data, false);
        xhr.send();
		
	return xhr.responseText;
}

function repeat(){
	PIR(); US(); TEMP(); LIGHT(); SOUND(); HUMI(); VR(); SW(); TOUCH(); PD(); BUMP(); IRO(); MERC(); TILT(); FLAME(); REED();
}
setInterval(function(){repeat();},500);

//--------------------------------------------------------//

function LEDON(){
	XHR_write('LEDON');
	
	document.LED.src='img/led_on.png';
}

function LEDOFF(){
	XHR_write('LEDOFF');
	
	document.LED.src='img/led_off.png';
}

function DCMON(){
	XHR_write('DCMON');
	
	document.DCM.src='img/dcm_on.png';
}

function DCMOFF(){
	XHR_write('DCMOFF');
	
	document.DCM.src='img/dcm_off.png';
}

function STMON(){
	XHR_write('STMON');
	
	document.STM.src='img/stm_on.png';
	
	setTimeout(function(){
			document.STM.src='img/stm_off.png';
		},5000);
}

function PIR(){
	var val=XHR_read('PIR');
	
	if(val==1){
		document.PIR.src='img/pir_on.png';
	}else{
		document.PIR.src='img/pir_off.png';
	}
}

function US(){
	var val=XHR_read('US');
	
	if(val>=100){
		document.US.src='img/ultrasonic3.png';
	}else if(val>=50){
		document.US.src='img/ultrasonic2.png';
	}else{
		document.US.src='img/ultrasonic1.png';
	}
	
	document.getElementById("US_val").value=val+"cm";
}
	
function TEMP(){
	var val=XHR_read('TEMP');
	
	if(val!=-1){
		document.TEMPOV.style.opacity=0.5-((parseInt(val)+50)/80*0.5);
		
		document.getElementById("TEMP_val").value=val+"'C";
	}
}	

function LIGHT(){
	var val=XHR_read('LIGHT');
	
	if(val>=1000){
		document.LIGHT.src='img/light_on.png';
	}else{
		document.LIGHT.src='img/light_off.png';
	}
}

function SOUND(){
	var val=XHR_read('SOUND');
	
	document.getElementById('SOUND_val').value=val;
	document.SOUND.style.opacity=val/2048/(4/5)+0.2;
}

function HUMI(){
	var val=XHR_read('HUMI');
	
	if(val!=-1){
		document.HUMIOV.style.opacity=val/100*0.5;
		
		document.getElementById("HUMI_val").value=val+"%";
	}
}	

function VR(){
	var val=XHR_read('VR');
	
	document.getElementById('VR_val').value=val;
	document.VR.style='transform : rotate(' + (val/4095*90-90) + 'deg);';
}	

function SW(){
	var val=XHR_read('SW');
	
	if(val==0){
		document.SW.src='img/sw_on.png';
	}else{
		document.SW.src='img/sw_off.png';
	}
}

function TOUCH(){
	var val=XHR_read('TOUCH');
	
	if(val==1){
		document.TOUCH.src='img/touch_on.png';
	}else{
		document.TOUCH.src='img/touch_off.png';
	}
}

function PD(){
	var val=XHR_read('PD');
	
	if(val==1){
		document.PD.src='img/pd_on.png';
	}else{
		document.PD.src='img/pd_off.png';
	}
}

function BUMP(){
	var val=XHR_read('BUMP');
	
	if(val==1){
		document.BUMP.src='img/bump_on.png';
	}else{
		document.BUMP.src='img/bump_off.png';
	}
}

function IRO(){
	var val=XHR_read('IRO');
	
	if(val==0){
		document.IRO.src='img/iro_on.png';
	}else{
		document.IRO.src='img/iro_off.png';
	}
}

function LASERON(){
	XHR_write('LASERON');
	
	document.LASER.src='img/laser_on.png';
}

function LASEROFF(){
	XHR_write('LASEROFF');
	
	document.LASER.src='img/laser_off.png';
}

function MERC(){
	var val=XHR_read('MERC');
	
	if(val==1){
		document.MERC.src='img/mercury_on.png';
	}else{
		document.MERC.src='img/mercury_off.png';
	}
}

function TILT(){
	var val=XHR_read('TILT');
	
	if(val==1){
		document.TILT.src='img/tilt_on.png';
	}else{
		document.TILT.src='img/tilt_off.png';
	}
}

function FLAME(){
	var val=XHR_read('FLAME');
	
	if(val==1){
		document.FLAME.src='img/flame_on.png';
	}else{
		document.FLAME.src='img/flame_off.png';
	}
}

function REED(){
	var val=XHR_read('REED');
	
	if(val==1){
		document.REED.src='img/reed_on.png';
	}else{
		document.REED.src='img/reed_off.png';
	}
}

function BUZZERON(){
	XHR_write('BUZZERON');
	
	document.BUZZER.src='img/buzzer_on.png';
}

function BUZZEROFF(){
	XHR_write('BUZZEROFF');
	
	document.BUZZER.src='img/buzzer_off.png';
}