// 팅커케드 연습용 4511디코더 커먼캐소드
int i = 0; // 폴문 사용
int t = 0; // time
int p = 0; // 일시정지 로직 

void segment(int n) // 99진 카운터 출력용 segment(n) 괄호안에 숫자를 넣어서 호출히시키면 된다.
{
  digitalWrite(6, (n >> 0) & 1); // 0101 >> 0 -> 0101 & 0001 == 1
  digitalWrite(7, (n >> 1) & 1); // 0101 >> 1 -> 0010 & 0001 == 0
  digitalWrite(8, (n >> 2) & 1); // 0101 >> 2 -> 0001 & 0001 == 1
  digitalWrite(9, (n >> 3) & 1); // 0101 >> 3 -> 0000 & 0001 == 0
} // 0101이 되므로 세그먼트에 출력 시킬 수 있다.

void digit2(int num, int ms) // num는 뜨울 숫자, ms는 유지할 시간을 가져온다.
{
  int tens = num / 10; // 10의 자리 ex. 25를 10으로 나누면 2, 나머지5는 버려진다.
  int ones = num % 10; // 1의 자리 ex. 15를 10으로 나누면 나머지가 5

  // 1바퀴에 약 4ms소요 따라서(시간/4)만큼 반복 500이 변수로 오면 125번만 반복하면 0.5초가 된다.
  for (t = 0; t < (ms / 4); t++) // 좌측 0.002초 켜고끄기, 우측 0.002초 켜고끄기를 반복하니 사람의 눈을 속일 수 있다.
  {
    // 10의 자리 켜기
    segment(tens); // 변수를 세팅해둔상태로
    digitalWrite(10, 0); // 좌측 세그먼트 켜기!!!
    digitalWrite(11, 1); // 우측 세그먼트 끄기
    delay(2);
    digitalWrite(10, 1); // 고스팅? 방지때문에 좌측세그먼트도 잠깐 끄기
    // 1의 자리 켜기
    segment(ones);
    digitalWrite(10, 1); // 좌측 세그먼트 끄기
    digitalWrite(11, 0); // 우측 세그먼트 켜기!!!
    delay(2);
    digitalWrite(11, 1); // 고스팅? 방지때문에 우측세그먼트도 잠깐 끄기
  }
}

void reset() // 초기화동작 함수
{
  // 세그먼트 88 00 2번 반복
  for (i = 0; i < 2; i++) // 2번반복
  {
    segment(8); // 88점등
    delay(1000);
    segment(0); // 00 점등
    delay(1000);
  }

  // RGB 점등
  digitalWrite(3, 1); // 적색1초
  delay(1000);
  digitalWrite(3, 0);
  digitalWrite(4, 1); // 녹색1초
  delay(1000);
  digitalWrite(4, 0);
  digitalWrite(5, 1); // 청색1초
  delay(1000);
  digitalWrite(5, 0); // 모두소등1초
  delay(1000);
  digitalWrite(3, 1); // 레드 점등 유지
} // 리셋여기까지

void up99() // 동작 1
{
  // 동작 1-1
  digitalWrite(3, 0); // 일단 RGB전부 소등
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  segment(8); // 88 점등
  delay(2000);
  digitalWrite(4, 1); // 그린 0.5초 점등
  delay(500);
  digitalWrite(4, 0);
  digitalWrite(3, 1); // 그린끄고 레드 0.5초 점등
  delay(500);
  digitalWrite(3, 0); // 레드도 끄기
  delay(500);

  // 동작 1-2
  for (i = 0; i < 100; i++)
  {
    // segment(i); // 수정
    digit2(i, 500); // 디지트2 함수를 호출 i가 num에 대입, 0.5초동안 양쪽에 번갈아 가면서 쏴라
    // 위함수에 이미 딜레이가 포함되어 있으므로 delay를 쓸 필요가 없다.
    if (i % 2 == 0) // 짝수일때만 동작시키기
    {
      digitalWrite(5, 1); // 청색 점등
    }
    else
    {
      digitalWrite(5, 0); // 청색 소등
    }
    // 일시정지로직 동작3을 수행
    if(digitalRead(0) == 0) // 1번 동작중에 1번 버튼을 누르면???
    {
      pause(i); // i에 등록된 숫자를 보낸다
    }
  }
  digitalWrite(3, 0); // 폴문 탈출할때도 RGB전부 소등
  digitalWrite(4, 0);
  digitalWrite(5, 0);
}

