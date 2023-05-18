#include "hls_stream.h"
#include "ap_int.h"

void shiftRegister(hls::stream<ap_uint<1>> &in, hls::stream<ap_uint<4>> &out) {
   static  ap_uint<4> reg[4] = {0};
    ap_uint<1> input;
    ap_uint<1> temp;
    in.read(input);

    temp = reg[0];
    reg[0] = input;

    for (int j = 3; j > 0; j--) {
        reg[j] = reg[j-1];
    }

    reg[1] = temp;
    for(int k=0;k<4;k++)
    {
            out.write(reg[k]);
    }

}
