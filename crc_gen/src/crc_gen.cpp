#include <ap_int.h>
#include <hls_stream.h>
#include <iostream>
using namespace std ;

static int msg_len = 0  ;

typedef struct
{
ap_uint < 8 > type_1 ;
bool last ;
} data_type ;

void crc_gen(
		hls::stream <data_type  > &input ,
		hls::stream < data_type > &output ) {

 #pragma HLS INTERFACE axis port=input                       // declaring input port as axis port
 #pragma HLS INTERFACE axis port=output                      // declaring output as axis port
 #pragma HLS PIPELINE II = 1                                // pipelining the design

 static enum states{state_0,state_1,state_2, state_3} state ;
 static data_type crc_out ;
 static data_type temp_data ;
 static ap_uint <4> gen_pol= 13 ; //1101
 static data_type in_t ;
 static ap_uint < 16 > data ;
 static ap_uint<4> count = 0 ;
 static ap_uint<4> counter = 0;
 static ap_uint<4> counter_1 = 0;
 static ap_uint<4> counter_2 = 0 ;

 // function implementation starts here
switch(state )
{
	case state_0 :

		input >> in_t ;

		 temp_data.type_1 =  in_t.type_1 ;
		 temp_data.last = 0;
		 output << temp_data ;

		 for(int i=0;i<8;i++)
		 {
			  data[i] = in_t.type_1[i ];
			  msg_len ++ ;
		 }
		 for(int j=0;j<5;j++)
		    {
		      if (data[counter_2] == 1)
		      {
				       for (int i = 0; i < 4 ; i++)
						{
						  data[i + counter_2 ] = data[i+counter_2] ^ gen_pol[i];
						}
			  }
		 	  counter_2 ++;
		  }
		state=state_1 ;

	break;

	case state_1:

        if(!in_t.last ){
			input  >> in_t ;
			temp_data.type_1 =  in_t.type_1 ;
			temp_data.last = 0;
			output << temp_data ;
       	 	  if(counter < 1)
       	 	  {
       	 		   for(int i=0 ; i< 8 ;i++)
       	 		   {
       	 				   data[i+8]=in_t.type_1[i] ;
       	 		   }
       	 		   msg_len = msg_len + 8 ;
       	 	 }
       	 	 else
       	 	 {
       	 		  for(int i=0;i<8;i++)
       	 		   {
       	 				  data[i]=data[i+8];
       	 		   }
       	 		   for(int i=0;i<8;i++)
       	 		   {
       	 				  data[i+8]=in_t.type_1[i];
       	 		   }
       	 		   msg_len = msg_len + 8 ;
       	 	  }
       	 	 counter ++ ;
       	 }
       	else{

       			if(msg_len == 8)
       			{
       				  for(int i=0;i<3;i++)
       			      {
       						data[i+8]= 0 ;
       						msg_len ++ ;
       				  }
       		          for(int j=0;j<1;j++){
       				      	if (data[counter_2] == 1)
       				      	{
       						     for (int i = 0; i < 4 ; i++)
       						     {
       						           data[i + counter_2 ] = data[i+counter_2] ^ gen_pol[i];
       						     }
       				     	}
       					    counter_2 ++;
       		          }
       		          state=state_2;
       			}
       			else
       			{
				       for(int i=0;i<8;i++)
				       {
					   data[i]=data[i+8];
				        }
				        if(counter_1 < 1)
				        {
					         for(int i=0;i<3;i++)
					         {
					         	data[i+8]= 0 ;
					         	msg_len ++ ;
					         }
					        counter_1 ++ ;
				         }
       			}

            }
        for(int j=0;j<8;j++)
        {
			if (data[count] == 1){

				for (int i = 0; i < 4 ; i++)
				{
				data[i + count ] = data[i+count] ^ gen_pol[i];
				}

			}
			count ++;

			if(count == 8 )
			{
				count = 0 ;
			}
        }
        if(msg_len < counter*8+ 11)
        {
        	state =  state_1 ;
        }
        else
        {
        	state=state_2 ;
        }
	break;

	case state_2 :
		for(int i=0 ;i<3 ;i++)
		{
			crc_out.type_1[i]=data[8+i];
			crc_out.last=(i==2)? 1 : 0 ;
		}

		output << crc_out ;
		state=state_3;
	break ;

	case state_3:
		state=state_0;
		count=0;
		counter_1=0;
		msg_len =0 ;
   break;

}
}









