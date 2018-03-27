#include <Wire.h>
#include <Servo.h>

// Demonstrates how to connect a LEGO MINDSTORMS to an Arduino and Send commands.
// A4 – SDA
// A5 – SCL
// See our website, www.dexterindustries.com/howto for more information on the physical setup.
int flag = 0;

Servo cam_servo;
int servo_pin = 9;
int increment = 5;
int servo_pos = 0;

byte currentCommand;
byte pan_left = 0x01;
byte pan_right = 0x02;


void setup()
{
  Wire.begin(0x0A); // Start I2C on Address 0x0A
  Wire.onReceive(receiveI2C); // Receive Event from Master
  cam_servo.attach(servo_pin);
  Serial.begin(9600); // We will spit it back out on the serial line.
}

// When data is received, this function is called.
void receiveI2C(int bytesIn)
{
  byte garbage = Wire.read();
  currentCommand = Wire.read();
  if(currentCommand == pan_left){
    move_servo(-increment);
    delay(50);
  }
  else if(currentCommand == pan_right){
    move_servo(increment);
    delay(50);
  }
  garbage = Wire.read();
  garbage = Wire.read();
}

void move_servo(int increment){
  Serial.println("move_servo");
  //cam_servo.write(servo_pos + servo_increment);// tell servo to go to position in variable 'pos'
  if(increment > 0 && servo_pos - increment <= 180){
    servo_pos = servo_pos + increment;
    cam_servo.write(servo_pos);
    delay(15);
  }
  else if(increment < 0 && servo_pos + increment >= 0){
    servo_pos = servo_pos + increment;
    cam_servo.write(servo_pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void loop()
{
  delay(50);
  Serial.println(servo_pos);
}

