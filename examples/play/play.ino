/*!
 *@file play.ino
 *@brief Music Playing Example Program
 *@details  Experimental phenomenon: control MP3 play music, obtain song information
 *@copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 *@version  V1.0
 *@date  2023-10-09
 *@url https://github.com/DFRobot/DFRobot_DF1201S
*/
#include <DFRobot_DF1201S.h>

/* ---------------------------------------------------------------------------------------------------------------------
 *    board   |             MCU                | Leonardo/Mega2560/M0 |    UNO    | ESP8266 | ESP32 |  microbit  |   m0  |
 *     VCC    |            3.3V/5V             |        VCC           |    VCC    |   VCC   |  VCC  |     X      |  vcc  |
 *     GND    |              GND               |        GND           |    GND    |   GND   |  GND  |     X      |  gnd  |
 *     RX     |              TX                |     Serial1 TX1      |     3     |   5/D6  |  D2   |     X      |  tx1  |
 *     TX     |              RX                |     Serial1 RX1      |     2     |   4/D7  |  D3   |     X      |  rx1  |
 * ----------------------------------------------------------------------------------------------------------------------*/
#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
#include "SoftwareSerial.h"
SoftwareSerial DF1201SSerial(2, 3);  //RX  TX
#else
#define DF1201SSerial Serial1
#endif

DFRobot_DF1201S DF1201S;
void setup(void)
{
  Serial.begin(115200);
#if (defined ESP32)
  DF1201SSerial.begin(115200, SERIAL_8N1, /*rx =*/D3, /*tx =*/D2);
#else
  DF1201SSerial.begin(115200);
#endif
  while (!DF1201S.begin(DF1201SSerial)) {
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }
  /*Set volume to 20*/
  DF1201S.setVol(/*VOL = */15);
  Serial.print("VOL:");
  /*Get volume*/
  Serial.println(DF1201S.getVol());
  /*Enter music mode*/
  DF1201S.switchFunction(DF1201S.MUSIC);
  /*Wait for the end of the prompt tone */
  delay(2000);
  /*Set playback mode to "repeat all"*/
  DF1201S.setPlayMode(DF1201S.ALLCYCLE);
  Serial.print("PlayMode:");
  /*Get playback mode*/
  Serial.println(DF1201S.getPlayMode());

  //Set baud rate to 115200(Need to power off and restart, power-down save)
  //DF1201S.setBaudRate(115200);
  //Turn on indicator LED (Power-down save)
  //DF1201S.setLED(true);
  //Turn on the prompt tone (Power-down save) 
  //DF1201S.setPrompt(true);
  //Enable amplifier chip 
  //DF1201S.enableAMP();
  //Disable amplifier chip 
  //DF1201S.disableAMP();
}

void loop()
{
  Serial.println("Start playing");
  /*Start playing*/
  DF1201S.start();
  delay(3000);
  Serial.println("Pause");
  /*Pause*/
  DF1201S.pause();
  delay(3000);
  Serial.println("Next");
  /*Play the next song*/
  DF1201S.next();
  delay(3000);
  Serial.println("Previous");
  /*Play the previous song*/
  DF1201S.last();
  delay(3000);
  Serial.println("Start playing");
  //Fast forward 10S
  DF1201S.fastForward(/*FF = */10);
  //Fast Rewind 10S
  //DF1201S.fastReverse(/*FR = */10);
  //Start the song from the 10th second 
  //DF1201S.setPlayTime(/*Play Time = */10);

  Serial.print("File number:");
  //Get file number
  Serial.println(DF1201S.getCurFileNumber());

  Serial.print("The number of files available to play:");
  //The number of files available to play
  Serial.println(DF1201S.getTotalFile());

  Serial.print("The time length the current song has played:");
  //Get the time length the current song has played 
  Serial.println(DF1201S.getCurTime());

  Serial.print("The total length of the currently-playing song: ");
  //Get the total length of the currently-playing song 
  Serial.println(DF1201S.getTotalTime());
  Serial.print("The name of the currently-playing file: ");
  //Get the name of the playing file 
  Serial.println(DF1201S.getFileName());
  delay(3000);
  //Play the file No.1, the numbers are arranged according to the sequence of the files copied into the U-disk 
  DF1201S.playFileNum(/*File Number = */1);
  //Play the test.mp3 file in test folder 
  //DF1201S.playSpecFile("/test/test.mp3");

  while (1) {
    // if(DF1201S.isPlaying()){
    //   Serial.println("is play");
    // }else{
    //   Serial.println("is stop");
    // }
  }
  /*Delete the currently-playing file */
  //DF1201S.delCurFile();
}
