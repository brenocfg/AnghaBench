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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * pdf_new_string (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * pdf_new_text_string_utf16be (int /*<<< orphan*/ *,char const*) ; 

pdf_obj *
pdf_new_text_string(fz_context *ctx, const char *s)
{
	int i = 0;
	while (s[i] != 0)
	{
		if (((unsigned char)s[i]) >= 128)
			return pdf_new_text_string_utf16be(ctx, s);
		++i;
	}
	return pdf_new_string(ctx, s, i);
}