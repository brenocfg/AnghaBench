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
 scalar_t__ OUT_HTML ; 
 scalar_t__ OUT_PCLM ; 
 scalar_t__ OUT_PS ; 
 scalar_t__ OUT_STEXT ; 
 scalar_t__ OUT_TRACE ; 
 scalar_t__ OUT_XHTML ; 
 int /*<<< orphan*/  bander ; 
 int /*<<< orphan*/  fz_drop_band_writer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_print_stext_trailer_as_html (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_print_stext_trailer_as_xhtml (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_write_ps_file_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out ; 
 scalar_t__ output_format ; 
 int /*<<< orphan*/  output_pagenum ; 

__attribute__((used)) static void
file_level_trailers(fz_context *ctx)
{
	if (output_format == OUT_STEXT || output_format == OUT_TRACE)
		fz_write_printf(ctx, out, "</document>\n");

	if (output_format == OUT_HTML)
		fz_print_stext_trailer_as_html(ctx, out);
	if (output_format == OUT_XHTML)
		fz_print_stext_trailer_as_xhtml(ctx, out);

	if (output_format == OUT_PS)
		fz_write_ps_file_trailer(ctx, out, output_pagenum);

	if (output_format == OUT_PCLM)
		fz_drop_band_writer(ctx, bander);
}