/*
Assignment : Implement 5G NR PDSCH Modulation function using HLS
Solution Approach : 
Pdsch supports 4 modulations QPSK(order-2),16QAM(order-4),64QAM(order-6),256QAM(order-8)
There are equations for these in 3GPP SPEC .

I/O declaration 

in           :input stream 
m            :input     (modulation order )
out_data     : output_stream 
*/
#include <hls_stream.h>
#include <ap_int.h>
#include <ap_fixed.h>
#include "x_values.h"  // stored real values in this header file
#include "y_values.h"  //stored imaginary values in this header file 


//taking real and imaginary in the same port using struct 
struct iq {
    ap_fixed<16,2> real;   //real values of  16 bit fixed point data type 
    ap_fixed<16,2> q;      //imaginary values of 16 bit fixed point data type 
 
//Function Implementation 
void modulation(ap_uint<8> in, hls::stream<iq>& out_data, int m) {
   

//internal varaibles declaration 
 iq out_t;
    ap_fixed<16,2> x_val;
    ap_fixed<16,2> y_val;
    switch (m) {
        case 2: // QPSK
        		x_val=x_values_1[in];   
        		y_val=y_values_1[in];

            break;

        case 4: // 16-QAM
        		x_val=x_values_2[in];
        		y_val=y_values_2[in];
        		break;

        case 6: // 64-QAM
            x_val = x_values_3[in];
            y_val = y_values_3[in];
            break;

        case 8: // 256-QAM
            x_val = x_values_4[in];
            y_val = y_values_4[in];
            break;

        default:
            x_val = 0;
            y_val = 0;
            break;
    }

    out_t.real = x_val;
    out_t.q = y_val;
    out_data << out_t;
}


/*#include <hls_stream.h>
#include   <ap_int.h>
#include <ap_fixed.h>
struct iq{
    ap_fixed<16,2> real;
    ap_fixed<16,2> q;
};
void modulation
(       ap_uint<8> in,
		hls::stream<iq> &out_data,
		int m
		)

{
	iq out_t;
    ap_fixed<16,0> x_val;
    ap_fixed<16,0> y_val;


        // Calculate real and imaginary values for the symbol
        switch (m) {
            case 2: // QPSK
                x_val = 0.707 * (1 - 2 *in[0]);
                y_val = 0.707 * (1 - 2 *in[1]);
                break;

            case 4:   // 16-QAM
                x_val = 0.316*((1 - 2 * in[0]) * (2 - (1 - 2 * in[2])));
                y_val= 0.316*((1 - 2 * in[1]) * (2 - (1 - 2 * in[3])));

                break;

            case 6:   // 64-QAM
                x_val =0.154* ((1 - 2 * in[0]) * ((4 - (1 - 2 * in[2])) * (2 - (1 - 2 * in[4]))));
                y_val =0.154* ((1 - 2 * in[1]) * ((4 - (1 - 2 * in[3])) * (2 - (1 - 2 * in[5]))));

                break;

            case 8:   // 256-QAM
               x_val = 0.07*((1 - 2 * in[0]) * ((8 - (1 - 2 *in[2])) * (4 - (1 - 2 * in[4])) * (2 - (1 - 2 * in[6]))));
               y_val= 0.07*((1 - 2 * in[1]) * ((8 - (1 - 2 *in[3])) * (4 - (1 - 2 * in[5])) * (2 - (1 - 2 * in[7]))));

                break;

        }
/*void modulation(ap_uint<8> in, hls::stream<iq>& out_data, int m) {
    iq out_t;
    ap_fixed<16,2> x_val;
    ap_fixed<16,2> y_val;
    switch (m) {
        case 2: // QPSK
        		x_val=x_values_1[in];
        		y_val=y_values_1[in];

            break;

        case 4: // 16-QAM
        		x_val=x_values_2[in];
        		y_val=y_values_2[in];
        		break;

        case 6: // 64-QAM
            x_val = x_values_3[in];
            y_val = y_values_3[in];
            break;

        case 8: // 256-QAM
            x_val = x_values_4[in];
            y_val = y_values_4[in];
            break;

        default:
            x_val = 0;
            y_val = 0;
            break;
    }

    out_t.real = x_val;
    out_t.q = y_val;
    out_data << out_t;
}


out_t.real = x_val;
out_t.q = y_val;
out_data<<out_t;


    }*/








