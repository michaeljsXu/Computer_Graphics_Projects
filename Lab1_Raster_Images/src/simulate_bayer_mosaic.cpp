#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  
  int px = 0;
  for (int j = 0; j < height; j++)
  {
    for (int i = 0; i < width; i++)
    {
    
      // if col is even xor row is odd
      // it is green
      if ((!(j % 2)) ^ (i % 2))
      {
        bayer[px] = rgb[1+i*3+j*3*width];
      } 
      else
      {
        int offset = (j % 2) ? 0 : 2;
        bayer[px] = rgb[offset+i*3+j*3*width];
      }
      px++;
    }
  }
}
