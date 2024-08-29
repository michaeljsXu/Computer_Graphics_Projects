#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  // has point and norm, both vectors
  double numer = -1 * (normal.dot(ray.origin - point));
  //(-1 * normal).dot(ray.origin - point);
  double denom = normal.dot(ray.direction);
  if (denom == 0) return false;
  double time = numer/denom;
  if (time<min_t) return false;

  t = time;

  auto proj1 = (ray.direction).dot(normal);
  auto proj2 = (ray.direction).dot(-1*normal);

  if (proj1 < proj2) n = -1*normal;
  else n = normal;

  n = normal.normalized();

  return true;
}

