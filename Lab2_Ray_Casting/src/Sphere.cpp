#include "Sphere.h"
#include "Ray.h"

inline double square(const double& in);

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  // has vector3d as center
  // has double as radius

  double a = square(ray.direction.norm());
  double b = 2.0 * (ray.direction.dot( ray.origin - center));
  double c = square( (ray.origin - center).norm() ) - square(radius);

  double discrim = square(b) - 4.0 * a * c;
  if (discrim <= 0) return false;

  discrim = std::sqrt(discrim);
  
  double t_1 = (-1.0 * b + discrim) / (2*a);
  double t_2 = (-1.0 * b - discrim) / (2*a);

  if (t_1 < min_t && t_2 < min_t) return false;

  if (t_1 >= min_t) t = t_1;
  if (t_2 >= min_t && t_2 < t_1) t = t_2;

  n = ((ray.origin + t * ray.direction)-center).normalized();

  return true;
}

inline double square(const double& in)
{
  return in*in;
}