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
 scalar_t__ BSWAP_16 (scalar_t__) ; 
 scalar_t__ const BSWAP_32 (scalar_t__ const) ; 
 int E2BIG ; 
 int EBADF ; 
 int EILSEQ ; 
 scalar_t__ UCONV_BOM_NORMAL ; 
 scalar_t__ UCONV_BOM_SWAPPED ; 
 int UCONV_IGNORE_NULL ; 
 int UCONV_IN_ACCEPT_BOM ; 
 int UCONV_IN_NAT_ENDIAN ; 
 int UCONV_OUT_EMIT_BOM ; 
 int UCONV_OUT_NAT_ENDIAN ; 
 scalar_t__ UCONV_U16_BIT_SHIFT ; 
 scalar_t__ UCONV_U16_HI_MIN ; 
 scalar_t__ UCONV_U16_LO_MIN ; 
 scalar_t__ UCONV_U16_START ; 
 scalar_t__ UCONV_UNICODE_MAX ; 
 scalar_t__ check_bom32 (scalar_t__ const*,size_t,int*) ; 
 scalar_t__ check_endian (int,int*,int*) ; 

int
uconv_u32tou16(const uint32_t *u32s, size_t *utf32len,
    uint16_t *u16s, size_t *utf16len, int flag)
{
	int inendian;
	int outendian;
	size_t u16l;
	size_t u32l;
	uint32_t hi;
	uint32_t lo;
	boolean_t do_not_ignore_null;

	if (u32s == NULL || utf32len == NULL)
		return (EILSEQ);

	if (u16s == NULL || utf16len == NULL)
		return (E2BIG);

	if (check_endian(flag, &inendian, &outendian) != 0)
		return (EBADF);

	u16l = u32l = 0;
	do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

	if ((flag & UCONV_IN_ACCEPT_BOM) &&
	    check_bom32(u32s, *utf32len, &inendian))
		u32l++;

	inendian &= UCONV_IN_NAT_ENDIAN;
	outendian &= UCONV_OUT_NAT_ENDIAN;

	if (*utf32len > 0 && *utf16len > 0 && (flag & UCONV_OUT_EMIT_BOM))
		u16s[u16l++] = (outendian) ? UCONV_BOM_NORMAL :
		    UCONV_BOM_SWAPPED;

	for (; u32l < *utf32len; u32l++) {
		if (u32s[u32l] == 0 && do_not_ignore_null)
			break;

		hi = (inendian) ? u32s[u32l] : BSWAP_32(u32s[u32l]);

		/*
		 * Anything bigger than the Unicode coding space, i.e.,
		 * Unicode scalar value bigger than U+10FFFF, is an illegal
		 * character.
		 */
		if (hi > UCONV_UNICODE_MAX)
			return (EILSEQ);

		/*
		 * Anything bigger than U+FFFF must be converted into
		 * a surrogate pair in UTF-16.
		 */
		if (hi >= UCONV_U16_START) {
			lo = ((hi - UCONV_U16_START) % UCONV_U16_BIT_SHIFT) +
			    UCONV_U16_LO_MIN;
			hi = ((hi - UCONV_U16_START) / UCONV_U16_BIT_SHIFT) +
			    UCONV_U16_HI_MIN;

			if ((u16l + 1) >= *utf16len)
				return (E2BIG);

			if (outendian) {
				u16s[u16l++] = (uint16_t)hi;
				u16s[u16l++] = (uint16_t)lo;
			} else {
				u16s[u16l++] = BSWAP_16(((uint16_t)hi));
				u16s[u16l++] = BSWAP_16(((uint16_t)lo));
			}
		} else {
			if (u16l >= *utf16len)
				return (E2BIG);
			u16s[u16l++] = (outendian) ? (uint16_t)hi :
			    BSWAP_16(((uint16_t)hi));
		}
	}

	*utf16len = u16l;
	*utf32len = u32l;

	return (0);
}