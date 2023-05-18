/*Assignment : Implement a 16 bit fixed point addition and multiplication circuit
 *
 * Solution Approach :
 *
 * To work with fixed point data types in HLS we have "ap_fixed.h" data types  in HLS .
 * ap_fixed<16,2>a ; this represents "a" is of fixed point data type of total 16 bits in which 2 bits area above the decimal and remaining are below the
 * decimal
 *
 * I/O Description :
 *
 * a     : input (using here as one of the operand for addition and multiplication )
 * b     : input (another operand)
 * result :output
 * --------------------------------------------------------------------------------------------------------------------------------------------------------
 * --------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#include <ap_fixed.h>
//typedef ap_fixed<16,8,AP_RND,AP_SAT> fixed_type;

void operation(ap_fixed<16,4> a,ap_ufixed<16,3 >b,char op,ap_fixed<16,7> &result )
{
       switch(op){
        case '+' ://addition 
                  result = a+b;
                  break ;
        case '-' ://subtraction 
                  result = a-b ;
                  break ;
        default :
                  result=0;
                  break ;
       }
}


