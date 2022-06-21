/*===============================================================*/
/*                                                               */
/*                        rendering.cpp                          */
/*                                                               */
/*                 C++ kernel for 3D Rendering                   */
/*                                                               */
/*===============================================================*/

#include "../host/typedefs.hpp"


void axi4_slave (
		  hls::stream<ap_uint<512> > & addr,
		  hls::stream<ap_uint<512> > & din,
		  hls::stream<ap_uint<512> > & dout,
		  hls::stream<ap_uint<512> > & brest,
		)

//( bit32 input[3*NUM_3D_TRI], bit32 output[NUM_FB])
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS DATAFLOW



}

