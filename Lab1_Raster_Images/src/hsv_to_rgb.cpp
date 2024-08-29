#include "hsv_to_rgb.h"
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  if (v == 0) 
  {
    r = 0;
    g = 0;
    b = 0;
    return;
  }

  if (h == 0 || s == 0)
  {
    r = v;
    g = v;
    b = v;
    return;
  }
 
  int h_i = int(std::floor(h/60.0)) % 6;
  double f = h/60.0 -h_i;
  double l = v * (1-s);
  double m = v * (1-f*s);
  double n = v * (1-(1-f)*s);

  if (h_i == 0)
  {
    r = v;
    g = n;
    b = l;
  } else if (h_i == 1)
  {
    r = m;
    g = v;
    b = l;
  } else if (h_i == 2)
  {
    r = l;
    g = v;
    b = m;
  } else if (h_i == 3)
  {
    r = l;
    g = m;
    b = v;
  } else if (h_i == 4)
  {
    r = n;
    g = l;
    b = v;
  } else if (h_i == 5)
  {
    r = v;
    g = l;
    b = m;
  }
}
