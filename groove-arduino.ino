#include <SoftwareSerial.h>

#define trigPin 5 //超音波腳位要確認 Trig
#define echoPin 6 //超音波腳位要確認 Echo
SoftwareSerial BT(10, 11); // RX | TX
String recieveData = "";
char val;
bool startRecieve = false;
int x0 = 0; //一開始的位置
int v0 = 0; //初速
float temp = 30.0; //溫度
float c = (331.5 + 0.6 * temp) / 10000; //單位是每微秒幾公分
float intervaltime = 100; //每幾毫秒測量一次
float duration, distance, velocity, acceleration;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BT.begin(9600);  // HC-05 default speed in AT command more
}

void loop()
{
  //  calcDis();
  bluetooth();
}

void bluetooth()
{
  if (Serial.available())
  {
    String inputString = "";
    while (Serial.available()) {
      delay(5);
      char c = (char)Serial.read();
      inputString += (c == '\r' || c == '\n') ? ' ' : c;
    }
    BT.println(inputString);
  }

  if (BT.available())
  {
    String inputString = "";
    while (BT.available()) {
      delay(5);
      char c = (char)BT.read();
      inputString += (c == '\r' || c == '\n') ? ' ' : c;
    }
    Serial.println(inputString);
  }
}

void calcDis()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);//超音波來回經過的時間，單位是微秒
  distance = (duration / 2) * c; //單位是公分
  velocity = (distance - x0) / (intervaltime / 1000); //每秒速度
  acceleration = (velocity - v0) / (intervaltime / 1000); //每秒加速度

  x0 = distance;
  v0 = velocity;
  //  Serial.print("distance = ");
  //  Serial.print("E");
  //  Serial.print(distance);//送出距離
  //  Serial.print(" velocity = ");
  //  Serial.print(",");
  //  Serial.print(velocity);//送出速度
  //  Serial.print(" acceleration = ");
  //  Serial.print(",");
  Serial.print(acceleration);//送出加速度
  Serial.println("");
  delay(intervaltime);
}
