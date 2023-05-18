#include <iostream>
#include <hls_stream.h>

using namespace std;
void fifo(hls::stream<int>& in, hls::stream<int>& out);

int main() {
    hls::stream<int> in;
    hls::stream<int> out;
    const int DEPTH=16;
    for (int i = 0; i <20; i++) {
    	if(i<DEPTH){

        in.write(i);
        cout << "Wrote data: " << i << endl;
    	}
    	else
    	{
    		cout<< "FIFO FULL " <<endl;
    	}

    }

    fifo(in, out);

    for (int i = 0; i < 17; i++) {
        if (!out.empty()) {
            int data_out = out.read();
            cout << "Read data: " << data_out << endl;
        } else {
            cout << "FIFO empty" << endl;
        }
        fifo(in, out);
    }

    return 0;
}
