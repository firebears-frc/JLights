#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  while(!Serial);
  Serial.println("the master");
}

byte x = 0;

void loop()
{
  Wire.beginTransmission(4); // transmit to device #4
  Serial.println(Wire.write("x is "));        // sends five bytes
  Serial.println(Wire.write(x));              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  delay(10); //Puts space between transmissions to prevent packet loss & freezing

  x++;
  
  Wire.requestFrom(4, 6);    // request 6 bytes from slave device #2
  delay(10); //Puts space between transmissions to prevent packet loss & freezing
  while(Wire.available())    // slave may send less than requested
  { 
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
  Serial.println();

  delay(500);
}
