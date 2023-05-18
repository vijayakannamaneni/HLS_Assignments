#include "hls_stream.h"
#include "ap_int.h"
#include <iostream>

void alu(hls::stream<ap_uint<8>> &in1, hls::stream<ap_uint<8>> &in2, hls::stream<ap_uint<3>> &ctrl, hls::stream<ap_uint<8>> &out);

int main()
{
    hls::stream<ap_uint<8>> in1;
    hls::stream<ap_uint<8>> in2;
    hls::stream<ap_uint<3>> ctrl;
    hls::stream<ap_uint<8>> out;

    in1.write(0x02);
    in2.write(0x03);
    ctrl.write(5);

    alu(in1, in2, ctrl, out);

    ap_uint<8> res = out.read();

    std::cout << "Result: " << res << std::endl;

    return 0;
}
