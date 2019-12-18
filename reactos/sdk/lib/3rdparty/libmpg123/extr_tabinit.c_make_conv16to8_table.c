#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dec_enc; } ;
struct TYPE_5__ {unsigned char* conv16to8_buf; unsigned char* conv16to8; void* err; TYPE_1__ af; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
#define  MPG123_ENC_ALAW_8 131 
#define  MPG123_ENC_SIGNED_8 130 
#define  MPG123_ENC_ULAW_8 129 
#define  MPG123_ENC_UNSIGNED_8 128 
 void* MPG123_ERR_16TO8TABLE ; 
 scalar_t__ NOQUIET ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error2 (char*,int,int) ; 
 double log (double) ; 
 scalar_t__ malloc (int) ; 

int make_conv16to8_table(mpg123_handle *fr)
{
  int i;
	int mode = fr->af.dec_enc;

  /*
   * ????: 8.0 is right but on SB cards '2.0' is a better value ???
   */
  const double mul = 8.0;

  if(!fr->conv16to8_buf){
    fr->conv16to8_buf = (unsigned char *) malloc(8192);
    if(!fr->conv16to8_buf) {
      fr->err = MPG123_ERR_16TO8TABLE;
      if(NOQUIET) error("Can't allocate 16 to 8 converter table!");
      return -1;
    }
    fr->conv16to8 = fr->conv16to8_buf + 4096;
  }

	switch(mode)
	{
	case MPG123_ENC_ULAW_8:
	{
		double m=127.0 / log(256.0);
		int c1;

		for(i=-4096;i<4096;i++)
		{
			/* dunno whether this is a valid transformation rule ?!?!? */
			if(i < 0)
			c1 = 127 - (int) (log( 1.0 - 255.0 * (double) i*mul / 32768.0 ) * m);
			else
			c1 = 255 - (int) (log( 1.0 + 255.0 * (double) i*mul / 32768.0 ) * m);
			if(c1 < 0 || c1 > 255)
			{
				if(NOQUIET) error2("Converror %d %d",i,c1);
				return -1;
			}
			if(c1 == 0)
			c1 = 2;
			fr->conv16to8[i] = (unsigned char) c1;
		}
	}
	break;
	case MPG123_ENC_SIGNED_8:
		for(i=-4096;i<4096;i++)
		fr->conv16to8[i] = i>>5;
	break;
	case MPG123_ENC_UNSIGNED_8:
		for(i=-4096;i<4096;i++)
		fr->conv16to8[i] = (i>>5)+128;
	break;
	case MPG123_ENC_ALAW_8:
	{
		/*
			Let's believe Wikipedia (http://en.wikipedia.org/wiki/G.711) that this
			is the correct table:

			s0000000wxyza... 	n000wxyz  [0-31] -> [0-15]
			s0000001wxyza... 	n001wxyz  [32-63] -> [16-31]
			s000001wxyzab... 	n010wxyz  [64-127] -> [32-47]
			s00001wxyzabc... 	n011wxyz  [128-255] -> [48-63]
			s0001wxyzabcd... 	n100wxyz  [256-511] -> [64-79]
			s001wxyzabcde... 	n101wxyz  [512-1023] -> [80-95]
			s01wxyzabcdef... 	n110wxyz  [1024-2047] -> [96-111]
			s1wxyzabcdefg... 	n111wxyz  [2048-4095] -> [112-127]

			Let's extend to -4096, too.
			Also, bytes are xored with 0x55 for transmission.

			Since it sounds OK, I assume it is fine;-)
		*/
		for(i=0; i<64; ++i)
		fr->conv16to8[i] = ((unsigned int)i)>>1;
		for(i=64; i<128; ++i)
		fr->conv16to8[i] = ((((unsigned int)i)>>2) & 0xf) | (2<<4);
		for(i=128; i<256; ++i)
		fr->conv16to8[i] = ((((unsigned int)i)>>3) & 0xf) | (3<<4);
		for(i=256; i<512; ++i)
		fr->conv16to8[i] = ((((unsigned int)i)>>4) & 0xf) | (4<<4);
		for(i=512; i<1024; ++i)
		fr->conv16to8[i] = ((((unsigned int)i)>>5) & 0xf) | (5<<4);
		for(i=1024; i<2048; ++i)
		fr->conv16to8[i] = ((((unsigned int)i)>>6) & 0xf) | (6<<4);
		for(i=2048; i<4096; ++i)
		fr->conv16to8[i] = ((((unsigned int)i)>>7) & 0xf) | (7<<4);

		for(i=-4095; i<0; ++i)
		fr->conv16to8[i] = fr->conv16to8[-i] | 0x80;

		fr->conv16to8[-4096] = fr->conv16to8[-4095];

		for(i=-4096;i<4096;i++)
		{
			/* fr->conv16to8[i] = - i>>5; */
			/* fprintf(stderr, "table %i %i\n", i<<AUSHIFT, fr->conv16to8[i]); */
			fr->conv16to8[i] ^= 0x55;
		}
	}
	break;
	default:
		fr->err = MPG123_ERR_16TO8TABLE;
		if(NOQUIET) error("Unknown 8 bit encoding choice.");
		return -1;
	break;
	}

	return 0;
}