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
typedef  int /*<<< orphan*/  fz_document_writer ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/ * fz_new_cbz_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_pam_pixmap_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_pbm_pixmap_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_pcl_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_pclm_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_pdf_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_pgm_pixmap_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_pkm_pixmap_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_png_pixmap_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_pnm_pixmap_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_ppm_pixmap_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_ps_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_pwg_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_svg_writer (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fz_new_text_writer (int /*<<< orphan*/ *,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  fz_strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 char* strrchr (char const*,char) ; 

fz_document_writer *
fz_new_document_writer(fz_context *ctx, const char *path, const char *format, const char *options)
{
	if (!format)
	{
		format = strrchr(path, '.');
		if (!format)
			fz_throw(ctx, FZ_ERROR_GENERIC, "cannot detect document format");
		format += 1; /* skip the '.' */
	}

	if (!fz_strcasecmp(format, "cbz"))
		return fz_new_cbz_writer(ctx, path, options);
#if FZ_ENABLE_PDF
	if (!fz_strcasecmp(format, "pdf"))
		return fz_new_pdf_writer(ctx, path, options);
#endif
	if (!fz_strcasecmp(format, "svg"))
		return fz_new_svg_writer(ctx, path, options);

	if (!fz_strcasecmp(format, "png"))
		return fz_new_png_pixmap_writer(ctx, path, options);
	if (!fz_strcasecmp(format, "pam"))
		return fz_new_pam_pixmap_writer(ctx, path, options);
	if (!fz_strcasecmp(format, "pnm"))
		return fz_new_pnm_pixmap_writer(ctx, path, options);
	if (!fz_strcasecmp(format, "pgm"))
		return fz_new_pgm_pixmap_writer(ctx, path, options);
	if (!fz_strcasecmp(format, "ppm"))
		return fz_new_ppm_pixmap_writer(ctx, path, options);
	if (!fz_strcasecmp(format, "pbm"))
		return fz_new_pbm_pixmap_writer(ctx, path, options);
	if (!fz_strcasecmp(format, "pkm"))
		return fz_new_pkm_pixmap_writer(ctx, path, options);

	if (!fz_strcasecmp(format, "pcl"))
		return fz_new_pcl_writer(ctx, path, options);
	if (!fz_strcasecmp(format, "pclm"))
		return fz_new_pclm_writer(ctx, path, options);
	if (!fz_strcasecmp(format, "ps"))
		return fz_new_ps_writer(ctx, path, options);
	if (!fz_strcasecmp(format, "pwg"))
		return fz_new_pwg_writer(ctx, path, options);

	if (!fz_strcasecmp(format, "txt") || !fz_strcasecmp(format, "text"))
		return fz_new_text_writer(ctx, "text", path, options);
	if (!fz_strcasecmp(format, "html"))
		return fz_new_text_writer(ctx, format, path, options);
	if (!fz_strcasecmp(format, "xhtml"))
		return fz_new_text_writer(ctx, format, path, options);
	if (!fz_strcasecmp(format, "stext"))
		return fz_new_text_writer(ctx, format, path, options);

	fz_throw(ctx, FZ_ERROR_GENERIC, "unknown output document format: %s", format);
}