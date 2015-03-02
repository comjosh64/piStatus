#define cs   A2
#define dc   D0
#define rst  0
#include "Adafruit_mfGFX.h"    // Core graphics library
#include "Adafruit_ST7735.h" // Hardware-specific library

int debounceDelay = 15;
int button0 = D1;
int button1 = D2;
int button2 = D3;
int button3 = D4;
int button4 = D5;

int updateCount = 0;
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst); // hardware spi

int myHandler(String data);
void printText(String input);
void clear();

String buffer;
int messageCount = 0;
const int maxMessages = 20;
String messages[maxMessages];
int viewing = 0;
bool update = false;


void setup() {
  pinMode(button0, INPUT_PULLDOWN);
  pinMode(button1, INPUT_PULLDOWN);
  pinMode(button2, INPUT_PULLDOWN);
  pinMode(button3, INPUT_PULLDOWN);
  pinMode(button4, INPUT_PULLDOWN);

  Spark.function("prntscr", myHandler);

     tft.initR(INITR_BLACKTAB);

     tft.fillScreen(ST7735_BLACK);

    tft.setCursor(0, 0);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextWrap(true);
    tft.drawLine(0, 0, tft.width()-1, tft.height()-1, ST7735_RED);
    tft.drawLine(tft.width()-1, 0, 0, tft.height()-1, ST7735_RED);
    tft.print("\n\n\n\n\n\n\n\n Waiting for first \n update from network!");

    delay(1500);

  for (int i; i < maxMessages; i++)
  {
      messages[i] = "Message " + i;
      messages[i] = messages[i] + " is blank!\n";
  }

}

void loop() {

  if (debounce(button0))
  {
    printText("Clear\n");
    delay(400);
    clear();
    messageCount = 0;
    viewing = messageCount;
    update = true;
  }
  if (debounce(button1))
  {
    printText("First (Most Recent)\n");
    delay(400);
    viewing = messageCount;
    update = true;
  }
  if (debounce(button2))
  {
    printText("Previous\n");
    delay(400);
    viewing = viewing - 1;
    if (viewing > 0)
    {
        viewing = maxMessages -1;
    }
    update = true;
  }
  if (debounce(button3))
  {
    printText("Next\n");
    delay(400);
    viewing++;
    if (viewing >= maxMessages)
    {
        viewing = 0;
    }
    update = true;
  }
  if (debounce(button4))
  {
    printText("Last (Oldest)\n");
    delay(100);
    viewing = messageCount - 1;
    if (viewing > 0)
    {
        viewing = maxMessages -1;
    }
    update = true;
  }

  if (update == true)
  {
     update = false;
     printText(messages[viewing]);
  }


  delay(10);


}



int myHandler(String data)
{

  messageCount++;
  if (messageCount >= maxMessages)
  {
     messageCount = 0;
  }
  messages[messageCount] = data;

  buffer = "\n" + data;

  if (data == "CLEAR")
  {
    clear();
  }

  if (buffer.length() > 420)
  {
    String temp = buffer.substring(0, 419);
    buffer = temp;
  }
  printText(buffer);
  return 0;


}

void clear()
{
  buffer = " \n";
  for (int i = 0; i < maxMessages; i++)
  {
    messages[i] = "\n";
  }
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

boolean debounce(int pin)
{
    boolean state;
    boolean previousState;

    previousState = digitalRead(pin);  // store button state
    for (int counter = 0; counter < debounceDelay; counter++)
    {
        delay(1);
        state = digitalRead(pin);
        if(state != previousState)
        {
            counter = 0;
            previousState = state;
        }
    }
    if (state == HIGH)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void printText(String input)
{

    char datachar[input.length() + 1];
    input.toCharArray(datachar, input.length() + 1);

    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextWrap(true);
    tft.print(datachar);

}
