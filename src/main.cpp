#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SimplexNoise.h>

#define rgb(r, g, b) tft.color565(b, g, r)
Adafruit_ST7735 tft = Adafruit_ST7735(D8, D0, -1);

SimplexNoise sn;

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
      tft.writePixel(rgb(255 * ((sn.noise(x / 8.0, y / 8.0) + 1.0) / 2.0), 0, 0));
    }
  }
  tft.endWrite();
}