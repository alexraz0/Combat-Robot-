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



void moveForward (int speed)
{   //channel 1 is moving the joystick right to left
    //move right joystick to the left makes the motor reverse
    // (1500-speed)->1500+(1500-speed)=3000-speed
    // (speed-1500)->1500-(speed-1500)=3000-speed
    int esc1Speed = 3000-speed; //fast forward
        int inverseSpeed=3000-speed;
        myESC_tLess.speed(inverseSpeed); //PIVOT STEER: we add 150 so it's offset from the other motor
        myESCtext.speed(speed);
        
        Serial.println("if ch2");
        Serial.println(speed);
      
}

void moveBackward (int speed)
{   //channel 1 is moving the joystick right to left
    //move right joystick to the left makes the motor reverse
    // (1500-speed)->1500+(1500-speed)=3000-speed
    // (speed-1500)->1500-(speed-1500)=3000-speed
    int inverseSpeed=3000-speed;
        myESC_tLess.speed(speed); //PIVOT STEER: we add 150 so it's offset from the other motor
        myESCtext.speed(speed);
        
        Serial.println("if ch2");
        Serial.println(speed);
      
}


void moveLeft (int speed)
{   
        int esc1Speed = speed; //fast forward
        int inverseSpeed=3000-speed + 150 ;
       // int inverseSpeed += 150;  //PIVOT STEER: we add 150 so it's offset from the other motor

       // myESC_tLess.speed(speed+150); //PIVOT STEER: we add 150 so it's offset from the other motor
       // myESCtext.speed(speed);
        
        if (inverseSpeed >= 1850)
        {
          myESC_tLess.speed(inverseSpeed); 
          myESCtext.speed(1150); //slow reverse
        }
        else
        {
          myESCtext.speed(esc1Speed); //slow
          myESC_tLess.speed(inverseSpeed);
        }
        Serial.println("if ch1");
        Serial.println(speed);
}

void moveRight (int speed)
{   
        int esc1Speed = speed; //fast forward
        int inverseSpeed=3000-speed + 150;  //PIVOT STEER: we add 150 so it's offset from the other motor

       // myESC_tLess.speed(speed+150); //PIVOT STEER: we add 150 so it's offset from the other motor
       // myESCtext.speed(speed);
        
        if (inverseSpeed >= 1850)
        {
          myESC_tLess.speed(1150); 
          myESCtext.speed(inverseSpeed); //slow reverse
        }
        else
        {
          myESCtext.speed(inverseSpeed); //slow
          myESC_tLess.speed(esc1Speed);
        }
        Serial.println("if ch1");
        Serial.println(speed);
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
    if (ch1Value >= 1525 ||  ch1Value <= 1475)
    { //NEED TO DOUBLE CHECK IF PIVOT STEER IS ACTUALLY REVERSED. MAY ACTUALLY BE TRADITIONALLY STEERING
      if (ch1Value < 1500)
      //channel 1 is moving the joystick right to left
      //move right joystick to the left makes the motor reverse
      { 
        
        moveLeft(ch1Value);
       
      }
      else // (ch1Value > 1500)
      //channel 1 is moving the joystick right to left
      //move right joystick to the left makes the motor reverse
      { 
        
        moveRight(ch1Value);
        Serial.println(ch1Value);
      }

    }
    else // (no ch1 input)
    {
      if (ch2Value > 1500)
      {
        moveForward(ch2Value);
        Serial.print("chValue2 ");
        Serial.println(ch2Value); 
      }
      else //ch2Value < 1500
      {
        moveBackward(ch2Value);
      }

      
      

      //myESCtext.speed(ch2Value);
      //myESC_tLess.speed(ch2Value); 
      Serial.print("chValue1 ");
      Serial.println(ch1Value);
    //  Serial.println("the else chValue2: "+ chValue2);
      
    }

}