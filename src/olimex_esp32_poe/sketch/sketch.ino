/*********************************************************************************
 *  MIT License
 * 
 *  Copyright (c) 2025 Kaleb Saw - Modified code
 *  Copyright (c) 2022 Gregg E. Berman - Original code (https://github.com/HomeSpan/HomeSpan/blob/master/examples/Other%20Examples/Pixel/Pixel.ino)
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/

// #include <ETH.h>
#include "HomeSpan.h"

// #define DEBUG 1
#define NEOPIXEL_PIN 4
#define NEOPIXEL_NUMPIXELS 7
#define NEOPIXEL_TYPE "GRBW" // "RGBW" or "GRBW" (depending on the type of NeoPixel you are using)

///////////////////////////////

struct NeoPixel_RGBW : Service::LightBulb {      // Addressable single-wire RGBW LED Strand (e.g. NeoPixel)
 
  Characteristic::On power{0, true};
  Characteristic::Hue H{0, true};
  Characteristic::Saturation S{0, true};
  Characteristic::Brightness V{100, true};
  Pixel *pixel;
  int nPixels;
  
  NeoPixel_RGBW(uint8_t pin, int nPixels) : Service::LightBulb()
  {
    V.setRange(5, 100, 1);                      // sets the range of the Brightness to be from a min of 5%, to a max of 100%, in steps of 1%
    pixel=new Pixel(pin, NEOPIXEL_TYPE);        // creates Pixel RGBW LED on specified pin (with order of colors changed to reflect this specific NeoPixel device)
    this->nPixels=nPixels;                      // save number of Pixels in this LED Strand
    power.setVal(0, true);                      // sets the power as off, avoids light from coming back on after power loss
    update();                                   // manually call update() to set pixel with restored initial values
  }

  boolean update() override
  {
    int p=power.getNewVal();
    
    float h=H.getNewVal<float>();       // range = [0,360]
    float s=S.getNewVal<float>();       // range = [0,100]
    float v=V.getNewVal<float>();       // range = [0,100]

#if defined(DEBUG)
    Serial.print("H:");
    Serial.print(h);
    Serial.print(", S:");
    Serial.print(s);
    Serial.print(", V:");
    Serial.print(v);
    Serial.print(", P:");
    Serial.println(p);
#endif

    Pixel::Color color;

    pixel->set(color.HSV(h*p, s*p, v*p), nPixels);       // sets all nPixels to the same HSV color

    return true;  
  }
};

///////////////////////////////

// Initializing everything at start up / after reset:
void setup()
{
  Serial.begin(115200);
  // ETH.begin();           // While connecting over ethernet does allow for successful pairing, if the device has a power loss, the Home app does not reconnect (even after repairing).
                            // See this issue for more details: https://github.com/HomeSpan/HomeSpan/issues/1058

  homeSpan.begin(Category::Lighting, "Pixel LEDs");

  SPAN_ACCESSORY("Pixel LEDs");
    new NeoPixel_RGBW(NEOPIXEL_PIN, NEOPIXEL_NUMPIXELS);
}


void loop()
{
  homeSpan.poll();
}
