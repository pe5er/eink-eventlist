// E-Ink Event Calendar. Uses a Waveshare ESP32 board and a 7.5" 3-Colour display
// Requirements: Adafruit GFX
// Display Library: https://github.com/ZinggJM/GxEPD2
// Resolution: 640x384

#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#if defined(ESP32)
GxEPD2_3C<GxEPD2_750c, GxEPD2_750c::HEIGHT> display(GxEPD2_750c(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25));
#endif

// Bitmap system. Needs an option added for this panel (we think 640x384, need to check the spec)
#include "bitmaps/Bitmaps3c200x200.h" // 1.54" b/w/r
//#include "bitmaps/Bitmaps3c640x384.h" // 7.5" b/w/r // This doesn't actually exist yet

// 230 x 374 is the bitmap size we want to fill the top of the screen

void setup()
{
  Serial.begin(115200); //Starts serial port for debugging
  Serial.println();
  Serial.println("setup");
  display.init(115200); // uses standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  SPI.end();
  SPI.begin(13, 12, 14, 15); 
  Serial.println("setup done");
  calendar(); //Writes setup text to the screen
}

struct bitmap_pair
{
  const unsigned char* black;
  const unsigned char* red;
};

void loop()
{
}

//const char Text1[] = "Swansea Hackspace";
//const char Text2[] = "Event List";
const char Cal1[] = "Mondays @ 7pm";
const char Cal1b[] = "Open / Social Night";
const char Cal2[] = "2nd & 4th Wednesdays @ 7pm";
const char Cal2b[] = "Crafternoon";
const char Cal3[] = "Tuesday 19th November";
const char Cal3b[] = "Axespace";
const char Cal4[] = "Soon";
const char Cal4b[] = "Your Event!";

void calendar()
{
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;

  //Measure width of each text string
  //display.getTextBounds(Text1, 0, 0, &tbx, &tby, &tbw, &tbh);
  //uint16_t x1 = ((display.width() - tbw) / 2) - tbx;
  //display.getTextBounds(Text2, 0, 0, &tbx, &tby, &tbw, &tbh);
  //uint16_t x2 = ((display.width() - tbw) / 2) - tbx;
  display.getTextBounds(Cal1, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x3 = ((display.width() - tbw) / 2) - tbx;
  display.getTextBounds(Cal1b, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x4 = ((display.width() - tbw) / 2) - tbx;
  display.getTextBounds(Cal2, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x5 = ((display.width() - tbw) / 2) - tbx;
  display.getTextBounds(Cal2b, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x6 = ((display.width() - tbw) / 2) - tbx;
  display.getTextBounds(Cal3, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x7 = ((display.width() - tbw) / 2) - tbx;
  display.getTextBounds(Cal3b, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x8 = ((display.width() - tbw) / 2) - tbx;
  display.getTextBounds(Cal4, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x9 = ((display.width() - tbw) / 2) - tbx;
  display.getTextBounds(Cal4b, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x10 = ((display.width() - tbw) / 2) - tbx;

  bitmap_pair bitmap_pairs[] =
  {
    //{Bitmap3c200x200_black, Bitmap3c200x200_red},
    {Calendar_Bitmap3c200x200_black, Calendar_Bitmap3c200x200_red}
  };
  
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_RED);
    
    display.fillRect(5, 540, 374, 95, GxEPD_WHITE);
    display.fillRect(5, 440, 374, 95, GxEPD_WHITE);
    display.fillRect(5, 340, 374, 95, GxEPD_WHITE);
    display.fillRect(5, 240, 374, 95, GxEPD_WHITE);
    display.fillRect(92, 20, 200, 200, GxEPD_WHITE);
    display.setCursor(x3, (270));
    display.print(Cal1);
    display.setCursor(x4, (300));
    display.print(Cal1b);
    display.setCursor(x5, (370));
    display.print(Cal2);
    display.setCursor(x6, (400));
    display.print(Cal2b);
    display.setCursor(x7, (470));
    display.print(Cal3);
    display.setCursor(x8, (500));
    display.print(Cal3b);
    display.setCursor(x9, (570));
    display.print(Cal4);
    display.setCursor(x10, (600));
    display.print(Cal4b);
    //different image code
    //display.writeImage(bitmap_pairs[0].black, bitmap_pairs[0].red, 420, 92, 200, 200, false, false, true);
    //display.refresh();
    //posx, posy, bitmap, sizex, sizey, colour
    display.drawBitmap(92,20,bitmap_pairs[0].black, 200, 200, GxEPD_BLACK);
    display.drawBitmap(92,20,bitmap_pairs[0].red, 200, 200, GxEPD_RED);
  }
  while (display.nextPage());
  delay(360000);
}
