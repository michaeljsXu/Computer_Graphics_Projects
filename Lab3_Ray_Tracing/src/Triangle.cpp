#include "Triangle.h"
#include "Plane.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d p0 = std::get<0>(corners);
  Eigen::Vector3d p1 = std::get<1>(corners);
  Eigen::Vector3d p2 = std::get<2>(corners);
  
  Eigen::Matrix3d A;
  Eigen::Matrix3d B;
  Eigen::Matrix3d C;
  Eigen::Matrix3d T;

  A << p0 - p1, p0-p2, ray.direction;
  double inv_A_det = A.determinant();
  if (inv_A_det != 0.0) 
  {
    inv_A_det = 1.0 / inv_A_det;
    T << p0 - p1, p0 - p2, p0 - ray.origin;
    double time = T.determinant() * inv_A_det;
    if (time >= min_t)
    {
      C << p0 - p1, p0 - ray.origin, ray.direction;
      double gamma = C.determinant() * inv_A_det;
      if (gamma >= 0.0 && gamma <= 1.0)
      {
        B << p0 - ray.origin, p0 - p2, ray.direction;
        double beta = B.determinant() * inv_A_det;
        if (beta >= 0.0 && beta + gamma <= 1.0)
        {
          t = time;
          n = (p2 - p0).cross(p1 - p0).normalized();
          if (n.dot(ray.direction.normalized()) > 0.0) n = -1.0*n;
          return true;
        }
      }
    }
  }
  return false;
}