#
# Copyright 2004,2005,2006,2008,2009,2010 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

include $(top_srcdir)/Makefile.common

# list of programs run by "make check" and "make distcheck"
TESTS = test_all

# ----------------------------------------------------------------
# rtty C++ library: libgnuradio-rtty.so
# ----------------------------------------------------------------

# C/C++ headers get installed in ${prefix}/include/$(modname)
modinclude_HEADERS = \
	rtty_decode_ff.h
	
lib_LTLIBRARIES = libgnuradio-rtty.la

libgnuradio_rtty_la_SOURCES = \
	rtty_decode_ff.cc
	
libgnuradio_rtty_la_LIBADD = \
	$(GNURADIO_CORE_LA)

libgnuradio_rtty_la_LDFLAGS = \
	$(NO_UNDEFINED)

# ----------------------------------------------------------------
# rtty C++ QA library: libgnuradio-rtty-qa.so (not installed)
# ----------------------------------------------------------------

#noinst_LTLIBRARIES = libgnuradio-rtty-qa.la

#libgnuradio_rtty_qa_la_SOURCES = \
#	qa_rtty.cc \
#	qa_rtty_decode_ff.cc \
#	qa_rtty_decode2_ff.cc

#libgnuradio_rtty_qa_la_LDFLAGS = $(NO_UNDEFINED) -version-info 0:0:0

#libgnuradio_rtty_qa_la_LIBADD = \
#	libgnuradio-rtty.la \
#	$(CPPUNIT_LIBS)

# ----------------------------------------------------------------
# headers that don't get installed
# ----------------------------------------------------------------
#noinst_HEADERS = \
#	qa_rtty.h \
#	qa_rtty_decode_ff.h \
#	qa_rtty_decode2_ff.h

# ----------------------------------------------------------------
# test program
# ----------------------------------------------------------------
#noinst_PROGRAMS = \
#	test_all

#test_all_SOURCES = test_all.cc
#test_all_LDADD   = libgnuradio-rtty-qa.la
