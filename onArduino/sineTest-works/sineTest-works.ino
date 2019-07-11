// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// define the pins used
#define CLK 13       // SPI Clock, shared with SD card
#define MISO 12      // Input data, from VS1053/SD card
#define MOSI 11      // Output data, to VS1053/SD card

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
 

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Simple Test");
  if(musicPlayer.playingMusic) {
    Serial.println("broken musicPlayer object");
  } else {
    Serial.println("constructed musicPlayer OK");
  }

  pinMode(CARDCS, OUTPUT);
  digitalWrite(CARDCS, HIGH);

  //uint8_t v  = Adafruit_VS1053::begin(); 
  //inside Adafruit_VS1053 'low level' interface
  //device obj stuff == musicPlayer.begin();
  Adafruit_VS1053 device(MOSI, MISO, CLK, BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ);

  if(device._reset == 9){
    Serial.println("pins for device object assigned in constructor");
  }

  if (device._reset >= 0) {
    pinMode(device._reset, OUTPUT);
    digitalWrite(device._reset, LOW); //_reset was private, so made public in header file
    Serial.println("reset pin OK");
  }

  pinMode(device._cs, OUTPUT);
  digitalWrite(device._cs, HIGH);
  pinMode(device._dcs, OUTPUT);
  digitalWrite(device._dcs, HIGH);
  Serial.println("cs and dcs pin OK");

  if (! device.useHardwareSPI) {
    pinMode(device._mosi, OUTPUT);
    pinMode(device._clk, OUTPUT);
    pinMode(device._miso, INPUT);
    Serial.println("MOSI pin OK");
    Serial.println("CLK pin OK");
    Serial.println("MISO pin OK");
  } else {
    SPI.begin();
  }

  //edit reset function in .h and .cpp for verification
  int val = device.reset();
  if(val == 11){
    Serial.println("reset successful");
  }

  Serial.print("return value of return function: ");
  Serial.println((device.sciRead(VS1053_REG_STATUS))); // >> 4) & 0x0F);
  uint8_t v = (device.sciRead(VS1053_REG_STATUS) >> 4) & 0x0F;
  Serial.print("v = ");
  Serial.println(v); //should print 4
  //end begin function

  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(50,50);
  
  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

  //edit sineTest in library to verify it played
  int worked = musicPlayer.sineTest(0x07, 1000);    // Make a tone to indicate VS1053 is working
  if(worked == 11)
    Serial.println("works");
}

void loop() {
  
}
