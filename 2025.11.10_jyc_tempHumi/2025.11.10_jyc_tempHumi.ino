
#include <DHT11.h>  // 다운로드 파일을 가져다쓰겠다. / 마우스 우클릭 정의로이동(쓸 수 있는 명령어를 볼 수 있다.)
DHT11 dht11(2); // DTH11(원본) dht11(사본으로 복사하고 이름을 바꾼다)을 데이터를 2번핀으로 쓰겠다

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
    //연결 방법: [왼쪽(data입력)] [중간(+)] [오른쪽 GND]
    Serial.begin(9600); // pinMord(2); 이 기본적으로 포함되어 있다.

    lcd.init(); // 초기화
    lcd.backlight(); // 백라이트

    lcd.setCursor(2,0); 
    lcd.print("Temp:"); //Temperature
    lcd.setCursor(10,0); 
    lcd.print("C"); // 기온 기호

    lcd.setCursor(2,1); 
    lcd.print("Humi:"); //Humidity
    lcd.setCursor(10,1);
    lcd.print("%"); // 습도 퍼센트

    pinMode(4,OUTPUT); // 연결 방법: [아두이노 4번 핀] ↔ [저항] ↔ [LED 긴 다리(+)] ↔ [LED 짧은 다리(-)] ↔ [아두이노 GND]
    pinMode(5,OUTPUT);
}

void loop() {
    int temperature = 0; // 온도값 
    int humidity = 0; // 습도값
    // 메모리 할당(초기화) 통을 비워서 0으로 만들어 버린다

    int result = dht11.readTemperatureHumidity(temperature, humidity); //리절트(결과)

    // 불러옴
    if (result == 0) { // 값을 읽어오면 0 , 읽지못하면 1
        Serial.print("Temperature: "); //시리얼 프린트 : 모니터에 출력하는 것
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    } else {
        Serial.println(DHT11::getErrorString(result)); // 에러 발생시 에러코드 출력
    }

    // lcd 온도
    if (temperature<=9) { // 온도 9이하의 숫자면 앞칸 비워두기
        lcd.setCursor(8,0);
        lcd.print(" ");
        lcd.setCursor(9,0);
        lcd.print(temperature);   
    } else {
        lcd.setCursor(8,0);
        lcd.print(temperature);
    }

    // lcd습도
    if (humidity<=9) { // 습도 9이하의 숫자면 앞칸 비워두기
        lcd.setCursor(8,1); // 9보다 작으면 8번째 비워두고
        lcd.print(" ");
        lcd.setCursor(9,1); // 9번째에 출력
        lcd.print(humidity);   
    } else {
        lcd.setCursor(8,1); // 10이상이면 8번째 출력
        lcd.print(humidity);
    }

    // 습도 높을 때 녹색 led 점등
    if (humidity>35) {
        digitalWrite(4,HIGH);
        Serial.println("over_humidity_35%"); // 프로그램이 동작하는지 안하는지는 Serial.println로 확인 가능하다
    } else {
        digitalWrite(4,LOW);
    }

    // 습도 낮을 때 적색 led 깜빡이기
    if (humidity<=25) {
        digitalWrite(5,HIGH);
        delay(1000);
        digitalWrite(5,LOW);
        delay(1000);
    } else {
        digitalWrite(5,LOW);
    }
}
