// Writing HLS code for packet shifter each packet of width  4096 bytes 

#include <hls_stream.h>

#include <ap_int.h>

#define SIZE 2048 			 // we need half of the  packet  size to store the elements in one array 

typedef ap_uint<8> data_t;              // data width is 8bits / 1byte 

typedef ap_uint<1> bool_1;


struct My_data {			// My_data is the name of the struct contains both data and tlast 										
    data_t data;
    bool_1 tlast;
};
 
 // main code starts here 
 
void data_packet(hls::stream<My_data>& input, hls::stream<My_data>& output) 
{         
    // data_packet is name of the topfunction contains both input and output stream ports 
    #pragma HLS INTERFACE axis port=input                       // declaring input port as axis port 
    
    #pragma HLS INTERFACE axis port=output		      	// declaring output as axis port 
    
    #pragma HLS PIPELINE II = 1                                // pipelining the design 
     
    static data_t arr[SIZE];                         	 // this array is used to store first half of the input stream 
    
    static int count = 0;                               // the counters are in the case statements for transition of states 
    
    static int counter = 0;
    
    static int counter_1 = 0 ;
    
    static bool_1 read_last_data = 0;
    
    static enum states {SEND_1, SEND_2 ,SEND_3 } state  ;       // using three states 

    
    My_data in_data, out_data;                                  // internal variables 

   
    switch(state)
     {
     
        case SEND_1:
            
            in_data = input.read();  
                                                                // reading input data to in_data
            arr[count] = in_data.data;	
            			                                // storing the half of the input data to the array							
            count++;      
            						       
            if (count <  SIZE)
            {	                                                // if count is less than 2048  it stores the data to the array ,else it goes to next state  			                 
                state = SEND_1;
            }
            else 
            {
                state = SEND_2;
            }
            
         break;
         
        case SEND_2:
        
            in_data = input.read();                                  //reading input stream to in_data (Other half of data )
            
            out_data.data = in_data.data;			     // giving the in_data directly to output 
            
            out_data.tlast = 0;
            
            output.write(out_data);                                    
            
            counter ++ ;
                 
            if(counter <  SIZE)
            				                            // if counter is  less than 2048 it writes the input directly to ouput ,else it goes to next state .
            {
            
                 state = SEND_2;
                 
            }
            
            else
            {
            	state = SEND_3 ;
            }
            
            break;
            
          case SEND_3:

            out_data.data = arr[counter_1];                                // the stored elements in send_1 are written to output here 
            
            out_data.tlast = (counter_1 == SIZE -1 ) ? 1 : 0;              //if counter_1 reacehes 2048  output last is high
            
            output.write(out_data);                                        
            													
            in_data= input.read();					   
            	                                                           //   when reading from the array write new data to the array  
            
            arr[counter_1]=in_data.data ;
            
            counter_1++;

            if (counter_1 <  SIZE)					 // the process continues between  send_2 and send_3 states 
             {  
                state = SEND_3;
            }
            
            else 
            {
            	state = SEND_2  ;
            	
            	counter =0;
            	
            	counter_1 =0 ;
            	
            	count = 0;
            }
            
            break;
   }
   
}












