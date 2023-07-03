#include <hls_stream.h>
#include <ap_int.h>
#include <iostream>
using namespace std ;

const int msg_len=64;
const int len_pol = 4; // length of generator polynomial

typedef struct
{
	  ap_uint <8 > data ;
	  bool last ;
}data_type ;

static enum states{st_0,st_1} state ;


void data_gen_crc( hls::stream < data_type >& output_data)
{
  //static ap_uint<1>  in_array [40] = {1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0, 1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0 };
  static ap_uint <1> in_t [64]={ 1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0, 1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,0,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,0,1,1 };
  static ap_uint<1> bool_1;
  static data_type  in;
  static ap_uint<7> counter = 0 ;
  #pragma HLS INTERFACE axis register both port=output_data
  #pragma HLS PIPELINE II=1
  #pragma HLS RESET variable=counter
  #pragma HLS RESET variable=state

  switch(state)
 {
	 case st_0 :

	   for(int i=0;i<8;i++)
	   {
				in.data[i]=in_t[i+counter];
				if(counter == 56 && i==7)
				{
				   in.last= 1 ;
		    	}
				else
				{
					in.last =0 ;
				}
	   }
	   output_data << in ;

	   if(counter < 56){
				state =st_0 ;
	   }
	   else
	   {
				state=st_1 ;
	   }
	   counter = counter + 8 ;
	   cout << " counter " << counter << endl ;
    break ;

   case st_1 :

			  counter = 0 ;

		}
}
