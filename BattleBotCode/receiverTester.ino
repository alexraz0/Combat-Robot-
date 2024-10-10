//simple receiver communication program

//CH1: right stick left and right
//CH2: right stick up and down
//Ch3: left stick up and down
//Ch4: left stick left and right
//Ch5: left knob
//CH6: right knob

#define signalPin 12 //signal cable goes in digital pin 12 of arduino

int ch1Value;

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setup() 
{
  pinMode(signalPin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  chValue = readChannel(signalPin, -500, 500, 0);
  Serial.println(chValue);
  delay(50);

}
