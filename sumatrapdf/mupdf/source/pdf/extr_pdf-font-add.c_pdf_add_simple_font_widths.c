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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FirstChar ; 
 int /*<<< orphan*/  LastChar ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Widths ; 
 int fz_advance_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int fz_encode_character_by_glyph_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const* const) ; 
 int /*<<< orphan*/  pdf_array_push_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pdf_new_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
pdf_add_simple_font_widths(fz_context *ctx, pdf_document *doc, pdf_obj *fobj, fz_font *font, const char * const encoding[])
{
	int width_table[256];
	pdf_obj *widths;
	int i, first, last;

	first = 0;
	last = 0;

	for (i = 0; i < 256; ++i)
	{
		int glyph = 0;
		if (encoding[i])
		{
			glyph = fz_encode_character_by_glyph_name(ctx, font, encoding[i]);
		}
		if (glyph > 0)
		{
			if (!first)
				first = i;
			last = i;
			width_table[i] = fz_advance_glyph(ctx, font, glyph, 0) * 1000;
		}
		else
			width_table[i] = 0;
	}

	widths = pdf_new_array(ctx, doc, last - first + 1);
	pdf_dict_put_drop(ctx, fobj, PDF_NAME(Widths), widths);
	for (i = first; i <= last; ++i)
		pdf_array_push_int(ctx, widths, width_table[i]);
	pdf_dict_put_int(ctx, fobj, PDF_NAME(FirstChar), first);
	pdf_dict_put_int(ctx, fobj, PDF_NAME(LastChar), last);
}