/*Assignment : Apply AXI-Stream interface on the I/O ports of the above experiment(Multiplier)
 *
 *Solution Appraoch :
 pragma HLS INTERFACE axis port=a ,which means a is a axis port(works on AXI protocol)

I/O declaration:
a= 8 bit input
b=8 bit input;
result=16 bit output.
 */


#include "ap_int.h"
#include "hls_stream.h"

void multiply(
		hls::stream < ap_uint<8> > &a,
		hls::stream < ap_uint<8> > &b,
		hls::stream < ap_uint<16> > &result
		)
{
#pragma HLS INTERFACE axis port=a
#pragma HLS INTERFACE axis port=b
#pragma HLS INTERFACE axis port=result

  ap_uint <8> a_val = a.read();//a.read(a_val)  //reading value from a to a_val
  ap_uint <8> b_val= b.read();//b.read(b_val)   //reading  value from b to b_val
  ap_uint <16> res = a_val * b_val;             //calculating the multiplication
  result.write(res);							//writng the result to  result from res
}


