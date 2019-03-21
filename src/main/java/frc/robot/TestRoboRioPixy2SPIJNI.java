
package frc.robot;

import java.util.ArrayList;

import java.util.Scanner;

public class TestRoboRioPixy2SPIJNI {
   
    static {
       System.loadLibrary("pixy2_spi");
    }
  
    // Declare an instance native method sayHello() which receives no parameter and returns void
    private native void pixy2SpiInit();

    private native void pixy2SpiGetVersion();

    private native void pixy2SpiLampOn();

    private native void pixy2SpiLampOff();
    
    private native void pixy2SpiGetBlocks();

    private native String pixy2SpiGetBlocksString();

    private static Block[] blocks;
    // Test Driver
    public static void main(String[] args) {
      TestRoboRioPixy2SPIJNI testRoboRioPixy2SPIJNI = new TestRoboRioPixy2SPIJNI();
      testRoboRioPixy2SPIJNI.pixy2SpiInit();
      testRoboRioPixy2SPIJNI.pixy2SpiGetVersion();
      testRoboRioPixy2SPIJNI.pixy2SpiLampOn();
      
      while (true) {
         String visionStuffs = testRoboRioPixy2SPIJNI.pixy2SpiGetBlocksString();
         String[] visionParts = visionStuffs.split("\n");
         blocks = new Block[visionParts.length];
         
         int arrayIndex = 0;
         
        for (String s : visionParts){
            
            if(!s.isEmpty() && !s.isBlank() && !s.equals(null) && !s.equals("")){
               
               try{
               Scanner sc = new Scanner(s);
               sc.next();
               sc.next();
               sc.next();
               sc.next();
               int sig = sc.nextInt();
               sc.next();
               int x = sc.nextInt();
               sc.next();
               int y = sc.nextInt();
               sc.next();
               int width = sc.nextInt();
               sc.next();
               int height = sc.nextInt();
               sc.next();
               int index = sc.nextInt();
               sc.next();
               int age = sc.nextInt();

               blocks[arrayIndex++] = new Block(sig, x, y, width, height, index, age);
               }catch (Exception e){
                  e.printStackTrace();
               }
            }
         }

         for (Block b: blocks){
            System.out.println(b.toString());
         }
         System.out.println("\n");
         try {
            Thread.sleep(10);
         } catch (InterruptedException e) {
            e.printStackTrace();
            break;
         }
      }
    }
 }