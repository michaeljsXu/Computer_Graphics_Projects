#include "rgb_to_hsv.h"
#include <vector>
#include <algorithm>
#include <cmath>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  std::vector<double> rgb_vec = {r, g, b};
  auto max_iter = std::max_element(rgb_vec.begin(), rgb_vec.end());
  auto min_iter = std::min_element(rgb_vec.begin(), rgb_vec.end());

  double c = *max_iter - *min_iter;
  v = *max_iter;

  if (c == 0)
  {
    h = 0;
  } else {
    int max_index = std::distance(rgb_vec.begin(), max_iter);

    if (max_index == 0)
    {
      h = std::fmod((g-b)/c, 6);
    } else if (max_index == 1)
    {
      h = (b-r)/c + 2;
    } else if (max_index == 2)
    {
      h = (r-g)/c +4;
    }

    h *= 60;

    while (h < 0) h += 360.0;
    while (h >= 360) h -= 360.0;
  }

  s = (v == 0) ? 0 : c/v;


}
