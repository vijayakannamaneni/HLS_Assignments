#include <hls_stream.h>
#include <ap_int.h>
#include <iostream>
using namespace std ;

const int len_msg  = 64; // length of input data

typedef struct
{
   ap_uint < 8 > type_1 ;
   bool last ;
}data_type ;

void crc_gen(hls::stream <data_type >& input ,hls::stream<data_type > & output ) ;

int main ()
{
	hls::stream <data_type > input_stream ("in ") ;
    hls::stream < data_type > output_stream ("out ");
	data_type result ;

	  //static ap_uint<1>  in_t[40] = {1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0 };
	  // static ap_uint<1> in_t[8]={1,1,1,0,0,1,0,1 };
	  // static ap_uint <1> in_t[24]={1,1,0,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,0,1,1 };
         static ap_uint <1> in_t [64]={ 1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0, 1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,0,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,0,1,1 };
    static ap_uint<1> bool_1;
	static data_type  in;

	for(int i=0;i<(len_msg)/8  ;i++){

	        for(int j=0 ;j< 8 ;j++){

		              in.type_1[j]=in_t[j + (i * 8)];

			           if ( i == 7 & j == 7 )
			           {
				                in.last = 1 ;
			           }
			           else{
				                in.last = 0 ;
			            }
	         }

              input_stream.write(in );
	          crc_gen(input_stream,output_stream) ;
	}

	for( int i=0 ;i< 2 ;i++){

	         crc_gen(input_stream ,output_stream ) ;

	 }
    while (!output_stream.empty())
	   {
	         result = output_stream.read();
	          cout << " result " << result.type_1 << endl ;
	      //   printf("%s\n",result.type_1.to_string(2).c_str());

	   }
}
