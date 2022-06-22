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
  typedef ap_uint<3> bit3;
  typedef ap_uint<8> bit8;
  typedef ap_uint<16> bit16;
  typedef ap_uint<32> bit32;
  typedef ap_uint<48> bit48;
  typedef ap_uint<64> bit64;
  typedef ap_uint<512> bit512;
  typedef ap_uint<128> bit128;


  typedef struct{
  	bit8  awid;
    bit48 awaddr;
    bit8  awlen;
    bit3  awsize;
  } awbus;

  //typedef ap_unit<67> awbus;

  typedef struct{
  	bit8  wid;
    bit64 wdata;
    bit8  wstrb;
    bit1  wlast;
  } wbus;

  //typedef ap_unit<81> wbus;

  typedef struct{
   	bit8 bid;
    bit3 bresp;
  } wbbus;

  //typedef ap_unit<11> wbbus;

  typedef struct{
   	bit48 addr;
    bit64 data;
    bit8  strb;
    bit1  last;
  } sbus;

  //typedef ap_unit<121> sbus;


#endif
