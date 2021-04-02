/*!
 *@file DFRobot_PLAY.cpp
 *@brief Define the basic structure of class DFRobot_PLAY, the implementation of the basic methods
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@licence     The MIT License (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2020-12-02
 *@get from https://www.dfrobot.com
 *@https://github.com/DFRobot/DFRobot_PLAY
*/

#include <DFRobot_PLAY.h>


DFRobot_PLAY::DFRobot_PLAY(){

}

bool DFRobot_PLAY::begin(Stream &s){
   sPacket_t cmd;
   _s = &s;
   cmd = pack();
   
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}

uint8_t DFRobot_PLAY::getVol(){
   String vol = "";
   sPacket_t cmd;
   cmd = pack("VOL","?");
   writeATCommand(cmd.str,cmd.length);
   String str = readAck(12);
   vol += str[7];
   if(str[8] != 0X5D)
         vol += str[8];
   return (uint8_t)atoi(vol.c_str());
}

bool DFRobot_PLAY::setVol(uint8_t vol){
   sPacket_t cmd;
   cmd = pack("VOL",String(vol));
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}

DFRobot_PLAY::ePlayMode_t DFRobot_PLAY::getPlayMode(){

   String playMode = "";
   sPacket_t cmd;
   cmd = pack("PLAYMODE","?");
   writeATCommand(cmd.str,cmd.length);
   String str = readAck(13);
   playMode = str[10];
   //Serial.println(str);
   if(str[11] == '\r'  && str[12] == '\n')
     return (ePlayMode_t)atoi(playMode.c_str());
   else 
     return ERROR;

}
bool DFRobot_PLAY::setBaudRate(uint32_t baud){
   sPacket_t cmd;
   cmd = pack("BAUDRATE",String(baud));
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}
bool DFRobot_PLAY::switchFunction(eFunction_t function){
   sPacket_t cmd;
   cmd = pack("FUNCTION",String(function));
   curFunction = function;
   writeATCommand(cmd.str,cmd.length);
   pauseFlag = 0;
   if(readAck() == "OK\r\n"){
    delay(1500);
    return true;
   } else{
    return false;
   }
}
bool DFRobot_PLAY::setPlayMode(ePlayMode_t mode){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("PLAYMODE",String(mode));
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}
bool DFRobot_PLAY::setLED(bool on){

   sPacket_t cmd;
   String mode;
   if(on == true )
     mode = "ON";
   else 
     mode = "OFF";
   cmd = pack("LED",mode);
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }

}
bool DFRobot_PLAY::setPrompt(bool on){
   sPacket_t cmd;
   String mode;
   if(on == true )
     mode = "ON";
   else 
     mode = "OFF";
   cmd = pack("PROMPT",mode);
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}

bool DFRobot_PLAY::next(){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("PLAY","NEXT");
   writeATCommand(cmd.str,cmd.length);
   pauseFlag = 1;
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}


bool DFRobot_PLAY::last(){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("PLAY","LAST");
   writeATCommand(cmd.str,cmd.length);
   pauseFlag = 1;
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}
bool DFRobot_PLAY::start(){
   sPacket_t cmd;
   cmd = pack("PLAY","PP");



   if(pauseFlag == 1) return false;
   pauseFlag = 1;
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}

bool DFRobot_PLAY::pause(){
   sPacket_t cmd;
   cmd = pack("PLAY","PP");

   if(pauseFlag == 0) return false;
   pauseFlag = 0;
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}


bool DFRobot_PLAY::delCurFile(){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   
   cmd = pack("DEL");
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }

}
bool DFRobot_PLAY::playSpecFile(String str){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("PLAYFILE",str);
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}
bool DFRobot_PLAY::playFileNum(int16_t num){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("PLAYNUM",String(num));
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}
bool DFRobot_PLAY::fastForward(uint16_t second){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;

   String str = "+"+String(second);
   cmd = pack("TIME",str);

   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }


}
bool DFRobot_PLAY::fastReverse(uint16_t second){

   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   String str = "-"+String(second);
   cmd = pack("TIME",str);
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }

}
bool DFRobot_PLAY::setPlayTime(uint16_t second){

   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("TIME",String(second));
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}

uint8_t DFRobot_PLAY::getINT(String str){
   uint8_t numLen = 0;
   uint16_t num =0 ;
   for(uint8_t i = 0; i < str.length();i++){
     if(str[i] != '\r' && str[i+1] != '\n'){
        numLen++;
      } else{ 
         break;
     }
      
   }

    for(uint8_t i = 0; i < numLen;i++){
      
      num = num * 10 + str[i] - '0';
      
    }
    return num;
}
uint16_t DFRobot_PLAY::getCurTime(){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("QUERY","3");
   writeATCommand(cmd.str,cmd.length);
   String str = readAck(6);
   return getINT(str);
   
}
bool DFRobot_PLAY::enableAMP(){

   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("AMP","ON");
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}

