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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  BaseEncoding ; 
 int /*<<< orphan*/  Differences ; 
 int /*<<< orphan*/  Encoding ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WinAnsiEncoding ; 
 int /*<<< orphan*/  pdf_array_push_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_array_push_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_put_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pdf_dict_put_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pdf_add_simple_font_encoding_imp(fz_context *ctx, pdf_document *doc, pdf_obj *font, const char *glyph_names[])
{
	pdf_obj *enc, *diff;
	int i, last;

	enc = pdf_dict_put_dict(ctx, font, PDF_NAME(Encoding), 2);
	pdf_dict_put(ctx, enc, PDF_NAME(BaseEncoding), PDF_NAME(WinAnsiEncoding));
	diff = pdf_dict_put_array(ctx, enc, PDF_NAME(Differences), 129);
	last = 0;
	for (i = 128; i < 256; ++i)
	{
		const char *glyph = glyph_names[i];
		if (glyph)
		{
			if (last != i-1)
				pdf_array_push_int(ctx, diff, i);
			last = i;
			pdf_array_push_name(ctx, diff, glyph);
		}
	}
}