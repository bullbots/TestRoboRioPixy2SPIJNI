// Save as "TestRoboRioPixy2SPIJNI.cpp"
#include <jni.h>        // JNI header provided by JDK
#include <iostream>      // C Standard IO Header
#include "TestRoboRioPixy2SPIJNI.h"   // Generated

#include <Pixy2.h>
#include <stdio.h>

// This is the main Pixy object 
Pixy2 pixy;

// Implementation of the native method pixy2SpiInit()
JNIEXPORT void JNICALL Java_frc_robot_TestRoboRioPixy2SPIJNI_pixy2SpiInit(JNIEnv *env, jobject thisObj) {
   std::cout << "Hello World from pixy2 spi init" << std::endl;
   pixy.init();
   return;
}

// Implementation of the native method pixy2_spi_get_blocks()
JNIEXPORT void JNICALL Java_frc_robot_TestRoboRioPixy2SPIJNI_pixy2SpiGetBlocks(JNIEnv *env, jobject thisObj) {
   std::cout << "Hello World from pix2 spi get blocks" << std::endl;
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
