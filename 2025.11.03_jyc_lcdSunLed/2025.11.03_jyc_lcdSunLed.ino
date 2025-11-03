// C++ code
//
#include <LiquidCrystal_I2C.h> //~를 포함하다(인클루드)LCD기능을 사용하겠다.
LiquidCrystal_I2C lcd(0x27,16,2); //lcd라는 이름으로 설정(주소=adress{컴퓨터는 0x27}, 행, 열) <복사 .h를 뺀다>
int temp = 0; // temp라는 !정수형(1.1이나 3.1같은건 못들어간다)! 변수를 만든다.
  // 초기값을 0으로 한다. 메모리 X를 temp에 할당한다.
  // CPU = 계산 / 메모리 = 기억,저장
int led = 7;

void setup()
{
  lcd.init(); //lcd초기기동 이니셜라이즈(초기설정)
  lcd.backlight(); //백라이트on
  lcd.setCursor(2,0); //3행 1열 : 커서 위치 설정(가로줄 012, 세로줄 0)
  lcd.print("Hellow world");
  lcd.setCursor(2,1); //3행 2열
  lcd.print("sun:");

  //  pinMode(13,INPUT); //핀13번에 입력 INPUT 무조건 대문자
  pinMode(A0,INPUT); //핀A0에 입력
  pinMode(2,OUTPUT); //웬지 모르겠는데 넣으면 더 밝아짐1
  pinMode(3,OUTPUT); //웬지 모르겠는데 넣으면 더 밝아짐1
}

// if : 만약 ~라면
// else : if를 만족하지 않으면
// else if : 위의 if랑 조건이 묶인다 (같은조건중 하나만 선택하게 할 때 필요)

void loop()
{
  // 읽기
  //temp=digitalRead(13); // 디지털 읽기 0 or 1 (0v = 0 , 3v이상{어느정도는 동작되게 원래는 5v부터} = 1)
  temp=analogRead(A0); // 아날로그 읽기 0~1023
  led=analogRead(A0);

  //  LED제어 점등 소등
  if(led<=200){
    digitalWrite(2,HIGH); //200이하면 녹색등 점등
 }
  else{
    digitalWrite(2,LOW); //200초과 돌아오면 다시 소동
 }
  if(led>500){
    digitalWrite(3,HIGH); //500초과면 적색등 점등
 }
  else{
    digitalWrite(3,LOW); //500이하로 돌아오면 다시 소등
 }

  // LCD제어 조도에 따른 아날로그 숫자 출력
  if(temp>999){ // 템프값이 999보다 크면  //ex. 값이 230이면 실행 안함
    lcd.setCursor(6,1); // 7열 2행에 커서 (0=1번째)
    lcd.print(temp); // temp값을 출력
 }
  else if(temp>99){ //템프값이 99보다 크면 //ex. 값이 230이면 실행한다
    lcd.setCursor(6,1); 
    lcd.print(" "); // 해당칸을 " " 상태로 표시 시킨다 // "0" 으로 하면 0500으로 출력된다.
    lcd.setCursor(7,1); // 가장 앞 칸부터 출력되는 특성이 있어서 한칸 뒤로 해야된다.
    lcd.print(temp);
 }
  else if(temp>9){ //템프값이 9보다 크면  //if로 써버리면 이것도 실행해버린다. 
    lcd.setCursor(6,1); 
    lcd.print("  ");// 빈칸 2개를 출력 // "00"으로 하면 "0050" 으로 출력된다.
    lcd.setCursor(8,1); 
    lcd.print(temp);
 }
  else { // 나머지는 전부다 9 이하의 숫자
    lcd.setCursor(6,1); 
    lcd.print("   "); //빈칸 3개를 출력 // "000"으로 하면 "0005"로 출력된다.
    lcd.setCursor(9,1); 
    lcd.print(temp);
 }

 // 아래 그냥 무식하게 해본거
 //   if(analogRead(A0) < 1000)
 //    lcd.print(" ");
 //   if(analogRead(A0) < 100)
 //    lcd.print(" ");
 //   if(analogRead(A0) < 10)
 //    lcd.print(" ");
}