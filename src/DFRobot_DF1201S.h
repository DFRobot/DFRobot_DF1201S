/*!
 *@file DFRobot_DF1201S.h
 *@brief Define the basic structure of class DFRobot_DF1201S, the implementation of basic methods.
 *@details This module is a conversion board, which can drive DF1201S DFPlayer PRO MP3 through I2C
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@license     The MIT license (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2021-10-15
 *@url https://github.com/DFRobot/DFRobot_DF1201S
*/


#ifndef DFROBOT_DF1201S_H
#define DFROBOT_DF1201S_H

#include <Arduino.h>
#include <string.h>

//#define ENABLE_DBG
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif
//extern Stream *dbg;
class DFRobot_DF1201S
{
public:

  typedef enum{
    MUSIC = 1,  /**<Music Mode */
    UFDISK,     /**<Slave mode */
  }eFunction_t;
  
  typedef struct{
   String str;
   uint8_t length;
  }sPacket_t;
  
  typedef enum{
    SINGLECYCLE = 1,  /**<Repeat one song */
    ALLCYCLE,         /**<Repeat all */
    SINGLE,           /**<Play one song only */
    RANDOM,           /**<Random*/
    FOLDER,           /**<Repeat all songs in folder */
    ERROR,             
  }ePlayMode_t;



  DFRobot_DF1201S();
  //~DFRobot_DF1201S();
  /**
   * @fn begin
   * @brief init function
   * @param s serial
   * @return Boolean type, Indicates the initialization result
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool begin(Stream& s);
  
  /**
   * @fn isPlaying
   * @brief Detects and refreshes the play status
   * @return Boolean type, Indicates the play result
   * @retval true be playing
   * @retval false has stopped
   */
  bool isPlaying();
  
  /**
   * @fn setBaudRate
   * @brief Set baud rate(Need to power off and restart, power-down save)
   * @param baud 9600,19200,38400,57600,115200
   * @return Boolean type, the result of seted
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool setBaudRate(uint32_t baud);

  /**
   * @fn setPlayMode
   * @brief Set playback mode 
   * @param mode ePlayMode_t:SINGLECYCLE,ALLCYCLE,SINGLE,RANDOM,FOLDER
   * @return Boolean type, the result of seted
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool setPlayMode(ePlayMode_t mode);

  /**
   * @fn setLED
   * @brief Set indicator LED(Power-down save) 
   * @param on true or false
   * @return Boolean type, the result of seted
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool setLED(bool on);
  
  /**
   * @fn setPrompt
   * @brief Set the prompt tone(Power-down save) 
   * @param on true or false
   * @return Boolean type, the result of seted
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool setPrompt(bool on);
  
  /**
   * @fn setVol
   * @brief Set volume 
   * @param vol 0-30
   * @return Boolean type, the result of seted
   * @retval true The setting succeeded
   * @retval false Setting failed
  */
  bool setVol(uint8_t vol);
  
  /**
   * @fn switchFunction
   * @brief Set working mode 
   * @param function eFunction_t:MUSIC,RECORD,UFDISK
   * @return Boolean type, the result of seted
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool switchFunction(eFunction_t function);
  
  /**
   * @fn next
   * @brief Next 
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool next();
  
  /**
   * @fn last
   * @brief Previous 
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool last();
  
  /**
   * @fn start
   * @brief Play 
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool start();
  
  /**
   * @fn pause
   * @brief Pause 
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool pause();
  
  /**
   * @fn delCurFile
   * @brief Delete the currently-playing file 
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool delCurFile();
  
  /**
   * @fn playSpecFile
   * @brief Play file of the specific path 
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool playSpecFile(String str);
  
  /**
   * @fn playFileNum
   * @brief Play the file of specific number, the numbers are arranged according to the sequences the files copied into the U-disk 
   * @param num file number, can be obtained by getCurFileNumber()
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool playFileNum(int16_t num);

  /**
   * @fn getVol
   * @brief Get volume 
   * @return vol volume
   */
  uint8_t getVol();

  /**
   * @fn getPlayMode
   * @brief Get palyback mode 
   * @return ePlayMode_t  Play Mode
   */
  ePlayMode_t getPlayMode();
  
  /**
   * @fn getCurFileNumber
   * @brief Get file number 
   * @return  file number
   */
  uint16_t getCurFileNumber();
  
  /**
   * @fn getTotalFile
   * @brief Get the number of files available to play 
   * @return Total number of files
   */
  uint16_t getTotalFile();
  
  /**
   * @fn getCurTime
   * @brief Get the time length the current song has played 
   * @return Time node
   */
  uint16_t getCurTime();
  
  /**
   * @fn getTotalTime
   * @brief Get the total length of the currently-playing song
   * @return The total number of time
   */
  uint16_t getTotalTime();
  
  /**
   * @fn getFileName
   * @brief Get the name of the playing file 
   * @return A string representing the filename
   */
  String getFileName();
  
  /**
   * @fn enableAMP
   * @brief Enable Amplifier chip
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool enableAMP();
  
  /**
   * @fn disableAMP
   * @brief Disable Amplifier chip
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool disableAMP();
  
  /**
   * @fn fastForward
   * @brief Fast forward the currently-playing song
   * @param second  FF time(Unit: S) 
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool fastForward(uint16_t second);
  
  /**
   * @fn fastReverse
   * @brief Fast Rewind the currently-playing song 
   * @param second  FR time(Unit: S)
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool fastReverse(uint16_t second);
  
  /**
   * @fn setPlayTime
   * @brief Let the currently-playing song start playing from a particular time point 
   * @param second  Fixed time point
   * @return Boolean type, the result of operation
   * @retval true The setting succeeded
   * @retval false Setting failed
   */
  bool setPlayTime(uint16_t second);
private:
  uint16_t getINT(String str);
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
