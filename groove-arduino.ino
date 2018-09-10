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
  Serial.begin(38400);
  Serial.println("Enter AT commands:");
  BT.begin(38400);  // HC-05 default speed in AT command more
}

void loop()
{
  calcDis();

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
  //Serial.print("distance = ");
  //  Serial.print("E");
  //  Serial.print(distance);//送出距離
  //Serial.print(" velocity = ");
  //  Serial.print(",");
//  Serial.print(velocity);//送出速度
  //  Serial.print(" acceleration = ");
  //  Serial.print(",");
  if(acceleration < 100000){
    
    Serial.print(acceleration);//送出加速度
  Serial.println("");
  delay(intervaltime);
  }
}





//  while (BT.available()) //如果有收到資料
//  {
//    startRecieve = true;
//    val = BT.read(); //每次接收一個字元
//    recieveData += val; //字元組成字串
//    BT.write(byte(val)); //把每次收到的字元轉成byte封包傳至手機端
//    delay(200);  //每次傳輸間隔，如果太短會造成資料遺失或亂碼
//  }
//
//  if (startRecieve)
//  {
//    startRecieve = false;
//    Serial.println(recieveData); //呈現收到字串
//    recieveData = "";
//  }
//
//  BT.write(Serial.read());
//  delay(300);
