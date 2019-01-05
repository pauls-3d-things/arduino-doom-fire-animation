#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <SimplexNoise.h>
#include <doom_image.h>

#define rgb(r, g, b) tft.color565(b, g, r)
Adafruit_ST7735 tft = Adafruit_ST7735(D8, D0, -1);

float m = 0; // movement
float r = 0; // red value
SimplexNoise sn;
void fireSimplexNosie(void) {
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

const uint16_t doomColorMap[36] = {
    //
    rgb(0x00, 0x00, 0x00), // #000000
    rgb(0x1f, 0x07, 0x07), // #1f0707
    rgb(0x2f, 0x0f, 0x07), // #2f0f07
    rgb(0x47, 0x0f, 0x07), // #470f07
    rgb(0x57, 0x17, 0x07), // #571707
    rgb(0x67, 0x1f, 0x07), // #671f07
    rgb(0x77, 0x1f, 0x07), // #771f07
    rgb(0x8f, 0x27, 0x07), // #8f2707
    rgb(0x9f, 0x2f, 0x07), // #9f2f07
    rgb(0xaf, 0x3f, 0x07), // #af3f07
    rgb(0xbf, 0x47, 0x07), // #bf4707
    rgb(0xc7, 0x47, 0x07), // #c74707
    rgb(0xDF, 0x4F, 0x07), // #DF4F07
    rgb(0xDF, 0x57, 0x07), // #DF5707
    rgb(0xDF, 0x57, 0x07), // #DF5707
    rgb(0xD7, 0x5F, 0x07), // #D75F07
    rgb(0xD7, 0x67, 0x0F), // #D7670F
    rgb(0xcf, 0x6f, 0x0f), // #cf6f0f
    rgb(0xcf, 0x77, 0x0f), // #cf770f
    rgb(0xcf, 0x7f, 0x0f), // #cf7f0f
    rgb(0xCF, 0x87, 0x17), // #CF8717
    rgb(0xC7, 0x87, 0x17), // #C78717
    rgb(0xC7, 0x8F, 0x17), // #C78F17
    rgb(0xC7, 0x97, 0x1F), // #C7971F
    rgb(0xBF, 0x9F, 0x1F), // #BF9F1F
    rgb(0xBF, 0x9F, 0x1F), // #BF9F1F
    rgb(0xBF, 0xA7, 0x27), // #BFA727
    rgb(0xBF, 0xA7, 0x27), // #BFA727
    rgb(0xBF, 0xAF, 0x2F), // #BFAF2F
    rgb(0xB7, 0xAF, 0x2F), // #B7AF2F
    rgb(0xB7, 0xB7, 0x2F), // #B7B72F
    rgb(0xB7, 0xB7, 0x37), // #B7B737
    rgb(0xCF, 0xCF, 0x6F), // #CFCF6F
    rgb(0xDF, 0xDF, 0x9F), // #DFDF9F
    rgb(0xEF, 0xEF, 0xC7), // #EFEFC7
    rgb(0xFF, 0xFF, 0xFF)  // #FFFFFF
};

uint8_t firePixels[80][160]; // only stores the pixel "temperature"
void setupFirepixels(void) {
  for (uint8_t y = 0; y < 80; y++) {
    for (uint8_t x = 0; x < 160; x++) {
      // last row is hot
      firePixels[y][x] = y == 79 ? 35 : 0;
    }
  }
}

uint16_t c = 0;
void fireDoom(void) {
  c++;
  // recalculate fire
  for (uint8_t y = 0; y < 79; y++) {
    for (uint8_t x = 0; x < 160; x++) {
      uint8_t wind = x + random(2);
      wind = wind >= 160 ? wind - 160 : wind;
      uint8_t speed = y + random(2);
      speed = speed >= 80 ? 79 : speed;
      firePixels[y][x] = firePixels[speed][wind] - random(2);
      firePixels[y][x] =
          firePixels[y][x] > 35 ? 0 : firePixels[y][x]; // fix overflow
    }
    delay(0);
  }

  // draw fire
  tft.startWrite();
  tft.setAddrWindow(0, 0, 160, 80);
  for (uint8_t y = 0; y < 80; y++) {
    for (uint8_t x = 0; x < 160; x++) {
      if (firePixels[y][x]) { // draw fire
        tft.writePixel(doomColorMap[firePixels[y][x]]);
      } else if (y < 77) { // draw DOOM logo (it is only 77 pixels high)
        uint16_t o = (y * 160 + x) * 3; // offset because of rgb data
        tft.writePixel(
            rgb(GO_Doom_s_rgb[o], GO_Doom_s_rgb[o + 1], GO_Doom_s_rgb[o + 2]));
      }
    }
  }
  tft.endWrite();
}

void setup(void) {
  setupFirepixels();
  tft.initR(INITR_MINI160x80);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(30, 12);
  tft.setTextSize(1);
  tft.setTextColor(doomColorMap[16]);
  tft.print("@pauls_3d_things");
}

void loop(void) { fireDoom(); }