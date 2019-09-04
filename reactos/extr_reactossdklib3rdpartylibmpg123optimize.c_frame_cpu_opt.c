#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__** plain; int /*<<< orphan*/ ** mono2stereo; int /*<<< orphan*/ ** mono; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  class; } ;
struct TYPE_6__ {TYPE_3__ synths; TYPE_1__ cpu_opts; } ;
typedef  TYPE_2__ mpg123_handle ;
typedef  enum optdec { ____Placeholder_optdec } optdec ;

/* Variables and functions */
 scalar_t__ NOQUIET ; 
 int TRUE ; 
 scalar_t__ VERBOSE ; 
 int autodec ; 
 int /*<<< orphan*/  decclass (scalar_t__) ; 
 int dectype (char const*) ; 
 int defopt ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error2 (char*,int,int) ; 
 size_t f_16 ; 
 size_t f_8 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ generic_dither ; 
 scalar_t__ ifuenf_dither ; 
 void* nodec ; 
 size_t r_1to1 ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ synth_1to1_8bit_wrap ; 
 int /*<<< orphan*/  synth_1to1_8bit_wrap_m2s ; 
 int /*<<< orphan*/  synth_1to1_8bit_wrap_mono ; 
 TYPE_3__ synth_base ; 

int frame_cpu_opt(mpg123_handle *fr, const char* cpu)
{
	const char* chosen = ""; /* the chosen decoder opt as string */
	enum optdec want_dec = nodec;
	int done = 0;
	int auto_choose = 0;
#ifdef OPT_DITHER
	int dithered = FALSE; /* If some dithered decoder is chosen. */
#endif

	want_dec = dectype(cpu);
	auto_choose = want_dec == autodec;
	/* Fill whole array of synth functions with generic code first. */
	fr->synths = synth_base;

#ifndef OPT_MULTI
	{
		if(!auto_choose && want_dec != defopt)
		{
			if(NOQUIET) error2("you wanted decoder type %i, I only have %i", want_dec, defopt);
		}
		auto_choose = TRUE; /* There will be only one choice anyway. */
	}
#endif

	fr->cpu_opts.type = nodec;
#ifdef OPT_MULTI
#ifndef NO_LAYER3
#if (defined OPT_3DNOW_VINTAGE || defined OPT_3DNOWEXT_VINTAGE || defined OPT_SSE || defined OPT_X86_64 || defined OPT_AVX || defined OPT_NEON || defined OPT_NEON64)
	fr->cpu_opts.the_dct36 = dct36;
#endif
#endif
#endif
	/* covers any i386+ cpu; they actually differ only in the synth_1to1 function, mostly... */
#ifdef OPT_X86
	if(cpu_i586(cpu_flags))
	{
#		ifdef OPT_MULTI
		debug2("standard flags: 0x%08x\textended flags: 0x%08x", cpu_flags.std, cpu_flags.ext);
#		endif
#		ifdef OPT_SSE
		if(   !done && (auto_choose || want_dec == sse)
		   && cpu_sse(cpu_flags) && cpu_mmx(cpu_flags) )
		{
			chosen = dn_sse;
			fr->cpu_opts.type = sse;
#ifdef OPT_MULTI
#			ifndef NO_LAYER3
			/* if(cpu_fast_sse(cpu_flags)) */ fr->cpu_opts.the_dct36 = dct36_sse;
#			endif
#endif
#			ifndef NO_16BIT
			fr->synths.plain[r_1to1][f_16] = synth_1to1_sse;
#			ifdef ACCURATE_ROUNDING
			fr->synths.stereo[r_1to1][f_16] = synth_1to1_stereo_sse;
#			endif
#			endif
#			ifndef NO_REAL
			fr->synths.plain[r_1to1][f_real] = synth_1to1_real_sse;
			fr->synths.stereo[r_1to1][f_real] = synth_1to1_real_stereo_sse;
#			endif
#			ifndef NO_32BIT
			fr->synths.plain[r_1to1][f_32] = synth_1to1_s32_sse;
			fr->synths.stereo[r_1to1][f_32] = synth_1to1_s32_stereo_sse;
#			endif
			done = 1;
		}
#		endif
#		ifdef OPT_SSE_VINTAGE
		if(   !done && (auto_choose || want_dec == sse_vintage)
		   && cpu_sse(cpu_flags) && cpu_mmx(cpu_flags) )
		{
			chosen = dn_sse_vintage;
			fr->cpu_opts.type = sse_vintage;
#			ifndef NO_16BIT
			fr->synths.plain[r_1to1][f_16] = synth_1to1_sse;
#			ifdef ACCURATE_ROUNDING
			fr->synths.stereo[r_1to1][f_16] = synth_1to1_stereo_sse;
#			endif
#			endif
#			ifndef NO_REAL
			fr->synths.plain[r_1to1][f_real] = synth_1to1_real_sse;
			fr->synths.stereo[r_1to1][f_real] = synth_1to1_real_stereo_sse;
#			endif
#			ifndef NO_32BIT
			fr->synths.plain[r_1to1][f_32] = synth_1to1_s32_sse;
			fr->synths.stereo[r_1to1][f_32] = synth_1to1_s32_stereo_sse;
#			endif
			done = 1;
		}
#		endif
#		ifdef OPT_3DNOWEXT
		if(   !done && (auto_choose || want_dec == dreidnowext)
		   && cpu_3dnow(cpu_flags)
		   && cpu_3dnowext(cpu_flags)
		   && cpu_mmx(cpu_flags) )
		{
			chosen = dn_dreidnowext;
			fr->cpu_opts.type = dreidnowext;
#			ifndef NO_16BIT
			fr->synths.plain[r_1to1][f_16] = synth_1to1_3dnowext;
#			endif
			done = 1;
		}
#		endif
#		ifdef OPT_3DNOWEXT_VINTAGE
		if(   !done && (auto_choose || want_dec == dreidnowext_vintage)
		   && cpu_3dnow(cpu_flags)
		   && cpu_3dnowext(cpu_flags)
		   && cpu_mmx(cpu_flags) )
		{
			chosen = dn_dreidnowext_vintage;
			fr->cpu_opts.type = dreidnowext_vintage;
#ifdef OPT_MULTI
#			ifndef NO_LAYER3
			fr->cpu_opts.the_dct36 = dct36_3dnowext;
#			endif
#endif
#			ifndef NO_16BIT
			fr->synths.plain[r_1to1][f_16] = synth_1to1_3dnowext;
#			endif
			done = 1;
		}
#		endif
#		ifdef OPT_3DNOW
		if(    !done && (auto_choose || want_dec == dreidnow)
		    && cpu_3dnow(cpu_flags) && cpu_mmx(cpu_flags) )
		{
			chosen = dn_dreidnow;
			fr->cpu_opts.type = dreidnow;
#			ifndef NO_16BIT
			fr->synths.plain[r_1to1][f_16] = synth_1to1_3dnow;
#			endif
			done = 1;
		}
#		endif
#		ifdef OPT_3DNOW_VINTAGE
		if(    !done && (auto_choose || want_dec == dreidnow_vintage)
		    && cpu_3dnow(cpu_flags) && cpu_mmx(cpu_flags) )
		{
			chosen = dn_dreidnow_vintage;
			fr->cpu_opts.type = dreidnow_vintage;
#ifdef OPT_MULTI
#			ifndef NO_LAYER3
			fr->cpu_opts.the_dct36 = dct36_3dnow;
#			endif
#endif
#			ifndef NO_16BIT
			fr->synths.plain[r_1to1][f_16] = synth_1to1_3dnow;
#			endif
			done = 1;
		}
#		endif
		#ifdef OPT_MMX
		if(   !done && (auto_choose || want_dec == mmx)
		   && cpu_mmx(cpu_flags) )
		{
			chosen = dn_mmx;
			fr->cpu_opts.type = mmx;
#			ifndef NO_16BIT
			fr->synths.plain[r_1to1][f_16] = synth_1to1_mmx;
#			endif
			done = 1;
		}
		#endif
		#ifdef OPT_I586
		if(!done && (auto_choose || want_dec == ifuenf))
		{
			chosen = "i586/pentium";
			fr->cpu_opts.type = ifuenf;
#			ifndef NO_16BIT
			fr->synths.plain[r_1to1][f_16] = synth_1to1_i586;
#			endif
			done = 1;
		}
		#endif
		#ifdef OPT_I586_DITHER
		if(!done && (auto_choose || want_dec == ifuenf_dither))
		{
			chosen = "dithered i586/pentium";
			fr->cpu_opts.type = ifuenf_dither;
			dithered = TRUE;
#			ifndef NO_16BIT
			fr->synths.plain[r_1to1][f_16] = synth_1to1_i586_dither;
#			ifndef NO_DOWNSAMPLE
			fr->synths.plain[r_2to1][f_16] = synth_2to1_dither;
			fr->synths.plain[r_4to1][f_16] = synth_4to1_dither;
#			endif
#			endif
			done = 1;
		}
		#endif
	}
	#ifdef OPT_I486
	/* That won't cooperate in multi opt mode - forcing i486 in layer3.c
	   But still... here it is... maybe for real use in future. */
	if(!done && (auto_choose || want_dec == ivier))
	{
		chosen = dn_ivier;
		fr->cpu_opts.type = ivier;
		done = 1;
	}
	#endif
	#ifdef OPT_I386
	if(!done && (auto_choose || want_dec == idrei))
	{
		chosen = dn_idrei;
		fr->cpu_opts.type = idrei;
		done = 1;
	}
	#endif

	if(done)
	{
		/*
			We have chosen some x86 decoder... fillup some i386 stuff.
			There is an open question about using dithered synth_1to1 for 8bit wrappers.
			For quality it won't make sense, but wrapped i586_dither wrapped may still be faster...
		*/
		enum synth_resample ri;
		enum synth_format   fi;
#		ifndef NO_8BIT
#		ifndef NO_16BIT /* possibility to use a 16->8 wrapper... */
		if(fr->synths.plain[r_1to1][f_16] != synth_base.plain[r_1to1][f_16])
		{
			fr->synths.plain[r_1to1][f_8] = synth_1to1_8bit_wrap;
			fr->synths.mono[r_1to1][f_8] = synth_1to1_8bit_wrap_mono;
			fr->synths.mono2stereo[r_1to1][f_8] = synth_1to1_8bit_wrap_m2s;
		}
#		endif
#		endif
		for(ri=0; ri<r_limit; ++ri)
		for(fi=0; fi<f_limit; ++fi)
		{
			if(fr->synths.plain[ri][fi] == synth_base.plain[ri][fi])
			fr->synths.plain[ri][fi] = plain_i386[ri][fi];
		}
	}

#endif /* OPT_X86 */

#ifdef OPT_AVX
	if(!done && (auto_choose || want_dec == avx) && cpu_avx(cpu_flags))
	{
		chosen = "x86-64 (AVX)";
		fr->cpu_opts.type = avx;
#ifdef OPT_MULTI
#		ifndef NO_LAYER3
		fr->cpu_opts.the_dct36 = dct36_avx;
#		endif
#endif
#		ifndef NO_16BIT
		fr->synths.plain[r_1to1][f_16] = synth_1to1_avx;
		fr->synths.stereo[r_1to1][f_16] = synth_1to1_stereo_avx;
#		endif
#		ifndef NO_REAL
		fr->synths.plain[r_1to1][f_real] = synth_1to1_real_avx;
		fr->synths.stereo[r_1to1][f_real] = synth_1to1_fltst_avx;
#		endif
#		ifndef NO_32BIT
		fr->synths.plain[r_1to1][f_32] = synth_1to1_s32_avx;
		fr->synths.stereo[r_1to1][f_32] = synth_1to1_s32_stereo_avx;
#		endif
		done = 1;
	}
#endif

#ifdef OPT_X86_64
	if(!done && (auto_choose || want_dec == x86_64))
	{
		chosen = "x86-64 (SSE)";
		fr->cpu_opts.type = x86_64;
#ifdef OPT_MULTI
#		ifndef NO_LAYER3
		fr->cpu_opts.the_dct36 = dct36_x86_64;
#		endif
#endif
#		ifndef NO_16BIT
		fr->synths.plain[r_1to1][f_16] = synth_1to1_x86_64;
		fr->synths.stereo[r_1to1][f_16] = synth_1to1_stereo_x86_64;
#		endif
#		ifndef NO_REAL
		fr->synths.plain[r_1to1][f_real] = synth_1to1_real_x86_64;
		fr->synths.stereo[r_1to1][f_real] = synth_1to1_real_stereo_x86_64;
#		endif
#		ifndef NO_32BIT
		fr->synths.plain[r_1to1][f_32] = synth_1to1_s32_x86_64;
		fr->synths.stereo[r_1to1][f_32] = synth_1to1_s32_stereo_x86_64;
#		endif
		done = 1;
	}
#endif

#	ifdef OPT_ALTIVEC
	if(!done && (auto_choose || want_dec == altivec))
	{
		chosen = dn_altivec;
		fr->cpu_opts.type = altivec;
#		ifndef NO_16BIT
		fr->synths.plain[r_1to1][f_16] = synth_1to1_altivec;
		fr->synths.stereo[r_1to1][f_16] = synth_1to1_stereo_altivec;
#		endif
#		ifndef NO_REAL
		fr->synths.plain[r_1to1][f_real] = synth_1to1_real_altivec;
		fr->synths.stereo[r_1to1][f_real] = synth_1to1_fltst_altivec;
#		endif
#		ifndef NO_32BIT
		fr->synths.plain[r_1to1][f_32] = synth_1to1_s32_altivec;
		fr->synths.stereo[r_1to1][f_32] = synth_1to1_s32_stereo_altivec;
#		endif
		done = 1;
	}
#	endif

#	ifdef OPT_NEON
	if(!done && (auto_choose || want_dec == neon) && cpu_neon(cpu_flags))
	{
		chosen = dn_neon;
		fr->cpu_opts.type = neon;
#ifdef OPT_MULTI
#		ifndef NO_LAYER3
		fr->cpu_opts.the_dct36 = dct36_neon;
#		endif
#endif
#		ifndef NO_16BIT
		fr->synths.plain[r_1to1][f_16] = synth_1to1_neon;
		fr->synths.stereo[r_1to1][f_16] = synth_1to1_stereo_neon;
#		endif
#		ifndef NO_REAL
		fr->synths.plain[r_1to1][f_real] = synth_1to1_real_neon;
		fr->synths.stereo[r_1to1][f_real] = synth_1to1_real_stereo_neon;
#		endif
#		ifndef NO_32BIT
		fr->synths.plain[r_1to1][f_32] = synth_1to1_s32_neon;
		fr->synths.stereo[r_1to1][f_32] = synth_1to1_s32_stereo_neon;
#		endif
		done = 1;
	}
#	endif

#	ifdef OPT_ARM
	if(!done && (auto_choose || want_dec == arm))
	{
		chosen = dn_arm;
		fr->cpu_opts.type = arm;
#		ifndef NO_16BIT
		fr->synths.plain[r_1to1][f_16] = synth_1to1_arm;
#		endif
		done = 1;
	}
#	endif

#	ifdef OPT_NEON64
	if(!done && (auto_choose || want_dec == neon64) && cpu_neon(cpu_flags))
	{
		chosen = dn_neon64;
		fr->cpu_opts.type = neon64;
#ifdef OPT_MULTI
#		ifndef NO_LAYER3
		fr->cpu_opts.the_dct36 = dct36_neon64;
#		endif
#endif
#		ifndef NO_16BIT
		fr->synths.plain[r_1to1][f_16] = synth_1to1_neon64;
		fr->synths.stereo[r_1to1][f_16] = synth_1to1_stereo_neon64;
#		endif
#		ifndef NO_REAL
		fr->synths.plain[r_1to1][f_real] = synth_1to1_real_neon64;
		fr->synths.stereo[r_1to1][f_real] = synth_1to1_fltst_neon64;
#		endif
#		ifndef NO_32BIT
		fr->synths.plain[r_1to1][f_32] = synth_1to1_s32_neon64;
		fr->synths.stereo[r_1to1][f_32] = synth_1to1_s32st_neon64;
#		endif
		done = 1;
	}
#	endif

#	ifdef OPT_GENERIC
	if(!done && (auto_choose || want_dec == generic))
	{
		chosen = dn_generic;
		fr->cpu_opts.type = generic;
		done = 1;
	}
#	endif

#ifdef OPT_GENERIC_DITHER
	if(!done && (auto_choose || want_dec == generic_dither))
	{
		chosen = "dithered generic";
		fr->cpu_opts.type = generic_dither;
		dithered = TRUE;
#		ifndef NO_16BIT
		fr->synths.plain[r_1to1][f_16] = synth_1to1_dither;
#		ifndef NO_DOWNSAMPLE
		fr->synths.plain[r_2to1][f_16] = synth_2to1_dither;
		fr->synths.plain[r_4to1][f_16] = synth_4to1_dither;
#		endif
#		endif
		done = 1;
	}
#endif

	fr->cpu_opts.class = decclass(fr->cpu_opts.type);

#	ifndef NO_8BIT
#	ifndef NO_16BIT /* possibility to use a 16->8 wrapper... */
	/* Last chance to use some optimized routine via generic wrappers (for 8bit). */
	if(     fr->cpu_opts.type != ifuenf_dither
	     && fr->cpu_opts.type != generic_dither
	     && fr->synths.plain[r_1to1][f_16] != synth_base.plain[r_1to1][f_16] )
	{
		fr->synths.plain[r_1to1][f_8] = synth_1to1_8bit_wrap;
		fr->synths.mono[r_1to1][f_8] = synth_1to1_8bit_wrap_mono;
		fr->synths.mono2stereo[r_1to1][f_8] = synth_1to1_8bit_wrap_m2s;
	}
#	endif
#	endif

#ifdef OPT_DITHER
	if(done && dithered)
	{
		/* run-time dither noise table generation */
		if(!frame_dither_init(fr))
		{
			if(NOQUIET) error("Dither noise setup failed!");
			return 0;
		}
	}
#endif

	if(done)
	{
		if(VERBOSE) fprintf(stderr, "Decoder: %s\n", chosen);
		return 1;
	}
	else
	{
		if(NOQUIET) error("Could not set optimization!");
		return 0;
	}
}