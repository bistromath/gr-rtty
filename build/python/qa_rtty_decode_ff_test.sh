#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/backup/gnuradio/oot/gr-rtty/python
export PATH=/backup/gnuradio/oot/gr-rtty/build/python:$PATH
export LD_LIBRARY_PATH=/backup/gnuradio/oot/gr-rtty/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/backup/gnuradio/oot/gr-rtty/build/swig:$PYTHONPATH
/usr/bin/python2 /backup/gnuradio/oot/gr-rtty/python/qa_rtty_decode_ff.py 
