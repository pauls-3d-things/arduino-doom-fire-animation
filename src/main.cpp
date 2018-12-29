#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>

Adafruit_ST7735 tft = Adafruit_ST7735(D8, D0, -1);

void setup(void) {
  tft.initR(INITR_MINI160x80);
  tft.fillScreen(ST77XX_BLACK);
}

void loop(void) {
  tft.setCursor(30, 20);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.print("@pauls_3d_things");
}