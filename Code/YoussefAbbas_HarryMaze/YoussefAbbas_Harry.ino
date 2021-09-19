/*
Author : Youssef Abbas
Date   : 19/9/2021
About  : Harry in Maze (harrys path accordings to IRs)
MC     : Arduino NANO
*/

#define IR_UP            4   
#define IR_RIGHT         5 
#define IR_LEFT          6
#define LEFT_MOTOR_UP    7
#define LEFT_MOTOR_DOWN  8
#define RIGHT_MOTOR_UP   9
#define RIGHT_MOTOR_DOWN 10

bool    up;    //take reading of IR_UP
bool right;    //take reading of IR_RIGHT
bool  left;    //take reading of IR_LEFT

void setup() 
{
//define IR pins
  pinMode(IR_UP   ,INPUT);
  pinMode(IR_RIGHT,INPUT);
  pinMode(IR_LEFT ,INPUT);

//define MOTOR pins
  pinMode(LEFT_MOTOR_UP    , OUTPUT);
  pinMode(LEFT_MOTOR_DOWN  , OUTPUT);
  pinMode(RIGHT_MOTOR_UP   , OUTPUT);
  pinMode(RIGHT_MOTOR_DOWN , OUTPUT);
  
}

void loop() 
{
  readSensors();

  if (up == HIGH )
  {
    //Always bias to go forward than other directions
    moveForward();  
  }
  else if (up == LOW)
  {
    if(right == HIGH)
    {
      //Always bias to go right than left 
      rotate90right();  
    }
    else if (left == HIGH)
    {
      rotate90left();  
    }
    else
    {
      //if end up in no way up,right and left , then we back
      moveBackward();  
    }
  }
  

}

void readSensors()
{
  //take reading form IRs and put that in globals
  up    = digitalRead(IR_UP);
  right = digitalRead(IR_RIGHT);
  left  = digitalRead(IR_LEFT);
}
void moveForward()
{
  digitalWrite(LEFT_MOTOR_UP   ,HIGH);
  digitalWrite(LEFT_MOTOR_DOWN ,HIGH);
  digitalWrite(RIGHT_MOTOR_UP  ,HIGH);
  digitalWrite(RIGHT_MOTOR_DOWN,HIGH);
}
void moveBackward()
{
  //first rotate 180 degree then keep going forward
  rotate90right();
  rotate90right();
  digitalWrite(LEFT_MOTOR_UP   ,HIGH);
  digitalWrite(LEFT_MOTOR_DOWN ,HIGH);
  digitalWrite(RIGHT_MOTOR_UP  ,HIGH);
  digitalWrite(RIGHT_MOTOR_DOWN,HIGH);  
}
void rotate90right()
{
  
  digitalWrite(LEFT_MOTOR_UP   ,HIGH);
  digitalWrite(LEFT_MOTOR_DOWN ,HIGH);
  digitalWrite(RIGHT_MOTOR_UP  ,LOW );
  digitalWrite(RIGHT_MOTOR_DOWN,LOW );  
}
void rotate90left()
{
  
  digitalWrite(LEFT_MOTOR_UP   ,LOW );
  digitalWrite(LEFT_MOTOR_DOWN ,LOW );
  digitalWrite(RIGHT_MOTOR_UP  ,HIGH);
  digitalWrite(RIGHT_MOTOR_DOWN,HIGH);  
}
