#include "reflect.h"

// fn to 
void cp_col(const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & output,
  const int input_col,
  const int output_col);

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);

  
  int j = width-1;
  for (int i = 0; i < width; i++)
  {
    cp_col(input, width, height, num_channels, reflected, i, j);
    j--;
  }
}

void cp_col(const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & output,
  const int input_col,
  const int output_col)
{
  for (int i = 0; i < height; i++)
  {
    for(int j = 0; j < num_channels; j++)
    {
      output[j+i*width*num_channels+output_col*num_channels] = input[j+i*width*num_channels+input_col*num_channels];
    }
  }
}