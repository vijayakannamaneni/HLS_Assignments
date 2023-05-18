/*
 * Assignment : Design a basic integer ALU unit
Requirements : -->Number of operands -2
 *Bit widths of operands - 8 bits
 *List of operations
   -->Addition
   -->Subtraction
   -->Multiplication
   -->Division
   --AND
   -->OR
   -->XOR
 *Use a control input with appropriate bit width to select the above operations
 *Use AXIS interface for all I/O ports
 * Verify the design in both C-simulation and RTL simulation .
 * -------------------------------------------------------------------------------------------
 * -------------------------------------------------------------------------------------------*/
 /* Solution Approach
  * As mentioned in the Assignment we need two operands so I took "a" and  "b " of width 8 bits .
  * And also we need a control input "ctrl" of width 3 to select the above 7 operations
  * So we can do the above assignment using switch cases.
  * I/O Description
  *      1.input_stream   --> Input Variable
  *      2.control_stream  -->Input Variable for control purpose
  *      3.output_stream   -->Output variable

  *
  *------------------------------------------------------------------------------------------------
  *------------------------------------------------------------------------------------------------*/



#include "hls_stream.h"
#include "ap_int.h"
typedef hls::stream <ap_uint<8> > input_stream ;
typedef hls::stream <ap_uint<3> > control_stream ;
typedef hls::stream <ap_uint<8> > output_stream ;

void alu
(
		input_stream &in1,
		input_stream &in2,
		control_stream &ctrl,
		output_stream &out
		)
  {
	//internal variables declaration
	ap_uint<8> a,b,result ;
	ap_uint<3> op_ctrl ;
    op_ctrl=ctrl.read() ;//reading from ctrl to op_ctrl
	a=in1.read() ;//reading from in1 to a
	b=in2.read() ;//reading from in2 to b
#pragma HLS INTERFACE axis port=in1  //{  declaring  in1 ,in2, ctrl ,out as axis ports }
#pragma HLS INTERFACE axis port=in2
#pragma HLS INTERFACE axis port=ctrl
#pragma HLS INTERFACE axis port=out


	switch(op_ctrl){
		case 0://addition
			result=a+b;
			break;
		case 1://subtraction 
			result=a-b;
			break;
		case 2: //multiplication 
			result=a*b;
			break;
		case 3 ://division 
			result=a/b;
		 	break;
		case 4: //AND 
			result=a & b;
			break;
		case 5://OR
			result =a |b;
			break;
		case 6: //XOR 
			result =a^b;
			break;
		default:
			result=0;
			break ;
		}
       out.write(result);
 }

		
