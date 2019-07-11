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


void setup() {
  Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  Adafruit_VS1053_FilePlayer(MOSI, MISO,CLK, BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
 
  Serial.begin(9600);
  if(musicPlayer.playingMusic) {
    Serial.println("broken musicPlayer object");
  } else {
    Serial.println("constructed musicPlayer OK");
  }

  pinMode(CARDCS, OUTPUT);
  digitalWrite(CARDCS, HIGH);

  //sets pinModes
  musicPlayer.begin();
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);
  
  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

  //edit sineTest in library to verify it played
  int worked = musicPlayer.sineTest(0x07, 1000);    // Make a tone to indicate VS1053 is working
  if(worked == 11)
    Serial.println("sineTest OK");

  //plugin stored as char*
  char plug[] = "admix-left.plg";
  
  //check SD card is connected
  if (!SD.begin(CARDCS))
    Serial.println("SD failed, or not present");
  else
    Serial.println("SD Card setup OK");
  Serial.println("***********************************");

  // list files
  SD.printDirectory(SD.open("/"), 0);
  Serial.println("***********************************");

  // Play one file, don't return until complete
  Serial.println(F("Playing track 001"));
  //bool found = musicPlayer.playFullFile(tiger);
  //if(!found)
  //  Serial.println("track name NOT OPENED/FOUND");
  
  Serial.println("probing Adafruit_VS1053_FilePlayer::playFullFile");
  musicPlayer.playFullFile("secret.mp3");
  //this will call Adafruit_VS1053_FilePlayer::startPlayingFile, which will print error statements inside lib
  
  
  
  Serial.println("******************END OF PLAYFILE*****************");





    

  //loading plugin from SD card
  uint16_t val = musicPlayer.loadPlugin(plug);
  if(val == 0xFFFF)
    Serial.println("result 1");
  else
    Serial.println("result 2");
    
}

void loop() {
  
}
