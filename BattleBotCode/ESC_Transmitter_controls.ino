#include "ESC.h"

#define LED_PIN (13)  
#define ESC_PIN (9)
#define MAX_REVERSE (1000)
#define MAX_FORWARD (2000)
#define ARM_VAL (1500)                                        // Midpoint

ESC myESC (ESC_PIN, MAX_REVERSE, MAX_FORWARD, ARM_VAL);       // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
int speedSet;                                                 // Variable for the speed sent to the ESC

#define signalPin 8 //signal cable goes in digital pin 12 of arduino

int chValue;

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue)
{
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

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
    chValue = readChannel(signalPin, 1000, 2000, 1500);
    myESC.speed(chValue);   

}
