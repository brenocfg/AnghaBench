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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  in_uint8a (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 

int
rdp_in_unistr(RDPCLIENT * This, STREAM s, wchar_t *string, int uni_len)
{
#ifdef HAVE_ICONV
	size_t ibl = uni_len, obl = uni_len;
	char *pin = (char *) s->p, *pout = string;
	static iconv_t iconv_h = (iconv_t) - 1;

	if (This->rdp.iconv_works)
	{
		if (iconv_h == (iconv_t) - 1)
		{
			if ((iconv_h = iconv_open(This->codepage, WINDOWS_CODEPAGE)) == (iconv_t) - 1)
			{
				warning("rdp_in_unistr: iconv_open[%s -> %s] fail %d\n",
					WINDOWS_CODEPAGE, This->codepage, (int) iconv_h);

				This->rdp.iconv_works = False;
				return rdp_in_unistr(This, s, string, uni_len);
			}
		}

		if (iconv(iconv_h, (ICONV_CONST char **) &pin, &ibl, &pout, &obl) == (size_t) - 1)
		{
			iconv_close(iconv_h);
			iconv_h = (iconv_t) - 1;
			warning("rdp_in_unistr: iconv fail, errno %d\n", errno);

			This->rdp.iconv_works = False;
			return rdp_in_unistr(This, s, string, uni_len);
		}

		/* we must update the location of the current STREAM for future reads of s->p */
		s->p += uni_len;

		return pout - string;
	}
	else
#endif
	// TODO
	{
		int i = 0;

		while (i < uni_len / 2)
		{
			in_uint8a(s, &string[i++], 1);
			in_uint8s(s, 1);
		}

		return i - 1;
	}
}