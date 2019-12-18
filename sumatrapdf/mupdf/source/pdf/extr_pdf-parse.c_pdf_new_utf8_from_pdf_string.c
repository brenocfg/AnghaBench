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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 char* fz_malloc (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ fz_runelen (int) ; 
 int /*<<< orphan*/  fz_runetochar (char*,int) ; 
 int* fz_unicode_from_pdf_doc_encoding ; 
 scalar_t__ rune_from_utf16be (int*,unsigned char const*,unsigned char const*) ; 
 scalar_t__ rune_from_utf16le (int*,unsigned char const*,unsigned char const*) ; 
 size_t skip_language_code_utf16be (unsigned char const*,size_t,size_t) ; 
 size_t skip_language_code_utf16le (unsigned char const*,size_t,size_t) ; 
 size_t skip_language_code_utf8 (unsigned char const*,size_t,size_t) ; 

char *
pdf_new_utf8_from_pdf_string(fz_context *ctx, const char *ssrcptr, size_t srclen)
{
	const unsigned char *srcptr = (const unsigned char*)ssrcptr;
	char *dstptr, *dst;
	size_t dstlen = 0;
	int ucs;
	size_t i, n;

	/* UTF-16BE */
	if (srclen >= 2 && srcptr[0] == 254 && srcptr[1] == 255)
	{
		i = 2;
		while (i + 2 <= srclen)
		{
			n = skip_language_code_utf16be(srcptr, srclen, i);
			if (n)
				i += n;
			else
			{
				i += rune_from_utf16be(&ucs, srcptr + i, srcptr + srclen);
				dstlen += fz_runelen(ucs);
			}
		}

		dstptr = dst = fz_malloc(ctx, dstlen + 1);

		i = 2;
		while (i + 2 <= srclen)
		{
			n = skip_language_code_utf16be(srcptr, srclen, i);
			if (n)
				i += n;
			else
			{
				i += rune_from_utf16be(&ucs, srcptr + i, srcptr + srclen);
				dstptr += fz_runetochar(dstptr, ucs);
			}
		}
	}

	/* UTF-16LE */
	else if (srclen >= 2 && srcptr[0] == 255 && srcptr[1] == 254)
	{
		i = 2;
		while (i + 2 <= srclen)
		{
			n = skip_language_code_utf16le(srcptr, srclen, i);
			if (n)
				i += n;
			else
			{
				i += rune_from_utf16le(&ucs, srcptr + i, srcptr + srclen);
				dstlen += fz_runelen(ucs);
			}
		}

		dstptr = dst = fz_malloc(ctx, dstlen + 1);

		i = 2;
		while (i + 2 <= srclen)
		{
			n = skip_language_code_utf16le(srcptr, srclen, i);
			if (n)
				i += n;
			else
			{
				i += rune_from_utf16le(&ucs, srcptr + i, srcptr + srclen);
				dstptr += fz_runetochar(dstptr, ucs);
			}
		}
	}

	/* UTF-8 */
	else if (srclen >= 3 && srcptr[0] == 239 && srcptr[1] == 187 && srcptr[2] == 191)
	{
		i = 3;
		while (i < srclen)
		{
			n = skip_language_code_utf8(srcptr, srclen, i);
			if (n)
				i += n;
			else
			{
				i += 1;
				dstlen += 1;
			}
		}

		dstptr = dst = fz_malloc(ctx, dstlen + 1);

		i = 3;
		while (i < srclen)
		{
			n = skip_language_code_utf8(srcptr, srclen, i);
			if (n)
				i += n;
			else
				*dstptr++ = srcptr[i++];
		}
	}

	/* PDFDocEncoding */
	else
	{
		for (i = 0; i < srclen; i++)
			dstlen += fz_runelen(fz_unicode_from_pdf_doc_encoding[srcptr[i]]);

		dstptr = dst = fz_malloc(ctx, dstlen + 1);

		for (i = 0; i < srclen; i++)
		{
			ucs = fz_unicode_from_pdf_doc_encoding[srcptr[i]];
			dstptr += fz_runetochar(dstptr, ucs);
		}
	}

	*dstptr = 0;
	return dst;
}