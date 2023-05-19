#include <hls_stream.h>
#include <ap_int.h>
#include <iostream>
#include <ap_fixed.h>
#include <cstdlib>

const int N=2048;
typedef ap_fixed<16,15>fixed_t;
typedef struct{
	fixed_t data;
	ap_uint<1> tlast;
}ap_uint15_axis;

void counter
(
		hls::stream<ap_uint15_axis> &out_data,
		hls::stream< fixed_t > &input_data
		);

int main()
{
	 hls::stream<ap_uint15_axis>out_data;
	  hls::stream< fixed_t> in_data;

    // Generate random input values
    for(int i=0; i<N; i++)
    {
        in_data << (rand() % (1 << 15));
    }


    counter(out_data, in_data);


    for(int i=0; i<N; i++)
    {
        ap_uint15_axis out_t;
        out_data >> out_t;

        std::cout << "out_data[" << i << "].data = " << out_t.data << std::endl;
        std::cout << "out_data[" << i << "].tlast = " << out_t.tlast << std::endl;
    }

    return 0;
}

