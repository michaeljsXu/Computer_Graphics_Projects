#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  // has corners, 3 of them
  Eigen::Vector3d basis1 = std::get<1>(corners) - std::get<0>(corners);
  Eigen::Vector3d basis2 = std::get<2>(corners) - std::get<0>(corners);
  Eigen::Vector3d triangle_normal = basis1.cross(basis2);
  double determinant = -1 * ray.direction.dot(triangle_normal);
  double inverse_det = 1.0/determinant;
  Eigen::Vector3d corner_origin = ray.origin - std::get<0>(corners);
  Eigen::Vector3d cross_AO_dir = corner_origin.cross(ray.direction);

  double u_param = basis2.dot(cross_AO_dir) * inverse_det;
  double v_param = -1 * basis1.dot(cross_AO_dir) * inverse_det;
  double time = corner_origin.dot(triangle_normal) * inverse_det;

  if (!(determinant >= 0 && t >= min_t && u_param >= 0 && v_param >= 0 && (u_param + v_param) <= 1.0))
  return false;

  t = time;

  auto proj1 = (ray.direction).dot(triangle_normal);
  auto proj2 = (ray.direction).dot(-1*triangle_normal);

  if (proj1 < proj2) n = triangle_normal.normalized();
  else n = -1*triangle_normal.normalized();

  return true;

}


