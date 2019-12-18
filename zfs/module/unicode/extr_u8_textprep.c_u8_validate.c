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
typedef  size_t uchar_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_FALSE ; 
 int B_TRUE ; 
 int EBADF ; 
 int EILSEQ ; 
 int EINVAL ; 
 int ERANGE ; 
 int U8_ILLEGAL_CHAR ; 
 scalar_t__ U8_ILLEGAL_NEXT_BYTE_COMMON (size_t) ; 
 int U8_MAX_BYTES_UCS2 ; 
 int U8_OUT_OF_RANGE_CHAR ; 
 int U8_VALIDATE_CHECK_ADDITIONAL ; 
 int U8_VALIDATE_ENTIRE ; 
 int U8_VALIDATE_UCS2_RANGE ; 
 int* u8_number_of_bytes ; 
 size_t* u8_valid_max_2nd_byte ; 
 size_t* u8_valid_min_2nd_byte ; 

int
u8_validate(char *u8str, size_t n, char **list, int flag, int *errnum)
{
	uchar_t *ib;
	uchar_t *ibtail;
	uchar_t **p;
	uchar_t *s1;
	uchar_t *s2;
	uchar_t f;
	int sz;
	size_t i;
	int ret_val;
	boolean_t second;
	boolean_t no_need_to_validate_entire;
	boolean_t check_additional;
	boolean_t validate_ucs2_range_only;

	if (! u8str)
		return (0);

	ib = (uchar_t *)u8str;
	ibtail = ib + n;

	ret_val = 0;

	no_need_to_validate_entire = ! (flag & U8_VALIDATE_ENTIRE);
	check_additional = flag & U8_VALIDATE_CHECK_ADDITIONAL;
	validate_ucs2_range_only = flag & U8_VALIDATE_UCS2_RANGE;

	while (ib < ibtail) {
		/*
		 * The first byte of a UTF-8 character tells how many
		 * bytes will follow for the character. If the first byte
		 * is an illegal byte value or out of range value, we just
		 * return -1 with an appropriate error number.
		 */
		sz = u8_number_of_bytes[*ib];
		if (sz == U8_ILLEGAL_CHAR) {
			*errnum = EILSEQ;
			return (-1);
		}

		if (sz == U8_OUT_OF_RANGE_CHAR ||
		    (validate_ucs2_range_only && sz > U8_MAX_BYTES_UCS2)) {
			*errnum = ERANGE;
			return (-1);
		}

		/*
		 * If we don't have enough bytes to check on, that's also
		 * an error. As you can see, we give illegal byte sequence
		 * checking higher priority then EINVAL cases.
		 */
		if ((ibtail - ib) < sz) {
			*errnum = EINVAL;
			return (-1);
		}

		if (sz == 1) {
			ib++;
			ret_val++;
		} else {
			/*
			 * Check on the multi-byte UTF-8 character. For more
			 * details on this, see comment added for the used
			 * data structures at the beginning of the file.
			 */
			f = *ib++;
			ret_val++;
			second = B_TRUE;
			for (i = 1; i < sz; i++) {
				if (second) {
					if (*ib < u8_valid_min_2nd_byte[f] ||
					    *ib > u8_valid_max_2nd_byte[f]) {
						*errnum = EILSEQ;
						return (-1);
					}
					second = B_FALSE;
				} else if (U8_ILLEGAL_NEXT_BYTE_COMMON(*ib)) {
					*errnum = EILSEQ;
					return (-1);
				}
				ib++;
				ret_val++;
			}
		}

		if (check_additional) {
			for (p = (uchar_t **)list, i = 0; p[i]; i++) {
				s1 = ib - sz;
				s2 = p[i];
				while (s1 < ib) {
					if (*s1 != *s2 || *s2 == '\0')
						break;
					s1++;
					s2++;
				}

				if (s1 >= ib && *s2 == '\0') {
					*errnum = EBADF;
					return (-1);
				}
			}
		}

		if (no_need_to_validate_entire)
			break;
	}

	return (ret_val);
}