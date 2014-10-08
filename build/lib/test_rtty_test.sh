#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/backup/gnuradio/oot/gr-rtty/lib
export PATH=/backup/gnuradio/oot/gr-rtty/build/lib:$PATH
export LD_LIBRARY_PATH=/backup/gnuradio/oot/gr-rtty/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-rtty 
