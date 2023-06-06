#include <hls_stream.h>
#include <ap_int.h>
#include <ap_fixed.h>
// Data type for the samples
typedef ap_fixed<16,1> data_t;

// Structure definition
typedef struct {
    data_t data;
    bool tlast;
} MyDataStruct;

// Top-level function to generate data samples and pass them through streams
void topFunction( hls::stream<MyDataStruct>& outputStream) {
#pragma HLS INTERFACE axis register both port=outputStream
#pragma HLS PIPELINE II=1

	data_t in_array[9]={0.0971,0.3171,0.4388,0.8235,0.9502,0.3816,0.6948,0.0345,0.7655};
    static enum states {SEND, STOP} state;
#pragma HLS RESET variable=state

   static int counter =0;
#pragma HLS RESET variable=counter


   // data_t in_array[9]={0.0971,0.3171,0.4388,0.8235,0.9502,0.3816,0.6948,0.0345,0.7655};
    MyDataStruct dataPacket;

    switch (state) {
        case SEND:

        	counter ++;
            dataPacket.data = in_array[counter-1];
            dataPacket.tlast = (counter == 9);
            outputStream << dataPacket;

            if (counter == 9) {
                state = STOP;
            }
            else {
                state = SEND;
            }
            break;
        case STOP:
        	counter=0 ;
        	dataPacket.data = in_array[counter];
        	            dataPacket.tlast = (counter == 9);
        	            outputStream << dataPacket;
        	            counter++;
        	state =SEND ;
            break;
    }

// dataPacket.data = in_array[counter];
//    dataPacket.tlast=(counter == 9);
//    if(counter == 9)
//    {
//    	counter =0;
//    }
//
//    counter ++ ;
//    outputStream << dataPacket ;
}
