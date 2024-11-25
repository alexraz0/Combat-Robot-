#include "ESC.h"

#define LED_PIN (13)  
#define ESC_PIN (9)                                           // Pin for the LED 
#define SPEED_MIN (1000)                                      // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)   
#define ARM_VAL (1400)                                        // Set the Minimum Speed in microseconds

ESC myESC (ESC_PIN, SPEED_MIN, SPEED_MAX, ARM_VAL);           // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
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
 
    for (speedSet = SPEED_MIN; speedSet <= SPEED_MAX; speedSet += 1) 
    { 
        digitalWrite(LED_PIN, HIGH); 
        myESC.speed(speedSet);                               // tell ESC to go to the oESC speed value
        delay(30);                                           // waits 10ms for the ESC to reach speed
        Serial.println(speedSet);
    }

    for (speedSet2 = SPEED_MAX; speedSet2 >= SPEED_MIN; speedSet2 -= 1) 
    {   
        digitalWrite(LED_PIN, LOW); 
        myESC.speed(speedSet2);                              // tell ESC to go to the oESC speed value
        delay(30);                                           // waits 10ms for the ESC to reach speed
        Serial.println(speedSet2);
    }
   
 
  

    
}