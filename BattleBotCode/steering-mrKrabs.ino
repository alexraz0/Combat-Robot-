#include "ESC.h"

//channel 1 is pin 8
//channel 2 is pin 7
//d10 is going M1
//d9 is going M2

#define SIGNAL_PIN1 (8) 
#define SIGNAL_PIN2 (7) 
#define ESC_PIN_M2 (9)
#define ESC_PIN_M1 (10)
#define LED_PIN (13)  
#define MAX_REVERSE (1125)
#define MAX_FORWARD (1875)
#define ARM_VAL (1500)
/*
6V/8V = 0.75
Assumed 1500 = 0V and 2000 = 8V and 1000 = 8V
2000 - 1500 = 500 which is the range the volts can span
0.75(500) = 375 so we add this to the neutral value 1500 to get the 6 Volt max
1500 + 375 = 1875 upper 6 volt max
1500 - 375 = 1125  lower 6 volt max
*/


// ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
ESC myESC_M1 (ESC_PIN_M1, MAX_REVERSE, MAX_FORWARD, ARM_VAL); 
ESC myESC_M2 (ESC_PIN_M2, MAX_REVERSE, MAX_FORWARD, ARM_VAL); 

int ch1Value;
int ch2Value;
int inverseMotorCH1;
int inverseMotorCH2;
bool exitRightLeft;




// Testing Backwards
void moveForwardBackward (int speed, int invSpeed)
{   //channel 2, the right joystick moves up and down
        myESC_M1.speed(speed); 
        myESC_M2.speed(invSpeed);
        
        Serial.println("if ch2");
        Serial.println(speed);
}

// works well as pure pivot turn
void moveLeftRight (int speed, int invSpeed)
{   //channel 2, the right joystick moves up and down
        myESC_M1.speed(speed); 
        myESC_M2.speed(speed);
}




//defaultValue is ARM_VAL=1500
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
    inverseMotorCH1 = 3000-ch1Value; 
    inverseMotorCH2 = 3000-ch2Value; 


    if ((ch1Value >= 1500) && (ch1Value <= ch2Value))
    { 
       moveLeftRight(ch1Value, inverseMotorCH1);
    }
    else if ((ch1Value >= 1500) && (ch1Value <= inverseMotorCH2))
    { 
       moveLeftRight(ch1Value, inverseMotorCH1);
    }
    else if ((ch1Value <= 1500) && (ch1Value >= ch2Value))
    {
        moveLeftRight(ch1Value, inverseMotorCH1);
    }
    else if ((ch1Value <= 1500) && (ch1Value >= inverseMotorCH2))
    {
        moveLeftRight(ch1Value, inverseMotorCH1); 
    }
    else
    {
        moveForwardBackward(ch2Value, inverseMotorCH2);
    }

    delay(500);

}