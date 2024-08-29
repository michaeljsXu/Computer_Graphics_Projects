#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  auto obj_ptr = objects[hit_id];
  auto mat_ptr = obj_ptr->material;
  Eigen::Vector3d color = mat_ptr->ka * 0.1;
  Ray light_ray;
  int unused_int;
  Eigen::Vector3d unused_vec;
  for (auto light_ptr : lights)
  {
    double max_time = 0;
    light_ray.origin = ray.origin+t*ray.direction;
    light_ptr->direction(light_ray.origin, light_ray.direction, max_time);
    light_ray.direction = light_ray.direction.normalized();
    light_ray.origin += light_ray.direction * 10e-3;
    double hit_time = 0;
    bool hit = first_hit(light_ray, 0, objects, unused_int, hit_time,unused_vec);
    if (hit && hit_time < max_time) continue;
    
    Eigen::Vector3d h = light_ray.direction - ray.direction.normalized();
    h = h.normalized(); 
    double nDotl = std::max(0.0, n.dot(light_ray.direction));
    double nDoth = std::max(0.0, n.dot(h));
    color += (mat_ptr->kd.array() * nDotl * light_ptr->I.array()
      + mat_ptr->ks.array() * std::pow(nDoth, mat_ptr->phong_exponent) * light_ptr->I.array()).matrix();
  }
  return color;
}
