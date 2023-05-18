#include <iostream>
#include "ap_int.h"
#include "hls_stream.h"
using namespace std;
void shiftRegister(hls::stream<ap_uint<1>> &in, hls::stream<ap_uint<4>> &out);

int main() {
	hls::stream<ap_uint<1>> instream;
	hls::stream<ap_uint<4>> outstream;
	ap_uint<1> inputs[4] = {1,0,1,0};
	for (int i = 0; i < 4; i++) {
		instream.write(inputs[i]);
		shiftRegister(instream, outstream);

		ap_uint<4> output_array[4];
 for (int j = 0; j < 4; j++) {
 outstream.read(output_array[j]);
}

 std::cout << "Output "<<i+1 << " : ";
 for (int j= 0;j < 4; j++) {
 cout<<output_array[j]<<"";
 }
 cout << endl;
}
 return 0;
}


