
#include <iostream>
#include <ap_int.h>

void counter(ap_uint<2>ctrl, ap_uint<3>load_val, ap_uint<3>&out_val);

int main() {
// Define internal variables
 ap_uint<2>ctrl;
 ap_uint<3> load_val, out_val;

//Test count up
 load_val = 0;
 for (int i = 0; i < 8; i++) {
	 ctrl=1;
	 counter(ctrl,load_val, out_val);
 std::cout << "Count up: " << out_val << std::endl;
 }
}
//Test count down
/*
for(int i=0 ;i<8;i++)
{
	ctrl=0;
	counter(ctrl,load_val,out_val);
	std::cout<< "count down:" << out_val<<std::endl;
}
}
*/
