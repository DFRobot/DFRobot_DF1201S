/*!
 *@file DFRobot_PLAY.cpp
 *@brief Define the basic structure of class DFRobot_PLAY, the implementation of basic methods.
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@licence     The MIT License (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2020-12-02
 *@get from https://www.dfrobot.com
 *@https://github.com/DFRobot/DFRobot_PLAY
*/


#ifndef DFROBOT_RP_H
#define DFROBOT_RP_H

#include <Arduino.h>
#include <string.h>

//extern Stream *dbg;
class DFRobot_PLAY
{
public:

  typedef enum{
    MUSIC = 1,  //Music Mode 
    UFDISK,     //Slave mode 
  }eFunction_t;
  
  typedef struct{
   String str;
   uint8_t length;
  }sPacket_t;
  
  typedef enum{
    SINGLECYCLE = 1,  //Repeat one song 
    ALLCYCLE,         //Repeat all 
    SINGLE,           //Play one song only 
    RANDOM,           //Random
    FOLDER,           //Repeat all songs in folder 
    ERROR,             
  }ePlayMode_t;



  DFRobot_PLAY();
  //~DFRobot_PLAY();
  /**
   * @brief init function
   * @return true or false
   */
  bool begin(Stream &s);
  
  /**
   * @brief Set baud rate(Need to power off and restart, power-down save)
   * @param 9600,19200,38400,57600,115200
   * @return true or false
   */
  bool setBaudRate(uint32_t baud);

  /**
   * @brief Set playback mode 
   * @param ePlayMode_t:SINGLECYCLE,ALLCYCLE,SINGLE,RANDOM,FOLDER
   * @return true or false
   */
  bool setPlayMode(ePlayMode_t mode);

  /**
   * @brief Set indicator LED(Power-down save) 
   * @param true or false
   * @return true or false
   */
  bool setLED(bool on);
  
  /**
   * @brief Set the prompt tone(Power-down save) 
   * @param true or false
   * @return true or false
   */
  bool setPrompt(bool on);
  
  /**
   * @brief Set volume 
   * @param vol:0-30
   * @return true or false
  */
  bool setVol(uint8_t vol);
  
  /**
   * @brief Set working mode 
   * @param eFunction_t:MUSIC,RECORD,UFDISK
   * @return true or false
   */
  bool switchFunction(eFunction_t function);
  
  /**
   * @brief Next 
   * @return true or false
   */
  bool next();
  
  /**
   * @brief Previous 
   * @return true or false
   */
  bool last();
  
  /**
   * @brief Play 
   * @return true or false
   */
  bool start();
  
  /**
   * @brief Pause 
   * @return true or false
   */
  bool pause();
  /**
   * @brief Delete the currently-playing file 
   * @return true or false
   */
  bool delCurFile();
  
  /**
   * @brief Play file of the specific path 
   * @param The designated path 
   */
  bool playSpecFile(String str);
  
  /**
   * @brief Play the file of specific number, the numbers are arranged according to the sequences the files copied into the U-disk 
   * @param File number, can be obtained by getCurFileNumber()
   */
  bool playFileNum(int16_t num);

  /**
   * @brief Get volume 
   * @return vol
   */
  uint8_t getVol();

  /**
   * @brief Get palyback mode 
   * @return ePlayMode_t
   */
  ePlayMode_t getPlayMode();
  
  /**
   * @brief Get file number 
   */
  uint16_t getCurFileNumber();
  
  /**
   * @brief Get the number of files available to play 
   */
  uint16_t getTotalFile();
  
  /**
   * @brief Get the time length the current song has played 
   */
  uint16_t getCurTime();
  
  /**
   * @brief Get the total length of the currently-playing song
   */
  uint16_t getTotalTime();
  
  /**
   * @brief Get the name of the playing file 
   */
  String   getFileName();
  
  /**
   * @brief Enable Amplifier chip
   * @return true or false
   */
  bool enableAMP();
  /**
   * @brief Disable Amplifier chip
   * @return true or false
   */
  bool disableAMP();
  
  /**
   * @brief Fast forward the currently-playing song
   * @param second  FF time(Unit: S) 
   */
  bool fastForward(uint16_t second);
  
  /**
   * @brief Fast Rewind the currently-playing song 
   * @param second  FR time(Unit: S)
   */
  bool fastReverse(uint16_t second);
  
  /**
   * @brief Let the currently-playing song start playing from a particular time point 
   * @param second  Fixed time point
   */
  bool setPlayTime(uint16_t second);
private:
  uint8_t getINT(String str);
  uint8_t unicodeToUtf8(uint16_t unicode ,uint8_t * uft8);
  sPacket_t pack(String cmd = " ",String para = " " );
  Stream *_s = NULL;
  void writeATCommand(String command,uint8_t length);
  String readAck(uint8_t len = 4);
  eFunction_t curFunction;
  String atCmd;
  
  uint8_t pauseFlag;
  
};

#endif
