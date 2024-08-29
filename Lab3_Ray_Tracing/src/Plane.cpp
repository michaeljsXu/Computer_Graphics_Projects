#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  // has point and norm, both vectors
  auto true_normal = normal.normalized();
  if (true_normal.dot(ray.direction.normalized()) > 0.0) true_normal = -1.0*true_normal;
  double numer = -1 * (normal.dot(ray.origin - point));
  //(-1 * normal).dot(ray.origin - point);
  double denom = normal.dot(ray.direction);
  if (denom == 0) return false;
  double time = numer/denom;
  if (time<min_t) return false;

  t = time;
  n = true_normal;
  


  return true;
}

