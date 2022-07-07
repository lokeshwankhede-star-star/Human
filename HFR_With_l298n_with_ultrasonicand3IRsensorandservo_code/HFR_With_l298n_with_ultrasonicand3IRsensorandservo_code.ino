#include<Servo.h>
#define Echopin 3
#define Trigpin 4
#define IN2 5
#define IN4 9
#define IRSensor1 A4
#define IRSensor2 A3
#define IRSensor3 A2
Servo myservo;
int pos =0;
long duration;
int distance;
void setup() {
  myservo.attach(12);
  pinMode(IRSensor1,INPUT);
  pinMode(IRSensor2,INPUT);
  pinMode(IRSensor3,INPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(Echopin,INPUT);
  pinMode(Trigpin,OUTPUT);
  for(pos =60;pos<=100;pos++)
  {
    myservo.write(pos);
    delay(20);
  }
  for(pos =100;pos>=60;pos--)
  {
    myservo.write(pos);
    delay(20);
  }
  for(pos =0;pos<=60;pos++)
  {
    myservo.write(pos);
    delay(30);
  }
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  int a = digitalRead(IRSensor1);
  int b = digitalRead(IRSensor2);
  int c = digitalRead(IRSensor3);
  digitalWrite(Trigpin,LOW);
  delayMicroseconds(4);
  digitalWrite(Trigpin,HIGH);
  delayMicroseconds(15);
  digitalWrite(Trigpin,LOW);
  duration = pulseIn(Echopin,HIGH);
  distance = duration*(0.034/2);
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print(" ; IRSensor1 = ");
  Serial.print(a);
  Serial.print(" ; IRSensor2 = ");
  Serial.print(b);
  Serial.print(" ; IRSensor3 = ");
  Serial.print(c);  
  Serial.print("\n");
  
  if(distance<30 && b==0 && a==1 && c==1)
  {
  digitalWrite(IN2,20);
  digitalWrite(IN4,20);
  delay(100);
  }
  else if(distance<30 && b==0 && a==1 && c==0)
  {
  digitalWrite(IN2,20);
  digitalWrite(IN4,0);
  delay(100);
  }
  else if(distance<30 && b==0 && a==0 && c==1)
  {
  digitalWrite(IN2,0);
  digitalWrite(IN4,10);
  delay(100);
  }
  else if(distance>30 && b==1 && a==1 && c==1)
  {
  digitalWrite(IN2,0);
  digitalWrite(IN4,0);
  delay(100);
  }
  // put your main code here, to run repeatedly:

}
