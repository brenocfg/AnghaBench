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

/* Variables and functions */
 int /*<<< orphan*/  JS ; 
 int /*<<< orphan*/  JavaScript ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get_val (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pdf_dict_len (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_load_name_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pdf_load_stream_or_string_as_utf8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_to_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  showtext (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void showjs(void)
{
	pdf_obj *tree;
	int i;

	tree = pdf_load_name_tree(ctx, doc, PDF_NAME(JavaScript));
	for (i = 0; i < pdf_dict_len(ctx, tree); ++i)
	{
		pdf_obj *name = pdf_dict_get_key(ctx, tree, i);
		pdf_obj *action = pdf_dict_get_val(ctx, tree, i);
		pdf_obj *js = pdf_dict_get(ctx, action, PDF_NAME(JS));
		char *src = pdf_load_stream_or_string_as_utf8(ctx, js);
		fz_write_printf(ctx, out, "// %s\n", pdf_to_name(ctx, name));
		showtext(src, 0);
		fz_free(ctx, src);
	}
}