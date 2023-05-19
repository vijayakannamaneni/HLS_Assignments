/*Assignment : For generating a t_last signal for every 2048 samples.
 *
 *
 */
// taking the necessary header files
#include <hls_stream.h>
#include <ap_fixed.h>
#include<ap_int.h>
const int N=2048;  //FFT size is 2048
typedef ap_fixed<16,15>fixed_t;
//Inorder to make a port having both data and tlast in it ,we used struct here
typedef struct{
	fixed_t data;
	ap_uint<1> tlast;
}ap_uint15_axis;
     //Function Implementation
void counter
(
		hls::stream<ap_uint15_axis> &out_data,
		hls::stream<fixed_t> &input_data
		)
{
	 //internal variables
	ap_uint15_axis out_t;
    fixed_t in_t;

	static int count = 0;
#pragma HLS INTERFACE axis port=out_data
#pragma HLS INTERFACE axis port=input_data
	#pragma HLS reset variable=count
	while(!input_data.empty()){
	input_data >> in_t;   //reading the input from input_data to in_t
		count++;
		if(count ==2048)
		{
				out_t.tlast=1;
		}
		else
		{
			out_t.tlast=0;
		}
out_t.data=in_t;
out_data<<out_t;      //writing the data from out_t to out_data
}
}
