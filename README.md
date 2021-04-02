# DFRobot_PLAY

Here comes the DFPlayer Pro-a mini simple but powerful MP3 Player! This MP3 player module supports four controlling modes: Arduino, AT command, on-board buttons, and ADKEY. You can directly press the on-board button to play or switch music without using a controller. By using a USB cable, you can easily copy your favorite songs into this module to play them any where you want, or use it as a sound card for your PC or Raspberry Pi after connecting them together.

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary
1. Playing Music



## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods
```C++
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
   * @brief Set indicator(Power-down save) 
   * @param true or false
   * @return true or false
   */
  bool setLED(bool on);
  
  /**
   * @brief Set prompt tone (Power-down save) 
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
   * @brief Play the file of specific path 
   * @param The designated path 
   */
  bool playSpecFile(String str);
  
  /**
   * @brief Play the file of specific number, the numbers are arranged according to the sequence of the files copied into the U-disk 
   * @param File number, can be obtained by getCurFileNumber()
   */
  bool playFileNum(int16_t num);

  /**
   * @brief Get volume 
   * @return vol
   */
  uint8_t getVol();

  /**
   * @brief Get playback mode 
   * @return ePlayMode_t
   */
  ePlayMode_t getPlayMode();
  
  /**
   * @brief Get file number 
   */
  uint16_t getCurFileNumber();
  
  /**
   * @brief Get numbers of files that are available to play
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
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
ESP8266        |      √       |              |             | 
M0        |      √       |              |             | 


## History

- Date 2020-7-31
- Version V0.1


## Credits

Written by fengli(li.feng@dfrobot.com), 2020.7.31 (Welcome to our [website](https://www.dfrobot.com/))





