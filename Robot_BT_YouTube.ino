// Simple Bluetooth Controlled Car using App Inventor
// by EZTech (Mark Conner)
// Videos & Instructions can be found at - Youtube & Instructables 
// Code for this and other projects @ GitHub https://github.com/mkconer/
// Arduino Mega
// HC-06 Slave 5v Bluetooth module
// L293D Motor Shield - Be sure to Install the Adafruit Motor Shield Library


#include <AFMotor.h>                                      // The Adafruit Motor Shield Library ver. 1
                                                      
//****************************************************************************************************
// Setup Drive Motors using the Adafruit Motor Controller version 1.0 Library

AF_DCMotor motor1(1, MOTOR12_64KHZ);                      // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ);                      // create motor #2, 64KHz pwm
AF_DCMotor motor3(3, MOTOR12_64KHZ);                      // create motor #3, 64KHz pwm
AF_DCMotor motor4(4, MOTOR12_64KHZ);                      // create motor #4, 64KHz pwm

int mtr_Spd = 250;                                        // set the speed of the motors

//*****************************************************************************************************
// Bluetooth Variables & Setup

String str;                                               // raw string received from android to arduino
int blueToothVal;                                         // stores the last value sent over via bluetooth

//*****************************************************************************************************

void setup() 
{  
  Serial.begin(115200);                                  // Serial 0 is for communication with the serial monitor
  Serial1.begin(9600);                                   // Serial 1 is for Bluetooth communication - DO NOT MODIFY  
}

//*****************************************************************************************************
// Main Loop

void loop()
{   
  bluetooth();                                          // Run the Bluetooth procedure to see if there is any data being sent via BT
}




//*****************************************************************************************************
// This procedure reads the serial port - Serial1 - for bluetooth commands being sent from the Android device

void bluetooth()
{
 while (Serial1.available())                             // Read bluetooth commands over Serial1 // Warning: If an error with Serial1 occurs, make sure Arduino Mega 2560 is Selected
 {  
  {  
      str = Serial1.readStringUntil('\n');               // str is the temporary variable for storing the last sring sent over bluetooth from Android device
      //Serial.print(str);             
  } 
    
    blueToothVal = (str.toInt());                        //  convert the string 'str' into an integer and assign it to blueToothVal
    Serial.print("BlueTooth Value ");
    Serial.println(blueToothVal);    



// Bluetooth Section
// *********************************************************************************************************

 switch (blueToothVal) 
 {
      case 1:                                
        Serial1.println("Forward");
        Forward();
        break;

      case 2:                 
        Serial1.println("Reverse");
        Reverse();
        break;

      case 3:         
        Serial1.println("Left");
        LeftTurn();
        Stop();
        break;
        
      case 4:                     
        Serial1.println("Right");
        RightTurn();
        Stop();
        break;
        
      case 5:                                            
        Serial1.println("Stop");
        Stop();
        break;      

 }                                                              // end of switch case 

 }                                                              // end of while loop Serial1 read
 
                                                                // if no data from Bluetooth 
   if (Serial1.available() < 0)                              
    {
     Serial1.println("No Bluetooth Data ");          
    }
  
}




// Motor Control Section
// **********************************************************************************************************************************************************************

void Forward()
{
  Serial.println("Forward");
  motor1.setSpeed(mtr_Spd);                                                   
  motor2.setSpeed(mtr_Spd);     
  motor3.setSpeed(mtr_Spd);     
  motor4.setSpeed(mtr_Spd);                           
  
  motor1.run(FORWARD);                                                         
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

// **********************************************************************************************************************************************************************


void Reverse()
{
  Serial.println("Reverse");
  motor1.setSpeed(mtr_Spd);                                                   
  motor2.setSpeed(mtr_Spd);     
  motor3.setSpeed(mtr_Spd);     
  motor4.setSpeed(mtr_Spd);    
  
  motor1.run(BACKWARD);                                                        
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

// **********************************************************************************************************************************************************************

void LeftTurn()
{
  Serial.println("Left");
  motor1.setSpeed(mtr_Spd);                                                   
  motor2.setSpeed(mtr_Spd);     
  motor3.setSpeed(mtr_Spd);     
  motor4.setSpeed(mtr_Spd);    
  
  motor1.run(BACKWARD);                                                        
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  delay(100);    
}

// **********************************************************************************************************************************************************************

void RightTurn()
{
  Serial.println("Right");
  motor1.setSpeed(mtr_Spd);                                                   
  motor2.setSpeed(mtr_Spd);     
  motor3.setSpeed(mtr_Spd);     
  motor4.setSpeed(mtr_Spd);   

  motor1.run(FORWARD);                                              
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  delay(100);                                                                     
}

// **********************************************************************************************************************************************************************

void Stop()
{ 
  motor1.run(RELEASE);                                                         
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);   
}





