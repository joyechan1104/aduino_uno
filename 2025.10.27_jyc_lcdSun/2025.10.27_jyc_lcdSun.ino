// C++ code
//
#include <LiquidCrystal_I2C.h> //~를 포함하다(인클루드)LCD기능을 사용하겠다.
LiquidCrystal_I2C lcd(0x27,16,2); //lcd라는 이름으로 설정(주소{컴퓨터는 0x27}, 행, 열) <복사 .h를 뺀다>
int temp = 0; // temp: 임시

void setup()
{
  lcd.init(); //lcd초기기동 이니셜라이즈(초기설정)
  lcd.backlight(); //백라이트on
  lcd.setCursor(2,0); //2행 0열 : 커서 위치 설정(가로줄 012, 세로줄 0)
  lcd.print("Hellow world");
  lcd.setCursor(2,1); //2행 1열
  lcd.print("sun:");
  
//  pinMode(13,INPUT); //핀13번에 입력 INPUT 무조건 대문자
  pinMode(A0,INPUT); //핀A0에 입력
}

void loop()
{
//  temp=digitalRead(13); // 디지털 읽기 0 or 1
  temp=analogRead(A0); // 아날로그 읽기 0~1026
   if(analogRead(A0) < 1000)
    lcd.print(" ");
   if(analogRead(A0) < 100)
    lcd.print(" ");
   if(analogRead(A0) < 10)
    lcd.print(" ");
  lcd.setCursor(7,1); 
  lcd.print(temp); // temp값을 출력
}
