#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int format; int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ fz_text_writer ;
typedef  int /*<<< orphan*/  fz_document_writer ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  FZ_FORMAT_HTML 130 
#define  FZ_FORMAT_STEXT 129 
#define  FZ_FORMAT_XHTML 128 
 int /*<<< orphan*/  fz_close_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_print_stext_trailer_as_html (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_print_stext_trailer_as_xhtml (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
text_close_writer(fz_context *ctx, fz_document_writer *wri_)
{
	fz_text_writer *wri = (fz_text_writer*)wri_;
	switch (wri->format)
	{
	case FZ_FORMAT_HTML:
		fz_print_stext_trailer_as_html(ctx, wri->out);
		break;
	case FZ_FORMAT_XHTML:
		fz_print_stext_trailer_as_xhtml(ctx, wri->out);
		break;
	case FZ_FORMAT_STEXT:
		fz_write_string(ctx, wri->out, "</document>\n");
		break;
	}
	fz_close_output(ctx, wri->out);
}