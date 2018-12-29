#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>

Adafruit_ST7735 tft = Adafruit_ST7735(D8, D0, -1);

void setup(void) {
  tft.initR(INITR_MINI160x80);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
}

void loop(void) {
  tft.startWrite();
  tft.setAddrWindow(0, 0, 160, 80);
  for (uint8_t y = 0; y < 80; y++) {
    for (uint8_t x = 0; x < 160; x++) {
      tft.writePixel(tft.color565(random(255), 0, 0));
    }
  }
  tft.endWrite();
}