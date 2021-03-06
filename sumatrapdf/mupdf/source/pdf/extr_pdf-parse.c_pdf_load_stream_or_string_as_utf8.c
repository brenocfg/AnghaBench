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
 scalar_t__ pdf_is_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* pdf_new_utf8_from_pdf_stream_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* pdf_new_utf8_from_pdf_string_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

char *
pdf_load_stream_or_string_as_utf8(fz_context *ctx, pdf_obj *src)
{
	if (pdf_is_stream(ctx, src))
		return pdf_new_utf8_from_pdf_stream_obj(ctx, src);
	return pdf_new_utf8_from_pdf_string_obj(ctx, src);
}