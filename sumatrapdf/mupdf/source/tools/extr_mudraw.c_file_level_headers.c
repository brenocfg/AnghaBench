#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ fz_pclm_options ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ OUT_HTML ; 
 scalar_t__ OUT_PCLM ; 
 scalar_t__ OUT_PS ; 
 scalar_t__ OUT_PWG ; 
 scalar_t__ OUT_STEXT ; 
 scalar_t__ OUT_TRACE ; 
 scalar_t__ OUT_XHTML ; 
 int /*<<< orphan*/  bander ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  fz_new_pclm_band_writer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_parse_pclm_options (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  fz_print_stext_header_as_html (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_print_stext_header_as_xhtml (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fz_write_ps_file_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_pwg_file_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out ; 
 scalar_t__ output_format ; 

__attribute__((used)) static void
file_level_headers(fz_context *ctx)
{
	if (output_format == OUT_STEXT || output_format == OUT_TRACE)
		fz_write_printf(ctx, out, "<?xml version=\"1.0\"?>\n");

	if (output_format == OUT_HTML)
		fz_print_stext_header_as_html(ctx, out);
	if (output_format == OUT_XHTML)
		fz_print_stext_header_as_xhtml(ctx, out);

	if (output_format == OUT_STEXT || output_format == OUT_TRACE)
		fz_write_printf(ctx, out, "<document name=\"%s\">\n", filename);

	if (output_format == OUT_PS)
		fz_write_ps_file_header(ctx, out);

	if (output_format == OUT_PWG)
		fz_write_pwg_file_header(ctx, out);

	if (output_format == OUT_PCLM)
	{
		fz_pclm_options opts = { 0 };
		fz_parse_pclm_options(ctx, &opts, "compression=flate");
		bander = fz_new_pclm_band_writer(ctx, out, &opts);
	}
}