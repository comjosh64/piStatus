
#define cs   A2
#define dc   D0
#define rst  0

#include "Adafruit_mfGFX.h"    // Core graphics library
#include "Adafruit_ST7735.h" // Hardware-specific library

int updateCount = 0;
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst); // hardware spi

int myHandler(String data);
String buffer;
void setup() {

  Spark.function("prntscr", myHandler);

     tft.initR(INITR_BLACKTAB);

     tft.fillScreen(ST7735_BLACK);

    tft.setCursor(0, 0);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextWrap(true);
    tft.print("\n\n\n\n\n\n\n\nWaiting for first \nupdate from network!");

    tft.drawLine(0, 0, tft.width()-1, tft.height()-1, ST7735_YELLOW);
    tft.drawLine(tft.width()-1, 0, 0, tft.height()-1, ST7735_YELLOW);

    tft.drawPixel(0, tft.height()/2, ST7735_GREEN);
    delay(1500);

}

void loop() {

delay(500);


}



int myHandler(String data)
{


  buffer = "\n" + buffer;
  buffer = data + buffer;
  if (data == "CLEAR")
  {
    buffer = " \n";
  }

  if (buffer.length() > 420)
  {
    String temp = buffer.substring(0, 419);
    buffer = temp;
  }
  char datachar[buffer.length()];
  buffer.toCharArray(datachar, buffer.length());
  tft.fillScreen(ST7735_BLACK);
  testdrawtext(datachar, ST7735_WHITE);
  return 0;


}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}
