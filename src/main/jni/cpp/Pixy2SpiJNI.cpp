// Save as "TestRoboRioPixy2SPIJNI.cpp"
#include <jni.h>        // JNI header provided by JDK
#include <iostream>      // C Standard IO Header
#include "Pixy2SpiJNI.h"   // Generated

#include <Pixy2.h>
#include <stdio.h>
#include <sstream>

// This is the main Pixy object 
Pixy2 pixy;

// Implementation of the native method pixy2SpiInit()
JNIEXPORT void JNICALL Java_frc_robot_vision_Pixy2SpiJNI_pixy2SpiInit(JNIEnv *env, jobject thisObj) {
   std::cout << "Hello World from pixy2 spi init" << std::endl;
   pixy.init();
   return;
}

JNIEXPORT void JNICALL Java_frc_robot_vision_Pixy2SpiJNI_pixy2SpiGetVersion(JNIEnv *env, jobject thisObj) {
   std::cout << "Hello World from pixy2 spi get version" << std::endl;
   pixy.version->print();
   return;
}

JNIEXPORT void JNICALL Java_frc_robot_vision_Pixy2SpiJNI_pixy2SpiLampOn(JNIEnv *env, jobject thisObj) {
   std::cout << "Hello World from pixy2 spi Lamp On" << std::endl;
   pixy.setLamp(0x01, 0x00);
   return;
}

JNIEXPORT void JNICALL Java_frc_robot_vision_Pixy2SpiJNI_pixy2SpiLampOff(JNIEnv *env, jobject thisObj) {
   std::cout << "Hello World from pixy2 spi Lamp Off" << std::endl;
   pixy.setLamp(0x00, 0x00);
   return;
}

// Implementation of the native method pixy2_spi_get_blocks()
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
