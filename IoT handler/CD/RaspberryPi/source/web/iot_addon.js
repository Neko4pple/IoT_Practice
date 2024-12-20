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
	IRT(); LIMIT(); KNOCK(); DUST(); SM(); GAS(); THERM(); AT();
}
setInterval(function(){repeat();},500);

//--------------------------------------------------------//

function REDON(){
	XHR_write('REDON');
	
	document.RED.src='img/RGB_r.png';
}

function REDOFF(){
	XHR_write('REDOFF');
	
	document.RED.src='img/RGB_off.png';
}

function GREENON(){
	XHR_write('GREENON');
	
	document.GREEN.src='img/RGB_g.png';
}

function GREENOFF(){
	XHR_write('GREENOFF');
	
	document.GREEN.src='img/RGB_off.png';
}

function BLUEON(){
	XHR_write('BLUEON');
	
	document.BLUE.src='img/RGB_b.png';
}

function BLUEOFF(){
	XHR_write('BLUEOFF');

	document.BLUE.src='img/RGB_off.png';
}

function RELAYON(){
        XHR_write('RELAYON');

        document.RELAY.src='img/relay_on.png';
}

function RELAYOFF(){
        XHR_write('RELAYOFF');

        document.RELAY.src='img/relay_off.png';
}

function IRT(){
	var val=XHR_read('IRT');
	
	if(val==1){
		document.IRT.src='img/irt_on.png';
	}else{
		document.IRT.src='img/irt_off.png';
	}
}

function LIMIT(){
	var val=XHR_read('LIMIT');

	if(val==0){
		document.LIMIT.src='img/limit_on.png';
	}else{
		document.LIMIT.src='img/limit_off.png';
	}
}
	
function KNOCK(){
	var val=XHR_read('KNOCK');

	if(val==0){
		document.KNOCK.src='img/knock_on.png';
	}else{
		document.KNOCK.src='img/knock_off.png';
	}
}

function DUST(){
	var val=XHR_read('DUST');

	document.DUST.style.opacity=(parseInt(val)/4095)*0.8+0.2;
	document.getElementById("DUST_val").value=val;
}	

function SM(){
        var val=XHR_read('SM');

        document.SM.style.opacity=(parseInt(val)/4095)*0.8+0.2;
        document.getElementById("SM_val").value=val;
}

function GAS(){
        var val=XHR_read('GAS');

        document.GAS.style.opacity=(parseInt(val)/4095)*0.8+0.2;
        document.getElementById("GAS_val").value=val;
}

function THERM(){
        var val=XHR_read('THERM');

        document.THERM.style.opacity=((parseFloat(val)+30)/80)*0.8+0.2;
        document.getElementById("THERM_val").value=val;
}

function AT(){
        var val=XHR_read('AT');

        document.AT.style.opacity=((parseFloat(val)+30)/80)*0.8+0.2;
        document.getElementById("AT_val").value=val;
}


