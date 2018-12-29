#include "ImprovedPerlin.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>

#define W 160
#define H 80

Adafruit_ST7735 tft = Adafruit_ST7735(D8, D0, -1);
ImprovedPerlin ip;

uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) { return tft.color565(b, g, r); }
uint32_t c = 0;
float r, g, nr, ng, z1;

void setup(void) {
  tft.initR(INITR_MINI160x80);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
}

void loop(void) {
  c += 3;
  tft.setCursor(30, 20);
  tft.setTextSize(1);
  tft.setTextColor(rgb(4 + c / 3, 4 + c / 3, 4 + c / 3));
  tft.print("@pauls_3d_things");

  tft.startWrite();
  tft.setAddrWindow(0, 40, W, H);
  for (uint8_t y = 0; y < H; y += 2) {
    for (uint8_t x = 0; x < W; x++) {
      nr = (ip.noise2((x * 3.5 - 80.0) / (16.0 + z1), //
                      (y + c) / 18.0) +
            1.0) /
           2.0;
      ng = (ip.noise2((x * 4.0 - 80.0) / (8.0 + z1), //
                      (y + c) / 10.0) +
            1.0) /
           2.0;
      g = ng > 0.2 ? 64 * ng : 0;
      g *= (y / 400.0);
      r = nr > 0.3 ? (255 - g) * nr + g : g;
      r *= (y / 300.0);

      tft.writePixel(rgb(r, g, 0));
    }
  }
  tft.endWrite();
}