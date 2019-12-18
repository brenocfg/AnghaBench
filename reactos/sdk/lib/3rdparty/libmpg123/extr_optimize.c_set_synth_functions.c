#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ class; scalar_t__ type; } ;
struct TYPE_15__ {int /*<<< orphan*/ ** mono; int /*<<< orphan*/ ** mono2stereo; int /*<<< orphan*/ ** stereo; int /*<<< orphan*/ ** plain; } ;
struct TYPE_14__ {int dec_enc; int channels; } ;
struct TYPE_17__ {int down_sample; int /*<<< orphan*/  (* make_decode_tables ) (TYPE_4__*) ;TYPE_3__ cpu_opts; int /*<<< orphan*/  err; TYPE_2__ synths; TYPE_1__ af; int /*<<< orphan*/  synth_mono; int /*<<< orphan*/  synth_stereo; int /*<<< orphan*/  synth; } ;
typedef  TYPE_4__ mpg123_handle ;
typedef  enum synth_resample { ____Placeholder_synth_resample } synth_resample ;
typedef  enum synth_format { ____Placeholder_synth_format } synth_format ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MPG123_BAD_DECODER_SETUP ; 
 int MPG123_ENC_16 ; 
 int MPG123_ENC_24 ; 
 int MPG123_ENC_32 ; 
 int MPG123_ENC_8 ; 
 int MPG123_ENC_FLOAT ; 
 int MPG123_ERR ; 
 int /*<<< orphan*/  MPG123_NO_BUFFERS ; 
 scalar_t__ MPG123_OK ; 
 scalar_t__ NOQUIET ; 
 scalar_t__ avx ; 
 int /*<<< orphan*/  debug2 (char*,int,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int f_16 ; 
 int f_32 ; 
 int f_8 ; 
 int f_none ; 
 int f_real ; 
 scalar_t__ find_dectype (TYPE_4__*) ; 
 scalar_t__ frame_buffers (TYPE_4__*) ; 
 int /*<<< orphan*/  init_layer12_stuff (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_layer12_table ; 
 int /*<<< orphan*/  init_layer12_table_mmx ; 
 int /*<<< orphan*/  init_layer3_gainpow2 ; 
 int /*<<< orphan*/  init_layer3_gainpow2_mmx ; 
 int /*<<< orphan*/  init_layer3_stuff (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ make_conv16to8_table (TYPE_4__*) ; 
 int /*<<< orphan*/  make_decode_tables (TYPE_4__*) ; 
 int /*<<< orphan*/  make_decode_tables_mmx (TYPE_4__*) ; 
 scalar_t__ mmxsse ; 
 scalar_t__ neon ; 
 scalar_t__ neon64 ; 
 int r_1to1 ; 
 int r_2to1 ; 
 int r_4to1 ; 
 int r_none ; 
 int r_ntom ; 
 scalar_t__ sse ; 
 scalar_t__ sse_vintage ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 scalar_t__ x86_64 ; 

int set_synth_functions(mpg123_handle *fr)
{
	enum synth_resample resample = r_none;
	enum synth_format basic_format = f_none; /* Default is always 16bit, or whatever. */

	/* Select the basic output format, different from 16bit: 8bit, real. */
	if(FALSE){}
#ifndef NO_16BIT
	else if(fr->af.dec_enc & MPG123_ENC_16)
	basic_format = f_16;
#endif
#ifndef NO_8BIT
	else if(fr->af.dec_enc & MPG123_ENC_8)
	basic_format = f_8;
#endif
#ifndef NO_REAL
	else if(fr->af.dec_enc & MPG123_ENC_FLOAT)
	basic_format = f_real;
#endif
#ifndef NO_32BIT
	/* 24 bit integer means decoding to 32 bit first. */
	else if(fr->af.dec_enc & MPG123_ENC_32 || fr->af.dec_enc & MPG123_ENC_24)
	basic_format = f_32;
#endif

	/* Make sure the chosen format is compiled into this lib. */
	if(basic_format == f_none)
	{
		if(NOQUIET) error("set_synth_functions: This output format is disabled in this build!");

		return -1;
	}

	/* Be explicit about downsampling variant. */
	switch(fr->down_sample)
	{
		case 0: resample = r_1to1; break;
#ifndef NO_DOWNSAMPLE
		case 1: resample = r_2to1; break;
		case 2: resample = r_4to1; break;
#endif
#ifndef NO_NTOM
		case 3: resample = r_ntom; break;
#endif
	}

	if(resample == r_none)
	{
		if(NOQUIET) error("set_synth_functions: This resampling mode is not supported in this build!");

		return -1;
	}

	debug2("selecting synth: resample=%i format=%i", resample, basic_format);
	/* Finally selecting the synth functions for stereo / mono. */
	fr->synth = fr->synths.plain[resample][basic_format];
	fr->synth_stereo = fr->synths.stereo[resample][basic_format];
	fr->synth_mono = fr->af.channels==2
		? fr->synths.mono2stereo[resample][basic_format] /* Mono MPEG file decoded to stereo. */
		: fr->synths.mono[resample][basic_format];       /* Mono MPEG file decoded to mono. */

	if(find_dectype(fr) != MPG123_OK) /* Actually determine the currently active decoder breed. */
	{
		fr->err = MPG123_BAD_DECODER_SETUP;
		return MPG123_ERR;
	}

	if(frame_buffers(fr) != 0)
	{
		fr->err = MPG123_NO_BUFFERS;
		if(NOQUIET) error("Failed to set up decoder buffers!");

		return MPG123_ERR;
	}

#ifndef NO_8BIT
	if(basic_format == f_8)
	{
		if(make_conv16to8_table(fr) != 0)
		{
			if(NOQUIET) error("Failed to set up conv16to8 table!");
			/* it's a bit more work to get proper error propagation up */
			return -1;
		}
	}
#endif

#ifdef OPT_MMXORSSE
	/* Special treatment for MMX, SSE and 3DNowExt stuff.
	   The real-decoding SSE for x86-64 uses normal tables! */
	if(fr->cpu_opts.class == mmxsse
#	ifndef NO_REAL
	   && basic_format != f_real
#	endif
#	ifndef NO_32BIT
	   && basic_format != f_32
#	endif
#	ifdef ACCURATE_ROUNDING
	   && fr->cpu_opts.type != sse
	   && fr->cpu_opts.type != sse_vintage
	   && fr->cpu_opts.type != x86_64
	   && fr->cpu_opts.type != neon
	   && fr->cpu_opts.type != neon64
	   && fr->cpu_opts.type != avx
#	endif
	  )
	{
#ifndef NO_LAYER3
		init_layer3_stuff(fr, init_layer3_gainpow2_mmx);
#endif
#ifndef NO_LAYER12
		init_layer12_stuff(fr, init_layer12_table_mmx);
#endif
		fr->make_decode_tables = make_decode_tables_mmx;
	}
	else
#endif
	{
#ifndef NO_LAYER3
		init_layer3_stuff(fr, init_layer3_gainpow2);
#endif
#ifndef NO_LAYER12
		init_layer12_stuff(fr, init_layer12_table);
#endif
		fr->make_decode_tables = make_decode_tables;
	}

	/* We allocated the table buffers just now, so (re)create the tables. */
	fr->make_decode_tables(fr);

	return 0;
}