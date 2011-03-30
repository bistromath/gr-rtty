/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access rtty_decode_ff from python as rtty.decode_ff
 */
GR_SWIG_BLOCK_MAGIC(rtty,decode_ff);

rtty_decode_ff_sptr rtty_make_decode_ff (float samp_rate, float baud_rate, bool polarity);

class rtty_decode_ff : public gr_block
{
private:
  rtty_decode_ff (float samp_rate, float baud_rate, bool polarity);
};
