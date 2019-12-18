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
typedef  int /*<<< orphan*/  fz_font ;

/* Variables and functions */
 int /*<<< orphan*/  Font ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  fz_drop_font (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char* fz_lookup_cjk_font (int /*<<< orphan*/ ,int,int*,int*) ; 
 int fz_lookup_cjk_ordering_by_language (char*) ; 
 int /*<<< orphan*/ * fz_new_font_from_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_add_cjk_font (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_puts (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_dict (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void add_cjkfont_res(pdf_obj *resources, char *name, char *lang, char *wm, char *style)
{
	const unsigned char *data;
	int size, index, ordering, wmode, serif;
	fz_font *font;
	pdf_obj *subres, *ref;

	ordering = fz_lookup_cjk_ordering_by_language(lang);

	if (wm && !strcmp(wm, "V"))
		wmode = 1;
	else
		wmode = 0;

	if (style && (!strcmp(style, "sans") || !strcmp(style, "sans-serif")))
		serif = 0;
	else
		serif = 1;

	data = fz_lookup_cjk_font(ctx, ordering, &size, &index);
	font = fz_new_font_from_memory(ctx, NULL, data, size, index, 0);

	subres = pdf_dict_get(ctx, resources, PDF_NAME(Font));
	if (!subres)
	{
		subres = pdf_new_dict(ctx, doc, 10);
		pdf_dict_put_drop(ctx, resources, PDF_NAME(Font), subres);
	}

	ref = pdf_add_cjk_font(ctx, doc, font, ordering, wmode, serif);
	pdf_dict_puts(ctx, subres, name, ref);
	pdf_drop_obj(ctx, ref);

	fz_drop_font(ctx, font);
}