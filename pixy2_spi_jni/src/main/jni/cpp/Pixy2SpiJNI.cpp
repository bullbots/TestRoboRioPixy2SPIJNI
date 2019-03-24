// Save as "TestRoboRioPixy2SPIJNI.cpp"
#include <jni.h>        // JNI header provided by JDK
#include <iostream>      // C Standard IO Header
#include "pixy2_vision_Pixy2SpiJNI.h"   // Generated

#include <Pixy2.h>

#include <frc/SPI.h>

#include <stdio.h>
#include <sstream>

#define NUM_SENSORS 2

// This are the main Pixy objects
Pixy2 pixy2_list[] = {Pixy2(frc::SPI::Port::kOnboardCS0), Pixy2(frc::SPI::Port::kOnboardCS1)};

// Implementation of the native method pixy2SpiInit()
JNIEXPORT jboolean JNICALL Java_pixy2_vision_Pixy2SpiJNI_pixy2SpiInit(JNIEnv *env, jobject thisObj) {
   std::cout << "INFO: C++ Pixy2 SPI Init" << std::endl;
   jboolean aborted = false;
   for (Pixy2& pixy : pixy2_list) {
      int result = pixy.init();
      if (result != 0) {
         aborted = true;
         break;
      }
   }
   return aborted;
}

JNIEXPORT void JNICALL Java_pixy2_vision_Pixy2SpiJNI_pixy2SpiGetVersion(JNIEnv *env, jobject thisObj) {
   std::cout << "INFO: C++ Pixy2 SPI GetVersion" << std::endl;
   for (Pixy2& pixy : pixy2_list) {
      pixy.version->print();
   }
   return;
}

JNIEXPORT void JNICALL Java_pixy2_vision_Pixy2SpiJNI_pixy2SpiLampOn(JNIEnv *env, jobject thisObj) {
   std::cout << "INFO: C++ Pixy2 SPI LampOn" << std::endl;
   for (Pixy2& pixy : pixy2_list) {
      pixy.setLamp(0x01, 0x00);
   }
   return;
}

JNIEXPORT void JNICALL Java_pixy2_vision_Pixy2SpiJNI_pixy2SpiLampOff(JNIEnv *env, jobject thisObj) {
   std::cout << "INFO: C++ Pixy2 SPI LampOff" << std::endl;
   for (Pixy2& pixy: pixy2_list) {
      pixy.setLamp(0x00, 0x00);
   }
   return;
}

JNIEXPORT void JNICALL Java_pixy2_vision_Pixy2SpiJNI_pixy2SpiGetBlocks(JNIEnv *env, jobject thisObj) {
   // need multiple reads because of filtering
   for (Pixy2& pixy : pixy2_list) {
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
   }
   return;
}

JNIEXPORT jobjectArray JNICALL Java_pixy2_vision_Pixy2SpiJNI_pixy2SpiGetBlocksStrings(JNIEnv *env, jobject thisObj) {
   jobjectArray ret = (jobjectArray) env->NewObjectArray(NUM_SENSORS, env->FindClass("java/lang/String"),
      env->NewStringUTF(""));

   int pixyIndex = 0;
   for (Pixy2& pixy : pixy2_list) {

#ifdef PIXY_DEBUG
      std::cout << "DEBUG: Pixy Index: " << pixyIndex << std::endl;
#endif
      std::stringstream ss;

      pixy.ccc.getBlocks();
      pixy.ccc.getBlocks();
      pixy.ccc.getBlocks();

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

      std::string blocks = ss.str();
#ifdef PIXY_DEBUG
      std::cout << "INFO: Blocks: \"" << blocks << "\"\n";
#endif
      env->SetObjectArrayElement(ret, pixyIndex++, env->NewStringUTF(blocks.c_str()));
   }

   return ret;
}
