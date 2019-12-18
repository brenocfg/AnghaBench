#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float ascent; float descent; TYPE_5__* font; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {int is_serif; } ;
struct TYPE_10__ {TYPE_3__* ft_face; TYPE_1__ flags; } ;
struct TYPE_9__ {float ascender; float units_per_EM; float descender; } ;
typedef  TYPE_3__* FT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_SYNTAX ; 
 int /*<<< orphan*/  PDF_FD_SYMBOLIC ; 
 TYPE_5__* fz_load_system_font (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned char* fz_lookup_base14_font (int /*<<< orphan*/ *,char const*,int*) ; 
 TYPE_5__* fz_new_font_from_memory (int /*<<< orphan*/ *,char const*,unsigned char const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 char* pdf_clean_font_name (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 

__attribute__((used)) static void
pdf_load_builtin_font(fz_context *ctx, pdf_font_desc *fontdesc, const char *fontname, int has_descriptor)
{
	FT_Face face;
	const char *clean_name = pdf_clean_font_name(fontname);
	if (clean_name == fontname)
		clean_name = "Times-Roman";

	fontdesc->font = fz_load_system_font(ctx, fontname, 0, 0, !has_descriptor);
	if (!fontdesc->font)
	{
		const unsigned char *data;
		int len;

		data = fz_lookup_base14_font(ctx, clean_name, &len);
		if (!data)
			fz_throw(ctx, FZ_ERROR_SYNTAX, "cannot find builtin font: '%s'", fontname);

		fontdesc->font = fz_new_font_from_memory(ctx, fontname, data, len, 0, 1);
		fontdesc->font->flags.is_serif = !!strstr(clean_name, "Times");
	}

	if (!strcmp(clean_name, "Symbol") || !strcmp(clean_name, "ZapfDingbats"))
		fontdesc->flags |= PDF_FD_SYMBOLIC;

	face = fontdesc->font->ft_face;
	fontdesc->ascent = 1000.0f * face->ascender / face->units_per_EM;
	fontdesc->descent = 1000.0f * face->descender / face->units_per_EM;
}