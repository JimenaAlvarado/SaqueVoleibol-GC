#include "include/Object.hpp"
  
using namespace std;
 
int main()
{
    Object obj1("obj/figure1.obj");
    obj1.Print();
    obj1.PrintNormals();
    obj1.PrintEquationsOfPlane(); 
    return 0;
}   
 

 