#include <iostream>
#include <hls_stream.h>
#include <ap_int.h>
using namespace std;
#define N 4
#include <ap_fixed.h>

typedef ap_fixed <16,1> data_t;
typedef ap_fixed <32,2> data_out;

typedef struct {
    data_t data;
    bool tlast;
} Mydata;
typedef struct {
	data_out data;
	bool tlast ;
}data_type;
void fir_filter_2(hls::stream<Mydata>& in, hls::stream<data_type>& out) {

#pragma HLS PIPELINE II =1
    #pragma HLS INTERFACE axis port=in
    #pragma HLS INTERFACE axis port=out

    static data_t  c[N] = {0.3171,0.4388,0.8235,0.9502};
    static data_t  d[N] = {0};

    static bool read_last_data = false;  // Flag to indicate if the last data should be read
    static int count = 0;
    static int counter=0;
    // Read input sample from stream
  static  Mydata datapacket;
  data_type  output ;
    if(!read_last_data)
    {
    	datapacket = in.read();
    }
    // Update data stages
    for (int i = N - 1; i > 0; i--) {
        d[i] = d[i - 1];
    }
    output.tlast=0;
    if (read_last_data) {
        d[0] = data_t(0);  // Set d[0] to the actual input data
        read_last_data = false;
        count ++;
        counter++;
    } else {
        d[0] = datapacket.data;
        counter++;
       // count ++;
    }
    cout<<count<<endl ;

    output.data =0;
    output.data += c[0]*d[0]+c[1]*d[1]+c[2]*d[2]+c[3]*d[3];


    if(counter == 12 )
         {
         	output.tlast =1;

         }
    if(count<4)
    {
    	out.write(output);

    }

    // Update flag based on tlast
    if (datapacket.tlast && !read_last_data) {
        read_last_data = true;
    }
    if(output.tlast ==1 )
    {
    	read_last_data=false ;
    	counter=0;
    	count=0;
    }

}
