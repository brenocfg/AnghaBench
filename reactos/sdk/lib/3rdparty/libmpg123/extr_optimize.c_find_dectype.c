#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ the_dct36; int type; int /*<<< orphan*/  class; } ;
struct TYPE_7__ {scalar_t__** plain; } ;
struct TYPE_9__ {scalar_t__ synth; int /*<<< orphan*/  err; TYPE_2__ cpu_opts; TYPE_1__ synths; } ;
typedef  TYPE_3__ mpg123_handle ;
typedef  scalar_t__ func_synth ;
typedef  enum optdec { ____Placeholder_optdec } optdec ;
struct TYPE_10__ {int /*<<< orphan*/  plain; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MPG123_BAD_DECODER_SETUP ; 
 int MPG123_ERR ; 
 int MPG123_OK ; 
 scalar_t__ NOQUIET ; 
 int altivec ; 
 int arm ; 
 int avx ; 
 scalar_t__ dct36_3dnow ; 
 scalar_t__ dct36_3dnowext ; 
 int /*<<< orphan*/  debug3 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decclass (int) ; 
 int /*<<< orphan*/ * decname ; 
 int dreidnow ; 
 int dreidnow_vintage ; 
 int dreidnowext ; 
 int dreidnowext_vintage ; 
 int /*<<< orphan*/  error (char*) ; 
 size_t f_16 ; 
 scalar_t__ find_synth (scalar_t__,int /*<<< orphan*/ ) ; 
 int generic ; 
 int generic_dither ; 
 int idrei ; 
 int ifuenf ; 
 int ifuenf_dither ; 
 int ivier ; 
 int mmx ; 
 int neon ; 
 int neon64 ; 
 int nodec ; 
 int /*<<< orphan*/  plain_i386 ; 
 size_t r_1to1 ; 
 int sse_or_vintage (TYPE_3__*) ; 
 scalar_t__ synth_1to1_3dnow ; 
 scalar_t__ synth_1to1_3dnowext ; 
 scalar_t__ synth_1to1_8bit_wrap ; 
 scalar_t__ synth_1to1_altivec ; 
 scalar_t__ synth_1to1_arm ; 
 scalar_t__ synth_1to1_avx ; 
 scalar_t__ synth_1to1_dither ; 
 scalar_t__ synth_1to1_i586 ; 
 scalar_t__ synth_1to1_i586_dither ; 
 scalar_t__ synth_1to1_mmx ; 
 scalar_t__ synth_1to1_neon ; 
 scalar_t__ synth_1to1_neon64 ; 
 scalar_t__ synth_1to1_real_altivec ; 
 scalar_t__ synth_1to1_real_avx ; 
 scalar_t__ synth_1to1_real_neon ; 
 scalar_t__ synth_1to1_real_neon64 ; 
 scalar_t__ synth_1to1_real_sse ; 
 scalar_t__ synth_1to1_real_x86_64 ; 
 scalar_t__ synth_1to1_s32_altivec ; 
 scalar_t__ synth_1to1_s32_avx ; 
 scalar_t__ synth_1to1_s32_neon ; 
 scalar_t__ synth_1to1_s32_neon64 ; 
 scalar_t__ synth_1to1_s32_sse ; 
 scalar_t__ synth_1to1_s32_x86_64 ; 
 scalar_t__ synth_1to1_sse ; 
 scalar_t__ synth_1to1_x86_64 ; 
 scalar_t__ synth_2to1_dither ; 
 scalar_t__ synth_4to1_dither ; 
 TYPE_4__ synth_base ; 
 int x86_64 ; 

__attribute__((used)) static int find_dectype(mpg123_handle *fr)
{
	enum optdec type = nodec;
	/* Direct and indirect usage, 1to1 stereo decoding.
	   Concentrating on the plain stereo synth should be fine, mono stuff is derived. */
	func_synth basic_synth = fr->synth;
#ifndef NO_8BIT
#ifndef NO_16BIT
	if(basic_synth == synth_1to1_8bit_wrap)
	basic_synth = fr->synths.plain[r_1to1][f_16]; /* That is what's really below the surface. */
#endif
#endif

	if(FALSE) ; /* Just to initialize the else if ladder. */
#ifndef NO_16BIT
#if defined(OPT_3DNOWEXT) || defined(OPT_3DNOWEXT_VINTAGE)
	else if(basic_synth == synth_1to1_3dnowext)
	{
		type = dreidnowext;
#		ifdef OPT_3DNOWEXT_VINTAGE
#		ifdef OPT_MULTI
		if(fr->cpu_opts.the_dct36 == dct36_3dnowext)
#		endif
		type = dreidnowext_vintage;
#		endif
	}
#endif
#if defined(OPT_SSE) || defined(OPT_SSE_VINTAGE)
	else if(basic_synth == synth_1to1_sse)
	{
		type = sse_or_vintage(fr);
	}
#endif
#if defined(OPT_3DNOW) || defined(OPT_3DNOW_VINTAGE)
	else if(basic_synth == synth_1to1_3dnow)
	{
		type = dreidnow;
#		ifdef OPT_3DNOW_VINTAGE
#		ifdef OPT_MULTI
		if(fr->cpu_opts.the_dct36 == dct36_3dnow)
#		endif
		type = dreidnow_vintage;
#		endif
	}
#endif
#ifdef OPT_MMX
	else if(basic_synth == synth_1to1_mmx) type = mmx;
#endif
#ifdef OPT_I586_DITHER
	else if(basic_synth == synth_1to1_i586_dither) type = ifuenf_dither;
#endif
#ifdef OPT_I586
	else if(basic_synth == synth_1to1_i586) type = ifuenf;
#endif
#ifdef OPT_ALTIVEC
	else if(basic_synth == synth_1to1_altivec) type = altivec;
#endif
#ifdef OPT_X86_64
	else if(basic_synth == synth_1to1_x86_64) type = x86_64;
#endif
#ifdef OPT_AVX
	else if(basic_synth == synth_1to1_avx) type = avx;
#endif
#ifdef OPT_ARM
	else if(basic_synth == synth_1to1_arm) type = arm;
#endif
#ifdef OPT_NEON
	else if(basic_synth == synth_1to1_neon) type = neon;
#endif
#ifdef OPT_NEON64
	else if(basic_synth == synth_1to1_neon64) type = neon64;
#endif
#ifdef OPT_GENERIC_DITHER
	else if(basic_synth == synth_1to1_dither) type = generic_dither;
#endif
#ifdef OPT_DITHER /* either i586 or generic! */
#ifndef NO_DOWNSAMPLE
	else if
	(
		   basic_synth == synth_2to1_dither
		|| basic_synth == synth_4to1_dither
	) type = generic_dither;
#endif
#endif
#endif /* 16bit */

#ifndef NO_SYNTH32

#ifndef NO_REAL
#if defined(OPT_SSE) || defined(OPT_SSE_VINTAGE)
	else if(basic_synth == synth_1to1_real_sse)
	{
		type = sse_or_vintage(fr);
	}
#endif
#ifdef OPT_X86_64
	else if(basic_synth == synth_1to1_real_x86_64) type = x86_64;
#endif
#ifdef OPT_AVX
	else if(basic_synth == synth_1to1_real_avx) type = avx;
#endif
#ifdef OPT_ALTIVEC
	else if(basic_synth == synth_1to1_real_altivec) type = altivec;
#endif
#ifdef OPT_NEON
	else if(basic_synth == synth_1to1_real_neon) type = neon;
#endif
#ifdef OPT_NEON64
	else if(basic_synth == synth_1to1_real_neon64) type = neon64;
#endif

#endif /* real */

#ifndef NO_32BIT
#if defined(OPT_SSE) || defined(OPT_SSE_VINTAGE)
	else if(basic_synth == synth_1to1_s32_sse)
	{
		type = sse_or_vintage(fr);
	}
#endif
#ifdef OPT_X86_64
	else if(basic_synth == synth_1to1_s32_x86_64) type = x86_64;
#endif
#ifdef OPT_AVX
	else if(basic_synth == synth_1to1_s32_avx) type = avx;
#endif
#ifdef OPT_ALTIVEC
	else if(basic_synth == synth_1to1_s32_altivec) type = altivec;
#endif
#ifdef OPT_NEON
	else if(basic_synth == synth_1to1_s32_neon) type = neon;
#endif
#ifdef OPT_NEON64
	else if(basic_synth == synth_1to1_s32_neon64) type = neon64;
#endif
#endif /* 32bit */

#endif /* any 32 bit synth */

#ifdef OPT_X86
	else if(find_synth(basic_synth, plain_i386))
	type = idrei;
#endif

	else if(find_synth(basic_synth, synth_base.plain))
	type = generic;



#ifdef OPT_I486
	/* i486 is special ... the specific code is in use for 16bit 1to1 stereo
	   otherwise we have i386 active... but still, the distinction doesn't matter*/
	type = ivier;
#endif

	if(type != nodec)
	{
		fr->cpu_opts.type = type;
		fr->cpu_opts.class = decclass(type);

		debug3("determined active decoder type %i (%s) of class %i", type, decname[type], fr->cpu_opts.class);
		return MPG123_OK;
	}
	else
	{
		if(NOQUIET) error("Unable to determine active decoder type -- this is SERIOUS b0rkage!");

		fr->err = MPG123_BAD_DECODER_SETUP;
		return MPG123_ERR;
	}
}