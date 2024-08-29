#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  t = std::numeric_limits<double>::max();
  for (int i = 0; i < objects.size(); i++)
  {
    double time = std::numeric_limits<double>::max();
    Eigen::Vector3d normal;
    bool hit = objects[i]->intersect(ray, min_t, time, normal);
    if (hit && time < t)
    {
      t = time;
      hit_id = i;
      n = normal;
    }
  }
  
  return t != std::numeric_limits<double>::max();
}

