#include "ap_int.h"
#include <iostream>
using namespace std;

void multiplier(ap_uint<8> a, ap_uint<8> b, ap_uint<16> &c);

int main() {
  ap_uint<8> a = 5;
  ap_uint<8> b = 3;
  ap_uint<16> c;
  multiplier(a, b, c);
  std::cout << "result: " << c << std::endl;
  return 0;
}

