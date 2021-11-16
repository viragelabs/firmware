/***************************************************
  STM32 Support added by Jaret Burkett at OSHlab.com

  This is our library for the Adafruit  ILI9341_2 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#ifndef _ILI9341_2H_
#define _ILI9341_2H_

#include "Arduino.h"
#include <renderer.h>
#include <SPI.h>

#define ILI9341_2_TFTWIDTH  320
#define ILI9341_2_TFTHEIGHT 480

#define ILI9341_2_NOP        0x00     ///< No-op register
#define ILI9341_2_SWRESET    0x01     ///< Software reset register
#define ILI9341_2_RDDID      0x04     ///< Read display identification information
#define ILI9341_2_RDDST      0x09     ///< Read Display Status

#define ILI9341_2_SLPIN      0x10     ///< Enter Sleep Mode
#define ILI9341_2_SLPOUT     0x11     ///< Sleep Out
#define ILI9341_2_PTLON      0x12     ///< Partial Mode ON
#define ILI9341_2_NORON      0x13     ///< Normal Display Mode ON

#define ILI9341_2_RDMODE     0x0A     ///< Read Display Power Mode
#define ILI9341_2_RDMADCTL   0x0B     ///< Read Display MADCTL
#define ILI9341_2_RDPIXFMT   0x0C     ///< Read Display Pixel Format
#define ILI9341_2_RDIMGFMT   0x0D     ///< Read Display Image Format
#define ILI9341_2_RDSELFDIAG 0x0F     ///< Read Display Self-Diagnostic Result

#define ILI9341_2_INVOFF     0x20     ///< Display Inversion OFF
#define ILI9341_2_INVON      0x21     ///< Display Inversion ON
#define ILI9341_2_GAMMASET   0x26     ///< Gamma Set
#define ILI9341_2_DISPOFF    0x28     ///< Display OFF
#define ILI9341_2_DISPON     0x29     ///< Display ON

#define ILI9341_2_CASET      0x2A     ///< Column Address Set
#define ILI9341_2_PASET      0x2B     ///< Page Address Set
#define ILI9341_2_RAMWR      0x2C     ///< Memory Write
#define ILI9341_2_RAMRD      0x2E     ///< Memory Read

#define ILI9341_2_PTLAR      0x30     ///< Partial Area
#define ILI9341_2_MADCTL     0x36     ///< Memory Access Control
#define ILI9341_2_VSCRSADD   0x37     ///< Vertical Scrolling Start Address
#define ILI9341_2_PIXFMT     0x3A     ///< COLMOD: Pixel Format Set

#define ILI9341_2_FRMCTR1    0xB1     ///< Frame Rate Control (In Normal Mode/Full Colors)
#define ILI9341_2_FRMCTR2    0xB2     ///< Frame Rate Control (In Idle Mode/8 colors)
#define ILI9341_2_FRMCTR3    0xB3     ///< Frame Rate control (In Partial Mode/Full Colors)
#define ILI9341_2_INVCTR     0xB4     ///< Display Inversion Control
#define ILI9341_2_DFUNCTR    0xB6     ///< Display Function Control

#define ILI9341_2_PWCTR1     0xC0     ///< Power Control 1
#define ILI9341_2_PWCTR2     0xC1     ///< Power Control 2
#define ILI9341_2_PWCTR3     0xC2     ///< Power Control 3
#define ILI9341_2_PWCTR4     0xC3     ///< Power Control 4
#define ILI9341_2_PWCTR5     0xC4     ///< Power Control 5
#define ILI9341_2_VMCTR1     0xC5     ///< VCOM Control 1
#define ILI9341_2_VMCTR2     0xC7     ///< VCOM Control 2

#define ILI9341_2_RDID1      0xDA     ///< Read ID 1
#define ILI9341_2_RDID2      0xDB     ///< Read ID 2
#define ILI9341_2_RDID3      0xDC     ///< Read ID 3
#define ILI9341_2_RDID4      0xDD     ///< Read ID 4

#define ILI9341_2_GMCTRP1    0xE0     ///< Positive Gamma Correction
#define ILI9341_2_GMCTRN1    0xE1     ///< Negative Gamma Correction


// Color definitions
#define ILI9341_2_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_2_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_2_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_2_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_2_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_2_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_2_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_2_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_2_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_2_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_2_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_2_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_2_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_2_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_2_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_2_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_2_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_2_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_2_PINK        0xF81F


#define MADCTL_2_MY  0x80  ///< Bottom to top
#define MADCTL_2_MX  0x40  ///< Right to left
#define MADCTL_2_MV  0x20  ///< Reverse Mode
#define MADCTL_2_ML  0x10  ///< LCD refresh Bottom to top
#define MADCTL_2_RGB 0x00  ///< Red-Green-Blue pixel order
#define MADCTL_2_BGR 0x08  ///< Blue-Green-Red pixel order
#define MADCTL_2_MH  0x04  ///< LCD refresh right to left


class ILI9341_2 : public Renderer {

 public:

  ILI9341_2(int8_t cs, int8_t mosi, int8_t miso, int8_t sclk, int8_t res, int8_t dc, int8_t bp);

  void init(uint16_t width, uint16_t height);
  /*
  void begin(void);
  void DisplayInit(int8_t p,int8_t size,int8_t rot,int8_t font);
  void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
  void setScrollArea(uint16_t topFixedArea, uint16_t bottomFixedArea);
  void scroll(uint16_t pixels);
  void pushColor(uint16_t color);
  void pushColors(uint16_t *data, uint8_t len, boolean first);
  //void drawImage(const uint8_t* img, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  void fillScreen(uint16_t color);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color);
  void setRotation(uint8_t r);
  void invertDisplay(boolean i);
  uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
  void DisplayOnff(int8_t on);
  void writecommand(uint8_t c);
  void writedata(uint8_t d);
  void write16BitColor(uint16_t color);
  void commandList(uint8_t *addr);
  void hw_spi_init();
  void dim(uint8_t contrast);*/
  uint16_t GetColorFromIndex(uint8_t index);

 private:
  SPIClass *spi2;
  SPISettings sspi2;
  void writecmd(uint8_t d);
  void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void DisplayOnff(int8_t on);
  void setRotation(uint8_t m);
  void DisplayInit(int8_t p,int8_t size,int8_t rot,int8_t font);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  void fillScreen(uint16_t color);
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  void dim(uint8_t dim);


  void spiwrite(uint8_t c);
  void spiwrite16(uint16_t c);
  void spiwrite32(uint32_t c);

  uint8_t  tabcolor;
  uint8_t dimmer;
  int8_t _cs;
  int8_t _mosi;
  int8_t _miso;
  int8_t _sclk;
  int8_t _res;
  int8_t _dc;
  int8_t _bp;
  int8_t _hwspi;
};

#endif
