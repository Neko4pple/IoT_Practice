function measurement_start() {
    // 'Start' 버튼 클릭 시 호출되는 함수
    // 측정 횟수를 서버로 전송함
    console.log('start...'); // 시작 로그 출력
    measurementCnt = document.getElementById("measurementCnt"); // 입력된 측정 횟수 값을 가져옴
    socket.emit('measurement_start', {iterations: parseInt(measurementCnt.value)}); // WebSocket을 통해 서버로 'measurement_start' 이벤트와 횟수 데이터 전송
}

function do_led_chkbox_onclick(led, label) {
	//led: 체크박스 요소 (<input type="checkbox" id="tLed">) 자체를 인자로 받습니다.(28번줄)
	//label: 라벨 요소 (<div id="tLedLabel">) 자체를 인자로 받습니다. (29번줄)
    // LED 제어 체크박스 클릭 시 호출되는 함수
    // 체크박스 상태에 따라 LED를 켜거나 끔
    var xmlhttp = new XMLHttpRequest(); // 새로운 XMLHttpRequest 객체 생성
    xmlhttp.onreadystatechange = function() {
        // 서버 응답 처리
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            label.innerHTML = xmlhttp.responseText; // 응답 텍스트를 라벨에 표시
        }
    }
    xmlhttp.open("GET", "led1/" + led.checked, true); // 체크박스 상태를 서버에 GET 요청으로 전송
    xmlhttp.send(); // 요청 전송
}

window.onload = function() {
    // 페이지 로드 시 실행되는 함수
    // 초기 LED 상태를 서버에서 받아옴
    var led = document.getElementById("tLed"); // 체크박스 요소 가져옴
    var label = document.getElementById("tLedLabel"); // 라벨 요소 가져옴
    led.checked = false; // 체크박스 초기화
    do_led_chkbox_onclick(led, label); // 초기 상태 업데이트
};

var socket = io.connect('http://' + document.domain + ':' + location.port);
// WebSocket 연결 설정
socket.on('connect', function() {
    // WebSocket 연결 시 호출되는 함수
    console.log('Websocket connected!'); // 연결 로그 출력
});

socket.on('msg_from_server', function(msg) {
    // 서버로부터 메시지를 받을 때 호출되는 함수
    console.log(msg); // 메시지 로그 출력
    var logArea = document.getElementById("log"); // 로그 표시 영역 가져옴
    if (msg == null) {
        logArea.textContent = ''; // 메시지가 null일 경우 로그 영역 초기화
    } else {
        logArea.textContent = 'light value=' + msg.lightVal + '\n' + logArea.textContent; 
        // 새로운 메시지를 로그 영역에 추가
    }
});
