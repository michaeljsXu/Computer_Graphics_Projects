#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  if (num_recursive_calls > 20) return false;
  int hit_id = 0;
  double time = 0;
  Eigen::Vector3d normal;
  bool hit = first_hit(ray, min_t, objects, hit_id, time, normal);
  if (!hit) return false;

  Eigen::Vector3d reflection(0, 0, 0);
  Ray reflected;
  reflected.origin = ray.origin + time * ray.direction;
  reflected.direction = reflect(ray.direction, normal);
  reflected.origin = reflected.origin + reflected.direction * 10e-3;

  auto km = objects[hit_id]->material->km;

  if (!km.isZero(10e-3)
    && raycolor(reflected, 0.0, objects, lights, num_recursive_calls+1, reflection))
  {
    reflection = (reflection.array() * km.array()).matrix();
  }
  
  rgb = blinn_phong_shading(ray, hit_id, time, normal, objects, lights) + reflection;

  return true;
}
