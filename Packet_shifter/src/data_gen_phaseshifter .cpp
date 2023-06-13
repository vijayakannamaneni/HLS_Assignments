// Generating input data for the packet shift ,each packet of 4096 bytes 

#include <hls_stream.h>
#include <ap_int.h>
 
typedef ap_uint<8> data_t;          // here the  width of the data is 8 bits or 1 byte (mentioned in the assignment  )

typedef struct {                    // inorder to make data and tlast in one port we are using struct here 
      data_t  data;
      bool tlast;
  }   MyDataStruct ;		    // MyDataStruct is the name of the  struct that contains data and tlast 

void input_packet(hls::stream<MyDataStruct>& outputStream)       // input_packet is the name of the top function consists  of only one stream port 

{    

#pragma HLS INTERFACE axis register both port=outputStream
#pragma HLS PIPELINE II=1
#pragma HLS RESET variable=counter
#pragma HLS RESET variable=state

    static enum states {SEND, STOP} state;                      // taking 2 states for the continuous input stream 
    static int counter = 0;					 // counter value is used for the state transitions 
    MyDataStruct dataPacket;					 // internal variable  
    switch (state) 
    {
    
        case SEND:
        	
                counter++;                                          // counter values are taken as input's here 
	        dataPacket.data = counter;
                dataPacket.tlast = (counter == 4096);               // we need 4096 bytes of data in each packet ,after reaching 4096 samples make last signal high .
	        outputStream << dataPacket;
	        
                if (counter == 4096)
                 {
                   state = STOP;                                    // if counter reaches   4096 sample it goes to STOP state  otherwise in the same state 
                 }
               else 
                {
                   state = SEND;
                }
   	        break;
   	        
        case STOP:
                                                                     
        	counter=0 ;
        	dataPacket.data = counter + 1 ;
                dataPacket.tlast = (counter == 4096);
                outputStream << dataPacket;
        	counter++;
                state =SEND ;
               
               break;
    }
}
