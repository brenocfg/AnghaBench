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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ const BSWAP_16 (scalar_t__ const) ; 
 scalar_t__ BSWAP_32 (scalar_t__) ; 
 int E2BIG ; 
 int EBADF ; 
 int EILSEQ ; 
 int EINVAL ; 
 scalar_t__ UCONV_BOM_NORMAL ; 
 scalar_t__ UCONV_BOM_SWAPPED_32 ; 
 int UCONV_IGNORE_NULL ; 
 int UCONV_IN_ACCEPT_BOM ; 
 int UCONV_IN_NAT_ENDIAN ; 
 int UCONV_OUT_EMIT_BOM ; 
 int UCONV_OUT_NAT_ENDIAN ; 
 scalar_t__ UCONV_U16_BIT_MASK ; 
 scalar_t__ UCONV_U16_BIT_SHIFT ; 
 scalar_t__ UCONV_U16_HI_MAX ; 
 scalar_t__ UCONV_U16_HI_MIN ; 
 scalar_t__ UCONV_U16_LO_MAX ; 
 scalar_t__ UCONV_U16_LO_MIN ; 
 scalar_t__ UCONV_U16_START ; 
 scalar_t__ check_bom16 (scalar_t__ const*,size_t,int*) ; 
 scalar_t__ check_endian (int,int*,int*) ; 

int
uconv_u16tou32(const uint16_t *u16s, size_t *utf16len,
    uint32_t *u32s, size_t *utf32len, int flag)
{
	int inendian;
	int outendian;
	size_t u16l;
	size_t u32l;
	uint32_t hi;
	uint32_t lo;
	boolean_t do_not_ignore_null;

	/*
	 * Do preliminary validity checks on parameters and collect info on
	 * endians.
	 */
	if (u16s == NULL || utf16len == NULL)
		return (EILSEQ);

	if (u32s == NULL || utf32len == NULL)
		return (E2BIG);

	if (check_endian(flag, &inendian, &outendian) != 0)
		return (EBADF);

	/*
	 * Initialize input and output parameter buffer indices and
	 * temporary variables.
	 */
	u16l = u32l = 0;
	hi = 0;
	do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

	/*
	 * Check on the BOM at the beginning of the input buffer if required
	 * and if there is indeed one, process it.
	 */
	if ((flag & UCONV_IN_ACCEPT_BOM) &&
	    check_bom16(u16s, *utf16len, &inendian))
		u16l++;

	/*
	 * Reset inendian and outendian so that after this point, those can be
	 * used as condition values.
	 */
	inendian &= UCONV_IN_NAT_ENDIAN;
	outendian &= UCONV_OUT_NAT_ENDIAN;

	/*
	 * If there is something in the input buffer and if necessary and
	 * requested, save the BOM at the output buffer.
	 */
	if (*utf16len > 0 && *utf32len > 0 && (flag & UCONV_OUT_EMIT_BOM))
		u32s[u32l++] = (outendian) ? UCONV_BOM_NORMAL :
		    UCONV_BOM_SWAPPED_32;

	/*
	 * Do conversion; if encounter a surrogate pair, assemble high and
	 * low pair values to form a UTF-32 character. If a half of a pair
	 * exists alone, then, either it is an illegal (EILSEQ) or
	 * invalid (EINVAL) value.
	 */
	for (; u16l < *utf16len; u16l++) {
		if (u16s[u16l] == 0 && do_not_ignore_null)
			break;

		lo = (uint32_t)((inendian) ? u16s[u16l] : BSWAP_16(u16s[u16l]));

		if (lo >= UCONV_U16_HI_MIN && lo <= UCONV_U16_HI_MAX) {
			if (hi)
				return (EILSEQ);
			hi = lo;
			continue;
		} else if (lo >= UCONV_U16_LO_MIN && lo <= UCONV_U16_LO_MAX) {
			if (! hi)
				return (EILSEQ);
			lo = (((hi - UCONV_U16_HI_MIN) * UCONV_U16_BIT_SHIFT +
			    lo - UCONV_U16_LO_MIN) & UCONV_U16_BIT_MASK)
			    + UCONV_U16_START;
			hi = 0;
		} else if (hi) {
			return (EILSEQ);
		}

		if (u32l >= *utf32len)
			return (E2BIG);

		u32s[u32l++] = (outendian) ? lo : BSWAP_32(lo);
	}

	/*
	 * If high half didn't see low half, then, it's most likely the input
	 * parameter is incomplete.
	 */
	if (hi)
		return (EINVAL);

	/*
	 * Save the number of consumed and saved characters. They do not
	 * include terminating NULL character (U+0000) at the end of
	 * the input buffer (even when UCONV_IGNORE_NULL isn't specified and
	 * the input buffer length is big enough to include the terminating
	 * NULL character).
	 */
	*utf16len = u16l;
	*utf32len = u32l;

	return (0);
}