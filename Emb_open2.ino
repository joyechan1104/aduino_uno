#define sw1 0
#define sw2 1
#define sw3 2
#define R 3
#define G 4
#define B 5

unsigned int cnt = 0; // 카운터용 변수
char tsw1=0, tsw2=0, tsw3=0; // toggle sw
unsigned int nowNum = 50;

void RGB_Alloff() // RGB모두 끄는 함수 호출
{
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
}

void segment_Alloff() // segment모두 끄는 함수 호출
{
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void CheckKeyIn(char *psw1, char *psw2, char *psw3) // 포인터는 자료형 필수
{
  static unsigned char swRead1, swRead2, swRead3; // 스위치 3개 읽기 변수
  static unsigned int cntsw1, cntsw2, cntsw3;
  // 전원이 들어오면 0.16초만에 0xFF가 되도록 설정  
  swRead1 <<= 1;
  if(digitalRead(sw1) == 1) // 아두이노가 읽어온 스위치값이 1(안누름) 이면
    swRead1 |= 0x01; // 버튼을 안누르면 0.16초만에 0x00이 된다.
  swRead2 <<= 1;
  if(digitalRead(sw2) == 1)
    swRead2 |= 0x01;
  swRead3 <<= 1;
  if(digitalRead(sw3) == 1)
    swRead3 |= 0x01;
  
  // 스위치를 누르면 1초뒤에 동작되게 설정
  if((swRead1 & 0x01) == 0x00) // 1번째 스위치를 누르는 순간 0.16초만에 0x00이 된다.
  {
    cntsw1++;
    if(cntsw1 == 50) // 버튼을 1초누르면 1로
      *psw1 = 1; // 0으로 초기화 시키는건 호출한 함수가 끝날때 tsw3 = 0;으로 만들어야 오류 발생 없음
  }
  else
    cntsw1 = 0; // 다시 카운터를 초기화
  if((swRead2 & 0x01) == 0x00) // 2번째 스위치 
  {
    cntsw2++;
    if(cntsw2 == 50)
      *psw2 = 1; // *psw2가 가리키는 값 즉 tsw2는 1이 된다.
  }
  else
    cntsw2 = 0;
  if((swRead3 & 0x01) == 0x00) // 3번째 스위치
  {
    cntsw3++;
    if(cntsw3 == 50)
      *psw3 = 1; 
  }
  else
    cntsw3 = 0;
}

void decord(int n) // 정수를 받아서 2진수로 바꾸기
{
 digitalWrite(6, (n >> 0) & 1); // 0101 >> 0 & 1 -> 1
 digitalWrite(7, (n >> 1) & 1); // 0101 >> 1 & 1 -> 0
 digitalWrite(8, (n >> 2) & 1); // 0101 >> 2 & 1 -> 1
 digitalWrite(9, (n >> 3) & 1); // 0101 >> 3 & 1 -> 0
}

void fastBlink(int num, int ms, int swMode) // num은 출력시킬 숫자, ms는 시간, swMode는 무슨 동작인지
{
  unsigned int i = 0, j = 0;
  unsigned char fnd_value[2]; // 숫자를 디코딩 안하면 출력 불가
  fnd_value[0] = num%10; // 75%10 = 7...5
  fnd_value[1] = (num/10)%10; // 75/10 = 7, 7%10 = 0 ..7 백의자리 숫자 입력 방지
  for(i=0; i<ms/10; i++) // 한바퀴에 10ms 걸리므로 500이 들어오면 500ms/10=50회 반복
  {
    for(j=0; j<2; j++)
    {
      segment_Alloff(); // 잔상방지를 위해 off
      decord(fnd_value[j]); // 0은 1의자리 1은 십의자리 !! 디코딩 안해주면 이상한수 찍힘
      digitalWrite(11-j, 1); // 11은 1의자리, 10은 십의자리
      delay(5);
      if(swMode == 1 && digitalRead(sw1) == 1) // 스위치모드가 1이면서 sw1을 떼면
      {
        RGB_Alloff();
        segment_Alloff();
        digitalWrite(R, 1); // 적색램프 켜고
        return; //함수종료
      }
      if(swMode == 2 && digitalRead(sw2) == 1) // 스위치모드가 2이면서 sw2을 떼면
      {
        RGB_Alloff();
        segment_Alloff();
        digitalWrite(R, 1); // 적색램프 켜고
        return; //함수종료
      } 
    }
  }
}

void down99() // sw1 동작1
{
  unsigned int i = 0;
  RGB_Alloff(); // 일단 전부 off
  segment_Alloff();
  for(i=100; i>0; i--) // 99부터 출력이나 i-1필수
  {
    nowNum = (i-1); // <------- 버튼을 떼면 값을 유지 시키기 위함
    if(i%2 == 0)
      digitalWrite(B, 1); // 0.5초마다 점등 시키기
    else
      RGB_Alloff();
    fastBlink(i-1, 500, 1); // num: 99부터, ms 500, mode 동작1
    if(digitalRead(sw1) == 1) // 버튼을 뗀상태 ing면 폴문 탈출
      break;
  }
}

void up99() // sw2 동작2
{
  unsigned int i = 0;
  RGB_Alloff(); // 일단 전부 off
  segment_Alloff();
  for(i=0; i<100; i++) // 0~99
  {
    nowNum = i; // <------- 버튼을 떼면 값을 유지 시키기 위함
    if(i%2 == 0)
      digitalWrite(G, 1); // 0.5초마다 점등 시키기
    else
      RGB_Alloff();
    fastBlink(i, 500, 2); // num: 0부터, ms 500, mode 동작2
    if(digitalRead(sw2) == 1) // 버튼을 뗀상태 ing면 폴문 탈출
      break;
  }
}

void reset() // sw3 초기화동작
{ 
  unsigned int i = 0;
  RGB_Alloff(); // 일단 전부 off
  segment_Alloff();
  for(i=0; i<2; i++) // 2회반복
  {
    fastBlink(88, 1000, 3); // 88 1초 점등 모드3
    segment_Alloff(); // 1초 소등
    delay(1000);
  }
  for(i=0; i<2; i++) // 숫자50을 표시하고 G, B를 각각 1초씩 점등 2회반복
  {
    digitalWrite(G, 1);
    fastBlink(50, 1000, 3);
    RGB_Alloff();
    digitalWrite(B, 1);
    fastBlink(50, 1000, 3);
    RGB_Alloff();
  }
  digitalWrite(R, 1); // 적색 점등 유지
  nowNum = 50; // 50상태 유지
}

void startReset() // 시작시 초기화
{ 
  unsigned int i = 0;
  RGB_Alloff(); // 일단 전부 off
  segment_Alloff();
  for(i=0; i<1; i++) // !!!!!!!!!!! 버그 때매 초기화 함수 하나더 만든 원인
  {
    fastBlink(88, 1000, 3);
    segment_Alloff();
    delay(1000);
  }
  for(i=0; i<2; i++)
  {
    digitalWrite(G, 1);
    fastBlink(50, 1000, 3);
    RGB_Alloff();
    digitalWrite(B, 1);
    fastBlink(50, 1000, 3);
    RGB_Alloff();
  }
  digitalWrite(R, 1);
  nowNum = 50;
}

void setup()
{
  pinMode(0, INPUT); // sw1 풀업저항 초기1 누르면 0
  pinMode(1, INPUT); // sw2
  pinMode(2, INPUT); // sw3
  pinMode(3, OUTPUT); // R
  pinMode(4, OUTPUT); // G
  pinMode(5, OUTPUT); // B
  pinMode(6, OUTPUT); // A LSB
  pinMode(7, OUTPUT); // B
  pinMode(8, OUTPUT); // C
  pinMode(9, OUTPUT); // D MSB
  pinMode(10, OUTPUT); // 좌측세그먼트 커먼애노드 1을 넣어야 on
  pinMode(11, OUTPUT); // 우측세그먼트 
  startReset(); // 전원인가시 리셋 동작 실행
}

void loop()
{
  fastBlink(nowNum, 10, 0); // 초기에는 50, 10ms마다 실행
  cnt++; // 10ms마다 카운트업
  if(cnt%2 == 0) // 20ms마다 실행
  {
    CheckKeyIn(&tsw1, &tsw2, &tsw3);
    if(tsw1 == 1) // 1번동작
    {
      tsw1 = 0; // 실행하면 다시 0으로
      down99();
    }
    else if(nowNum == 0 && digitalRead(sw1) == 0) // nowNum이 0이면서 스위치를 누르고있는 상황이면
    {
      fastBlink(nowNum, 1000, 0); // 탈출하고 1초 누른상태 00이면 초기화 실행
      if(digitalRead(sw1) == 0) // 도중에 떼면 초기화 같은거 없음
        reset();
    } // nowNum변수는 0인 상태로 탈출

    else if(tsw2 == 1) // 2번동작
    {
      tsw2 = 0; // 실행하면 다시 0으로
      up99();
    }
    else if(nowNum == 99 && digitalRead(sw2) == 0)
    {
      fastBlink(nowNum, 1000, 0); // 탈출하고 1초 누른상태 99면 초기화 실행
      if(digitalRead(sw2) == 0)
        reset();
    }

    else if(tsw3 == 1) // 3번동작
    {
      tsw3 = 0;
      reset();
    }
  }
}