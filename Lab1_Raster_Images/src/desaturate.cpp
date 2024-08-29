#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  
  for (int i = 0; i < width*height; i++)
  {
    double r = double(rgb[i*3]) / 255.0 ;
    double g = double(rgb[i*3+1]) / 255.0;
    double b = double(rgb[i*3+2]) / 255.0;
    double h = 0;
    double s = 0;
    double v = 0;
    rgb_to_hsv(r, g, b, h, s, v);
    s *= factor;
    if (s < 0.0) s = 0.0;
    if (s > 1.0) s = 1.0;
    hsv_to_rgb(h, s, v, r, g, b);
    desaturated[i*3] = r * 255;
    desaturated[i*3+1] = g * 255;
    desaturated[i*3+2] = b * 255;
  }
}
