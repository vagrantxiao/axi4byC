/*===============================================================*/
/*                                                               */
/*                        rendering.cpp                          */
/*                                                               */
/*                 C++ kernel for 3D Rendering                   */
/*                                                               */
/*===============================================================*/

#include "typedefs.hpp"


void axi4_slave_ctrl (
		  hls::stream< ap_uint<67>  > & aw,
		  hls::stream< ap_uint<81>  > & w,
		  hls::stream< ap_uint<121> > & dout,
		  hls::stream< ap_uint<11>  > & bresp
		){
#pragma HLS INTERFACE axis register both port=aw
#pragma HLS INTERFACE axis register both port=w
#pragma HLS INTERFACE axis register both port=dout
#pragma HLS INTERFACE axis register both port=bresp


	ap_uint<67>  aw_in;
	ap_uint<81>  w_in;
	ap_uint<121> dout_tmp;
	ap_uint<11>  bresp_out;


	aw_in = aw.read();

	int awlen = aw_in(10, 3);

	for(int i=0; i<awlen+1; i++){
#pragma HLS PIPELINE II=1
		w_in = w.read();
		dout_tmp(0,    0) = w_in(0, 0);
		dout_tmp(8,    1) = w_in(8, 1);
		dout_tmp(72,   9) = w_in(72,9);
		dout_tmp(120, 73) = aw_in(58, 11)+i<<3;
		dout.write(dout_tmp);
	}

	if (w_in(0, 0)){ bresp_out(2, 0) = 0; }
	else           { bresp_out(2, 0) = 1; }
	bresp_out(10, 3) = 0;

	bresp.write(bresp_out);
}

