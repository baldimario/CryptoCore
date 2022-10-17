#include "RGB.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
    10, 25,
    NEO_GRB +
    NEO_KHZ800); 

RGB::RGB() {
  this->init();
}

void RGB::init() {
  pixels.begin();
  setColor(0, 0, 0);
}

void RGB::setColor(uint8_t r, uint8_t g, uint8_t b) {
  for(int i = 0; i < 10; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b)); 
  }
  pixels.show();
}

void _rgb_init() {
  pixels.begin();
}

void _rgb_set_color(uint8_t r, uint8_t g, uint8_t b) {
  for(int i = 0; i < 10; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b)); 
  }
  pixels.show();
}
//RGB rgb = RGB();