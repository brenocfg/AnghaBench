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
typedef  int /*<<< orphan*/  fz_document_writer ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/ * fz_new_cbz_writer_with_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * fz_new_pcl_writer_with_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * fz_new_pclm_writer_with_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * fz_new_pdf_writer_with_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * fz_new_ps_writer_with_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * fz_new_pwg_writer_with_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * fz_new_text_writer_with_output (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fz_strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 

fz_document_writer *
fz_new_document_writer_with_output(fz_context *ctx, fz_output *out, const char *format, const char *options)
{
	if (!fz_strcasecmp(format, "cbz"))
		return fz_new_cbz_writer_with_output(ctx, out, options);
#if FZ_ENABLE_PDF
	if (!fz_strcasecmp(format, "pdf"))
		return fz_new_pdf_writer_with_output(ctx, out, options);
#endif

	if (!fz_strcasecmp(format, "pcl"))
		return fz_new_pcl_writer_with_output(ctx, out, options);
	if (!fz_strcasecmp(format, "pclm"))
		return fz_new_pclm_writer_with_output(ctx, out, options);
	if (!fz_strcasecmp(format, "ps"))
		return fz_new_ps_writer_with_output(ctx, out, options);
	if (!fz_strcasecmp(format, "pwg"))
		return fz_new_pwg_writer_with_output(ctx, out, options);

	if (!fz_strcasecmp(format, "txt") || !fz_strcasecmp(format, "text"))
		return fz_new_text_writer_with_output(ctx, "text", out, options);
	if (!fz_strcasecmp(format, "html"))
		return fz_new_text_writer_with_output(ctx, format, out, options);
	if (!fz_strcasecmp(format, "xhtml"))
		return fz_new_text_writer_with_output(ctx, format, out, options);
	if (!fz_strcasecmp(format, "stext"))
		return fz_new_text_writer_with_output(ctx, format, out, options);

	fz_throw(ctx, FZ_ERROR_GENERIC, "unknown output document format: %s", format);
}