bool DFRobot_PLAY::disableAMP(){

   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("AMP","OFF");
   writeATCommand(cmd.str,cmd.length);
   if(readAck() == "OK\r\n"){
    return true;
   } else{
    return false;
   }
}
uint16_t DFRobot_PLAY::getTotalTime(){

   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("QUERY","4");
   
   writeATCommand(cmd.str,cmd.length);
   String str = readAck(6);
   //Serial.println(str);
   return getINT(str);
}
uint16_t DFRobot_PLAY::getCurFileNumber(){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("QUERY","1");
   writeATCommand(cmd.str,cmd.length);
   String str = readAck(6);
   //Serial.println(str);
   return getINT(str);
}
uint16_t DFRobot_PLAY::getTotalFile(){
   if(curFunction != MUSIC) return false;
   sPacket_t cmd;
   cmd = pack("QUERY","2");
   writeATCommand(cmd.str,cmd.length);
   String str = readAck(6);
   //Serial.println(str);
   return getINT(str);
}
String DFRobot_PLAY::getFileName(){
   String name="";
   uint8_t dataUtf8[6];
   if(curFunction != MUSIC) return "error";
   sPacket_t cmd;
   cmd = pack("QUERY","5");
   writeATCommand(cmd.str,cmd.length);
   String str = readAck(0);
   //Serial.println(str);
   for(uint16_t i = 0;i < str.length();i+=2){
     uint16_t dataUnicode = (str[i+1] << 8) | (uint8_t)str[i];
     if(dataUnicode == 0x0a0d) break;
     //Serial.println((uint8_t)str[i+1],HEX);
     //Serial.println((uint8_t)str[i],HEX);
     //Serial.println(dataUnicode,HEX);
     //Serial.print(" ");
     uint8_t len = unicodeToUtf8(dataUnicode,dataUtf8);
     //Serial.println(len);
      char *cDataUtf8 =(char *)dataUtf8;
      
      for(uint8_t i=0;i < len ;i++){
        name += cDataUtf8[i];
        //Serial.print(cDataUtf8[i],HEX);
     }
   }
   return name;
}
uint8_t DFRobot_PLAY::unicodeToUtf8(uint16_t unicode ,uint8_t * uft8){
    //Serial.println(unicode,HEX);
    if ( unicode <= 0x0000007F )
    {
        // * U-00000000 - U-0000007F:  0xxxxxxx
        *uft8     = (unicode & 0x7F);
        return 1;
    }
    else if ( unicode >= 0x00000080 && unicode <= 0x000007FF )
    {
        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
        *(uft8+1) = (unicode & 0x3F) | 0x80;
        *uft8     = ((unicode >> 6) & 0x1F) | 0xC0;
        return 2;
    }
    else if ( unicode >= 0x00000800 && unicode <= 0x0000FFFF )
    {
        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
        *(uft8+2) = (unicode & 0x3F) | 0x80;
        *(uft8+1) = ((unicode >>  6) & 0x3F) | 0x80;
        *uft8     = ((unicode >> 12) & 0x0F) | 0xE0;
        return 3;
    }
    else if ( unicode >= 0x00010000 && unicode <= 0x001FFFFF )
    {
        // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(uft8+3) = (unicode & 0x3F) | 0x80;
        *(uft8+2) = ((unicode >>  6) & 0x3F) | 0x80;
        *(uft8+1) = ((unicode >> 12) & 0x3F) | 0x80;
        *uft8     = ((unicode >> 18) & 0x07) | 0xF0;
        return 4;
    }
    else if ( unicode >= 0x00200000 && unicode <= 0x03FFFFFF )
    {
        // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(uft8+4) = (unicode & 0x3F) | 0x80;
        *(uft8+3) = ((unicode >>  6) & 0x3F) | 0x80;
        *(uft8+2) = ((unicode >> 12) & 0x3F) | 0x80;
        *(uft8+1) = ((unicode >> 18) & 0x3F) | 0x80;
        *uft8     = ((unicode >> 24) & 0x03) | 0xF8;
        return 5;
    }
    else if ( unicode >= 0x04000000 && unicode <= 0x7FFFFFFF )
    {
        // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(uft8+5) = (unicode & 0x3F) | 0x80;
        *(uft8+4) = ((unicode >>  6) & 0x3F) | 0x80;
        *(uft8+3) = ((unicode >> 12) & 0x3F) | 0x80;
        *(uft8+2) = ((unicode >> 18) & 0x3F) | 0x80;
        *(uft8+1) = ((unicode >> 24) & 0x3F) | 0x80;
        *uft8     = ((unicode >> 30) & 0x01) | 0xFC;
        return 6;
    }
  
    return 0;
}


DFRobot_PLAY::sPacket_t DFRobot_PLAY::pack(String cmd ,String para){
  sPacket_t pack;
  atCmd = "";
  atCmd += "AT";
  if(cmd != " "){
   atCmd += "+";
   atCmd += cmd;
  }
 
  if(para != " "){
   atCmd += "=";
   atCmd += para;
  }
  atCmd += "\r\n";
  pack.str = atCmd;
  pack.length = atCmd.length();
  return pack;
}
void DFRobot_PLAY::writeATCommand(String command,uint8_t length){
    uint8_t data[40];
    while(_s->available()) {
         _s->read();
    }
    for(uint8_t i=0;i<length;i++)
      data[i] = command[i];
    _s->write(data,length);
}



String DFRobot_PLAY::readAck(uint8_t len){

  String str="";
  size_t offset = 0,left = len;
  long long curr = millis();
  if(len == 0){
    while(1) {
      if(_s->available()) {
        str += (char)_s->read();
        offset++;
      }
      if((str[offset - 1]) == '\n' && (str[offset - 2] == '\r')) break;
      if(millis() - curr > 1000) {
        return "error";
        break;
      }
    }

  } else {
    while(left) {
      if(_s->available()) {
         str += (char)_s->read();
        left--;
        offset++;
      }
      if(str[offset - 1] == '\n' && str[offset - 2] == '\r') break;
      if(millis() - curr > 1000) {
        return "error";
        break;
      }
  }
  str[len]=0;
  }
  return str;
}




