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

int chValue1;
int chValue2;


void moveMotorsForward (int speed1, int speed2)
{
    myESCtext.speed(speed1); // set the first ESC speed to the input value (forwared direction)
    //1500-(speed2-1500)=3000-speed2
    myESC_tLess.speed(speed2); // set the second ESC speed to the reverse of input value
}
void moveMotorsBackwards (int speed1, int speed2)
{
    myESCtext.speed(speed2); // set the first ESC speed to the input value (forwared direction)
    myESC_tLess.speed(3000-speed1); // set the second ESC speed to the reverse of input value
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
    chValue1 = readChannel(SIGNAL_PIN1, MAX_REVERSE, MAX_FORWARD, ARM_VAL);
    //myESCFont.speed(chValue1);   
    chValue2 = readChannel(SIGNAL_PIN2, MAX_REVERSE, MAX_FORWARD, ARM_VAL);
    //myESC_fLess.speed(chValue2);
    //moveMotorsForward(chValue1, chValue2);
    if (chValue1 >= 1550 ||  chValue1 <= 1450)
    { //NEED TO DOUBLE CHECK IF PIVOT STEER IS ACTUALLY REVERSED. MAY ACTUALLY BE TRADITIONALLY STEERING
      if (chValue1 <= 1400)
      //channel 1 is moving the joystick right to left
      //move right joystick to the left makes the motor reverse
      { //1500+(1500-chvalue1)=3000-chValue1; the value (1500-chValue1) is the distance from the midpoint value 1500
        int esc1Speed = 3000-chValue1+150;
        myESC_tLess.speed(esc1Speed); //PIVOT STEER: we add 150 so it's offset from the other motor
        if (esc1Speed >= 1850)
        {
          myESCtext.speed(1150);
        }
        else
        {
          myESCtext.speed(chValue1);
        }
        Serial.println("if ch1");
        Serial.println(chValue1);
      }
      else
      {
        myESCtext.speed(chValue1);
        Serial.println(chValue1);
      }

    }
    else
    {
      myESCtext.speed(chValue2);
      myESC_tLess.speed(chValue2); 
      Serial.print("chValue1 ");
      Serial.println(chValue1);
    //  Serial.println("the else chValue2: "+ chValue2);
      Serial.print("chValue2 ");
      Serial.println(chValue2); 
    }

}
