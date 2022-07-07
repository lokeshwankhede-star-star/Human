#include<Servo.h>
#include<AFMotor.h>
#define echopin A1 // echo pin
#define trigpin A2 // Trigger pin
#define R2 A4
#define L1 A3
#define R1 A5

AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);

Servo myservo;
 
int pos =0;
long time;
void setup() {
Serial.begin(9600);
myservo.attach(10);

for(pos = 60; pos <= 100; pos += 1){
myservo.write(pos);
delay(15);
}
 
for(pos = 100; pos >= 60; pos-= 1) {
myservo.write(pos);
delay(15);
}

for(pos = 0; pos<=60; pos += 1) {
myservo.write(pos);
delay(15);
}
pinMode(R2, INPUT);
pinMode(L1, INPUT);
pinMode(R1, INPUT);
//pinMode(LEFT, INPUT);

pinMode(trigpin, OUTPUT);
pinMode(echopin, INPUT);

}
long read_cm(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  time = pulseIn (echopin, HIGH);
  return time / 29 / 2;
}


void loop(){
unsigned int distance = read_cm();

int R1_Value = digitalRead(R1);
int L1_Value = digitalRead(L1);
int R2_Value = digitalRead(R2);
//int Left_Value  = digitalRead(LEFT);

Serial.print("R1= ");
Serial.print(R1_Value);
Serial.print(" L1= ");
Serial.print(L1_Value);
Serial.print(" R2= ");
Serial.print(R2_Value);
Serial.print(" D= ");
Serial.println(distance);

if(distance<60 && (R2_Value == 0 || L1_Value == 0))
{
Motor1.setSpeed(100); //turn right
Motor1.run(BACKWARD);
Motor2.setSpeed(100);
Motor2.run(BACKWARD);
Motor3.setSpeed(0);
Motor3.run(RELEASE);
Motor4.setSpeed(0);
Motor4.run(RELEASE);  
  }
else if(distance<60 && (R1_Value == 0 || L1_Value == 0))
{
Motor1.setSpeed(0); //turn left
Motor1.run(RELEASE);
Motor2.setSpeed(0);
Motor2.run(RELEASE);
Motor3.setSpeed(100);
Motor3.run(BACKWARD);
Motor4.setSpeed(100);
Motor4.run(BACKWARD); 
  }
else if(distance<60)
{
Motor1.setSpeed(80); // forward
Motor1.run(BACKWARD);
Motor2.setSpeed(80);
Motor2.run(BACKWARD);
Motor3.setSpeed(80);
Motor3.run(BACKWARD);
Motor4.setSpeed(80);
Motor4.run(BACKWARD);
  }
else if(distance>60)
{
Motor1.setSpeed(0);  // stop
Motor1.run(RELEASE);
Motor2.setSpeed(0);
Motor2.run(RELEASE);
Motor3.setSpeed(0);
Motor3.run(RELEASE);
Motor4.setSpeed(0);
Motor4.run(RELEASE);  
}
delay(50);
}
