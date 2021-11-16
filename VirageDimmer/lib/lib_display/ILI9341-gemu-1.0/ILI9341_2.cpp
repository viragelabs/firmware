/*!
* @file ILI9341_2.cpp
*
* @mainpage Adafruit ILI9341 TFT Displays
*
* @section intro_sec Introduction
*
* This is the documentation for Adafruit's ILI9341 driver for the
* Arduino platform.
*
* This library works with the Adafruit 2.8" Touch Shield V2 (SPI)
*    http://www.adafruit.com/products/1651
*
* Adafruit 2.4" TFT LCD with Touchscreen Breakout w/MicroSD Socket - ILI9341
*    https://www.adafruit.com/product/2478
*
* 2.8" TFT LCD with Touchscreen Breakout Board w/MicroSD Socket - ILI9341
*    https://www.adafruit.com/product/1770
*
* 2.2" 18-bit color TFT LCD display with microSD card breakout - ILI9340
*    https://www.adafruit.com/product/1770
*
* TFT FeatherWing - 2.4" 320x240 Touchscreen For All Feathers
*    https://www.adafruit.com/product/3315
*
* These displays use SPI to communicate, 4 or 5 pins are required
* to interface (RST is optional).
*
* Adafruit invests time and resources providing this open source code,
* please support Adafruit and open-source hardware by purchasing
* products from Adafruit!
*
* @section dependencies Dependencies
*
* This library depends on <a href="https://github.com/adafruit/Adafruit_GFX">
* Adafruit_GFX</a> being present on your system. Please make sure you have
* installed the latest version before using this library.
*
* @section author Author
*
* Written by Limor "ladyada" Fried for Adafruit Industries.
*
* @section license License
*
* BSD license, all text here must be included in any redistribution.
*
*/

#ifdef ESP32
#include "ILI9341_2.h"
#include <limits.h>


// ESP32 uses 2. SPI BUS, ESP8266 uses software spi
#ifdef ESP32
#undef ILI9341_2_DIMMER
#define ILI9341_2_DIMMER
#undef ESP32_PWM_CHANNEL
#define ESP32_PWM_CHANNEL 1
#define ILI9341_2_HWSPI
#endif


const uint16_t ili9341_2_colors[]={ILI9341_2_BLACK,ILI9341_2_WHITE,ILI9341_2_RED,ILI9341_2_GREEN,ILI9341_2_BLUE,ILI9341_2_CYAN,ILI9341_2_MAGENTA,\
  ILI9341_2_YELLOW,ILI9341_2_NAVY,ILI9341_2_DARKGREEN,ILI9341_2_DARKCYAN,ILI9341_2_MAROON,ILI9341_2_PURPLE,ILI9341_2_OLIVE,\
ILI9341_2_LIGHTGREY,ILI9341_2_DARKGREY,ILI9341_2_ORANGE,ILI9341_2_GREENYELLOW,ILI9341_2_PINK};

uint16_t ILI9341_2::GetColorFromIndex(uint8_t index) {
  if (index>=sizeof(ili9341_2_colors)/2) index=0;
  return ili9341_2_colors[index];
}

static const uint8_t PROGMEM ili9341_2_initcmd[] = {
  0xEF, 3, 0x03, 0x80, 0x02,
  0xCF, 3, 0x00, 0xC1, 0x30,
  0xED, 4, 0x64, 0x03, 0x12, 0x81,
  0xE8, 3, 0x85, 0x00, 0x78,
  0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
  0xF7, 1, 0x20,
  0xEA, 2, 0x00, 0x00,
  ILI9341_2_PWCTR1  , 1, 0x23,             // Power control VRH[5:0]
  ILI9341_2_PWCTR2  , 1, 0x10,             // Power control SAP[2:0];BT[3:0]
  ILI9341_2_VMCTR1  , 2, 0x3e, 0x28,       // VCM control
  ILI9341_2_VMCTR2  , 1, 0x86,             // VCM control2
  ILI9341_2_MADCTL  , 1, 0x48,             // Memory Access Control
  ILI9341_2_VSCRSADD, 1, 0x00,             // Vertical scroll zero
  ILI9341_2_PIXFMT  , 1, 0x55,
  ILI9341_2_FRMCTR1 , 2, 0x00, 0x18,
  ILI9341_2_DFUNCTR , 3, 0x08, 0x82, 0x27, // Display Function Control
  0xF2, 1, 0x00,                         // 3Gamma Function Disable
  ILI9341_2_GAMMASET , 1, 0x01,             // Gamma curve selected
  ILI9341_2_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
    0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
  ILI9341_2_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
    0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
  ILI9341_2_SLPOUT  , 0x80,                // Exit Sleep
  ILI9341_2_DISPON  , 0x80,                // Display on
//  ILI9341_2_DISPOFF  , 0x80,                // Display on
  0x00                                   // End of list
};


