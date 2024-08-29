#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  return (in.array() - 2.0 * in.dot(n) * n.array()).matrix();  
}
