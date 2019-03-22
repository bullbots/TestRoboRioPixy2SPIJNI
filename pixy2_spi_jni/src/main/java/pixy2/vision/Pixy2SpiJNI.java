
package pixy2.vision;

import java.util.ArrayList;

import java.util.Scanner;
import java.util.concurrent.ArrayBlockingQueue;

import edu.wpi.first.hal.NotifierJNI;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.RobotController;

public class Pixy2SpiJNI {

   static {
      System.loadLibrary("pixy2_spi");
   }

   private final static int NUM_DISTANCE_SENSORS = 2;
  
   private Thread m_acquire_task;
   private static Block[] blocks;
   public static final ArrayBlockingQueue<Block[][]> blocksBuffer = new ArrayBlockingQueue<>(2);

   private class AcquireTask implements Runnable {
      private Pixy2SpiJNI pixy2SpiJNI;
      private double m_expirationTime;
      private final int m_notifier = NotifierJNI.initializeNotifier();
      private final double m_period = 2;

      public AcquireTask(Pixy2SpiJNI pixy2SpiJNI) {
         this.pixy2SpiJNI = pixy2SpiJNI;
      }

      @Override
      public void run() {
         System.out.println("INFO: Begin Pixy2SpiJNI AcquireTask");
         boolean aborted = pixy2SpiJNI.pixy2SpiInit();
         if (!aborted) {
            System.out.println("INFO: Pixy cameras initialized successfully");
            pixy2SpiJNI.pixy2SpiGetVersion();
            pixy2SpiJNI.pixy2SpiLampOff();

            m_expirationTime = RobotController.getFPGATime() * 1e-6 + m_period;
            updateAlarm();

            while(true) {
               long curTime = NotifierJNI.waitForNotifierAlarm(m_notifier);
               if(curTime == 0){
                  break;
               }
      
               m_expirationTime += m_period;
               updateAlarm();
      
               loopfunc();
            }
         } else {
            String warnStr = "Error loading Pixy2 cameras";
            DriverStation.reportWarning(warnStr, false);
         }
      }

      private void loopfunc() {
         System.out.println("INFO: running loopfunc");

         String[] visionStuffs = pixy2SpiJNI.pixy2SpiGetBlocksStrings();
         // for (String visionStr : visionStuffs) {
         //    if (visionStr == null) {
         //       System.out.println("INFO: blocks string was null");
         //    } else {
         //       System.out.println(visionStr);
         //    }
         // }

         // Check all block strings for content
         for (String visionStr : visionStuffs) {
            if (visionStr.equals("")) {
               return;
            }
         }

         int visionStrIndex = 0;
         Block[][] blocksArray = new Block[NUM_DISTANCE_SENSORS][0];
         for (String visionStr : visionStuffs) {
            String[] visionParts = visionStr.split("\n");
            blocks = new Block[visionParts.length];
            int arrayIndex = 0;

            for (String s : visionParts) {
              
               if(!s.isEmpty() && !s.isBlank() && !s.equals(null) && !s.equals("")) {
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
                     blocksArray[visionStrIndex] = blocks;
                  } catch (Exception e){
                     e.printStackTrace();
                  }
               }
            }
         }

         synchronized(blocksBuffer) {
            if (blocksBuffer.remainingCapacity() == 0) {
               blocksBuffer.remove();
            }
            try {
               blocksBuffer.put(blocksArray);
            } catch (InterruptedException e){
               e.printStackTrace();
            }
         }
      }

      private void updateAlarm() {
         NotifierJNI.updateNotifierAlarm(m_notifier, (long) (m_expirationTime * 1e6));
      }
   }

   public Pixy2SpiJNI() {
      m_acquire_task = new Thread(new AcquireTask(this));
      m_acquire_task.setDaemon(true);
      m_acquire_task.start();
   }

   // Declare an instance native method sayHello() which receives no parameter and returns void
   private native boolean pixy2SpiInit();

   private native void pixy2SpiGetVersion();

   private native void pixy2SpiLampOn();

   private native void pixy2SpiLampOff();
   
   private native void pixy2SpiGetBlocks();

   private native String[] pixy2SpiGetBlocksStrings();
}