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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ uchar_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ BSWAP_16 (scalar_t__) ; 
 int E2BIG ; 
 int EBADF ; 
 int EILSEQ ; 
 int EINVAL ; 
 size_t UCONV_ASCII_MAX ; 
 scalar_t__ UCONV_BOM_NORMAL ; 
 scalar_t__ UCONV_BOM_SWAPPED ; 
 int UCONV_IGNORE_NULL ; 
 int UCONV_OUT_EMIT_BOM ; 
 int UCONV_OUT_NAT_ENDIAN ; 
 size_t UCONV_U16_BIT_SHIFT ; 
 size_t UCONV_U16_HI_MIN ; 
 size_t UCONV_U16_LO_MIN ; 
 size_t UCONV_U16_START ; 
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
uconv_u8tou16(const uchar_t *u8s, size_t *utf8len,
    uint16_t *u16s, size_t *utf16len, int flag)
{
	int inendian;
	int outendian;
	size_t u16l;
	size_t u8l;
	uint32_t hi;
	uint32_t lo;
	int remaining_bytes;
	int first_b;
	boolean_t do_not_ignore_null;

	if (u8s == NULL || utf8len == NULL)
		return (EILSEQ);

	if (u16s == NULL || utf16len == NULL)
		return (E2BIG);

	if (check_endian(flag, &inendian, &outendian) != 0)
		return (EBADF);

	u16l = u8l = 0;
	do_not_ignore_null = ((flag & UCONV_IGNORE_NULL) == 0);

	outendian &= UCONV_OUT_NAT_ENDIAN;

	if (*utf8len > 0 && *utf16len > 0 && (flag & UCONV_OUT_EMIT_BOM))
		u16s[u16l++] = (outendian) ? UCONV_BOM_NORMAL :
		    UCONV_BOM_SWAPPED;

	for (; u8l < *utf8len; ) {
		if (u8s[u8l] == 0 && do_not_ignore_null)
			break;

		/*
		 * Collect a UTF-8 character and convert it to a UTF-32
		 * character. In doing so, we screen out illegally formed
		 * UTF-8 characters and treat such as illegal characters.
		 * The algorithm at below also screens out anything bigger
		 * than the U+10FFFF.
		 *
		 * See Unicode 3.1 UTF-8 Corrigendum and Unicode 3.2 for
		 * more details on the illegal values of UTF-8 character
		 * bytes.
		 */
		hi = (uint32_t)u8s[u8l++];

		if (hi > UCONV_ASCII_MAX) {
			if ((remaining_bytes = remaining_bytes_tbl[hi]) == 0)
				return (EILSEQ);

			first_b = hi;
			hi = hi & u8_masks_tbl[remaining_bytes];

			for (; remaining_bytes > 0; remaining_bytes--) {
				/*
				 * If we have no more bytes, the current
				 * UTF-8 character is incomplete.
				 */
				if (u8l >= *utf8len)
					return (EINVAL);

				lo = (uint32_t)u8s[u8l++];

				if (first_b) {
					if (lo < valid_min_2nd_byte[first_b] ||
					    lo > valid_max_2nd_byte[first_b])
						return (EILSEQ);
					first_b = 0;
				} else if (lo < UCONV_U8_BYTE_MIN ||
				    lo > UCONV_U8_BYTE_MAX) {
					return (EILSEQ);
				}
				hi = (hi << UCONV_U8_BIT_SHIFT) |
				    (lo & UCONV_U8_BIT_MASK);
			}
		}

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
	*utf8len = u8l;

	return (0);
}