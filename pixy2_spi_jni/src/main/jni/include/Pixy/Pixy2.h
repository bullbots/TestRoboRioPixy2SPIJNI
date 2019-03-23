//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// Arduino ICSP SPI link class 

#ifndef _PIXY2_H
#define _PIXY2_H

#include "TPixy2.h"
#include <frc/SPI.h>

#define PIXY_SPI_CLOCKRATE 2000000

class Link2SPI
{
public:
  Link2SPI(frc::SPI::Port port) : spi(port)
  {
    dummyByte[0] = {0};
  }

  int8_t open(uint32_t arg)
  {
    // Note: Original Arduino pixy2 SPI connections
    // SPI.begin();
    // SPI.beginTransaction(SPISettings(PIXY_SPI_CLOCKRATE, MSBFIRST, SPI_MODE3));
    spi.SetClockRate(PIXY_SPI_CLOCKRATE);
    spi.SetMSBFirst();
    spi.SetSampleDataOnTrailingEdge();
    spi.SetClockActiveLow();
    spi.SetChipSelectActiveLow();
	  return 0;
  }
	
  void close()
  {
    // Note: Original Arduino pixy2 SPI connections
    // SPI.endTransaction();
  }
    
  int16_t recv(uint8_t *buf, uint8_t len, uint16_t *cs=NULL)
  {
    uint8_t i;
    if (cs)
      *cs = 0;
    for (i=0; i<len; i++)
    {
      // Note: Original Arduino pixy2 SPI connections
      // buf[i] = SPI.transfer(0x00);
      spi.Transaction(0x00, &buf[i], 1);
      if (cs)
        *cs += buf[i];
    }
    return len;
  }
    
  int16_t send(uint8_t *buf, uint8_t len)
  {
    uint8_t i;
    for (i=0; i<len; i++)
      // Note: Original Arduino pixy2 SPI connections
      // SPI.transfer(buf[i]);
      spi.Transaction(&buf[i], &dummyByte[0], 1);
    return len;
  }

  inline frc::SPI& GetSPI() { return spi; }

protected:
  frc::SPI spi;
  uint8_t dummyByte[1];
};

typedef TPixy2<Link2SPI> Pixy2;

#endif
