#include <Keyboard.h>

struct VECTOR2D
{
  unsigned long ulTime;
  byte value;
};

float lerp(float v0, float v1, float t, float t1, float t2)
{
  float tNorm = (t - t1) / (t2 - t1);
  return (1-tNorm)*v0 + tNorm*v1;
}

const int FAN = 3;
const int LED = 13;

const int AirLength = 25;
VECTOR2D Air[] = {{0, 0},
                 {1520, 0},
                 {4040, 255},
                 {5560, 255},
                 {9800, 0},
                 {13760, 0},
                 {17080, 255},
                 {18530, 255},
                 {23400, 0},
                 {25880, 0},
                 {30440, 255},
                 {32360, 255},
                 {37560, 0},
                 {39520, 0},
                 {44440, 255},
                 {46320, 255},
                 {50520, 0},
                 {55040, 0},
                 {58760, 255},
                 {59440, 255},
                 {63880, 0},
                 {68760, 0},
                 {72320, 255},
                 {73000, 255},
                 {77480, 0}};
                 
unsigned long ulTime;
unsigned long passedTime = 0;

void setup()
{
  pinMode(FAN, OUTPUT);
  pinMode(LED, OUTPUT);
  
  Keyboard.begin();
  
  // /*
  Serial.begin(9600);
  // */
  
  analogWrite(FAN, 0);
}

void loop()
{
  ulTime = millis() - passedTime;
  
  // determine at which point in the array it should be
  int c;
  for (c = 0; c < AirLength; c++)
  {
    if (ulTime <= Air[c].ulTime)
      break;
  }
  
  // if close to the end, restart the track
  if (c >= AirLength - 1)
  {
    Keyboard.write('n');
    passedTime += ulTime;
  }
  
  // write number to fan / led / serial (optional)
  int value = lerp(Air[c -1].value, Air[c].value, ulTime, Air[c -1].ulTime, Air[c].ulTime);
  analogWrite(FAN, value);
  analogWrite(LED, value);
  // /*
  Serial.print(ulTime);
  Serial.print(" : ");
  Serial.print(c);
  Serial.print(" : ");
  Serial.println(value);
  // */
}
