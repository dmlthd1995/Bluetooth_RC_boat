#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

String txString = "";   // txString 설정 및 초기화

void setup()
{
  Serial.begin(9600); //시리얼 통신을 하기위한 통신속도설정
  mySerial.begin(9600); //Serial 통신속도 9600 설정

  pinMode(8, INPUT_PULLUP);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop()
{
  Speed_send();
  delay(100);
}

void Speed_send()
{
  txString += analogRead(A1);   //analogRead(A1)값 붙이기, x축
  txString += ',';                    //구분자 ',' 삽입
  txString += analogRead(A2);  //analogRead(A2)값 붙이기, y축
  txString += ',';                    //구분자 ',' 삽입
  txString += digitalRead(8);   //digitalRead(8)값 붙이기, push버튼
  txString += ',';                    //구분자 ',' 삽입
  txString += analogRead(A0);    //analogRead(A0)값 붙이기, 가변저항(방향타제어용)
  mySerial.println(txString);           //String을 Serial로 전송
  //Serial.println(txString);
  txString = "";                      //String 초기화
}
