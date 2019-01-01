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

float m = 0; // movement
float r = 0; // red value

void loop(void) {
  m += 2.5;
  tft.startWrite();
  tft.setAddrWindow(0, 40, 160, 40);
  for (uint8_t y = 40; y < 80; y++) {
    for (uint8_t x = 0; x < 160; x++) {
      r = (((y - 40) * (y - 40) / (1200.0)) *
           (sn.noise(x / 8.0, (y + m) / 8.0) + 1.0) / 2.0);
      tft.writePixel(rgb(255 * r, r > .2 ? 16 * r : 0, 0));
    }
  }
  tft.endWrite();
}