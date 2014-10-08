/* -*- c++ -*- */

#define RTTY_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "rtty_swig_doc.i"

%{
#include "rtty/rtty_decode_ff.h"
%}


%include "rtty/rtty_decode_ff.h"
GR_SWIG_BLOCK_MAGIC2(rtty, rtty_decode_ff);
