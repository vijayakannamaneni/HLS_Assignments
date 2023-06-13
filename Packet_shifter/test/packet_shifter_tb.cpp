// test bench code for the packet_shifter 


#include <iostream>

#include <hls_stream.h>

#include <ap_int.h>

using namespace std;

 #define N_1 4096              // we need each packet of width 4096 bytes 
 
typedef ap_uint<8> data_t;

 struct  My_data {
    data_t  data;
    bool tlast;
} ;


void data_packet (hls::stream<My_data>& input, hls::stream<My_data>& output);

int main() 

    hls::stream<My_data> input_stream("in");          // varibles declaration which as same as function ports  
    
    hls::stream<My_data> output_stream("out");
    

    // Prepare test data
    
    My_data test_data[N_1];
    
    for (int i = 0; i < N_1; i++)
     {
        test_data[i].data = i;          // Assign input data
        
        test_data[i].tlast = false;
    }
    
    test_data[N_1 - 1].tlast = true;
    
cout  << "-------------1st ip----------------"<< endl;

    // Write input data to the input stream and call the function 
    
    for (int i = 0; i < N_1 ; i++)
     {
        input_stream.write(test_data[i]);
        
        data_packet(input_stream, output_stream);

    }
   
    for (int i = 0; i < 2048  ; i++) {
        input_stream.write(test_data[i]);
        data_packet(input_stream, output_stream);

    }
 
    // Check the output
    while (!output_stream.empty()) {
        My_data result = output_stream.read();
        std::cout << "Data: " << result.data << ", tlast: " << result.tlast << std::endl;
    }
}
