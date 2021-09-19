/*
Author : Youssef Abbas
Date   : 18/9/2021
About  : Hermione Potions
*/
#include<Timer.h>

#define RED 9
#define GREEN 8
#define WHITE 7
#define BUTTON 6

Timer recipe;   //Define Timer object

void setup() 
{
  Serial.begin(9600);
  
  //Define Pins 
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(WHITE,OUTPUT);
  pinMode(BUTTON,INPUT);

  //Timing 
  recipe.after(0    , flash_red    );         //indicate the time that the heat should be turned on
  recipe.after(900000 , end_red    );         //indicate the time that the heat should be turned off
  recipe.every(120000 , flash_green);         //indicate the need for mixing the ingredients in the pot
  recipe.every(125000 , end_green  );         //End of need mixing the ingredients 
  recipe.after(300000 , flash_white);         //indicate the need for adding the next ingredient to the pot
  recipe.after(480000 , flash_white);         //indicate the need for adding the next ingredient to the pot
  recipe.after(310000 ,   end_white);         //Finish the need for adding the next ingredient to the pot
  recipe.after(490000 ,   end_white);         //Finish the need for adding the next ingredient to the pot
  
}

void loop() 
{
  if(digitalRead(BUTTON) == HIGH)  //when Hermoine press button
  {
    recipe.update();   
  }
}

void flash_green()
{
  Serial.println("FLASH GREEN");
  digitalWrite(GREEN,HIGH); 
}
void end_green()
{
  Serial.println("END GREEN");
  digitalWrite(GREEN,LOW);

}
void flash_red()
{
  Serial.println("FLASH RED");
  digitalWrite(RED,HIGH); 
}
void end_red()
{
  Serial.println("END RED");
  digitalWrite(RED,LOW);

}
void flash_white()
{
  Serial.println("FLASH WHITE");
  digitalWrite(WHITE,HIGH); 
}
void end_white()
{
  Serial.println("END WHITE");
  digitalWrite(WHITE,LOW);

}
