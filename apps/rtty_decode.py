#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: RTTY decoder example
# Author: Nick Foster
# Generated: Wed Mar 30 09:58:21 2011
##################################################

from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.gr import firdes
from gnuradio.wxgui import scopesink2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import rtty
import wx

class rtty_decode(grc_wxgui.top_block_gui):

	def __init__(self):
		grc_wxgui.top_block_gui.__init__(self, title="RTTY decoder example")

		##################################################
		# Variables
		##################################################
		self.samp_rate = samp_rate = 44100

		##################################################
		# Blocks
		##################################################
		self.wxgui_scopesink2_0 = scopesink2.scope_sink_f(
			self.GetWin(),
			title="Scope Plot",
			sample_rate=samp_rate/40,
			v_scale=1,
			v_offset=0,
			t_scale=25e-3,
			ac_couple=False,
			xy_mode=False,
			num_inputs=1,
			trig_mode=gr.gr_TRIG_MODE_AUTO,
			y_axis_label="Counts",
		)
		self.Add(self.wxgui_scopesink2_0.win)
		self.rtty_decode_ff_0 = rtty.decode_ff(
		  samp_rate=samp_rate/40, 
		  baud_rate=45.45, 
		  polarity=True,
		)
		self.low_pass_filter_0 = gr.fir_filter_fff(40, firdes.low_pass(
			100, samp_rate, 45.45*3, 20, firdes.WIN_HANN, 6.76))
		self.gr_wavfile_source_0 = gr.wavfile_source("/home/nick/Downloads/ksm_rtty.wav", False)
		self.gr_sub_xx_0 = gr.sub_ff(1)
		self.gr_quadrature_demod_cf_0 = gr.quadrature_demod_cf(1)
		self.gr_moving_average_xx_0 = gr.moving_average_ff(5000, 1.0/5000, 20000)
		self.gr_hilbert_fc_0 = gr.hilbert_fc(64)
		self.gr_file_sink_0 = gr.file_sink(gr.sizeof_char*1, "/home/nick/Desktop/rtty/test.dat")
		self.gr_file_sink_0.set_unbuffered(False)

		##################################################
		# Connections
		##################################################
		self.connect((self.low_pass_filter_0, 0), (self.gr_moving_average_xx_0, 0))
		self.connect((self.gr_moving_average_xx_0, 0), (self.gr_sub_xx_0, 1))
		self.connect((self.gr_sub_xx_0, 0), (self.wxgui_scopesink2_0, 0))
		self.connect((self.low_pass_filter_0, 0), (self.gr_sub_xx_0, 0))
		self.connect((self.rtty_decode_ff_0, 0), (self.gr_file_sink_0, 0))
		self.connect((self.gr_sub_xx_0, 0), (self.rtty_decode_ff_0, 0))
		self.connect((self.gr_quadrature_demod_cf_0, 0), (self.low_pass_filter_0, 0))
		self.connect((self.gr_hilbert_fc_0, 0), (self.gr_quadrature_demod_cf_0, 0))
		self.connect((self.gr_wavfile_source_0, 0), (self.gr_hilbert_fc_0, 0))

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate
		self.wxgui_scopesink2_0.set_sample_rate(self.samp_rate/40)
		self.low_pass_filter_0.set_taps(firdes.low_pass(100, self.samp_rate, 45.45*3, 20, firdes.WIN_HANN, 6.76))

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	tb = rtty_decode()
	tb.Run(True)

