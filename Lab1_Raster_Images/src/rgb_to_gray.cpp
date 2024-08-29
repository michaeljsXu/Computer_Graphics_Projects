#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  
  for(int i = 0; i < width*height; i++)
  {
    gray[i] = 0.2126* double(rgb[3*i]) + 0.7152* double(rgb[3*i + 1]) + 0.0722* double(rgb[3*i + 2]);
  }
}


