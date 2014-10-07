#include <Wire.h>

#define DEVICE 0x04

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  while(!Serial);
  Serial.println("false CRio");
}

void recv() {
  Wire.requestFrom(4, 6);    // request 6 bytes from slave device #2
  delay(10); //Puts space between transmissions to prevent packet loss & freezing
  while(Wire.available())    // slave may send less than requested
  { 
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
  Serial.println();

  delay(100);
}

void sndp(char x, char y) {
  Serial.println("sending....");
  Wire.beginTransmission(4); // transmit to device #4
  Serial.println(Wire.write(x));        // sends five bytes
  Serial.println(Wire.write(y));              // sends one byte  
  Serial.println(Wire.endTransmission());    // stop transmitting
  delay(100); //Puts space between transmissions to prevent packet loss & freezing
  Serial.println("sent");
}

int readInt(void) {
  while(!Serial.available());
  String inString = "";    // string to hold input
  // Read serial input:
  while (Serial.available() > 0) {
    delay(1);
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char 
      // and add it to the string:
      inString += (char)inChar; 
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      //break;
    }
  }
  int x = inString.toInt();
  inString = ""; // clear the string for new input:
  return x;
}

void loop()
{
  delay(10);
  char x, y;
  Serial.println("send byte 1:");
  x = readInt();
  Serial.println("send byte 2:");
  y = readInt();
  
  Serial.print("packet: ");
  Serial.print((int)x);
  Serial.print(",");
  Serial.println((int)y);
  sndp(x, y);
  recv();

}
