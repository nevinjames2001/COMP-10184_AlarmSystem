////I, Nevin James, student number 000825144, certify that this material is my original work. No other person's work has been used without due acknowledgment and I have not made my work available to anyone else.

//I have completed all the 5 stages of the IoT Alarm System

// COMP-10184 – Mohawk College 
// PIR Sensor Test Application 
// Turn on the blue LED with motion is detected. 
 
#include <Arduino.h> 
 
// digital input pin definitions 
#define PIN_PIR D5 
#define PIN_BUTTON D6 
#define buttonDelay 200 
#define OnDelay 20
#define OffDelay 230

//Declaration of delays, number of flashings, variables
bool ALARM=1;
int times=40;
bool bPIR; 
byte buttonState;
bool check;
bool permanent;

 
// ************************************************************* 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // configure the LED output 
  pinMode(LED_BUILTIN, OUTPUT); 

  //Setting up the state of LED button to be switched off
  digitalWrite(LED_BUILTIN, HIGH);
 
  // PIR sensor is an INPUT 
  pinMode(PIN_PIR, INPUT); 
 
  // Button is an INPUT 
  pinMode(PIN_BUTTON, INPUT_PULLUP); 
} 

// ************************************************************* 
void loop() { 
  
  check=1;
  permanent=1;
  

  //Reading the button state and changing the permission to sensor the movement
  buttonState = digitalRead(PIN_BUTTON);
  if(!buttonState){
    ALARM=1;
  }
 
  // read PIR sensor (true = Motion detected!).  As long as there 
  // is motion, this signal will be true.  About 2.5 seconds after  
  // motion stops, the PIR signal will become false. 

  //Check there is any movement or not in sensor
  if(ALARM){
    bPIR = digitalRead(PIN_PIR);
  }
  
   
  //Checking the sensor detects any movement or not  
  if(bPIR && ALARM){
    //Light flashing if the conditons go true and proceeds until some click the switch
    while(bPIR && ALARM){
      if(check && ALARM){
        //Flashing the light for 10seconds (4 seconds per minute)
          for(int i=0;i<times;i++){
            digitalWrite(LED_BUILTIN,LOW);
            delay(OnDelay);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(OffDelay);

            //If button is pressed the light should goes off (alaram is disabled)
            buttonState = digitalRead(PIN_BUTTON);
            if(!buttonState && ALARM){
              ALARM=0;
              permanent=0;
              bPIR=0;
              check=0;
              digitalWrite(LED_BUILTIN, HIGH);
              i=times;    
            }
        }
        check=0;
      }  
      //If the alarm is not disbaled the light will be permanently on until the program terminates
      if(permanent){
        digitalWrite(LED_BUILTIN, LOW);
      }   
    }
  }
  //Delay to avoid the fluctuation when button is clicked
  delay(buttonDelay);

  //Setting the state of led off if no sensor detects it
  digitalWrite(LED_BUILTIN, HIGH);
}

