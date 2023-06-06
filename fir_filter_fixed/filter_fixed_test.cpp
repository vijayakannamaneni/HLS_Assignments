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
void fir_filter_2(hls::stream<Mydata>& in, hls::stream<data_type>& out);

int main() {
    hls::stream<Mydata> in_stream("in");
    hls::stream<data_type> out_stream("out");
    data_type  output ;

   static  data_t  input[9]={0.0971,0.3171,0.4388,0.8235,0.9502,0.3816,0.6948,0.0345,0.7655};
   Mydata input_data[9];

    for (int i = 0; i < 9; i++) {
        input_data[i].tlast = false;
        input_data[i].data =input[i];

    }
    input_data[8].tlast = true;  // Set tlast for the last data packet

    // Push input data into the input stream
    for (int i = 0; i < 9; i++) {
        in_stream.write(input_data[i]);
        fir_filter_2(in_stream, out_stream);
    }
    cout << "after 9 th data  " << endl;
    fir_filter_2(in_stream, out_stream);
    fir_filter_2(in_stream, out_stream);
   fir_filter_2(in_stream,out_stream);


    // Read output data from the output stream and print
   for(int i=0;i<12;i++) {
	   if((!out_stream.empty()) ){
        output = out_stream.read();
        std::cout << "Output:"   << output.data  << std::endl;
        std::cout <<"output_talst " << output.tlast <<std::endl ;
    }
 }
   // 2nd set of input data .
   cout  << "*************** 2nd input_set  ********************" << endl;

   cout << "input empy " << in_stream.empty() <<  endl;
   cout << "output empty" << out_stream.empty() << endl;


   for (int i = 0; i < 9; i++) {
       input_data[i].tlast = false;
       input_data[i].data =input[i];

   }
   input_data[8].tlast = true;  // Set tlast for the last data packet

   // Push input data into the input stream
   for (int i = 0; i < 9; i++) {
       in_stream.write(input_data[i]);
       fir_filter_2(in_stream, out_stream);
   }
   cout << "after 9 th data  " << endl;
   fir_filter_2(in_stream, out_stream);
   fir_filter_2(in_stream, out_stream);
  fir_filter_2(in_stream,out_stream);


   // Read output data from the output stream and print
  for(int i=0;i<12;i++) {
	   if((!out_stream.empty()) ){
       output = out_stream.read();
       std::cout << "Output:"   << output.data  << std::endl;
       std::cout <<"output_talst " << output.tlast <<std::endl ;
   }
}
    return 0;
}
