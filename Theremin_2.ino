#define Buzzer 9
#define TRIG 12
#define ECHO 13

float duration;
float dist;
int freq;

void setup() 
{
  pinMode(Buzzer, OUTPUT); // 9번 핀을 출력으로 소리를 나게 한다.
  pinMode(TRIG, OUTPUT); // 12번 핀을 출력으로 초음파를 발사하게 한다.
  pinMode(ECHO, INPUT); // 13번 핀을 입력으로 초음파를 읽어들이게 한다.
  Serial.begin(9600); // 직렬통신을 하겠다.
}

void loop() 
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10); // 10마이크로초 동안 전압이 들어오는데 이건 초음파를 발사하기 위한 준비과정이다.
  digitalWrite(TRIG, LOW); // 전압이 끊기면 Falingedge가 트리거가 되어서 바로 초음파를 팡 하고 쏜다!
  // 초음파를 쏘는 순간부터 ECHO는 HIGH상태가 되며
  duration = pulseIn(ECHO, HIGH); // 초음파가 돌아오면 ECHO는 LOW상태가 된다. 따라서 duration에는 ECHO가 HIGH인 시간이 대입된다. (왕복이므로 /2를 하면 편도시간)

  dist = duration * 0.0343/2; // 속도 == (거리*2)/시간 (초음파가 나가는 시간이랑 들어오는 시간이 있으므로 2를 곱한다.)  // 거리 == (속도*시간)/2

  dist = constrain(dist, 10, 240);
  Serial.print("dist: ");
  Serial.print(dist); // dist값을 시리얼 모니터에 출력한다.
  Serial.println("cm"); // 알파벳 LN ln (소문자) == c언어의 \n

  freq = map(dist, 10, 240, 880, 220); // 주파수를 매핑 한다. 10cm면 880Hz로, 240cm면 220Hz로 해라.
  Serial.print("Freq: ");
  Serial.print(freq);
  Serial.println("Hz");

  Serial.println("");  // lnln을 쓸 수 없으니 하나더 추가해서 띄우기

  tone(9, freq); // 9번핀에 프리퀀시값을 출력하겠다.
  delay(100);
  noTone(9); // 9번핀의 출력을 그만두겠다.
  delay(200);
}