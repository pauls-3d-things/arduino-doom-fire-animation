#include "ImprovedPerlin.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SPI.h>

#define W 160
#define H 80

Adafruit_ST7735 tft = Adafruit_ST7735(D8, D0, -1);
ImprovedPerlin ip;

uint16_t buffer[W * H];
uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) { return tft.color565(b, g, r); }

void setup(void) {
  SPI.setFrequency(80000000);
  tft.initR(INITR_MINI160x80); // Init ST7735S mini display
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  //   ip.setSeed_unsafe(analogRead(A0));
}

uint32_t c = 0;
uint8_t z = 4;
bool zUp = true;
uint8_t zMax = 128;
void nextZ(void) {
  z = zUp ? z + 1 : z - 1;
  if (z >= zMax) {
    zUp = false;
  } else if (z == 0) {
    zUp = true;
  }
}

float r, g, nr, ng, z1;
void loop(void) {
  z1 = z / 4.0;

  c += 3;

  tft.startWrite();
  tft.setAddrWindow(0, 40, W, H);
  for (uint8_t y = 0; y < H; y += 2) {
    for (uint8_t x = 0; x < W; x++) {
      //   tft.writePixel(buffer[x + (W * y)]);
      nr = (ip.noise2((x * 3 - 80.0) / (16.0 + z1), //
                      (y + c) / (16.0 + z1)) +
            1.0) /
           2.0;
      ng = (ip.noise2((x * 4.0 - 80.0) / (8.0 + z1), //
                      (y + c) / (8.0 + z1)) +
            1.0) /
           2.0;
      g = ng > 0.2 ? 64 * ng : 0;
      g *= (y / 400.0);
      r = nr > 0.3 ? (255 - g) * nr + g : g;
      r *= (y / 300.0);

      tft.writePixel(rgb(r, g, 0));
    } // rgb(100,100,0)
  }
  tft.endWrite();

  //   for (uint8_t y = 0; y < H; y++) {
  //     for (uint8_t x = 0; x < W; x++) {
  //       buffer[x + (y * W)] =
  //           rgb(255 * ip.noise2((x + c) / 160.0, y / 160.0), 0, 0);
  //     }
  //   }
}