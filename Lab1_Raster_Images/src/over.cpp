#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  
  for (int i = 0; i < width*height; i++)
  {
    double a_A = double(A[i*4+3]) / 255.0;
    double a_B = double(B[i*4+3]) / 255.0;
    double a_C = a_A + a_B * (1.0 - a_A);
    for (int j = 0; j < 3; j++)
    {
      C[i*4+j] = (double(A[i*4+j]) * a_A + double(B[i*4+j]) * a_B * (1.0 - a_A)) / a_C;
      // C[i*4+j] = A[i*4+j] * (A[i*4+3]/255.0) * (1.0 - (B[i*4+3]/255.0)) 
      //   + B[i*4+j] * (B[i*4+3]/255.0) * (1.0 - A[i*4+3]/255.0)
      //   + A[i*4+j] * (A[i*4+3]/255.0) * (B[i*4+3]/255.0);
    }
    C[i*4+3] = a_C * 255.0;
    // bool A_present = !(A[i*4] == 0 && A[i*4+1] == 0 && A[i*4+2] == 0);
    // bool B_present = !(B[i*4] == 0 && B[i*4+1] == 0 && B[i*4+2] == 0);
    // C[i*4+3] = (A[i*4+3]/255.0) * (1.0 - (B[i*4+3]/255.0)) * A_present
    //   + (B[i*4+3]/255.0) * (1.0 - A[i*4+3]/255.0) * B_present
    //   + (A[i*4+3]/255.0) * (B[i*4+3]/255.0) * (A_present && B_present);
  }
}
