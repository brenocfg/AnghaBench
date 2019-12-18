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
typedef  scalar_t__ uchar_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ const BSWAP_32 (scalar_t__ const) ; 
 int E2BIG ; 
 int EBADF ; 
 int EILSEQ ; 
 int UCONV_IGNORE_NULL ; 
 int UCONV_IN_ACCEPT_BOM ; 
 int UCONV_IN_NAT_ENDIAN ; 
 scalar_t__ UCONV_U8_FOUR_BYTES ; 
 scalar_t__ UCONV_U8_ONE_BYTE ; 
 scalar_t__ UCONV_U8_THREE_BYTES ; 
 scalar_t__ UCONV_U8_TWO_BYTES ; 
 scalar_t__ check_bom32 (scalar_t__ const*,size_t,int*) ; 
 scalar_t__ check_endian (int,int*,int*) ; 

int
uconv_u32tou8(const uint32_t *u32s, size_t *utf32len,
    uchar_t *u8s, size_t *utf8len, int flag)
{
	int inendian;
	int outendian;
	size_t u32l;
	size_t u8l;
	uint32_t lo;
	boolean_t do_not_ignore_null;

	if (u32s == NULL || utf32len == NULL)
		return (EILSEQ);

	if (u8s == NULL || utf8len == NULL)
		return (E2BIG);

	if (check_endian(flag, &inendian, &outendian) != 0)
		return (EBADF);

	u32l = u8l = 0;
	do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

	if ((flag & UCONV_IN_ACCEPT_BOM) &&
	    check_bom32(u32s, *utf32len, &inendian))
		u32l++;

	inendian &= UCONV_IN_NAT_ENDIAN;

	for (; u32l < *utf32len; u32l++) {
		if (u32s[u32l] == 0 && do_not_ignore_null)
			break;

		lo = (inendian) ? u32s[u32l] : BSWAP_32(u32s[u32l]);

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

	*utf32len = u32l;
	*utf8len = u8l;

	return (0);
}