void down99() // 동작 2
{
  // 동작 2-1
  digitalWrite(3, 0); // 일단 RGB전부 소등
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  segment(8);
  delay(2000);
  digitalWrite(5, 1); // 청색 0.5초 점등
  delay(500);
  digitalWrite(5, 0);
  digitalWrite(3, 1); // 청색끄고 적색 0.5초 점등
  delay(500);
  digitalWrite(3, 0); // 레드도 끄기

  // 동작 2-2
  for (i = 99; i >= 0; i--)
  {
    digit2(i, 500);
    if (i % 2 != 0)
    {
      digitalWrite(4, 1); // 초록켜기
    }
    else
    {
      digitalWrite(4, 0); // 초록끄기
    }
    // 일시정지 로직 동작3을 수행
    if(digitalRead(1) == 0) // 2번 동작중에 2번 버튼을 누르면???
    {
      pause(i); // i에 등록된 숫자를 보낸다
    }
  }
  digitalWrite(3, 0); // 폴문 탈출할때도 RGB전부 소등
  digitalWrite(4, 0);
  digitalWrite(5, 0);
}

void pause(int i) // 동작3 일시정지 
{
  digitalWrite(3, 0); // 일단 RGB전부 소등
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  // 동작1중에 sw1을 누리면 일시정지후 동작3를 수행
  // 동작2중에 sw2를 누르면 일시정지후 동작3를 수행
  for(p=0; p<2; p++) // 현재숫자 2초점등 2초 소등 2회반복 !!!! 현재숫자 어떻게 넣지? !!!!!
  {
    digit2(i, 2000); // 디짙트2로 현재 숫자를 2초동안 화면에 표시한다.
    digitalWrite(10, 0);
    digitalWrite(11, 0);
    digitalWrite(10, 1); // 소등하고 2초대기
    digitalWrite(11, 1);
    delay(2000);
  }
  for(p=0; p<2; p++) // RGB모듈 적색2초점등 2초소등 반복
  {
    digitalWrite(3, 1);
    delay(2000);
    digitalWrite(3, 0);
    delay(2000);
  }
}

void setup()
{
  pinMode(0, INPUT); // 풀업저항 안누르면 1 누르면 0 스위치1
  pinMode(1, INPUT); // 스위치2
  pinMode(2, INPUT); // 스위치3
  pinMode(3, OUTPUT); // RGB 동작용 3은 레드
  pinMode(4, OUTPUT); // 4는 그린
  pinMode(5, OUTPUT); // 5는 블루
  pinMode(6, OUTPUT); // 4511 디코더 동작용 입력1 LSB 0001
  pinMode(7, OUTPUT); // 입력2 0010
  pinMode(8, OUTPUT); // 입력3 0100
  pinMode(9, OUTPUT); // 입력4 MSB 1000
  pinMode(10, OUTPUT); // 세그먼트 동작용 커먼 캐소드는 0으로 만들어야 불들어옴 좌측 세그먼트
  pinMode(11, OUTPUT); // 우측 세그먼트
  digitalWrite(10, 0); // 캐소드공통은 0일때 동작
  digitalWrite(11, 0);
  reset(); // 전원을 최초로 인가 할 때 동작을 수행
}

void loop()
{
  // 딜레이 때문에 눌러도 즉시 동작하지를 않음 해결방법은 뭐지??
  if (digitalRead(2) == 0) // 스위치3을 누르면(0이되면) 전원인가시!! 즉시수행!!
  {
    reset(); // 초기화 함수 호출
  }
  if (digitalRead(0) == 0) // 스위치1을 누르면 즉시!! 수행
  {
    up99(); // 동작1 함수 호출
  }
  if (digitalRead(1) == 0) // 스위치2를 누르면 즉시!! 수행
  {
    down99(); // 동작2 함수 호출
  }
}
