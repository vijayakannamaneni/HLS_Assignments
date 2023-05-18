

#include <ap_fixed.h>

void operation(ap_fixed<16,4> a,ap_ufixed<16,3 >b,char op,ap_fixed<16,7> &result );
int main()
{
	 ap_fixed<16,4>       a =5.64;
	 ap_fixed<16,3>     b =4.32;
        char op='+';

 ap_fixed<16,7>  result;
 	 	 std::cout<< a<< " ";
        operation(a,b,op,result);
        std::cout<<"result : " << result << std::endl ;
        return 0;
}

