#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  
  for (int i = 0; i < width*height; i++)
  {
    double r = double(rgb[i*3]) / 255.0 ;
    double g = double(rgb[i*3+1]) / 255.0;
    double b = double(rgb[i*3+2]) / 255.0;
    double h = 0;
    double s = 0;
    double v = 0;
    rgb_to_hsv(r, g, b, h, s, v);
    h += shift;
    while (h < 0) h += 360.0;
    while (h >= 360.0) h -= 360.0;
    hsv_to_rgb(h, s, v, r, g, b);
    shifted[i*3] = r * 255;
    shifted[i*3+1] = g * 255;
    shifted[i*3+2] = b * 255;
  }
}
