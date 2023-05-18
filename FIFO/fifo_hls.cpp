/*
Assignment : Design a FIFO using HLS .

Solution Approach :
Theory :      As known by the definition that  FIFO is first in and First out ,means what ever we are giving to FIFO  ,it has to come out first .It acts as  temporary storage
					*We cant't read from empty fifo and cant't write to full fifo .


I/O declaration :
 in :Input
 out: Output
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


*/
#include <hls_stream.h>

const int DEPTH = 16;

void fifo(hls::stream<int>& in, hls::stream<int>& out) {
    static int memory[DEPTH];
    static int wr_ptr = 0;
    static int rd_ptr = 0;
    static int count = 0;


    if (!in.empty()&& count < DEPTH) {
        memory[wr_ptr] = in.read();
        wr_ptr = (wr_ptr + 1) % DEPTH;
        count++;
    }

    if ( !out.full() &&count > 0) {
        out.write(memory[rd_ptr]);
        rd_ptr = (rd_ptr + 1) % DEPTH;
        count--;
    }
}
