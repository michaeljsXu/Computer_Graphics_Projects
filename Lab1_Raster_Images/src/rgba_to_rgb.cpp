#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  
  auto rgba_iter = rgba.begin();
  auto rgb_iter = rgb.begin();
  int index = 0;

  while(rgb_iter != rgb.end())
  {
    if (index == 3)
    {
      index = 0;
    }
    else
    {
      *rgb_iter = *rgba_iter;
      index++;
      rgb_iter++;
    }

    rgba_iter++;
  }
}
