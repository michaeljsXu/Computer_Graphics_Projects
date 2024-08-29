#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ray.origin = camera.e;

  double azimuth = (camera.width / width) * (j + 0.5) - camera.width / 2.0;
  double altitude = (camera.height / height) * (height - i + 0.5) - camera.height / 2.0;

  Eigen::Matrix3d direction_matrix;
  direction_matrix.col(0) = camera.u;
  direction_matrix.col(1) = camera.v;
  direction_matrix.col(2) = camera.w;

  Eigen::Vector3d direction_vector;
  direction_vector[0] = azimuth;
  direction_vector[1] = altitude;
  direction_vector[2] = -1 * camera.d; 

  ray.direction = direction_matrix * direction_vector;
}

