#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial mySerial(0, 1);
Servo microServo;
int servoPin = 9;
int E2 = 11;
int M2 = 13;
String inString;
int conVAR;
int currentVar;
int previousVar;
int inString1, inString2, inString3, inString4;

void setup()

{
  microServo.attach(servoPin);
  Serial.begin(9600); //시리얼 통신을 하기위한 통신속도설정
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

    inString1 = inString.substring(0, index1).toInt();
    inString2 = inString.substring(index1 + 1, index2).toInt();
    inString3 = inString.substring(index2 + 1, index3).toInt();
    inString4 = inString.substring(index3 + 1, index4).toInt();
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
