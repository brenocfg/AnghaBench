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
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

void
fz_print_stext_header_as_xhtml(fz_context *ctx, fz_output *out)
{
	fz_write_string(ctx, out, "<?xml version=\"1.0\"?>\n");
	fz_write_string(ctx, out, "<!DOCTYPE html");
	fz_write_string(ctx, out, " PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"");
	fz_write_string(ctx, out, " \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n");
	fz_write_string(ctx, out, "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
	fz_write_string(ctx, out, "<head>\n");
	fz_write_string(ctx, out, "<style>\n");
	fz_write_string(ctx, out, "p{white-space:pre-wrap}\n");
	fz_write_string(ctx, out, "</style>\n");
	fz_write_string(ctx, out, "</head>\n");
	fz_write_string(ctx, out, "<body>\n");
}