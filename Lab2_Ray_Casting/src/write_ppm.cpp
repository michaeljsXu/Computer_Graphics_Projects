#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  
  std::ofstream write_out;
  write_out.open(filename, std::ofstream::out | std::ofstream::trunc);

  if (write_out.fail()) return false; 

  std::string format("P3");
  if (num_channels == 1) format = "P2";

  write_out << format << "\n";
  write_out << width << " " << height << "\n";
  write_out << "255\n"; 

  int max_col = num_channels * width;
  int col = 0;

  for (auto value : data)
  {
    write_out << std::to_string(value) << " ";
    col++;
    if (col >= max_col)
    {
      write_out << "\n";
      col = 0;
    }
  }

  write_out.close();
  return true;
}
