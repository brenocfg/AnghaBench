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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * pdf_copy_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_copy_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_dict_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_resolve_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpr_inherit_res_contents(fz_context *ctx, pdf_obj *res, pdf_obj *dict, pdf_obj *text)
{
	pdf_obj *o, *r;
	int i, n;

	/* If the parent node doesn't have an entry of this type, give up. */
	o = pdf_dict_get(ctx, dict, text);
	if (!o)
		return;

	/* If the resources dict we are building doesn't have an entry of this
	 * type yet, then just copy it (ensuring it's not a reference) */
	r = pdf_dict_get(ctx, res, text);
	if (r == NULL)
	{
		o = pdf_resolve_indirect(ctx, o);
		if (pdf_is_dict(ctx, o))
			o = pdf_copy_dict(ctx, o);
		else if (pdf_is_array(ctx, o))
			o = pdf_copy_array(ctx, o);
		else
			o = NULL;
		if (o)
			pdf_dict_put_drop(ctx, res, text, o);
		return;
	}

	/* Otherwise we need to merge o into r */
	if (pdf_is_dict(ctx, o))
	{
		n = pdf_dict_len(ctx, o);
		for (i = 0; i < n; i++)
		{
			pdf_obj *key = pdf_dict_get_key(ctx, o, i);
			pdf_obj *val = pdf_dict_get_val(ctx, o, i);

			if (pdf_dict_get(ctx, res, key))
				continue;
			pdf_dict_put(ctx, res, key, val);
		}
	}
}