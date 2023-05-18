/*Assignment : Creating pipelined design for multiplier
-->for optimization purpose we use HLS pragmas .
-->for pipelining we use the pragma #pragma HLS PIPELINE II ,II is initiation interval .
-->Compare the resources before and after pipelining ,the resources will decrease

*/
#include "ap_int.h"
void multiplier2(ap_uint<32> a,ap_uint<32> b,ap_uint<32> &c)

{
    #pragma HLS PIPELINE II=2
    c=a*b;

}


