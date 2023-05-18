#include <hls_stream.h>
#include   <ap_int.h>
#include <ap_fixed.h>
struct iq{
    ap_fixed<16,2> real;
    ap_fixed<16,2> q;
};
void modulation(ap_uint<8>in,hls::stream<iq> &out_data,int m);

int main() {
    ap_uint<8> in;
    hls::stream<iq> out_data;
    int m = 4;

    in =3;
    modulation(in, out_data, m);

    iq out_t;
    out_data >> out_t;

    std::cout << "out_data: " << out_t.real << std::endl;
    std::cout << "out_complex_data: " << out_t.q << std::endl;

    return 0;
}
