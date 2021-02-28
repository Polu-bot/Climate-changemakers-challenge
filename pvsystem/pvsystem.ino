#include <Servo.h> 
int topLeftLight = 0;     
int topRightLight = 0;
int bottomLeftLight = 0;
int bottomRightLight = 0;
int LeftLight = 0;
int RightLight = 0;
int TopLight = 0;
int BottomLight = 0;
Servo servo_9;
Servo servo_10;

void setup()
{
  pinMode(A0, INPUT);   
  pinMode(A1, INPUT);   
  pinMode(A2, INPUT);   
  pinMode(A3, INPUT);   
  pinMode(A4, INPUT);   
  pinMode(A5, INPUT);   
  servo_9.attach(9);    
  servo_10.attach(10);  
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,t,voltage,current,power");
}

void loop()
{   float voltage = analogRead(A6)*5*5.0/1023;    
    float current = analogRead(A7)*5.0/1023;     
    float power = voltage*current;
    Serial.print("DATA,TIME,"); // PLX-DAQ command
    Serial.print(voltage);    //send the voltage to serial port
    Serial.print(",");
    Serial.print(current);    //send the current to serial port
    Serial.print(",");
    Serial.println(power);  //send the power to serial port

    topLeftLight = map(analogRead(A2),50,980,0,100);
    topRightLight = map(analogRead(A3),200,990,0,100);
    bottomLeftLight = map(analogRead(A4),170,970,0,100);
    bottomRightLight = map(analogRead(A5),250,1000,0,100);
    //Calculate the average light conditions
    TopLight = ((topRightLight + topLeftLight) / 2);
    BottomLight = ((bottomRightLight + bottomLeftLight) / 2);
    LeftLight = ((topLeftLight + bottomLeftLight) / 2);
    RightLight = ((topRightLight + bottomRightLight) / 2);
    //Rotate the servos if needed
    if (abs((RightLight - LeftLight)) > 4) {    //Change position only if light difference is bigger then 4%
      if (RightLight < LeftLight) {
        if (servo_9.read() < 180) {
          servo_9.write((servo_9.read() + 1));
        }
      }
      if (RightLight > LeftLight) {
        if (servo_9.read() > 0) {
          servo_9.write((servo_9.read() - 1));
        }
      }
    }
    if (abs((TopLight - BottomLight)) > 4) {  //Change position only if light difference is bigger then 4%
      if (TopLight < BottomLight) {
        if (servo_10.read() < 180) {
          servo_10.write((servo_10.read() - 1));
        }
      }
      if (TopLight > BottomLight) {
        if (servo_10.read() > 0) {
          servo_10.write((servo_10.read() + 1));
        }
      }
    }
    delay(1000);
}
