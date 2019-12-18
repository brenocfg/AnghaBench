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
typedef  int real ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_5__ {double outscale; } ;
struct TYPE_7__ {double lastscale; void** decwin; TYPE_2__ cpu_opts; TYPE_1__ p; } ;
typedef  TYPE_3__ mpg123_handle ;

/* Variables and functions */
 void* DOUBLE_TO_REAL (double) ; 
 int DOUBLE_TO_REAL_15 (double) ; 
 scalar_t__ NOQUIET ; 
 void* REAL_SCALE_WINDOW (int /*<<< orphan*/ ) ; 
 scalar_t__ altivec ; 
 scalar_t__ arm ; 
 scalar_t__ avx ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug1 (char*,long) ; 
 scalar_t__* intwinbase ; 
 scalar_t__ neon ; 
 scalar_t__ neon64 ; 
 int /*<<< orphan*/  sat_mul32 (scalar_t__,int) ; 
 scalar_t__ sse ; 
 scalar_t__ sse_vintage ; 
 int /*<<< orphan*/  warning (char*) ; 
 scalar_t__ x86_64 ; 

void make_decode_tables(mpg123_handle *fr)
{
	int i,j;
	int idx = 0;
	double scaleval;
#ifdef REAL_IS_FIXED
	real scaleval_long;
#endif
	/* Scale is always based on 1.0 . */
	scaleval = -0.5*(fr->lastscale < 0 ? fr->p.outscale : fr->lastscale);
	debug1("decode tables with scaleval %g", scaleval);
#ifdef REAL_IS_FIXED
	scaleval_long = DOUBLE_TO_REAL_15(scaleval);
	debug1("decode table with fixed scaleval %li", (long)scaleval_long);
	if(scaleval_long > 28618 || scaleval_long < -28618)
	{
		/* TODO: Limit the scaleval itself or limit the multiplication afterwards?
		   The former basically disables significant amplification for fixed-point
		   decoders, but avoids (possibly subtle) distortion. */
		/* This would limit the amplification instead:
		   scaleval_long = scaleval_long < 0 ? -28618 : 28618; */
		if(NOQUIET) warning("Desired amplification may introduce distortion.");
	}
#endif
	for(i=0,j=0;i<256;i++,j++,idx+=32)
	{
		if(idx < 512+16)
#ifdef REAL_IS_FIXED
		fr->decwin[idx+16] = fr->decwin[idx] =
			REAL_SCALE_WINDOW(sat_mul32(intwinbase[j],scaleval_long));
#else
		fr->decwin[idx+16] = fr->decwin[idx] = DOUBLE_TO_REAL((double) intwinbase[j] * scaleval);
#endif

		if(i % 32 == 31)
		idx -= 1023;
		if(i % 64 == 63)
#ifdef REAL_IS_FIXED
		scaleval_long = - scaleval_long;
#else
		scaleval = - scaleval;
#endif
	}

	for( /* i=256 */ ;i<512;i++,j--,idx+=32)
	{
		if(idx < 512+16)
#ifdef REAL_IS_FIXED
		fr->decwin[idx+16] = fr->decwin[idx] =
			REAL_SCALE_WINDOW(sat_mul32(intwinbase[j],scaleval_long));
#else
		fr->decwin[idx+16] = fr->decwin[idx] = DOUBLE_TO_REAL((double) intwinbase[j] * scaleval);
#endif

		if(i % 32 == 31)
		idx -= 1023;
		if(i % 64 == 63)
#ifdef REAL_IS_FIXED
		scaleval_long = - scaleval_long;
#else
		scaleval = - scaleval;
#endif
	}
#if defined(OPT_X86_64) || defined(OPT_ALTIVEC) || defined(OPT_SSE) || defined(OPT_SSE_VINTAGE) || defined(OPT_ARM) || defined(OPT_NEON) || defined(OPT_NEON64) || defined(OPT_AVX)
	if(  fr->cpu_opts.type == x86_64
	  || fr->cpu_opts.type == altivec
	  || fr->cpu_opts.type == sse
	  || fr->cpu_opts.type == sse_vintage
	  || fr->cpu_opts.type == arm
	  || fr->cpu_opts.type == neon
	  || fr->cpu_opts.type == neon64
	  || fr->cpu_opts.type == avx )
	{ /* for float SSE / AltiVec / ARM decoder */
		for(i=512; i<512+32; i++)
		{
			fr->decwin[i] = (i&1) ? fr->decwin[i] : 0;
		}
		for(i=0; i<512; i++)
		{
			fr->decwin[512+32+i] = -fr->decwin[511-i];
		}
#if defined(OPT_NEON) || defined(OPT_NEON64)
		if(fr->cpu_opts.type == neon || fr->cpu_opts.type == neon64)
		{
			for(i=0; i<512; i+=2)
			{
				fr->decwin[i] = -fr->decwin[i];
			}
		}
#endif
	}
#endif
	debug("decode tables done");
}