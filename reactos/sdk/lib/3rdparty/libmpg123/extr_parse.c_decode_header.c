#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lay; int lsf; int mpeg25; size_t sampling_frequency; int error_protection; size_t bitrate_index; long padding; scalar_t__ mode; int freeformat; int stereo; scalar_t__ freeformat_framesize; long framesize; int spf; int ssize; int /*<<< orphan*/  do_layer; int /*<<< orphan*/  emphasis; int /*<<< orphan*/  original; int /*<<< orphan*/  copyright; int /*<<< orphan*/  mode_ext; int /*<<< orphan*/  extension; } ;
typedef  TYPE_1__ mpg123_handle ;

/* Variables and functions */
 unsigned long HDR_BITRATE ; 
 size_t HDR_BITRATE_VAL (unsigned long) ; 
 int /*<<< orphan*/  HDR_CHANEX_VAL (unsigned long) ; 
 scalar_t__ HDR_CHANNEL_VAL (unsigned long) ; 
 int /*<<< orphan*/  HDR_COPYRIGHT_VAL (unsigned long) ; 
 int HDR_CRC_VAL (unsigned long) ; 
 int /*<<< orphan*/  HDR_EMPHASIS_VAL (unsigned long) ; 
 int HDR_LAYER_VAL (unsigned long) ; 
 int /*<<< orphan*/  HDR_ORIGINAL_VAL (unsigned long) ; 
 long HDR_PADDING_VAL (unsigned long) ; 
 int /*<<< orphan*/  HDR_PRIVATE_VAL (unsigned long) ; 
 void* HDR_SAMPLERATE_VAL (unsigned long) ; 
 int HDR_VERSION_VAL (unsigned long) ; 
 scalar_t__ MAXFRAMESIZE ; 
 int MPG123_NEED_MORE ; 
 scalar_t__ MPG_MD_MONO ; 
 scalar_t__ NOQUIET ; 
 int PARSE_BAD ; 
 int PARSE_GOOD ; 
 scalar_t__ VERBOSE2 ; 
 scalar_t__ VERBOSE3 ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug2 (char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  do_layer1 ; 
 int /*<<< orphan*/  do_layer2 ; 
 int /*<<< orphan*/  do_layer3 ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error1 (char*,unsigned long) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 int* freqs ; 
 int guess_freeformat_framesize (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  head_check (unsigned long) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__*** tabsel_123 ; 

__attribute__((used)) static int decode_header(mpg123_handle *fr,unsigned long newhead, int *freeformat_count)
{
#ifdef DEBUG /* Do not waste cycles checking the header twice all the time. */
	if(!head_check(newhead))
	{
		error1("trying to decode obviously invalid header 0x%08lx", newhead);
	}
#endif
	/* For some reason, the layer and sampling freq settings used to be wrapped
	   in a weird conditional including MPG123_NO_RESYNC. What was I thinking?
	   This information has to be consistent. */
	fr->lay = 4 - HDR_LAYER_VAL(newhead);

	if(HDR_VERSION_VAL(newhead) & 0x2)
	{
		fr->lsf = (HDR_VERSION_VAL(newhead) & 0x1) ? 0 : 1;
		fr->mpeg25 = 0;
		fr->sampling_frequency = HDR_SAMPLERATE_VAL(newhead) + (fr->lsf*3);
	}
	else
	{
		fr->lsf = 1;
		fr->mpeg25 = 1;
		fr->sampling_frequency = 6 + HDR_SAMPLERATE_VAL(newhead);
	}

	#ifdef DEBUG
	/* seen a file where this varies (old lame tag without crc, track with crc) */
	if((HDR_CRC_VAL(newhead)^0x1) != fr->error_protection) debug("changed crc bit!");
	#endif
	fr->error_protection = HDR_CRC_VAL(newhead)^0x1;
	fr->bitrate_index    = HDR_BITRATE_VAL(newhead);
	fr->padding          = HDR_PADDING_VAL(newhead);
	fr->extension        = HDR_PRIVATE_VAL(newhead);
	fr->mode             = HDR_CHANNEL_VAL(newhead);
	fr->mode_ext         = HDR_CHANEX_VAL(newhead);
	fr->copyright        = HDR_COPYRIGHT_VAL(newhead);
	fr->original         = HDR_ORIGINAL_VAL(newhead);
	fr->emphasis         = HDR_EMPHASIS_VAL(newhead);
	fr->freeformat       = !(newhead & HDR_BITRATE);

	fr->stereo = (fr->mode == MPG_MD_MONO) ? 1 : 2;

	/* we can't use tabsel_123 for freeformat, so trying to guess framesize... */
	if(fr->freeformat)
	{
		/* when we first encounter the frame with freeformat, guess framesize */
		if(fr->freeformat_framesize < 0)
		{
			int ret;
			*freeformat_count += 1;
			if(*freeformat_count > 5)
			{
				if(VERBOSE3) error("You fooled me too often. Refusing to guess free format frame size _again_.");
				return PARSE_BAD;
			}
			ret = guess_freeformat_framesize(fr, newhead);
			if(ret == PARSE_GOOD)
			{
				fr->freeformat_framesize = fr->framesize - fr->padding;
				if(VERBOSE2)
				fprintf(stderr, "Note: free format frame size %li\n", fr->freeformat_framesize);
			}
			else
			{
				if(ret == MPG123_NEED_MORE)
				debug("Need more data to guess free format frame size.");
				else if(VERBOSE3)
				error("Encountered free format header, but failed to guess frame size.");

				return ret;
			}
		}
		/* freeformat should be CBR, so the same framesize can be used at the 2nd reading or later */
		else
		{
			fr->framesize = fr->freeformat_framesize + fr->padding;
		}
	}

	switch(fr->lay)
	{
#ifndef NO_LAYER1
		case 1:
			fr->spf = 384;
			fr->do_layer = do_layer1;
			if(!fr->freeformat)
			{
				fr->framesize  = (long) tabsel_123[fr->lsf][0][fr->bitrate_index] * 12000;
				fr->framesize /= freqs[fr->sampling_frequency];
				fr->framesize  = ((fr->framesize+fr->padding)<<2)-4;
			}
		break;
#endif
#ifndef NO_LAYER2
		case 2:
			fr->spf = 1152;
			fr->do_layer = do_layer2;
			if(!fr->freeformat)
			{
				debug2("bitrate index: %i (%i)", fr->bitrate_index, tabsel_123[fr->lsf][1][fr->bitrate_index] );
				fr->framesize = (long) tabsel_123[fr->lsf][1][fr->bitrate_index] * 144000;
				fr->framesize /= freqs[fr->sampling_frequency];
				fr->framesize += fr->padding - 4;
			}
		break;
#endif
#ifndef NO_LAYER3
		case 3:
			fr->spf = fr->lsf ? 576 : 1152; /* MPEG 2.5 implies LSF.*/
			fr->do_layer = do_layer3;
			if(fr->lsf)
			fr->ssize = (fr->stereo == 1) ? 9 : 17;
			else
			fr->ssize = (fr->stereo == 1) ? 17 : 32;

			if(fr->error_protection)
			fr->ssize += 2;

			if(!fr->freeformat)
			{
				fr->framesize  = (long) tabsel_123[fr->lsf][2][fr->bitrate_index] * 144000;
				fr->framesize /= freqs[fr->sampling_frequency]<<(fr->lsf);
				fr->framesize = fr->framesize + fr->padding - 4;
			}
		break;
#endif 
		default:
			if(NOQUIET) error1("Layer type %i not supported in this build!", fr->lay); 

			return PARSE_BAD;
	}
	if (fr->framesize > MAXFRAMESIZE)
	{
		if(NOQUIET) error1("Frame size too big: %d", fr->framesize+4-fr->padding);

		return PARSE_BAD;
	}
	return PARSE_GOOD;
}