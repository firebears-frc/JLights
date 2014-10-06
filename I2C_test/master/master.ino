#include <Wire.h>

#define DEVICE 0x04

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void recv() {
  delay(10);
  Wire.requestFrom(DEVICE, 2);    // request 2 bytes from slave device #2

  Serial.println("checking...\n");

  while(!Wire.available());
  
  Serial.print("response: ");

  while(Wire.available())    // slave may send less than requested
  { 
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
  Serial.println();
}

void sndp(byte x, byte y) {
  Serial.println("sending....");
  Wire.beginTransmission(DEVICE); // transmit to device #4
  Serial.println("SFD");
  Wire.write(x);                  // sends one byte
  Wire.write(y);                  // sends one byte 
  Serial.println("ending..."); 
  Wire.endTransmission();         // stop transmitting
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
