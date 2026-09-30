// 임베디드 기능사 공개1번 7447디코더 커먼애노드
#define R 3
#define G 4
#define B 5
int i = 0; // 동작1, 동작2 for문용
int f = 0; // fastBlink for문용
int p = 0; // 일시정지 함수용

// RGB 모두 소등용 함수
void RGB_Alloff()
{
  digitalWrite(R, 0); 
  digitalWrite(G, 0);
  digitalWrite(B, 0);
}

// 세그먼트 2개 전부 불 점등
void segmentHIGH()
{
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
}

// 세그먼트 2개 전부 불 소등
void segmentLOW()
{
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

// 세그먼트 숫자 출력용 함수 
void segment(int n) // 이것만으로는 일단 0~15까지만 출력가능
{                             // 좌측세그먼트용 8이 올때         // 우측세그먼트용 6이 올때
  digitalWrite(6,(n>>0) & 1); // 1000 >> 0 -> 1000 & 1 == 0 // 0100 >> 0 -> 0100 & 1 == 0
  digitalWrite(7,(n>>1) & 1); // 1000 >> 1 -> 0100 & 1 == 0 // 0100 >> 1 -> 0010 & 1 == 0
  digitalWrite(8,(n>>2) & 1); // 1000 >> 2 -> 0010 & 1 == 0 // 0100 >> 2 -> 0001 & 1 == 1
  digitalWrite(9,(n>>3) & 1); // 1000 >> 3 -> 0001 & 1 == 1 // 0100 >> 3 -> 0000 & 1 == 0
}

// 좌우세그먼트 빠른 속도로 번갈아가며 쏴주는 용도
void fastBlink(int num, int ms) // 이 함수로 ~초 동안 출력 시키므로 딜레이를 쓸필요가 없다.
{
  int tens = num / 10; // 86 / 10 -> 8
  int ones = num % 10; // 86 % 10 -> 6

  for(f=0; f<(ms/4); f++) // 좌측2m초 우측2m초씩 쏴줄거라서 500초가 변수로 오면 125번만 반복하면 된다.
  {
    // 세그먼트에서 10의 자리를 출력시키기
    segment(tens); // 1000이 가면..
    digitalWrite(10, HIGH); // 좌측세그먼트 점등
    digitalWrite(11, LOW); // 우측세그먼트 소등
    delay(2); // 0.002초동안만
    digitalWrite(10, LOW); // 고스팅? 방지를 위해 소등
    // 세그먼트에서 01의 자리를 출력시키기
    segment(ones); // 0100이 가면..
    digitalWrite(10, LOW); // 좌측세그먼트 소등
    digitalWrite(11, HIGH); // 우측세그먼트 점등
    delay(2); // 0.002초동안만
    digitalWrite(11, LOW); // 고스팅? 방지를 위해 소등
  }
}

// 초기화 동작: 전원을 최초로 인가할때, 동작1 또는 동작2를 수행중 sw3(아두이노2번)을 누르면 수행
void reset() // 초기화 동작 수행중에는 모든 스위치를 무시해야함
{
  RGB_Alloff(); // 일단 전부 소등
  // 초기화동작 - 1번
  for(i=0; i<2; i++)
  {
    segment(8); // 88을 1초 점등
    segmentHIGH();
    delay(1000);
    segmentLOW(); // 둘다 1초 소등
    delay(1000);
  }
  // 초기화동작 - 2번
  digitalWrite(R, 1); // 적색 1초 점등
  delay(1000);
  RGB_Alloff(); 
  digitalWrite(G, 1); // 녹색 1초 점등
  delay(1000);
  RGB_Alloff(); 
  digitalWrite(B, 1); // 청색 1초 점등
  delay(1000);
  RGB_Alloff(); 
  delay(1000);
  // 초기화동작 - 3번
  digitalWrite(R, 1); // 적색 점등 유지
  // reste 초기화 상태 유지ing... 이상태에서 버튼 누르면 다른거 동작? 근데 탈출하니 상관없나?
}

//동작 1 99진 업카운터: 초기화 상태 or 동작 2 수행중 sw1(아두이노 0번)을 누르면 즉시동작
void up99()
{
  RGB_Alloff();
  // 동작 1-1
  segment(8); // 88을 2초간 점등한다.
  segmentHIGH();
  delay(2000);
  segmentLOW(); // 세그먼트 소등
  digitalWrite(G, 1); // 녹색 0.5초 점등
  delay(500);
  RGB_Alloff(); 
  digitalWrite(R, 1); // 적색 0.5초 점등
  delay(500);
  RGB_Alloff(); 
  // 동작 1-2 | 동작 1-3
  for(i=0; i<100; i++)
  {
    if(i%2 == 0) // i를 2로 나눈 나머지가 0이면 (짝수라면)
      digitalWrite(B, 1); // 청색 점등
    else
      digitalWrite(B, 0); // 청색 소등
    fastBlink(i, 500); // 딜레이 넣으면 오류동작함
    if(digitalRead(0) == 0) // sw1(아두이노 0번)을 누르면 일시정지
      pasue(i);
    if(digitalRead(1) == 0) // sw2(아두이노 1번)을 누르면 탈출후 동작2
      break; // 탈출 후 void loop로
    if(digitalRead(2) == 0) // sw3(아두이노 2번)을 누르면 탈출후 초기화
      break; // 탈출 후 void loop로
  }
}

// 동작 2 99진 다운카운터: 초기화 상태 or 동작 1 수행중 sw2(아두이노 1번)을 누르면 즉시동작
void down99()
{
  RGB_Alloff();
  // 동작 2-1
  segment(8); // 88을 2초간 점등한다.
  segmentHIGH();
  delay(2000);
  segmentLOW(); // 세그먼트 소등
  digitalWrite(B, 1); // 청색 0.5초 점등
  delay(500);
  RGB_Alloff(); 
  digitalWrite(R, 1); // 적색 0.5초 점등
  delay(500);
  RGB_Alloff(); 
  // 동작 2-2 | 동작 2-3
  for(i=99; i>=0; i--)
  {
    if(i%2 != 0) // i를 2로 나눈 나머지가 0이 아니라면 (홀수라면)
      digitalWrite(G, 1); // 녹색 점등
    else
      digitalWrite(G, 0); // 녹색 소등
    fastBlink(i, 500); // 딜레이 넣으면 오류동작함
    if(digitalRead(1) == 0) // sw2(아두이노 1번)을 누르면 일시정지
      pasue(i);
    if(digitalRead(0) == 0) // sw1(아두이노 0번)을 누르면 탈출후 동작1
      break; // 탈출 후 void loop로
    if(digitalRead(2) == 0) // sw3(아두이노 2번)을 누르면 탈출후 초기화
      break; // 탈출 후 void loop로
  }
}

// 동작3: 동작1을 수행중 sw1을 또는 동작2 수행중 sw2를 누르면 일시정지 로직이 동작, 끝내면 그대로 계속
void pasue(int pn) // 동작1이나 동작2의 i값을 가져와서 현재화면에 출력 되게함
{
  for(p=0; p<2; p++)
  {
    fastBlink(pn, 2000);
    segmentHIGH();
    segmentLOW();
    delay(2000);
  }
  for(p=0; p<2; p++)
  {
    digitalWrite(R, 1);
    delay(2000);
    RGB_Alloff();
    delay(2000);
  }
  // 일시정지 탈출
}

void setup()
{
  pinMode(0, INPUT); // 풀업저항 안누르면 1 누르면 0 스위치1
  pinMode(1, INPUT); // 스위치2
  pinMode(2, INPUT); // 스위치3
  pinMode(3, OUTPUT); // RGB 동작용 3은 레드
  pinMode(4, OUTPUT); // 4는 그린
  pinMode(5, OUTPUT); // 5는 블루
  pinMode(6, OUTPUT); // 7447 디코더 동작용 입력1 LSB 0001
  pinMode(7, OUTPUT); // 입력2 0010
  pinMode(8, OUTPUT); // 입력3 0100
  pinMode(9, OUTPUT); // 입력4 MSB 1000
  pinMode(10, OUTPUT); // 좌측 세그먼트 !커먼애노드는 1로 해야 동작
  pinMode(11, OUTPUT); // 우측 세그먼트

  reset(); // 전원인가시 리셋 동작을 할것
}

// 즉시 동작이 안됨 why? 딜레이 시간때문에 버튼을 눌러서 0.5초 사이의 시간이면 동작불가
void loop()
{
  if(digitalRead(2) == 0) // 초기화 동작
    reset();
  if(digitalRead(0) == 0) // 동작1
    up99();
  if(digitalRead(1) == 0) // 동작2
    down99();
}
