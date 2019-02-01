
package frc.robot;

public class TestRoboRioPixy2SPIJNI {
    static {
       System.loadLibrary("pixy2_spi");
    }
  
    // Declare an instance native method sayHello() which receives no parameter and returns void
    private native void pixy2SpiInit();

    private native void pixy2SpiGetVersion();

    private native void pixy2SpiLampOn();

    private native void pixy2SpiLampOff();
    
    private native String pixy2SpiGetBlocks();
    // Test Driver
    public static void main(String[] args) {
      System.out.println("Hello from java!") ;
      TestRoboRioPixy2SPIJNI testRoboRioPixy2SPIJNI = new TestRoboRioPixy2SPIJNI();
      testRoboRioPixy2SPIJNI.pixy2SpiInit();
      testRoboRioPixy2SPIJNI.pixy2SpiGetVersion();
      testRoboRioPixy2SPIJNI.pixy2SpiLampOn();
      while (true) {
         String visionStuffs = testRoboRioPixy2SPIJNI.pixy2SpiGetBlocks();
         String[] visionParts = visionStuffs.split("\n");
         System.out.println(String.join(",", visionParts));
         
         try {
            Thread.sleep(10);
         } catch (InterruptedException e) {
            e.printStackTrace();
            break;
         }
      }
    }
 }