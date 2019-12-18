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
typedef  size_t uint32_t ;
typedef  scalar_t__ uchar_t ;
typedef  int boolean_t ;

/* Variables and functions */
 size_t BSWAP_32 (size_t) ; 
 int E2BIG ; 
 int EBADF ; 
 int EILSEQ ; 
 int EINVAL ; 
 size_t UCONV_ASCII_MAX ; 
 size_t UCONV_BOM_NORMAL ; 
 size_t UCONV_BOM_SWAPPED_32 ; 
 int UCONV_IGNORE_NULL ; 
 int UCONV_OUT_EMIT_BOM ; 
 int UCONV_OUT_NAT_ENDIAN ; 
 size_t UCONV_U8_BIT_MASK ; 
 size_t UCONV_U8_BIT_SHIFT ; 
 size_t UCONV_U8_BYTE_MAX ; 
 size_t UCONV_U8_BYTE_MIN ; 
 scalar_t__ check_endian (int,int*,int*) ; 
 int* remaining_bytes_tbl ; 
 size_t* u8_masks_tbl ; 
 size_t* valid_max_2nd_byte ; 
 size_t* valid_min_2nd_byte ; 

int
uconv_u8tou32(const uchar_t *u8s, size_t *utf8len,
    uint32_t *u32s, size_t *utf32len, int flag)
{
	int inendian;
	int outendian;
	size_t u32l;
	size_t u8l;
	uint32_t hi;
	uint32_t c;
	int remaining_bytes;
	int first_b;
	boolean_t do_not_ignore_null;

	if (u8s == NULL || utf8len == NULL)
		return (EILSEQ);

	if (u32s == NULL || utf32len == NULL)
		return (E2BIG);

	if (check_endian(flag, &inendian, &outendian) != 0)
		return (EBADF);

	u32l = u8l = 0;
	do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

	outendian &= UCONV_OUT_NAT_ENDIAN;

	if (*utf8len > 0 && *utf32len > 0 && (flag & UCONV_OUT_EMIT_BOM))
		u32s[u32l++] = (outendian) ? UCONV_BOM_NORMAL :
		    UCONV_BOM_SWAPPED_32;

	for (; u8l < *utf8len; ) {
		if (u8s[u8l] == 0 && do_not_ignore_null)
			break;

		hi = (uint32_t)u8s[u8l++];

		if (hi > UCONV_ASCII_MAX) {
			if ((remaining_bytes = remaining_bytes_tbl[hi]) == 0)
				return (EILSEQ);

			first_b = hi;
			hi = hi & u8_masks_tbl[remaining_bytes];

			for (; remaining_bytes > 0; remaining_bytes--) {
				if (u8l >= *utf8len)
					return (EINVAL);

				c = (uint32_t)u8s[u8l++];

				if (first_b) {
					if (c < valid_min_2nd_byte[first_b] ||
					    c > valid_max_2nd_byte[first_b])
						return (EILSEQ);
					first_b = 0;
				} else if (c < UCONV_U8_BYTE_MIN ||
				    c > UCONV_U8_BYTE_MAX) {
					return (EILSEQ);
				}
				hi = (hi << UCONV_U8_BIT_SHIFT) |
				    (c & UCONV_U8_BIT_MASK);
			}
		}

		if (u32l >= *utf32len)
			return (E2BIG);

		u32s[u32l++] = (outendian) ? hi : BSWAP_32(hi);
	}

	*utf32len = u32l;
	*utf8len = u8l;

	return (0);
}