ILI9341_2::ILI9341_2(int8_t cs, int8_t mosi, int8_t miso, int8_t sclk, int8_t res, int8_t dc, int8_t bp) : Renderer(ILI9341_2_TFTWIDTH, ILI9341_2_TFTHEIGHT) {
  _cs   = cs;
  _mosi  = mosi;
  _miso  = miso;
  _sclk = sclk;
  _res = res;
  _dc = dc;
  _bp = bp;
  _hwspi = 0;
}

#define ILI9341_2_CS_LOW digitalWrite( _cs, LOW);
#define ILI9341_2_CS_HIGH digitalWrite( _cs, HIGH);


void ILI9341_2::writecmd(uint8_t d) {
  digitalWrite( _dc, LOW);
#ifdef ILI9341_2_HWSPI
  spi2->write(d);
#else
  spiwrite(d);
#endif
  digitalWrite( _dc, HIGH);
}

void ILI9341_2::init(uint16_t width, uint16_t height) {
  //sspi2 = SPISettings(2500000, MSBFIRST, SPI_MODE3);

#ifdef ILI9341_2_HWSPI
  spi2 = new SPIClass(HSPI);
  spi2->setDataMode(SPI_MODE3);
  spi2->setBitOrder(MSBFIRST);
  spi2->setFrequency(40000000);
  spi2->begin(_sclk, _miso, _mosi, -1);
#else
  pinMode(_mosi, OUTPUT);
  digitalWrite(_mosi,HIGH);
  pinMode(_sclk, OUTPUT);
  digitalWrite(_sclk,LOW);
  pinMode(_miso, INPUT);
#endif

  pinMode(_cs, OUTPUT);
  digitalWrite(_cs,HIGH);
  pinMode(_dc, OUTPUT);
  digitalWrite(_dc,HIGH);
  pinMode(_bp, OUTPUT);
  digitalWrite(_bp,HIGH);
  pinMode(_res, OUTPUT);
  digitalWrite(_res,HIGH);


  if (_bp>=0) {
#ifdef ILI9341_2_DIMMER
    ledcSetup(ESP32_PWM_CHANNEL,4000,8);
    ledcAttachPin(_bp,ESP32_PWM_CHANNEL);
    ledcWrite(ESP32_PWM_CHANNEL,128);
#else
    pinMode(_bp, OUTPUT);
#endif
  }

  pinMode(_res, OUTPUT);
  digitalWrite(_res, HIGH);
  delay(100);
  digitalWrite(_res, LOW);
  delay(100);
  digitalWrite(_res, HIGH);
  delay(200);

  uint8_t        cmd, x, numArgs;
  const uint8_t *addr = ili9341_2_initcmd;

  while ((cmd = pgm_read_byte(addr++)) > 0) {
      ILI9341_2_CS_LOW
      writecmd(cmd);
      x = pgm_read_byte(addr++);
      numArgs = x & 0x7F;

#ifdef ILI9341_2_HWSPI
      while (numArgs--) spi2->write(pgm_read_byte(addr++));
#else
      while (numArgs--) spiwrite(pgm_read_byte(addr++));
#endif

      ILI9341_2_CS_HIGH
      if(x & 0x80) delay(120);
  }

//  endWrite();
}

void ILI9341_2::DisplayInit(int8_t p,int8_t size,int8_t rot,int8_t font) {
  setRotation(rot);
  setTextFont(font&3);
  setTextSize(size&7);
  setTextColor(ILI9341_2_WHITE,ILI9341_2_BLACK);
  setCursor(0,0);
  fillScreen(ILI9341_2_BLACK);
}

void ILI9341_2::setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    uint32_t xa = ((uint32_t)x << 16) | (x+w-1);
    uint32_t ya = ((uint32_t)y << 16) | (y+h-1);
    writecmd(ILI9341_2_CASET); // Column addr set
#ifdef ILI9341_2_HWSPI
    spi2->write32(xa);
#else
    spiwrite32(xa);
#endif
    writecmd(ILI9341_2_PASET); // Row addr set

#ifdef ILI9341_2_HWSPI
    spi2->write32(ya);
#else
    spiwrite32(ya);
#endif
    writecmd(ILI9341_2_RAMWR); // write to RAM
}

void ILI9341_2::drawPixel(int16_t x, int16_t y, uint16_t color) {


  if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;

  ILI9341_2_CS_LOW

  setAddrWindow(x,y,1,1);

#ifdef ILI9341_2_HWSPI
  spi2->write16(color);
#else
  spiwrite16(color);
#endif
  ILI9341_2_CS_HIGH

}

