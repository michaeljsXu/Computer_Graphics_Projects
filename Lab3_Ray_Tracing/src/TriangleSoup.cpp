#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  double time = 0;
  Eigen::Vector3d normal;
  int hit_id = -1;
  bool hit = first_hit(ray, min_t, triangles, hit_id, time, normal);
  if (hit)
  {
    t = time;
    n = normal;
  }
  return hit;
}



