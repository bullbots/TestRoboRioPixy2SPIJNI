
package frc.robot;

public class TestRoboRioPixy2SPIJNI {
    static {
       System.loadLibrary("pixy2_spi");
    }
  
    // Declare an instance native method sayHello() which receives no parameter and returns void
    private native void pixy2SpiInit();

    private native void pixy2SpiGetVersion();
    
    private native void pixy2SpiGetBlocks();
    // Test Driver
    public static void main(String[] args) {
      System.out.println("Hello from java!") ;
      TestRoboRioPixy2SPIJNI testRoboRioPixy2SPIJNI = new TestRoboRioPixy2SPIJNI();
      testRoboRioPixy2SPIJNI.pixy2SpiInit();
      testRoboRioPixy2SPIJNI.pixy2SpiGetVersion();
      // testRoboRioPixy2SPIJNI.pixy2SpiGetBlocks();
    }
 }