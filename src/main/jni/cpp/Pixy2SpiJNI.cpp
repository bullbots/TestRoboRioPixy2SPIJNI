// Save as "TestRoboRioPixy2SPIJNI.cpp"
#include <jni.h>        // JNI header provided by JDK
#include <iostream>      // C Standard IO Header
#include "Pixy2SpiJNI.h"   // Generated

#include <Pixy2.h>

#include <frc/SPI.h>

#include <stdio.h>
#include <sstream>

// This is the main Pixy object 
Pixy2 pixy(frc::SPI::Port::kOnboardCS0);

// Implementation of the native method pixy2SpiInit()
JNIEXPORT void JNICALL Java_frc_robot_TestRoboRioPixy2SPIJNI_pixy2SpiInit(JNIEnv *env, jobject thisObj) {
   std::cout << "INFO: C++ Pixy2 SPI Init" << std::endl;
   pixy.init();
   return;
}

JNIEXPORT void JNICALL Java_frc_robot_TestRoboRioPixy2SPIJNI_pixy2SpiGetVersion(JNIEnv *env, jobject thisObj) {
   std::cout << "INFO: C++ Pixy2 SPI GetVersion" << std::endl;
   pixy.version->print();
   return;
}

JNIEXPORT void JNICALL Java_frc_robot_TestRoboRioPixy2SPIJNI_pixy2SpiLampOn(JNIEnv *env, jobject thisObj) {
   std::cout << "INFO: C++ Pixy2 SPI LampOn" << std::endl;
   pixy.setLamp(0x01, 0x00);
   return;
}

JNIEXPORT void JNICALL Java_frc_robot_vision_Pixy2SpiJNI_pixy2SpiLampOff(JNIEnv *env, jobject thisObj) {
   pixy.setLamp(0x00, 0x00);


   
JNIEXPORT void JNICALL Java_frc_robot_vision_Pixy2SpiJNI_pixy2SpiGetBlocks(JNIEnv *env, jobject thisObj) {
   // std::cout << "Hello World from pix2 spi get blocks" << std::endl;
   // need multiple reads because of filtering
   pixy.ccc.getBlocks();
   pixy.ccc.getBlocks();
   pixy.ccc.getBlocks();

   // If there are detect blocks, print them!
   if (pixy.ccc.numBlocks)
   {
      std::cout <<  "Detected: " << pixy.ccc.numBlocks << std::endl;
      for (int i=0; i<pixy.ccc.numBlocks; ++i)
      {
         std::cout << "  block " << i << ": ";
         pixy.ccc.blocks[i].print();
      }
   }  
   return;
}

JNIEXPORT jstring JNICALL Java_frc_robot_vision_Pixy2SpiJNI_pixy2SpiGetBlocksString(JNIEnv *env, jobject thisObj) {

   pixy.ccc.getBlocks();
   pixy.ccc.getBlocks();
   pixy.ccc.getBlocks();

   std::stringstream ss;

   if (pixy.ccc.numBlocks){
      for (int i=0; i<pixy.ccc.numBlocks; ++i)
      {
         ss << "block " << i << " : ";
         ss << pixy.ccc.blocks[i].str();
         if(i<pixy.ccc.numBlocks-1){
            ss << std::endl;
         }
      }
   }

   return env->NewStringUTF(ss.str().c_str());
}