void ILI9341_2::setRotation(uint8_t m) {
    rotation = m % 4; // can't be higher than 3
    switch (rotation) {
        case 0:
            m = (MADCTL_2_MX | MADCTL_2_BGR);
            _width  = ILI9341_2_TFTWIDTH;
            _height = ILI9341_2_TFTHEIGHT;
            break;
        case 1:
            m = (MADCTL_2_MV | MADCTL_2_BGR);
            _width  = ILI9341_2_TFTHEIGHT;
            _height = ILI9341_2_TFTWIDTH;
            break;
        case 2:
            m = (MADCTL_2_MY | MADCTL_2_BGR);
            _width  = ILI9341_2_TFTWIDTH;
            _height = ILI9341_2_TFTHEIGHT;
            break;
        case 3:
            m = (MADCTL_2_MX | MADCTL_2_MY | MADCTL_2_MV | MADCTL_2_BGR);
            _width  = ILI9341_2_TFTHEIGHT;
            _height = ILI9341_2_TFTWIDTH;
            break;
    }

    ILI9341_2_CS_LOW
    writecmd(ILI9341_2_MADCTL);
    spiwrite(m);
    ILI9341_2_CS_HIGH
}

void ILI9341_2::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {

  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;
  if((y+h-1) >= _height) h = _height-y;

  ILI9341_2_CS_LOW

  setAddrWindow(x, y, 1, h);

  while (h--) {
#ifdef ILI9341_2_HWSPI
    spi2->write16(color);
#else
    spiwrite16(color);
#endif
  }

  ILI9341_2_CS_HIGH

}

void ILI9341_2::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {

  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;
  if((x+w-1) >= _width)  w = _width-x;

  ILI9341_2_CS_LOW

  setAddrWindow(x, y, w, 1);

  while (w--) {
#ifdef ILI9341_2_HWSPI
    spi2->write16(color);
#else
    spiwrite16(color);
#endif
  }

  ILI9341_2_CS_HIGH
}

void ILI9341_2::fillScreen(uint16_t color) {
  fillRect(0, 0,  _width, _height, color);
}

// fill a rectangle
void ILI9341_2::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {

  // rudimentary clipping (drawChar w/big text requires this)
  if((x >= _width) || (y >= _height)) return;
  if((x + w - 1) >= _width)  w = _width  - x;
  if((y + h - 1) >= _height) h = _height - y;

  ILI9341_2_CS_LOW

  setAddrWindow(x, y, w-1, h-1);

  for (y=h; y>0; y--) {
    for (x=w; x>0; x--) {
#ifdef ILI9341_2_HWSPI
      spi2->write16(color);
#else
      spiwrite16(color);
#endif
    }
  }
  ILI9341_2_CS_HIGH
}

void ILI9341_2::DisplayOnff(int8_t on) {
  if (on) {
    writecmd(ILI9341_2_DISPON);    //Display on
    if (_bp>=0) {
#ifdef ILI9341_2_DIMMER
      ledcWrite(ESP32_PWM_CHANNEL,dimmer);
#else
      digitalWrite(_bp,HIGH);
#endif
    }
  } else {
    writecmd(ILI9341_2_DISPOFF);
    if (_bp>=0) {
#ifdef ILI9341_2_DIMMER
      ledcWrite(ESP32_PWM_CHANNEL,0);
#else
      digitalWrite(_bp,LOW);
#endif
    }
  }
}

// dimmer 0-100
void ILI9341_2::dim(uint8_t dim) {
  dimmer = dim;
  if (dimmer>15) dimmer=15;
  dimmer=((float)dimmer/15.0)*255.0;
#ifdef ESP32
  ledcWrite(ESP32_PWM_CHANNEL,dimmer);
#endif
}


void ILI9341_2::spiwrite(uint8_t c) {

#ifdef ILI9341_2_HWSPI
  spi2->write(c);
#else
  for (uint8_t bit = 0x80; bit; bit >>= 1) {
	   digitalWrite(_sclk, LOW);
	    if (c & bit) digitalWrite(_mosi, HIGH);
	    else        digitalWrite(_mosi, LOW);
	    digitalWrite(_sclk, HIGH);
  }
#endif

}

void ILI9341_2::spiwrite16(uint16_t c) {
#ifdef ILI9341_2_HWSPI
    spi2->write16(c);
#else
    spiwrite(c>>8);
    spiwrite(c);
#endif
}

void ILI9341_2::spiwrite32(uint32_t c) {
#ifdef ILI9341_2_HWSPI
    spi2->write32(c);
#else
    spiwrite(c>>24);
    spiwrite(c>>16);
    spiwrite(c>>8);
    spiwrite(c);
#endif
}

#endif
