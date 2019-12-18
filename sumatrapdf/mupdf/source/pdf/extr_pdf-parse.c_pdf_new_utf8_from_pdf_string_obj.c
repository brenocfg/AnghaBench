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
 char* pdf_new_utf8_from_pdf_string (int /*<<< orphan*/ *,char const*,size_t) ; 
 char* pdf_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 

char *
pdf_new_utf8_from_pdf_string_obj(fz_context *ctx, pdf_obj *src)
{
	const char *srcptr;
	size_t srclen;
	srcptr = pdf_to_string(ctx, src, &srclen);
	return pdf_new_utf8_from_pdf_string(ctx, srcptr, srclen);
}