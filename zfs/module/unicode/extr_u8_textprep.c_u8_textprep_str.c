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
typedef  char uchar_t ;
typedef  int /*<<< orphan*/  u8_normalization_states_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int E2BIG ; 
 int EBADF ; 
 int EILSEQ ; 
 int EINVAL ; 
 int ERANGE ; 
 char U8_ASCII_TOLOWER (char) ; 
 char U8_ASCII_TOUPPER (char) ; 
 int U8_CANON_COMP ; 
 int U8_CANON_DECOMP ; 
 int U8_COMPAT_DECOMP ; 
 scalar_t__ U8_ISASCII (char) ; 
 int /*<<< orphan*/  U8_STATE_START ; 
 int /*<<< orphan*/  U8_STREAM_SAFE_TEXT_MAX ; 
 int U8_TEXTPREP_IGNORE_INVALID ; 
 int U8_TEXTPREP_IGNORE_NULL ; 
 int U8_TEXTPREP_NFC ; 
 int U8_TEXTPREP_NFD ; 
 int U8_TEXTPREP_NFKC ; 
 int U8_TEXTPREP_NFKD ; 
 int U8_TEXTPREP_TOLOWER ; 
 int U8_TEXTPREP_TOUPPER ; 
 size_t U8_UNICODE_LATEST ; 
 size_t collect_a_seq (size_t,char*,char**,char*,int,int,int,int,int,int*,int /*<<< orphan*/ *) ; 
 size_t do_case_conv (size_t,char*,char*,int,int) ; 
 int* u8_number_of_bytes ; 

