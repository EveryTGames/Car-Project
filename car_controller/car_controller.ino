#include <AFMotor.h>
//#include <TinyMPU6050.h>
#include <Arduino.h>
#include <Wire.h>



unsigned long timer = 0;





enum State {
  WAITING_FOR_R,
  READING_NUMBER_AFTER_R,
  WAITING_FOR_A,
  READING_NUMBER_AFTER_A,
  READING_NUMBER_AFTER_M,
  READING_NUMBER_AFTER_B,
  DATA_COMPLETE
};

String rvalue;
String avalue;


int angleofinput;
bool thereism = false;
  String mvalue;
  String bvalue;

State state = WAITING_FOR_R;
int numberAfterR = 0;
int numberAfterA = 0;
int numberAfterM = 0;
int numberAfterB = 0;

const int MAX_DATA_LENGTH = 10;
char dataBuffer[MAX_DATA_LENGTH];
int dataBufferIndex = 0;




enum Control{
basic,//b
analog//l

};
Control control = basic;

int rotation_ratio = 40 ; //from 0 to 100
int current_angle = 0;
int angle_diffrence;
int m_state;//the state of the motor forward stop release

// realease 4
//forward 1
//backward 2

int RTSPEED = 70;
int RDSPEED = 70;
int LTSPEED = 70;
int LDSPEED = 70;
float motor_speed = 100;//get it from the bluetooth


bool debug = false;






AF_DCMotor RT(4); //right top
AF_DCMotor RD(3);//right down
AF_DCMotor LT(1);//left top
AF_DCMotor LD(2);// left down

char read;
void setup() {


//mpu.Initialize();



    Serial.begin(9600);

  // turn on motor
LT.setSpeed(200);
LD.setSpeed(200);
RT.setSpeed(200);
RD.setSpeed(200);
 
  LT.run(RELEASE);
  LD.run(RELEASE);
  RT.run(RELEASE);
  RD.run(RELEASE);




   

  // Calibration
  
  // Serial.println("=====================================");
  // Serial.println("Starting calibration...");
  // mpu.Calibrate();
  // Serial.println("Calibration complete!");
  // Serial.println("Offsets:");
  // Serial.print("GyroX Offset = ");
  // Serial.println(mpu.GetGyroXOffset());
  // Serial.print("GyroY Offset = ");
  // Serial.println(mpu.GetGyroYOffset());
  // Serial.print("GyroZ Offset = ");
  // Serial.println(mpu.GetGyroZOffset());




 
  }


  



//basic movements with standered input
void basic_movement()
{
  LT.setSpeed(255);
LD.setSpeed(255);
RT.setSpeed(255);
RD.setSpeed(255);
  switch (read)
  {
    case '8':
      LT.run(FORWARD);
      LD.run(FORWARD);
      RT.run(FORWARD);
      RD.run(FORWARD);
      break;
    case '2':
      LT.run(BACKWARD);
      LD.run(BACKWARD);
      RT.run(BACKWARD);
      RD.run(BACKWARD);
      break;
    case '4':
      LT.run(RELEASE);
      LD.run(RELEASE);
      RT.run(FORWARD);
      RD.run(FORWARD);
      break;
    case '6':
      LT.run(FORWARD);
      LD.run(FORWARD);
      RT.run(RELEASE);
      RD.run(RELEASE);
      break;
      default :
      LT.run(RELEASE);
      LD.run(RELEASE);
      RT.run(RELEASE);
      RD.run(RELEASE);
      break;
      
  }
}

// void add_or_decrease(int amount)
// {


// RTSPEED = (amount  * motor_speed)/100; 
// RDSPEED = (amount  * motor_speed)/100;
// LTSPEED = (amount * motor_speed)/100;
// LDSPEED = (amount * motor_speed)/100;  


// }

//used in actual_move() to make it organised
void speed(int amount, AF_DCMotor motor)
{
  if (amount >0 )
  {


     motor.setSpeed((motor_speed/100) *map(amount,0,100,0,255));
    motor.run(m_state);
   // m_state = 1;
 // return map(percentage,0,100,0,255);
  }
  else
  {
    motor.run(4);
  }

  
}
String dir; 
int error = 5;
float x;
float xRD;
float xRT;
float xLT;
float xLD;

//making  the settings for motors for the desired movement 
void move()
{

// current_angle = readcurrentangle();
 

  // if(angle <= 90 && angle >= -90 )
  // {
    
  //   m_state = 1; //forward


  // }
  // else
  // {
  //     m_state = 2; //backward
  // }
//   if(current_angle < 0)
//   current_angle = current_angle + 360;
 
//  Serial.println(current_angle);

//angle_diffrence = angleofinput - current_angle; //angle diffrence is the input for pid loop
//if(debug)
//Serial.println(angle_diffrence);
  //add the state to stop idk where
  //define the algorithm to add power or decreese power to simulate the turn
  // if(angle_diffrence >= -error && angle_diffrence <= error)
  // angle_diffrence = 0;

    xRD = 100;
  xRT = 100;
        xLD = 100;
  xLT = 100;
  if(angleofinput < 90 && angleofinput>=0)
  {
 x = map (angleofinput, 0,90,100,0);
  dir = "right";
  xRD = x;
  xRT = x;

  m_state = 1;

  }
 else if(angleofinput < 180 && angleofinput>=90)
  {
 x = map (angleofinput, 90 ,180 ,0,100);
dir = "right";
  xRD = x;
  xRT = x;
 m_state = 2;
}


else  if(angleofinput < 360 && angleofinput >=270)
{
 x = map (angleofinput, 270,360,0,100);
dir = "left";
  xLD = x;
  xLT = x;
 m_state = 1;
}
else  if(angleofinput < 270 &&angleofinput >=180)
{
 x = map (angleofinput, 180,270,100,0);
dir = "left";
  xLD = x;
  xLT = x;
 m_state = 2;

}
//add_or_decrease(x  / 100 );

}

