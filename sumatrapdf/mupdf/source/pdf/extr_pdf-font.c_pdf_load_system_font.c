#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
typedef  TYPE_1__ pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ADOBE_CNS ; 
 int /*<<< orphan*/  FZ_ADOBE_GB ; 
 int /*<<< orphan*/  FZ_ADOBE_JAPAN ; 
 int /*<<< orphan*/  FZ_ADOBE_KOREA ; 
 int PDF_FD_FIXED_PITCH ; 
 int PDF_FD_FORCE_BOLD ; 
 int PDF_FD_ITALIC ; 
 int PDF_FD_SERIF ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  pdf_load_substitute_cjk_font (int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_load_substitute_font (int /*<<< orphan*/ *,TYPE_1__*,char const*,int,int,int,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static void
pdf_load_system_font(fz_context *ctx, pdf_font_desc *fontdesc, const char *fontname, const char *collection)
{
	int bold = 0;
	int italic = 0;
	int serif = 0;
	int mono = 0;

	if (strstr(fontname, "Bold"))
		bold = 1;
	if (strstr(fontname, "Italic"))
		italic = 1;
	if (strstr(fontname, "Oblique"))
		italic = 1;

	if (fontdesc->flags & PDF_FD_FIXED_PITCH)
		mono = 1;
	if (fontdesc->flags & PDF_FD_SERIF)
		serif = 1;
	if (fontdesc->flags & PDF_FD_ITALIC)
		italic = 1;
	if (fontdesc->flags & PDF_FD_FORCE_BOLD)
		bold = 1;

	if (collection)
	{
		if (!strcmp(collection, "Adobe-CNS1"))
			pdf_load_substitute_cjk_font(ctx, fontdesc, fontname, FZ_ADOBE_CNS, serif);
		else if (!strcmp(collection, "Adobe-GB1"))
			pdf_load_substitute_cjk_font(ctx, fontdesc, fontname, FZ_ADOBE_GB, serif);
		else if (!strcmp(collection, "Adobe-Japan1"))
			pdf_load_substitute_cjk_font(ctx, fontdesc, fontname, FZ_ADOBE_JAPAN, serif);
		else if (!strcmp(collection, "Adobe-Korea1"))
			pdf_load_substitute_cjk_font(ctx, fontdesc, fontname, FZ_ADOBE_KOREA, serif);
		else
		{
			if (strcmp(collection, "Adobe-Identity") != 0)
				fz_warn(ctx, "unknown cid collection: %s", collection);
			pdf_load_substitute_font(ctx, fontdesc, fontname, mono, serif, bold, italic);
		}
	}
	else
	{
		pdf_load_substitute_font(ctx, fontdesc, fontname, mono, serif, bold, italic);
	}
}