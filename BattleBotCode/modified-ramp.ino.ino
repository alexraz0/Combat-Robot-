/*
  ESC_Ramp
    Based on the Sweep example in the Servo library, this allow a ramp up and down of the ESC speed based on the Min and Max values.
    The Min and Max speed are defined so you can change them at one location and it will be used in the ramp as well.
    
  27 April 2017
  by Eric Nantel
 */
#include "ESC.h"
#define LED_PIN (13)                                      // Pin for the LED 
#define SPEED_MIN (1000)                                  // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)                                  // Set the Minimum Speed in microseconds

ESC myESC (9, SPEED_MIN, SPEED_MAX, 1500);                 // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
int oESC;                                                 // Variable for the speed sent to the ESC

void setup() {
  pinMode(LED_PIN, OUTPUT);                               // LED Visual Output
  myESC.arm();                                            // Send the Arm value so the ESC will be ready to take commands
  digitalWrite(LED_PIN, HIGH);                            // LED High Once Armed
  delay(5000);                                            // Wait for a while
  Serial.begin(9600);
}

void loop() {
 /*
 **************************
THIS IS THE REVERSE SECTION
***************************
 */ 
  for (oESC = 1500; oESC >= SPEED_MIN; oESC -= 1) {   // goes from 1500 microseconds to 1000 microseconds
    myESC.speed(oESC);                               // tell ESC to go to the oESC speed value
    delay(10);                                      // waits 10ms for the ESC to reach speed
   Serial.println(oESC);
  }
   delay(1000);
 
  for (oESC = SPEED_MIN; oESC <= 1500; oESC += 1) {  // goes from 1000 microseconds to 1500 microseconds
    myESC.speed(oESC);                                    // tell ESC to go to the oESC speed value
    delay(10);                                            // waits 10ms for the ESC to reach speed  
    Serial.println(oESC);
   }

/*
***************************
    MOVE FORWARD SECTION
***************************
 */ 
  for (oESC = 1500; oESC <= SPEED_MAX; oESC += 1) {       // goes from 1500 microseconds to 2000 microseconds
    myESC.speed(oESC);                                    // tell ESC to go to the oESC speed value
    delay(10);                                            // waits 10ms for the ESC to reach speed
   Serial.println(oESC);
  }
   delay(1000);
 
  for (oESC = SPEED_MAX; oESC >= 1500; oESC -= 1) {       // goes from 2000 microseconds to 1500 microseconds
    myESC.speed(oESC);                                    // tell ESC to go to the oESC speed value
    delay(10);                                            // waits 10ms for the ESC to reach speed  
  Serial.println(oESC);
   }
  
  delay(5000);                                            // Wait for a while before restart
}
