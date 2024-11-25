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
    digitalWrite(LED_PIN, HIGH); 
    myESC.speed(ARM_VAL);
    delay(3000);

    myESC.speed(1700);
    delay(3000);

    myESC.speed(MAX_FORWARD);
    delay(3000);

    myESC.speed(1700);
    delay(3000);

    myESC.speed(ARM_VAL);
    delay(3000);

    digitalWrite(LED_PIN, HIGH); 
    myESC.speed(1150);
    delay(3000);

    myESC.speed(MAX_REVERSE);
    delay(3000);

    myESC.speed(1150);
    delay(3000);
}