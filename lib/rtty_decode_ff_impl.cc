/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "rtty_decode_ff_impl.h"

namespace gr {
  namespace rtty {

    static const int MIN_IN = 1;	// mininum number of input streams
    static const int MAX_IN = 1;	// maximum number of input streams
    static const int MIN_OUT = 1;	// minimum number of output streams
    static const int MAX_OUT = 1;	// maximum number of output streams


    rtty_decode_ff::sptr
    rtty_decode_ff::make(float rate, float baud, bool polarity)
    {
      return gnuradio::get_initial_sptr
        (new rtty_decode_ff_impl(rate, baud, polarity));
    }

    /*
     * The private constructor
     */
    rtty_decode_ff_impl::rtty_decode_ff_impl(float rate, float baud, bool polarity)
      : gr::block("rtty_decode_ff",
              gr::io_signature::make(MIN_IN, MAX_IN, sizeof(float)),
              gr::io_signature::make(MIN_OUT, MAX_OUT, sizeof(char)))
    {
        state = WAITING_FOR_START;
        _baud = baud;
        _rate = rate;
        _spb = rate/baud;
        charset = LETTERS;
        if(polarity) {
            mark = true;
            space = false;
        } else {
            mark = false;
            space = true;
        }
        set_relative_rate((baud/rate) / 7.42); //assumes 1.42 stop bits, old school
        set_history(_spb * 8);
        set_output_multiple(10);
    }

    /*
     * Our virtual destructor.
     */
    rtty_decode_ff_impl::~rtty_decode_ff_impl()
    {
    }

    void
    rtty_decode_ff_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
	ninput_items_required[0] = noutput_items / ((_baud/_rate) / 7.42);
    }


    static unsigned char letters[] =
    {'\0','E','\n','A',' ','S','I','U','\n','D','R','J','N','F','C','K',
    'T','Z','L','W','H','Y','P','Q','O','B','G','\0','M','X','V','\0'};
    static unsigned char figures[] =
    {'\0','3','\n','-',' ',' ','8','7','\n','$','4','\'',',','!',':',
    '(','5','\"',')','2','#','6','0','1','9','?','&','\0','.','/',';','\0'};


    int
    rtty_decode_ff_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        const float *instart = in;
        char *out = (char *) output_items[0];
        char outchar = 0;
        int outcount = 0;
        while((outcount < noutput_items) && ((in - instart) < (ninput_items[0]-(_spb*8)))) {
            switch(state) {
                case WAITING_FOR_START:
                    if((*in > 0) == space) {
                        state = DATA;
                        datapos = 0;
                        in += int(_spb*1.5); //move to center of first data bit
                    } else in++; //advance by one sample waiting for start bit
                    break;
                case DATA:
                    if(datapos > 4) {
                        state = LOOKING_FOR_STOP;
                    }
                    else {
                        if((*in > 0) == mark) outchar += (1 << datapos);
                        datapos++;
                        in += int(_spb); //move ahead one bit
                    }
                    break;
                case LOOKING_FOR_STOP:
                    if((*in > 0) == mark) {
                        if(outchar == 27) charset = FIGURES;
                        if(outchar == 31) charset = LETTERS;
                        out[outcount++] = (charset == LETTERS) ? letters[outchar] : figures[outchar];
                    }
                    state = WAITING_FOR_START;
                    outchar = 0;
                    break;
            }
        }
        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each(in-instart);
        // Tell runtime system how many output items we produced.
        return outcount;        
    }

  } /* namespace rtty */
} /* namespace gr */

