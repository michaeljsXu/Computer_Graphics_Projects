#include "rotate.h"

std::vector<unsigned char> extract_col(const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  const int col_index);

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  
  int inserted = 0;
  for (int i = width; i > 0; i--)
  {
    for (auto value : extract_col(input, width, height, num_channels, i))
    {
      rotated[inserted] = value;
      inserted++;
    }
  }

}
std::vector<unsigned char> extract_col(const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  const int col_index)
{
  std::vector<unsigned char> col_vec(height*num_channels);
  int pushed = 0;
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < num_channels; j++)
    {
      col_vec[pushed] = input[j+i*width*num_channels+col_index*num_channels];
      pushed++;
    }
  }

  return col_vec;
}