
#include <DHT11.h>  // 다운로드 파일을 가져다쓰겠다. / 마우스 우클릭 정의로이동(쓸 수 있는 명령어를 볼 수 있다.)
DHT11 dht11(2); // DTH11(원본) dht11(사본으로 복사하고 이름을 바꾼다)을 데이터를 2번핀으로 쓰겠다

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

int pin_UL_TRIG = 7; // 발사 pin
int pin_UL_OUT = 8; // 도착 pin

void setup() {
   // 초음파 센서 Vcc Trig Echo Gnd
    Serial.begin(115200); // 컴푸터와 아두이노의 통신속도 band를 맞춰줘야한다.
    pinMode(pin_UL_OUT, INPUT);
    pinMode(pin_UL_TRIG, OUTPUT);
    digitalWrite(pin_UL_TRIG,0); // 초기화 트리거 0

    //LCD 모니터
    lcd.init(); // 초기화
    lcd.backlight(); // 백라이트
    lcd.setCursor(2,0); 
    lcd.print("Time:"); 
    lcd.setCursor(2,1); 
    lcd.print("Dist:"); 
    lcd.setCursor(13,0); 
    lcd.print("us"); 
    lcd.setCursor(11,1); 
    lcd.print("cm"); 

    //LED
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
}

void loop() {
    //초음파 센서
    unsigned long microseconds, distance_cm; // 변수 설정 / microseconds, distance_cm의 저장공간을 크게 만든다(unsigned long).
    // 초음파를 쏘는 부분
    digitalWrite(pin_UL_TRIG,0); // 트리거 생성 / 디지털 쓰기 0을 쓰겠어
    delayMicroseconds(2); // 2u초뒤에
    digitalWrite(pin_UL_TRIG,1); // 디지털 쓰기 1을 쓰겠어
    delayMicroseconds(10); // 10u
    digitalWrite(pin_UL_TRIG,0);

    //초음파를 받는 부분
    microseconds = pulseIn(pin_UL_OUT, HIGH); //수신시간 펄스인이란 함수를 써서 마이크로세컨즈에 넣는다 / 쏘고 받을때 까지의 시간
    distance_cm = microseconds * 17/1000; // 17/1000을 곱하니 cm거리로변환이 된다

    Serial.print("Time :");
    Serial.print(microseconds);
    Serial.print("[us], Dist :"); // u = 마이크로 s = 초 / 초음파는 거의 빛의 속도다.
    Serial.print(distance_cm);
    Serial.println("[cm]"); // Enter 시리얼 모니터 프린트의 줄을 바꿔서 출력시킨다.
    delay(500);

    //LCD 모니터
    if(microseconds>=100000) { // over 100,000us
        lcd.setCursor(7,0); 
        lcd.print(microseconds); //
    } else if (microseconds>=10000) { // 10,000us ~ 99,999us
        lcd.setCursor(7,0); 
        lcd.print(" ");
        lcd.setCursor(8,0); 
        lcd.print(microseconds);
    } else if (microseconds>=1000) { // 1,000us ~ 9,999us
        lcd.setCursor(7,0); 
        lcd.print("  ");
        lcd.setCursor(9,0); 
        lcd.print(microseconds);
    } else if (microseconds>=100) { // 100us ~ 999us
        lcd.setCursor(7,0); 
        lcd.print("  ");
        lcd.setCursor(10,0); 
        lcd.print(microseconds);
    } else if (microseconds>=10) { // 10us ~ 99us
        lcd.setCursor(7,0); 
        lcd.print("  ");
        lcd.setCursor(11,0); 
        lcd.print(microseconds);
    } else { // 0us ~ 9us
        lcd.setCursor(7,0); 
        lcd.print("  ");
        lcd.setCursor(12,0); 
        lcd.print(microseconds);
    }

    if(distance_cm>999) { // over 1,000cm
        lcd.setCursor(7,1); 
        lcd.print(distance_cm); 
    } else if (distance_cm>99) { // 100cm ~ 999cm
        lcd.setCursor(7,1); 
        lcd.print(" "); 
        lcd.setCursor(8,1); 
        lcd.print(distance_cm);
    } else if (distance_cm>9) { // 99cm ~ 10cm
        lcd.setCursor(7,1); 
        lcd.print("  "); 
        lcd.setCursor(9,1); 
        lcd.print(distance_cm);
    } else  { // 0cm ~ 9cm
        lcd.setCursor(7,1); 
        lcd.print("   "); 
        lcd.setCursor(10,1); 
        lcd.print(distance_cm);
    }

    //LED
    if(distance_cm<=10) { // 5 ~ 10cm
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
        delay(1000);
        digitalWrite(5,LOW);
        delay(1000);
    } else if(distance_cm<5) { // 0 ~ 4cm
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
        delay(100);
        digitalWrite(5,LOW);
        delay(100);
    } else // over 11cm
        digitalWrite(4,HIGH);
        digitalWrite(5,LOW);
}
