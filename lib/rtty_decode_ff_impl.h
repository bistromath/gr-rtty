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

#ifndef INCLUDED_RTTY_RTTY_DECODE_FF_IMPL_H
#define INCLUDED_RTTY_RTTY_DECODE_FF_IMPL_H

#include <rtty/rtty_decode_ff.h>

namespace gr {
  namespace rtty {

    class rtty_decode_ff_impl : public rtty_decode_ff
    {
     private:
      // Nothing to declare in this block.
        //friend rtty_decode_ff rtty_make_decode_ff (float rate, float baud, bool polarity);
        //rtty_decode_ff (float rate, float baud, bool polarity); // private constructor
        enum { WAITING_FOR_START, DATA, LOOKING_FOR_STOP } state;
        enum { LETTERS, FIGURES } charset;
        float _baud;
        float _rate;
        bool mark, space;
        float _spb;
        int datapos;

     public:
      rtty_decode_ff_impl(float rate, float baud, bool polarity);
      ~rtty_decode_ff_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace rtty
} // namespace gr

#endif /* INCLUDED_RTTY_RTTY_DECODE_FF_IMPL_H */

