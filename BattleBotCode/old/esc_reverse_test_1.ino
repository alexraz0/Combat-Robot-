#include "ESC.h"

#define LED_PIN (13)  
#define ESC_PIN (9)
#define MAX_REVERSE (1000)
#define MAX_FORWARD (2000)
#define ARM_VAL (1400)                                        // Midpoint

ESC myESC (ESC_PIN, MAX_REVERSE, MAX_FORWARD, ARM_VAL);           // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
int speedSet;                                                 // Variable for the speed sent to the ESC

void setup() 
{
    pinMode(LED_PIN, OUTPUT);                               // LED Visual Output
    myESC.arm();                                            // Send the Arm value so the ESC will be ready to take commands
    digitalWrite(LED_PIN, HIGH);                            // LED High Once Armed
    delay(5000); 
    digitalWrite(LED_PIN, LOW);                             // Wait for a while
    delay(1000);
    Serial.begin(9600);
}

void loop() 
{
    for (speedSet = ARM_VAL; speedSet <= MAX_FORWARD; speedSet ++) //speed up forward
    { 
        digitalWrite(LED_PIN, HIGH); 
        myESC.speed(speedSet);                               
        delay(30);                                           
        Serial.println(speedSet);
    }

    for (speedSet = MAX_FORWARD; speedSet >= ARM_VAL; speedSet --) //slow down forward
    { 
        myESC.speed(speedSet);                               
        delay(30);                                           
        Serial.println(speedSet);
    }

    for (speedSet = ARM_VAL; speedSet >= MAX_REVERSE; speedSet --) //speed up reverse
    {   
        digitalWrite(LED_PIN, LOW); 
        myESC.speed(speedSet);                              
        delay(30);                                           
        Serial.println(speedSet);
    }

    for (speedSet = MAX_REVERSE; speedSet <= ARM_VAL; speedSet ++) //slow down reverse
    {  
        myESC.speed(speedSet);                               
        delay(30);                                           
        Serial.println(speedSet);
    }
}
