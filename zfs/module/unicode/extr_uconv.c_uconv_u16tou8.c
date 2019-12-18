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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ uchar_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ const BSWAP_16 (scalar_t__ const) ; 
 int E2BIG ; 
 int EBADF ; 
 int EILSEQ ; 
 int EINVAL ; 
 int UCONV_IGNORE_NULL ; 
 int UCONV_IN_ACCEPT_BOM ; 
 int UCONV_IN_NAT_ENDIAN ; 
 int UCONV_U16_BIT_MASK ; 
 int UCONV_U16_BIT_SHIFT ; 
 int UCONV_U16_HI_MAX ; 
 int UCONV_U16_HI_MIN ; 
 int UCONV_U16_LO_MAX ; 
 int UCONV_U16_LO_MIN ; 
 int UCONV_U16_START ; 
 int UCONV_U8_FOUR_BYTES ; 
 int UCONV_U8_ONE_BYTE ; 
 int UCONV_U8_THREE_BYTES ; 
 int UCONV_U8_TWO_BYTES ; 
 scalar_t__ check_bom16 (scalar_t__ const*,size_t,int*) ; 
 scalar_t__ check_endian (int,int*,int*) ; 

int
uconv_u16tou8(const uint16_t *u16s, size_t *utf16len,
    uchar_t *u8s, size_t *utf8len, int flag)
{
	int inendian;
	int outendian;
	size_t u16l;
	size_t u8l;
	uint32_t hi;
	uint32_t lo;
	boolean_t do_not_ignore_null;

	if (u16s == NULL || utf16len == NULL)
		return (EILSEQ);

	if (u8s == NULL || utf8len == NULL)
		return (E2BIG);

	if (check_endian(flag, &inendian, &outendian) != 0)
		return (EBADF);

	u16l = u8l = 0;
	hi = 0;
	do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

	if ((flag & UCONV_IN_ACCEPT_BOM) &&
	    check_bom16(u16s, *utf16len, &inendian))
		u16l++;

	inendian &= UCONV_IN_NAT_ENDIAN;

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

		/*
		 * Now we convert a UTF-32 character into a UTF-8 character.
		 * Unicode coding space is between U+0000 and U+10FFFF;
		 * anything bigger is an illegal character.
		 */
		if (lo <= UCONV_U8_ONE_BYTE) {
			if (u8l >= *utf8len)
				return (E2BIG);
			u8s[u8l++] = (uchar_t)lo;
		} else if (lo <= UCONV_U8_TWO_BYTES) {
			if ((u8l + 1) >= *utf8len)
				return (E2BIG);
			u8s[u8l++] = (uchar_t)(0xc0 | ((lo & 0x07c0) >> 6));
			u8s[u8l++] = (uchar_t)(0x80 |  (lo & 0x003f));
		} else if (lo <= UCONV_U8_THREE_BYTES) {
			if ((u8l + 2) >= *utf8len)
				return (E2BIG);
			u8s[u8l++] = (uchar_t)(0xe0 | ((lo & 0x0f000) >> 12));
			u8s[u8l++] = (uchar_t)(0x80 | ((lo & 0x00fc0) >> 6));
			u8s[u8l++] = (uchar_t)(0x80 |  (lo & 0x0003f));
		} else if (lo <= UCONV_U8_FOUR_BYTES) {
			if ((u8l + 3) >= *utf8len)
				return (E2BIG);
			u8s[u8l++] = (uchar_t)(0xf0 | ((lo & 0x01c0000) >> 18));
			u8s[u8l++] = (uchar_t)(0x80 | ((lo & 0x003f000) >> 12));
			u8s[u8l++] = (uchar_t)(0x80 | ((lo & 0x0000fc0) >> 6));
			u8s[u8l++] = (uchar_t)(0x80 |  (lo & 0x000003f));
		} else {
			return (EILSEQ);
		}
	}

	if (hi)
		return (EINVAL);

	*utf16len = u16l;
	*utf8len = u8l;

	return (0);
}