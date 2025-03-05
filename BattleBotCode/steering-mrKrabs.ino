#include "ESC.h"

#define SIGNAL_PIN1 (8) 
#define SIGNAL_PIN2 (7) 
#define ESC_PIN (9)
#define ESC_PIN_fLess (10)
#define LED_PIN (13)  
#define MAX_REVERSE (1000)
#define MAX_FORWARD (2000)
#define ARM_VAL (1500)                                        // Midpoint

ESC myESCtext (ESC_PIN, MAX_REVERSE, MAX_FORWARD, ARM_VAL);       // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
ESC myESC_tLess (ESC_PIN_fLess, MAX_REVERSE, MAX_FORWARD, ARM_VAL);  
//ESC 1 is the text less motor ESC_tless 

int ch1Value;
int ch2Value;

//1500+(1500-speed)=3000-speed
//1500-(speed-1500)=3000-speed
int inverseMotorCH1 = 3000-ch1Value; 
int inverseMotorCH2 = 3000-ch2Value; 



// BACKWARD WORKS
void ForwardBackward (int speed)
{   //channel 2, the right joystick moves up and down
        myESC_tLess.speed(speed); 
        myESCtext.speed(speed);
        
        Serial.println("if ch2");
        Serial.println(speed);
}


void moveLeft (int speed)
{     
      myESC_tLess.speed(speed);
      myESCtext.speed(1500);
      
}

void moveRight (int speed)
{   
      myESC_tLess.speed(1500);
      myESCtext.speed(inverseMotorCH1);
}





int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue)
{
    int ch = pulseIn(channelInput, HIGH, 30000);
    if (ch < 100) return defaultValue;
    return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setup() 
{
    pinMode(LED_PIN, OUTPUT);                               // LED Visual Output
    myESCtext.arm();                                            // Send the Arm value so the ESC will be ready to take commands
    myESC_tLess.arm();
    digitalWrite(LED_PIN, HIGH);                            // LED High Once Armed
    delay(5000); 
    digitalWrite(LED_PIN, LOW);                             // Wait for a while
    delay(1000);
    Serial.begin(9600);
}

void loop() 
{
    ch1Value = readChannel(SIGNAL_PIN1, MAX_REVERSE, MAX_FORWARD, ARM_VAL);
    //myESCFont.speed(chValue1);   
    ch2Value = readChannel(SIGNAL_PIN2, MAX_REVERSE, MAX_FORWARD, ARM_VAL);
    //myESC_fLess.speed(chValue2);
    //moveMotorsForward(chValue1, chValue2);
    if (ch1Value >= 1550 ||  ch1Value <= 1450)
    { //NEED TO DOUBLE CHECK IF PIVOT STEER IS ACTUALLY REVERSED. MAY ACTUALLY BE TRADITIONALLY STEERING
      if (ch1Value < 1500)
      //channel 1 is moving the joystick right to left
      //move right joystick to the left makes the motor reverse
      { 
        
        moveLeft(ch1Value);
       
      }
      else // (ch1Value > 1500)
      { 
        
        moveRight(ch1Value);
        Serial.println(ch1Value);
      }

    }
    else // (no ch1 input)
    {

      ForwardBackward(ch2Value);
     
    }

}