size_t
u8_textprep_str(char *inarray, size_t *inlen, char *outarray, size_t *outlen,
    int flag, size_t unicode_version, int *errnum)
{
	int f;
	int sz;
	uchar_t *ib;
	uchar_t *ibtail;
	uchar_t *ob;
	uchar_t *obtail;
	boolean_t do_not_ignore_null;
	boolean_t do_not_ignore_invalid;
	boolean_t is_it_toupper;
	boolean_t is_it_tolower;
	boolean_t canonical_decomposition;
	boolean_t compatibility_decomposition;
	boolean_t canonical_composition;
	size_t ret_val;
	size_t i;
	size_t j;
	uchar_t u8s[U8_STREAM_SAFE_TEXT_MAX + 1];
	u8_normalization_states_t state;

	if (unicode_version > U8_UNICODE_LATEST) {
		*errnum = ERANGE;
		return ((size_t)-1);
	}

	f = flag & (U8_TEXTPREP_TOUPPER | U8_TEXTPREP_TOLOWER);
	if (f == (U8_TEXTPREP_TOUPPER | U8_TEXTPREP_TOLOWER)) {
		*errnum = EBADF;
		return ((size_t)-1);
	}

	f = flag & (U8_CANON_DECOMP | U8_COMPAT_DECOMP | U8_CANON_COMP);
	if (f && f != U8_TEXTPREP_NFD && f != U8_TEXTPREP_NFC &&
	    f != U8_TEXTPREP_NFKD && f != U8_TEXTPREP_NFKC) {
		*errnum = EBADF;
		return ((size_t)-1);
	}

	if (inarray == NULL || *inlen == 0)
		return (0);

	if (outarray == NULL) {
		*errnum = E2BIG;
		return ((size_t)-1);
	}

	ib = (uchar_t *)inarray;
	ob = (uchar_t *)outarray;
	ibtail = ib + *inlen;
	obtail = ob + *outlen;

	do_not_ignore_null = !(flag & U8_TEXTPREP_IGNORE_NULL);
	do_not_ignore_invalid = !(flag & U8_TEXTPREP_IGNORE_INVALID);
	is_it_toupper = flag & U8_TEXTPREP_TOUPPER;
	is_it_tolower = flag & U8_TEXTPREP_TOLOWER;

	ret_val = 0;

	/*
	 * If we don't have a normalization flag set, we do the simple case
	 * conversion based text preparation separately below. Text
	 * preparation involving Normalization will be done in the false task
	 * block, again, separately since it will take much more time and
	 * resource than doing simple case conversions.
	 */
	if (f == 0) {
		while (ib < ibtail) {
			if (*ib == '\0' && do_not_ignore_null)
				break;

			sz = u8_number_of_bytes[*ib];

			if (sz < 0) {
				if (do_not_ignore_invalid) {
					*errnum = EILSEQ;
					ret_val = (size_t)-1;
					break;
				}

				sz = 1;
				ret_val++;
			}

			if (sz == 1) {
				if (ob >= obtail) {
					*errnum = E2BIG;
					ret_val = (size_t)-1;
					break;
				}

				if (is_it_toupper)
					*ob = U8_ASCII_TOUPPER(*ib);
				else if (is_it_tolower)
					*ob = U8_ASCII_TOLOWER(*ib);
				else
					*ob = *ib;
				ib++;
				ob++;
			} else if ((ib + sz) > ibtail) {
				if (do_not_ignore_invalid) {
					*errnum = EINVAL;
					ret_val = (size_t)-1;
					break;
				}

				if ((obtail - ob) < (ibtail - ib)) {
					*errnum = E2BIG;
					ret_val = (size_t)-1;
					break;
				}

				/*
				 * We treat the remaining incomplete character
				 * bytes as a character.
				 */
				ret_val++;

				while (ib < ibtail)
					*ob++ = *ib++;
			} else {
				if (is_it_toupper || is_it_tolower) {
					i = do_case_conv(unicode_version, u8s,
					    ib, sz, is_it_toupper);

					if ((obtail - ob) < i) {
						*errnum = E2BIG;
						ret_val = (size_t)-1;
						break;
					}

					ib += sz;

					for (sz = 0; sz < i; sz++)
						*ob++ = u8s[sz];
				} else {
					if ((obtail - ob) < sz) {
						*errnum = E2BIG;
						ret_val = (size_t)-1;
						break;
					}

					for (i = 0; i < sz; i++)
						*ob++ = *ib++;
				}
			}
		}
	} else {
		canonical_decomposition = flag & U8_CANON_DECOMP;
		compatibility_decomposition = flag & U8_COMPAT_DECOMP;
		canonical_composition = flag & U8_CANON_COMP;

		while (ib < ibtail) {
			if (*ib == '\0' && do_not_ignore_null)
				break;

			/*
			 * If the current character is a 7-bit ASCII
			 * character and it is the last character, or,
			 * if the current character is a 7-bit ASCII
			 * character and the next character is also a 7-bit
			 * ASCII character, then, we copy over this
			 * character without going through collect_a_seq().
			 *
			 * In any other cases, we need to look further with
			 * the collect_a_seq() function.
			 */
			if (U8_ISASCII(*ib) && ((ib + 1) >= ibtail ||
			    ((ib + 1) < ibtail && U8_ISASCII(*(ib + 1))))) {
				if (ob >= obtail) {
					*errnum = E2BIG;
					ret_val = (size_t)-1;
					break;
				}

				if (is_it_toupper)
					*ob = U8_ASCII_TOUPPER(*ib);
				else if (is_it_tolower)
					*ob = U8_ASCII_TOLOWER(*ib);
				else
					*ob = *ib;
				ib++;
				ob++;
			} else {
				*errnum = 0;
				state = U8_STATE_START;

				j = collect_a_seq(unicode_version, u8s,
				    &ib, ibtail,
				    is_it_toupper,
				    is_it_tolower,
				    canonical_decomposition,
				    compatibility_decomposition,
				    canonical_composition,
				    errnum, &state);

				if (*errnum && do_not_ignore_invalid) {
					ret_val = (size_t)-1;
					break;
				}

				if ((obtail - ob) < j) {
					*errnum = E2BIG;
					ret_val = (size_t)-1;
					break;
				}

				for (i = 0; i < j; i++)
					*ob++ = u8s[i];
			}
		}
	}

	*inlen = ibtail - ib;
	*outlen = obtail - ob;

	return (ret_val);
}