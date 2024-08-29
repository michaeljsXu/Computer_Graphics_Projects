#include "demosaic.h"
#include <iostream>

inline void getCellInfo(const int &input, const int &width, int &out_color, int &out_row, int &out_col);
inline int getRow(const int &input, const int &width);
inline int getCol(const int &input, const int &width);
inline int getIndex(const int &row, const int &col, const int &width);
inline unsigned char getG(const std::vector<unsigned char> & bayer,const int &row, const int &col, const int &width, const int& height);
inline unsigned char getRB(const std::vector<unsigned char> & bayer,const int &row, const int &col, const int &width, const int& height);

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);

  for (int i = 0; i < width*height; i++)
  {
    int color = 0;
    int row = 0;
    int col = 0;
    getCellInfo(i, width, color, row, col);
    
    for (int j = 0; j < 3; j++)
    {
      if (j == color) rgb[i*3+j] = bayer[i];
      else rgb[i*3+j] = (j == 1) ? getG(bayer, row, col, width, height) : getRB(bayer, row, col, width, height);
    }
  }
  
}

inline void getCellInfo(const int &input, const int &width, int &out_color, int &out_row, int &out_col)
{
  out_col = getCol(input, width);
  out_row = getRow(input, width);
  if ((!(out_row % 2)) ^ (out_col % 2))
      {
        // green
        out_color = 1;
      } 
      else
      {
        out_color = (out_row % 2) ? 0 : 2;
      }
}

inline int getRow(const int &input, const int &width)
{
  return input / width;
}

inline int getCol(const int &input, const int &width)
{
  return input % width;
}

inline int getIndex(const int &row, const int &col, const int &width)
{
  return row*width + col;
}


inline unsigned char getG(const std::vector<unsigned char> & bayer,const int &row, const int &col, const int &width, const int& height)
{
  bool left = col != 0;
  bool right = col != width-1;
  bool up = row != 0;
  bool down = row != height -1;

  int sum = 0;

  if (left) sum += bayer[getIndex(row, col-1, width)];
  if (right) sum += bayer[getIndex(row, col+1, width)];
  if (up) sum += bayer[getIndex(row-1, col, width)];
  if (down) sum += bayer[getIndex(row+1, col, width)];

  return (unsigned char) (sum / (left+right+up+down));
}

inline unsigned char getRB(const std::vector<unsigned char> & bayer,const int &row, const int &col, const int &width, const int& height)
{
  bool up_left = (col != 0) && (row != 0);
  bool up_right = (col != width-1) && (row != 0);
  bool down_left = (col != 0) && (row != height-1);
  bool down_right = (col != width-1) && (row != height -1);

  int sum = 0;

  if (up_left) sum += bayer[getIndex(row-1, col-1, width)];
  if (up_right) sum += bayer[getIndex(row-1, col+1, width)];
  if (down_left) sum += bayer[getIndex(row+1, col-1, width)];
  if (down_right) sum += bayer[getIndex(row+1, col+1, width)];

  return (unsigned char) (sum /(up_left + up_right + down_left + down_right));
}