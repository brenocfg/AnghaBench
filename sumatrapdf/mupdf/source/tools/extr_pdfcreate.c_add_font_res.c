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
 int PDF_SIMPLE_ENCODING_CYRILLIC ; 
 int PDF_SIMPLE_ENCODING_GREEK ; 
 int PDF_SIMPLE_ENCODING_LATIN ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  fz_drop_font (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char* fz_lookup_base14_font (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/ * fz_new_font_from_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_new_font_from_memory (int /*<<< orphan*/ ,char*,unsigned char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_add_simple_font (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_puts (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_dict (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void add_font_res(pdf_obj *resources, char *name, char *path, char *encname)
{
	const unsigned char *data;
	int size, enc;
	fz_font *font;
	pdf_obj *subres, *ref;

	data = fz_lookup_base14_font(ctx, path, &size);
	if (data)
		font = fz_new_font_from_memory(ctx, path, data, size, 0, 0);
	else
		font = fz_new_font_from_file(ctx, NULL, path, 0, 0);

	subres = pdf_dict_get(ctx, resources, PDF_NAME(Font));
	if (!subres)
	{
		subres = pdf_new_dict(ctx, doc, 10);
		pdf_dict_put_drop(ctx, resources, PDF_NAME(Font), subres);
	}

	enc = PDF_SIMPLE_ENCODING_LATIN;
	if (encname)
	{
		if (!strcmp(encname, "Latin") || !strcmp(encname, "Latn"))
			enc = PDF_SIMPLE_ENCODING_LATIN;
		else if (!strcmp(encname, "Greek") || !strcmp(encname, "Grek"))
			enc = PDF_SIMPLE_ENCODING_GREEK;
		else if (!strcmp(encname, "Cyrillic") || !strcmp(encname, "Cyrl"))
			enc = PDF_SIMPLE_ENCODING_CYRILLIC;
	}

	ref = pdf_add_simple_font(ctx, doc, font, enc);
	pdf_dict_puts(ctx, subres, name, ref);
	pdf_drop_obj(ctx, ref);

	fz_drop_font(ctx, font);
}