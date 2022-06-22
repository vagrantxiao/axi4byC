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



#define MAX_NUM 90
void axis_master_a(
		hls::stream<ap_uint<32> > & Output_1) {
#include "desc_data.h"
#pragma HLS INTERFACE ap_hs port=Output_1
	for(int i=0; i<MAX_NUM; i++){
#pragma HLS PIPELINE II=1
		ap_uint<32> out_tmp;
		out_tmp(31,0) = ylxiao_blk_size[i](31, 0);
		Output_1.write(out_tmp);
	}
}


void axis_master_b(
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<73> > & Output_1) {
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
	ap_uint<73> out_tmp;
	ap_uint<8>  last_keep;
	int i;
	int size;
	int res_value;
	i = Input_1.read();
	printf("i=%d, %d\n", i, i);
	size = i%8 == 0 ? i/8 : i/8+1;
	res_value = i%8;

	last_keep[0] = res_value > 0 ? 1 : 0;
	last_keep[1] = res_value > 1 ? 1 : 0;
	last_keep[2] = res_value > 2 ? 1 : 0;
	last_keep[3] = res_value > 3 ? 1 : 0;
	last_keep[4] = res_value > 4 ? 1 : 0;
	last_keep[5] = res_value > 5 ? 1 : 0;
	last_keep[6] = res_value > 6 ? 1 : 0;
	last_keep[7] = res_value > 7 ? 1 : 0;

	if(res_value == 0) { last_keep(7, 0) = 0xff; }

	for(int j=0; j<size; j++){
#pragma HLS PIPELINE II=1
		out_tmp(31,  0) = j;
		out_tmp(63, 32) = j;
		if(j== size-1){
			out_tmp[72] = 1;
			out_tmp(71, 64) = last_keep;
		}else{
			out_tmp[72] = 0;
			out_tmp(71, 64) = 0xff;
		}
		Output_1.write(out_tmp);
	}
}


void desc_wr (hls::stream<ap_uint<288> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Output_1
#include "desc_data.h"
  ap_uint<288> out_tmp;
  for(int i=0; i<90; i++){
#pragma HLS PIPELINE II=1
    out_tmp(31 ,  0)=ylxiao_cnt[i];
    out_tmp(63 , 32)=ylxiao_rsvd0[i];
    out_tmp(95 , 64)=ylxiao_timestamp[i];
    out_tmp(127, 96)=ylxiao_tuple_cnt[i];
    out_tmp(159,128)=ylxiao_tuple_start[i];
    out_tmp(223,160)=ylxiao_blk_addr[i];
    out_tmp(255,224)=ylxiao_blk_size[i];
    out_tmp(263,256)=ylxiao_desc_id[i];
    out_tmp(267,264)=ylxiao_pkt_type[i];
    out_tmp(271,268)=ylxiao_dest[i];
    out_tmp(287,272)=ylxiao_desc_flags[i];
    Output_1.write(out_tmp);
  }
}



