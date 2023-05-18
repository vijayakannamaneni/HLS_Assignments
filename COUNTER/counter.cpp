/*
Assignment :	Design a configurable loadable UP/DOWN counter using HLS
		and one input to select UP or DOWN, One input to select load or not, one input to give the load value, Create pipelined design.


 Solution Approach : I implemented a  bit counter here .In that I took 2 bit control input one to select load or not and one to determine up or down counter .
 		     For example if we give two as a ctrl input , 2 represented in binary as 10 ,first bit(1)  to select load is high or not and second bit for(0) for 			     counting up or down .

 I/O description :
  ctrl     :     input       for load and counting purpose
  load_val :     input         giving a value for load
  out_val  :     output
------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#include <ap_int.h>

void counter(ap_uint<2>ctrl, ap_uint<3> load_val, ap_uint<3>& out_val) {
    //define no.of pipeline stages
    #pragma HLS pipeline II=2


    static ap_uint<3> counter_val = 0;

    //based on load value
    if (ctrl[1]==1) {
        counter_val = load_val;
    } else {
        // increment or decrement counter based on up input
        if (ctrl[0]==1) {
        	//  counter_val=(counter_val==7)? 0:counter_val+1;
           counter_val++;

        } else {
            counter_val--;
        }
    }

    // output counter value
    out_val = counter_val;
}

