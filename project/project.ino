
// 벨브 켠후 일정시간 후 잠금 //불꽃감지 후 일정시간 후 잠금
// 서브모터 스파크 // 절연시켜야됨
// 냄비 녹는다 어캐해// 이미 가스레인지에 온도센서 있다
// 물이 안튀면 우야노// 가스레인지 밑면에 달기?? 센서 안녹나 흠...?

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); // LCD
 
#include <DHT11.h>
DHT11 dht11(2); // 온습도 센서 pin 9

//#include <servo.h> // 서브모터

// 불꽃감지센서 pin 11
const int FLAME_SENSOR_PIN = 11; // 디지털 읽기(DO)
const int WARNING_LED_PIN = 2; // RL이랑 연결된 핀
int sensorValue = 0; // 변수

// 물수위 센서 pin A0
const int sensorPin = A0; // 아날로그 읽기(A0)

void setup() {
  // LCD
  lcd.init(); // 초기화
  lcd.backlight(); // 백라이트
  lcd.setCursor(2,0); // 1번째줄
  lcd.print("Temp:"); // Temperature 표시
  lcd.setCursor(9,0); // 1번째줄
  lcd.print("'C");

  // 불꽃감지센서 pin 11
  pinMode(FLAME_SENSOR_PIN, INPUT); // 11번을 입력으로
  pinMode(WARNING_LED_PIN, OUTPUT); // 2번을 출력으로
  Serial.begin(9600);
  Serial.println("Flame Sensor Ready!"); // 시리얼 통신

  // 물수위 센서 pin A0
  Serial.begin(9600);
  Serial.println("Water Sensor Ready!"); // 시리얼통신

  pinMode(2,OUTPUT); // RL
  pinMode(3,OUTPUT); // YL
  pinMode(4,OUTPUT); // BZ
  pinMode(5,INPUT); // PB0 비상벨 멈춤
  pinMode(6,INPUT); // PB1 가스벨브 오프
  //pinMode(8,PUT); // 서브모터
  //pinMode(9,PUT); // 온습도센서
  //pinMode(11,PUT); // 불꽃감지센서
  //pinMode(A0,PUT); // 물수위센서
}

void loop() {

  //온습도 센서 pin 9
  int temperature = 0; // 온도값 
  int humidity = 0; // 습도값
  int result = dht11.readTemperatureHumidity(temperature, humidity); //리절트(결과)
  // 시리얼 모닝터 세팅
  if (result == 0) { // 값을 읽어오면 0 , 읽지못하면 1
    Serial.print("Temperature: "); //시리얼 프린트 : 모니터에 출력하는 것
    Serial.print(temperature);
    Serial.print(" °C\tHumidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println(DHT11::getErrorString(result)); // 에러 발생시 에러코드 출력
  }
  //LCD 온도표시
  if (temperature>9) {
    lcd.setCursor(7,0);
    lcd.print(temperature);
  } else {
    lcd.setCursor(7,0);
    lcd.print(" ");
    lcd.setCursor(8,0);
    lcd.print(temperature);
  }
  // 고온경보
  if (temperature>=50) { // 고온 50도 이상
    digitalWrite(3,HIGH); // YL ON
    digitalWrite(4,HIGH); // BZ ON
    lcd.setCursor(2,1);
    lcd.print("!!! HIGH TEMP !!!"); // 고온시 LED ON 끌려면 PB0 누르기
  } else {
    lcd.setCursor(2,1);
    lcd.print("                 "); // LCD OFF
  }
  delay(1000);

  // 불꽃감지센서 pin 11
  sensorValue = digitalRead(FLAME_SENSOR_PIN); // 디지털핀의 값을 읽어 sensorValue에 저장
  if (sensorValue == LOW) { // LOW = 불꽃 점멸
    digitalWrite(WARNING_LED_PIN, HIGH); // RL ON
    Serial.println("!!! FIRE !!!"); // 불꽃점멸감지시 시리얼 모니터에 출력
    lcd.setCursor(2,1); //
    lcd.print("!!! FIRE !!!"); // 불꽃점멸감지시 LCD에 출력
  } else { // HIGH = 불꽃 소멸
    digitalWrite(WARNING_LED_PIN, LOW);  // RL OFF
    Serial.println("Safe."); // 불꽃소멸감지시 시리얼 모니터에 출력
    lcd.setCursor(2,1); //
    lcd.print("            "); // 불꽃소멸감지시 LCD OFF
  }
  delay(1000);

  // 물수위 센서 pin A0
  int waterLevel = analogRead(sensorPin); // 아날로그 읽기 (0~1023)
  Serial.print("물 수위 (0-1023): ");
  Serial.println(waterLevel); // 시리얼 출력
  if (waterLevel > 500) { // 많은 물감지시
    digitalWrite(3,HIGH); // YL ON
    digitalWrite(4,HIGH); // BZ ON
    delay(10000); // 10초 동안 ON
    digitalWrite(3,LOW); // YL OFF
    digitalWrite(4,LOW); // BZ OFF
    Serial.println("!!! Water !!!"); // 물 감지시 시리얼 모니터에 출력
    lcd.setCursor(2,1); //
    lcd.print("!!! HIGH WATER !!!"); // 물 감지시 LCD에 출력
    delay(10000);
    lcd.setCursor(2,1);
    lcd.print("                  "); // 10초후 LCD OFF
  } else if (waterLevel > 50) { // 물감지시
    digitalWrite(3,HIGH); // YL ON
    digitalWrite(4,HIGH); // BZ ON
    delay(3000); // 3초 동안 ON
    digitalWrite(3,LOW); // YL OFF
    digitalWrite(4,LOW); // BZ OFF
    Serial.println("!!! Water !!!"); // 물 감지시 시리얼 모니터에 출력
    lcd.setCursor(2,1); //
    lcd.print("!!! WATER !!!"); // 물 감지시 LCD에 출력
    delay(3000);
    lcd.setCursor(2,1);
    lcd.print("             "); // 3초후 LCD OFF
  } else {
    digitalWrite(3,LOW); // YL OFF
    digitalWrite(4,LOW); // BZ OFF
    lcd.setCursor(2,1);
    lcd.print("                  "); // LCD OFF
  }
  delay(1000);

  // LED, BZ
  // RL 불꽃감지시 켜짐
  // YL 물넘침2회/ 고온도, 이산화탄소 계속(PB0 누를때까지)
  // BZ 물넘침2회/ 고온도, 이산화탄소 계속(PB0 누를때까지)
}