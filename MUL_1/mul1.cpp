
#include "ap_int.h"
//Assignment : implement a 8 bit multiplier in vivao hls

void multiplier(ap_uint<8> a, ap_uint<8> b, ap_uint<16> &c) {
  c = a * b;
}


