void setup() {
  // put your setup code here, to run once:
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
  Serial.begin(9600);
}

int green = 0;
int red = 0;


void loop() {
  // put your main code here, to run repeatedly:
  for(green = 1; green <= 255; green++)
  {
    analogWrite(9, green);
    analogWrite(10, (255-green));
    Serial.print("green: ");
    Serial.print(green);
    Serial.print(" red: ");
    Serial.println(255 - green);
    delay(50);
  }
  for(green = 255; green >= 0; green--)
    {
    analogWrite(9, green);
    analogWrite(10, (255-green));
    Serial.print("green: ");
    Serial.print(green);
    Serial.print(" red: ");
    Serial.println(255 - green);
    delay(50);
    }


}
