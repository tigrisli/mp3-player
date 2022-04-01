#include "SoftwareSerial.h"
SoftwareSerial mySerial(10, 11);

# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

# define ACTIVATED LOW

int buttonNext = 2;
int buttonPause = 7;
int buttonPrevious = 4;
boolean isPlaying = false;

void setup () {

  Serial.begin(9600);

  pinMode(buttonPause, INPUT);
  digitalWrite(buttonPause,HIGH);
  
  mySerial.begin(9600);
  delay(1000);
  playFirst();
  isPlaying = true;


}



void loop () { 

}


void playFirst() {
  execute_CMD(0x3F, 0, 0);
  delay(500);
  setVolume(5);
  delay(1000);
  execute_CMD(0x11,0,1); 
  delay(10);
}

void pause() {
  execute_CMD(0x0E,0,0);
  delay(500);
}

void play() {
  execute_CMD(0x0D,0,1); 
  delay(100);
}

void playNext() {
  execute_CMD(0x01,0,1);
  delay(500);
}

void playPrevious() {
  execute_CMD(0x02,0,1);
  delay(500);
}

void setVolume(int volume) {
  execute_CMD(0x20, 0, volume); // Set the volume (0x00~0x30)
  delay(2000);
}

void execute_CMD(byte CMD, byte Par1, byte Par2) {
// Excecute the command and parameters
// Calculate the checksum (2 bytes)
word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

// Build the command line
byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};

//Send the command line to the module
  for (byte k=0; k<10; k++) {
    mySerial.write( Command_line[k]);
  }
}
