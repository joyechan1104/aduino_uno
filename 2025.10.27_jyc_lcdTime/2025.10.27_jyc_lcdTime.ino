// C++ code
//
#include <LiquidCrystal_I2C.h> //~를 포함하다(인클루드)LCD기능을 사용하겠다.
// 도구 -> 라이브러리 관리 -> 툴 다운
LiquidCrystal_I2C lcd(0x27,16,2); //lcd라는 이름으로 설정(주소{PC디폴트 값 0x27}, 행, 열) <복사 .h를 뺀다>
int cnt = 0; //변수설정
int min = 0;
int sec = 0;
int hou = 0;

void setup()
{
  lcd.init(); //lcd초기기동 이니셜라이즈(초기설정)
  lcd.backlight(); //백라이트on
// 위 두줄 동작하는데 필수, 아래 두줄 동작하는데 필수는 아님
  lcd.setCursor(2,0); //2행 0열 : 커서 위치 설정(가로줄 012, 세로줄 0)
  lcd.print("Hellow world");
  lcd.setCursor(2,1); //2행 1열
  lcd.print("time:");// ":"가 6번째위치다.
}

void loop()
{
  lcd.setCursor(7,1); // 7번째로 해야 안겹침 
  lcd.print(hou); // 프린트: 값을 출력
  lcd.setCursor(10,1); 
  lcd.print(min); 
  lcd.setCursor(13,1); 
  lcd.print(sec);
  lcd.setCursor(9,1);  
  lcd.print("h"); 
  lcd.setCursor(12,1);  
  lcd.print("m");
  lcd.setCursor(15,1);  
  lcd.print("s");
  delay(1000); // 1초대기
  cnt++; //cnt 값이 1증가
  hou = cnt/3600;
  min = cnt/60; // 나누기 60 = 분
  sec = cnt%60; // %퍼센트를 써야 60후 초기화
}
