
package frc.robot.vision;

import java.util.ArrayList;

import java.util.Scanner;
import java.util.concurrent.ArrayBlockingQueue;

import edu.wpi.first.hal.NotifierJNI;
import edu.wpi.first.wpilibj.RobotController;

public class Pixy2SpiJNI implements Runnable{
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

    public static final ArrayBlockingQueue<Block[]> blocksBuffer = new ArrayBlockingQueue<>(2);

    private double m_expirationTime;
    private final int m_notifier = NotifierJNI.initializeNotifier();
    private final double m_period = .05; //Milliseconds?
    private Pixy2SpiJNI pixy2SpiJNI;

   @Override
   public void run() {
      System.out.println("Hello from java!") ;
      pixy2SpiJNI = new Pixy2SpiJNI();
      pixy2SpiJNI.pixy2SpiInit();
      pixy2SpiJNI.pixy2SpiGetVersion();
      pixy2SpiJNI.pixy2SpiLampOn();

      System.out.println("Starting Thread");
     
      m_expirationTime = RobotController.getFPGATime() * 1e-6 + m_period;
      updateAlarm();

      while(true){
         long curTime = NotifierJNI.waitForNotifierAlarm(m_notifier);
         if(curTime == 0){
            break;
         }

         m_expirationTime += m_period;
         updateAlarm();

         loopfunc();
      }
   }

   private void loopfunc(){
      String visionStuffs = pixy2SpiJNI.pixy2SpiGetBlocksString();
        if(visionStuffs.equals("")){
           return;
        }
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

        /*for (Block b: blocks){
           System.out.println(b.toString());
        }*/
        synchronized(blocksBuffer){
         if(blocksBuffer.remainingCapacity()==0){
            blocksBuffer.remove();
         }
         try{
         blocksBuffer.put(blocks);
         }catch (InterruptedException e){
            e.printStackTrace();
         }
      }
     }

     private void updateAlarm(){
         NotifierJNI.updateNotifierAlarm(m_notifier, (long) (m_expirationTime * 1e6));
     }
   
}