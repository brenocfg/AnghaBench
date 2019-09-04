#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

void check_decoders(void )
{
#ifndef OPT_MULTI
	/* In non-multi mode, only the full list (one entry) is used. */
	return;
#else
	const char **d = mpg123_supported_decoder_list;
#if (defined OPT_X86) || (defined OPT_X86_64) || (defined OPT_NEON) || (defined OPT_NEON64)
	getcpuflags(&cpu_flags);
#endif
#ifdef OPT_X86
	if(cpu_i586(cpu_flags))
	{
		/* not yet: if(cpu_sse2(cpu_flags)) printf(" SSE2");
		if(cpu_sse3(cpu_flags)) printf(" SSE3"); */
#ifdef OPT_SSE
		if(cpu_sse(cpu_flags)) *(d++) = dn_sse;
#endif
#ifdef OPT_SSE_VINTAGE
		if(cpu_sse(cpu_flags)) *(d++) = dn_sse_vintage;
#endif
#ifdef OPT_3DNOWEXT
		if(cpu_3dnowext(cpu_flags)) *(d++) = dn_dreidnowext;
#endif
#ifdef OPT_3DNOWEXT_VINTAGE
		if(cpu_3dnowext(cpu_flags)) *(d++) = dn_dreidnowext_vintage;
#endif
#ifdef OPT_3DNOW
		if(cpu_3dnow(cpu_flags)) *(d++) = dn_dreidnow;
#endif
#ifdef OPT_3DNOW_VINTAGE
		if(cpu_3dnow(cpu_flags)) *(d++) = dn_dreidnow_vintage;
#endif
#ifdef OPT_MMX
		if(cpu_mmx(cpu_flags)) *(d++) = dn_mmx;
#endif
#ifdef OPT_I586
		*(d++) = dn_ifuenf;
#endif
#ifdef OPT_I586_DITHER
		*(d++) = dn_ifuenf_dither;
#endif
	}
#endif
/* just assume that the i486 built is run on a i486 cpu... */
#ifdef OPT_I486
	*(d++) = dn_ivier;
#endif
#ifdef OPT_ALTIVEC
	*(d++) = dn_altivec;
#endif
/* every supported x86 can do i386, any cpu can do generic */
#ifdef OPT_I386
	*(d++) = dn_idrei;
#endif
#ifdef OPT_AVX
	if(cpu_avx(cpu_flags)) *(d++) = dn_avx;
#endif
#ifdef OPT_X86_64
	*(d++) = dn_x86_64;
#endif
#ifdef OPT_ARM
	*(d++) = dn_arm;
#endif
#ifdef OPT_NEON
	if(cpu_neon(cpu_flags)) *(d++) = dn_neon;
#endif
#ifdef OPT_NEON64
	if(cpu_neon(cpu_flags)) *(d++) = dn_neon64;
#endif
#ifdef OPT_GENERIC
	*(d++) = dn_generic;
#endif
#ifdef OPT_GENERIC_DITHER
	*(d++) = dn_generic_dither;
#endif
#endif /* ndef OPT_MULTI */
}