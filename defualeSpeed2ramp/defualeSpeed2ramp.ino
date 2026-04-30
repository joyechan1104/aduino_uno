int i = 0;
int j = 0;
int brightness1 = 0;
int brightness2 = 0;
int FadeAmout1 = 0;
int FadeAmout2 = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  brightness1 = 0;
  brightness2 = 0;
  FadeAmout1 = 0;
  FadeAmout2 = 0;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(9, brightness1);
  analogWrite(10, brightness2);
  brightness1 += FadeAmout1; // 페이드아모우트가 5인 상태를 계속 유지하면서 루프한다. / -5가 대입되면 루프마다 -5
  brightness2 += FadeAmout2;
  Serial.print("green: ");
  Serial.print(brightness1);
  Serial.print(" red: ");
  Serial.println(brightness2);
  delay(100);
  
  if(brightness1 <= 0) // 그럼 브라이트네스1가 0보다 커지니 if문에 안걸린다
  {
    FadeAmout1 = 5; // 5가 한번대입된다
  }
  
  if(brightness2 <= 0)
  {
    FadeAmout2 = 2;
  }
  
  if(brightness1 >= 255) // 브라이트네스1이 255보다 같거나 커져버리면 
  {
    FadeAmout1 = -5; // -5가 대입된다
  }
  
  if(brightness2 >= 255)
  {
    FadeAmout2 = -2;
  }

}
