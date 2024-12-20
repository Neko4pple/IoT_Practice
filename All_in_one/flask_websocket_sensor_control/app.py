from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import wiringpi as wp
import datetime

app = Flask(__name__)
socketio = SocketIO(app)

# GPIO 및 SPI 설정
LED_PIN = 7
SPI_CH = 0
ADC_CH_LIGHT = 0
ADC_CS = 29
SPI_SPEED = 500000
wp.wiringPiSetup()
wp.wiringPiSPISetup(SPI_CH, SPI_SPEED)
wp.pinMode(LED_PIN, 1)
wp.pinMode(ADC_CS, 1)

#=======================================================================
#				index.html
#=======================================================================
@app.route('/')
def index():
    """Serve the index HTML"""
    return render_template('index.html') # index.html 페이지를 클라이언트에게 제공

#=======================================================================
#				led action + response
#=======================================================================
@app.route("/led1/<led_state>")
def control_led_action(led_state):
    # LED 제어를 위한 엔드포인트
    print("control_led_action")
    
    if led_state == "true": 
        print("action==true")
        wp.digitalWrite(LED_PIN, 1) # LED 켜기
        ledS="ON"      
    else: 
        print("action==false")
        wp.digitalWrite(LED_PIN, 0) # LED 끄기
        ledS="OFF"
      
    now = datetime.datetime.now()
    timeString = now.strftime("%Y-%m-%d %H:%M:%S")
    templateData = {
      'time': timeString ,
      'ledS' : ledS
    }                  
    return render_template('ajax_led_response.html', **templateData) # LED 상태를 클라이언트에 응답

@app.route('/iot_with_flask.js')
def gauge():
    # JavaScript 파일을 제공하는 엔드포인트
    return render_template('iot_with_flask.js')

#=======================================================================
#				socketio ( websocket ) 
#=======================================================================
@socketio.on('measurement_start')
def on_create(data):
    # 클라이언트가 측정을 시작할 때 호출되는 WebSocket 이벤트 핸들러
    print("measurement_start")
    it = data['iterations'] # 측정 횟수
    for i in range(it):
        wp.digitalWrite(ADC_CS, 1)
        buf = bytearray(3)
        buf[0] = 0x06 | ((ADC_CH_LIGHT & 0x04)>>2)
        buf[1] = ((ADC_CH_LIGHT & 0x03)<<6)
        buf[2] = 0x00
        wp.digitalWrite(ADC_CS, 0)
        ret_len, buf = wp.wiringPiSPIDataRW(SPI_CH, bytes(buf)) # SPI 통신을 통해 조도 센서 값 읽기
        buf = bytearray(buf)
        buf[1] = 0x0F & buf[1]
        light_val = int.from_bytes(bytes(buf), byteorder='big') # 읽어온 값을 정수로 변환
        wp.digitalWrite(ADC_CS, 1)
        print("light value=", light_val) # 조도 값 출력
        socketio.sleep(.2) # 0.2초 대기
        emit('msg_from_server', {'lightVal': light_val}) # 조도 값을 클라이언트에 전송

#=======================================================================        
if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5555, debug=False) # Flask 애플리케이션 실행
