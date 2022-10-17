#ifndef _RGB_H
#define _RGB_H

#include <M5Core2.h>
#include <Adafruit_NeoPixel.h>

typedef class RGB {
  public:
    RGB();
    void init();
    void setColor(uint8_t, uint8_t, uint8_t);
} RGB;

void _rgb_init();
void _rgb_set_color(uint8_t, uint8_t, uint8_t); 
extern Adafruit_NeoPixel pixels;
//extern RGB rgb;

#endif


