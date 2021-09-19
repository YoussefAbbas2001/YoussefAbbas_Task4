/*
Author : Youssef Abbas
Date   : 19/9/2021
About  : Harry in Maze (harry Safe)
MC     : Arduino MEGA
*/
#define ENCODER1_A 43    //first  encoder SIGNAL_A
#define ENCODER1_B 44    //first  encoder SIGNAL_B
#define ENCODER2_A 45    //second encoder SIGNAL_A
#define ENCODER2_B 46    //second encoder SIGNAL_B
#define ENCODER3_A 6     //third  encoder SIGNAL_A
#define ENCODER3_B 7     //third  encoder SIGNAL_B
#define GREEN_LED  18    //green led to indicate ecoders positions

long long counter1 = 0;  //Counter of encoder 1
long long counter2 = 0;  //Counter of encoder 2
long long counter3 = 0;  //Counter of encoder 3
const int PPR      = 512;//Puls Per Revolutions (Assume = 512)
int degree1;             //degree of first encoder
int degree2;             //degree of second encoder
int degree3;             //degree of third encoder

void setup()
{
  //define pin Modes
  pinMode(ENCODER1_A , INPUT );
  pinMode(ENCODER1_B , INPUT );
  pinMode(ENCODER2_A , INPUT );
  pinMode(ENCODER2_B , INPUT );
  pinMode(ENCODER3_A , INPUT );
  pinMode(ENCODER3_B , INPUT );
  pinMode(GREEN_LED  , OUTPUT);

  //define interrupts
  attachInterrupt(digitalPinToInterrupt(ENCODER1_A) , ISR1_A , CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER1_B) , ISR1_B , CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER2_A) , ISR2_A , CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER2_B) , ISR2_B , CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER3_A) , ISR3_A , CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER3_B) , ISR3_B , CHANGE);
 
}

void loop() 
{
  readDegrees(); //read the degrees of encoders
  
  if (degree1 == 37 && degree2 == 10 && degree3 == 54)
  {
    //when degrees in this position light the led
    digitalWrite(GREEN_LED , HIGH);  
  }
  else
  {
    digitalWrite(GREEN_LED , LOW);  
  }
}

void readDegrees()
{
    degree1 = (int)(counter1 /(PPR*4))*360;
    degree2 = (int)(counter2 /(PPR*4))*360;
    degree3 = (int)(counter3 /(PPR*4))*360;
}

//Interrupt Service Routine to Encoder number 1
void ISR1_A()
{
  if (digitalRead(ENCODER1_A) != digitalRead(ENCODER1_B))
    counter1++  ;
  else
    counter1--  ;
}
void ISR1_B()
{
  if (digitalRead(ENCODER1_A) == digitalRead(ENCODER1_B))
    counter1++   ;
  else
    counter1--  ;
}

//Interrupt Service Routine to Encoder number 2
void ISR2_A()
{
  if (digitalRead(ENCODER2_A) != digitalRead(ENCODER2_B))
    counter2++ ;
  else
    counter2--  ;
}
void ISR2_B()
{
  if (digitalRead(ENCODER2_A) == digitalRead(ENCODER2_B))
    counter2++ ;
  else
    counter2--  ;
}

//Interrupt Service Routine to Encoder number 3
void ISR3_A()
{
  if (digitalRead(ENCODER3_A) != digitalRead(ENCODER3_B))
    counter3++ ;
  else
    counter3--  ;
}
void ISR3_B()
{
  if (digitalRead(ENCODER3_A) == digitalRead(ENCODER3_B))
    counter3++ ;
  else
    counter3--  ;
}
