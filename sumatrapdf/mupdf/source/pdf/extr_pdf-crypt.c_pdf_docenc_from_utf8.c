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

/* Variables and functions */
 int /*<<< orphan*/  fz_chartorune (int*,char const*) ; 
 int* fz_unicode_from_pdf_doc_encoding ; 

__attribute__((used)) static void pdf_docenc_from_utf8(char *password, const char *utf8, int n)
{
	int i = 0, k, c;
	while (*utf8 && i + 1 < n)
	{
		utf8 += fz_chartorune(&c, utf8);
		for (k = 0; k < 256; k++)
		{
			if (c == fz_unicode_from_pdf_doc_encoding[k])
			{
				password[i++] = k;
				break;
			}
		}
		/* FIXME: drop characters that can't be encoded or return an error? */
	}
	password[i] = 0;
}