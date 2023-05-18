#include "ap_int.h"
#include <iostream>
using namespace std;
void multiplier2(ap_uint<32> a,ap_uint<32> b,ap_uint<32> &c);
int main() {
  ap_uint<32> a = 24;
  ap_uint<32> b = 25;
  ap_uint<32> c;
  multiplier2(a, b, c);
  std::cout << "result: " << c << std::endl;
  return 0;
}

