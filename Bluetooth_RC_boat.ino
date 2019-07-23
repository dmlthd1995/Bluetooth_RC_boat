#include <SoftwareSerial.h>      //시리얼통신 헤더
#include <Servo.h>               //서보제어 헤더

SoftwareSerial mySerial(0, 1);   //블루투스 Tx(0), Rx(1) 핀 설정
Servo microServo;                //서보 변수 설정
int servoPin = 9;                //서보 핀 설정
int E2 = 11;                     //모터 드라이브 핀(포트) 설정
int M2 = 13;                     //모터 드라이브 핀(포트) 설정
String inString;                 //문자열 변수 설정
int conVAR;                      
int currentVar;
int previousVar;
int inString1, inString2, inString3, inString4;

void setup()

{
  microServo.attach(servoPin);
  //Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(E2, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(servoPin, OUTPUT);
}



void loop()

{
  if (Serial.available() > 0)
  {
    inString = Serial.readStringUntil('\n');

    int index1 = inString.indexOf(',');                //첫번째 ',' index1주소 설정
    int index2 = inString.indexOf(',', index1 + 1);    //두번째 ',' index2주소 설정
    int index3 = inString.indexOf(',', index2 + 1);    //세번째 ',' index3주소 설정
    int index4 = inString.length();

    inString1 = inString.substring(0, index1).toInt();          //조이스틱 x축값 추출 후 정수형으로 변환
    inString2 = inString.substring(index1 + 1, index2).toInt(); //조이스틱 y축값 추출 후 정수형으로 변환
    inString3 = inString.substring(index2 + 1, index3).toInt(); //조이스틱 푸쉬버튼 값 추출 후 정수형으로 변환
    inString4 = inString.substring(index3 + 1, index4).toInt(); //가변저항 값 추출 후 정수형으로 변환
    Serial.println(inString);

    if (inString1 >= 530)
    {
      digitalWrite(M2, HIGH);
      digitalWrite(E2, LOW);
    }
    else if (inString1 <= 510)
    {
      digitalWrite(M2, LOW);
      digitalWrite(E2, HIGH);
    }
    else
    {
      digitalWrite(M2, 0);
      analogWrite(E2, 0);
    }

    conVAR = map(inString4, 0, 1023, 0, 179);
    currentVar = constrain(conVAR, 2, 178);

    if ((currentVar > previousVar + 4) or (currentVar < previousVar - 4))
    {
      microServo.attach(servoPin);
      microServo.write(currentVar);
      delay(90);
      previousVar = currentVar;
    }
    microServo.detach();

  }

}
