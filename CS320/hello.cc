/*****************************************************************************
   FILE: hello.cc        

   AUTHOR: kxiao (Kevin Xiao)      

   ASSIGNMENT:  Hello World

   DATE: August 30th 2013      

   DESCRIPTION: 

 *****************************************************************************/

// my first program in C++

#include <iostream>

using namespace std;

int main ()
{
  int ary[5] = {3, 3, 3, 4, 5};
  int N = 3;

  for (int i = 1; i < N; i++){
    if (ary[i] != ary[i-1]){
      cout << "False";
      return 0;
    }
  }
  cout << "True";
  return 1;
}
