/*===============================================================*/
/*                                                               */
/*                          typedefs.h                           */
/*                                                               */
/*                     Typedefs for the host                     */
/*                                                               */
/*===============================================================*/

#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

  // hls header
  #include "ap_int.h"
  #include "hls_stream.h"
  // specialized datatypes
  typedef ap_uint<1> bit1;
  typedef ap_uint<2> bit2;
  typedef ap_uint<8> bit8;
  typedef ap_uint<16> bit16;
  typedef ap_uint<32> bit32;
  typedef ap_uint<64> bit64;
  typedef ap_uint<512> bit512;
  typedef ap_uint<128> bit128;

  typedef struct{
  	double lut=0, ff=0, bram18=0, dsp2=0;
  } Res;


#define ENABLE_DATAFLOW
#endif