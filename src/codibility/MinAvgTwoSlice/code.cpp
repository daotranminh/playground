#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void check(int i, float val, int &pos, float &min)
{
  if (min > val)
    {
      min = val;
      pos = i;
    }
}

int solution(vector<int> &A) 
{
  int pos = -1;
  float min = numeric_limits<float>::max();
  
  for (int i = 0; i < A.size()-1; i++)
    {
      check(i, (A[i]+A[i+1])/2.0, pos, min);
      if (i < A.size()-2) check(i, (A[i]+A[i+1]+A[i+2])/3.0, pos, min);
    }
  
  return pos;
}

int main()
{
  vector<int> A = {4, 2, 2, 5, 1, 5, 8};
  cout << solution(A) << endl;
}
