#include "ap_int.h"
#include <hls_stream.h>
#include <iostream>

void multiply(hls::stream<ap_uint<8> >&a, hls::stream<ap_uint<8> >&b, hls::stream<ap_uint  <16> > &result);

int main() {
  hls::stream <ap_uint<8> > a;
  hls::stream <ap_uint<8> > b;
  hls::stream <ap_uint<16> > result;

  a.write(5);
  b.write(3);

  multiply(a, b, result);

 ap_uint<16> res = result.read();
  std::cout << "Result: " << res << std::endl;

  return 0;
}


