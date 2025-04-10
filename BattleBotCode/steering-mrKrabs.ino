#include "ESC.h"

//channel 1 is pin 8
//channel 2 is pin 7
//d9 is going M1
//d10 is going M2
//channel 2 goes left and right THIS IS FINAL
//channel 1 goes up and down THIS IS FINAL 
#define SIGNAL_PIN1 (8) 
#define SIGNAL_PIN2 (7) 
#define ESC_PIN_M1 (9)
#define ESC_PIN_M2 (10)
#define LED_PIN (13)  
#define MAX_REVERSE (1125)
#define MAX_FORWARD (1875)
#define ARM_VAL (1500)                                        // Midpoint                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 

ESC myESC_M2 (ESC_PIN_M2, MAX_REVERSE, MAX_FORWARD, ARM_VAL);       // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
ESC myESC_M1 (ESC_PIN_M1, MAX_REVERSE, MAX_FORWARD, ARM_VAL);  


int ch1Value;
int ch2Value;





// Testing Backwards
void moveForwardBackward (int speed)
{   //channel 1, the right joystick moves up and down
        myESC_M1.speed(speed); 
        myESC_M2.speed(speed);                                                                                                                                                                                                                                                                            myESC_M2.speed(speed);
        
       // Serial.println("if ch2");
       // Serial.println(speed);
}

// works well as pure pivot turn
void moveLeftRight (int speed, int invSpeed)
{   //channel 2, the right joystick moves left and right
        myESC_M1.speed(speed); 
        myESC_M2.speed(invSpeed);
}





int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue)
{
    int ch = pulseIn(channelInput, HIGH, 30000);
    if (ch < 100) return defaultValue;
    return map(ch, 1000, 2000, minLimit, maxLimit);
    //https://docs.arduino.cc/language-reference/en/functions/math/map/
    //if your project requires precise calculations (e.g. voltage accurate to 3 decimal places),
    // please consider avoiding map() and implementing the calculations manually in your code yourself.
}

void setup() 
{
    pinMode(LED_PIN, OUTPUT);                               // LED Visual Output
    myESC_M2.arm();                                            // Send the Arm value so the ESC will be ready to take commands
    myESC_M1.arm();
    digitalWrite(LED_PIN, HIGH);                            // LED High Once Armed
    delay(5000); 
    digitalWrite(LED_PIN, LOW);                             // Wait for a while
    delay(1000);
    Serial.begin(9600);
}

void loop() 
{
    ch1Value = readChannel(SIGNAL_PIN1, MAX_REVERSE, MAX_FORWARD, ARM_VAL); 
    ch2Value = readChannel(SIGNAL_PIN2, MAX_REVERSE, MAX_FORWARD, ARM_VAL);
    //1500+(1500-speed)=3000-speed
    //1500-(speed-1500)=3000-speed
    int inverseMotorCH1 = 3000-ch1Value; 
    int inverseMotorCH2 = 3000-ch2Value; 

     //moveForwardBackward(ch1Value); 

    if ((ch2Value >= 1605 ||  ch2Value <= 1300))
    { //NEED TO DOUBLE CHECK IF PIVOT STEER IS ACTUALLY REVERSED. MAY ACTUALLY BE TRADITIONALLY STEERING
       moveLeftRight(ch2Value, inverseMotorCH2);
    }
    else // (no ch1 input)
    {
      moveForwardBackward(ch1Value); 
    }


}