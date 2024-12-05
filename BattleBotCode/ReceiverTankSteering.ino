#include "ESC.h"

#define SIGNAL_PIN1 (8) 
#define SIGNAL_PIN2 (7) 
#define ESC_PIN (9)
#define ESC_PIN_fLess (10)
#define LED_PIN (13)  
#define MAX_REVERSE (1000)
#define MAX_FORWARD (2000)
#define ARM_VAL (1500)                                        // Midpoint

ESC myESCFont (ESC_PIN, MAX_REVERSE, MAX_FORWARD, ARM_VAL);       // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
ESC myESC_fLess (ESC_PIN_fLess, MAX_REVERSE, MAX_FORWARD, ARM_VAL);  

int chValue1;
int chValue2;


void moveMotorsForward (int speed1, int speed2)
{
    myESCFont.speed(speed1); // set the first ESC speed to the input value (forwared direction)
    //1500-(speed2-1500)=3000-speed2
    myESC_fLess.speed(3000-speed2); // set the second ESC speed to the reverse of input value
}
void moveMotorsBackwards (int speed1, int speed2)
{
    myESCFont.speed(speed2); // set the first ESC speed to the input value (forwared direction)
    myESC_fLess.speed(3000-speed1); // set the second ESC speed to the reverse of input value
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
    myESCFont.arm();                                            // Send the Arm value so the ESC will be ready to take commands
    myESC_fLess.arm();
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
    moveMotorsForward(chValue1, chValue2);
}