//changing the actual motor speed
void actual_move()
{
 //while (angledeffrence != 0)

  move();
  speed(xRT,RT);
  speed(xRD,RD);
  speed(xLT,LT);
 speed(xLD,LD);
  // RT.run(m_state);
  // RD.run(m_state);
  // LT.run(m_state);
  // LD.run(m_state);
  
}
// int calltheread()
// {
//    //if (Serial.available()) {
//    // char c = Serial.read();
//     processChar(read);

   
//       if(debug)
//       Serial.println("the angle read is " + avalue.toInt());
//       return angleofinput;
    
//   //}
// }
//for reading angle of input from bluetooth
void processChar(char c) {
  
  switch (state) {
    case WAITING_FOR_R:
      if (c == 'R') {
        state = READING_NUMBER_AFTER_R;
        numberAfterR = 0;
        dataBufferIndex = 0;
      }
      break;
    case READING_NUMBER_AFTER_R:
      if (isdigit(c)) {
        numberAfterR *= 10;
        numberAfterR += c - '0';
      } else if (c == 'A') {
        state = READING_NUMBER_AFTER_A;
        dataBuffer[dataBufferIndex++] = 'A';
      } else if (dataBufferIndex >= MAX_DATA_LENGTH) {
        state = WAITING_FOR_R;
      } else {
        dataBuffer[dataBufferIndex++] = c;
      }
      break;
    case WAITING_FOR_A:
      if (c == 'A') {
        state = READING_NUMBER_AFTER_A;
        dataBufferIndex = 0;
        dataBuffer[dataBufferIndex++] = 'A';
      } else if (dataBufferIndex >= MAX_DATA_LENGTH) {
        state = WAITING_FOR_R;
      } else {
        dataBuffer[dataBufferIndex++] = c;
      }
      break;
    case READING_NUMBER_AFTER_A:
      if (isdigit(c)) {
        numberAfterA *= 10;
        numberAfterA += c - '0';
        dataBuffer[dataBufferIndex++] = c;
      } else if (dataBufferIndex >= MAX_DATA_LENGTH) {
        state = WAITING_FOR_R;
      } else {
        dataBuffer[dataBufferIndex] = '\0';
        state = DATA_COMPLETE;
      }
      break;
    case DATA_COMPLETE:
      rvalue = String(numberAfterR);
      avalue = String(&dataBuffer[1]); // Skip "A"
      int extractedNumber = avalue.toInt();
 angleofinput = extractedNumber;
      // Serial.print("Number after R: ");
      // Serial.println(numberAfterR);
      // if(read == 'p')
      //  Serial.print("Number after A: ");
      //  Serial.println(extractedNumber);
      state = WAITING_FOR_R; // Reset for next data set
      break;
  }
}




void loop() {


 // mpu.Execute();

//  Serial.println(angleofinput);
//  Serial.println("current angle ");

// Serial.println(readcurrentangle());
//  Serial.println("current angle raw");
 //Serial.println(mpu.GetAngZ());
if(debug)
{
  Serial.println(angleofinput );
  Serial.println(xRT  );
  Serial.println(xRD );
  Serial.println(xLT );
  Serial.println(xLD );

  

}

//   if (Serial.available() )
//   {
//     read =Serial.read();
//     if (read = 's')
//       state = 4; //stopr the  car
//     else
//     basic_movement();

//   }
//   if (Serial.available())
//   {
//  int input_angle = read_angle_from_blutooth();
//   move(input_angle);
//   }
// actual_move();

if(Serial.available())
{
  read = Serial.read();
if(read == 'b')
{

Serial.println("in basic control");
control = basic;
debug = false;
 Serial.println("debug is off");
}
else if(read == 'u')
{
  Serial.println("wating for data");
  while(!Serial.available())
  {}
 // char read2 = Serial.read();
  motor_speed = Serial.readString().toInt();
    Serial.println("motor speed is done and se t to ");
        Serial.println(motor_speed);

 
 
  while(!Serial.available())
  {}


}
else if(read == 'd')
{
  debug = true;
  Serial.println("debug is on");
}
else if(read == 'l' )
{
Serial.println("in analog control");

control = analog;

}
else if(read == 'p')
{
  if( control == analog)
  Serial.println(angleofinput);

//Serial.println(readcurrentangle());
}


switch(control)
{
  case basic:
basic_movement();

break;
case analog:
processChar(read);
actual_move();
break;
}

}
//if(status == 0)
//Serial.println(readcurrentangle());


}

// float readcurrentangle()
// {
//   //see the mpu code and make it work here
//  //int angle = mpu.GetAngZ();//current angle
//  if(angle < 0)
// angle = angle + 360;
//   return angle;

// }