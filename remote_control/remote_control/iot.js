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
	US();
}
setInterval(function(){repeat();},500);

//--------------------------------------------------------//
function US(){
	var val=XHR_read('US');
	
	if(val>=20){
		document.US.src='img/ultrasonic3.png';
	}else if(val>=10){
		document.US.src='img/ultrasonic2.png';
	}else{
		document.US.src='img/ultrasonic1.png';
	}
	
	document.getElementById("US_val").value=val+"cm";
}

function LASERON(){
	XHR_write('LASERON');
	document.getElementById("LASER_BTN").value="OFF";
	document.getElementById("LASER_BTN").onclick=LASEROFF;
	document.LASER.src='img/laser_on.png';
}

function LASEROFF(){
	XHR_write('LASEROFF');
	document.getElementById("LASER_BTN").value="ON";
	document.getElementById("LASER_BTN").onclick=LASERON;
	document.LASER.src='img/laser_off.png';
}
