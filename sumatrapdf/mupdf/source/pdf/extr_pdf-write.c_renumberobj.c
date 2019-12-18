#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* renumber_map; } ;
typedef  TYPE_1__ pdf_write_state ;
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * PDF_NULL ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_array_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_dict_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void renumberobj(fz_context *ctx, pdf_document *doc, pdf_write_state *opts, pdf_obj *obj)
{
	int i;
	int xref_len = pdf_xref_len(ctx, doc);

	if (pdf_is_dict(ctx, obj))
	{
		int n = pdf_dict_len(ctx, obj);
		for (i = 0; i < n; i++)
		{
			pdf_obj *key = pdf_dict_get_key(ctx, obj, i);
			pdf_obj *val = pdf_dict_get_val(ctx, obj, i);
			if (pdf_is_indirect(ctx, val))
			{
				int o = pdf_to_num(ctx, val);
				if (o >= xref_len || o <= 0 || opts->renumber_map[o] == 0)
					val = PDF_NULL;
				else
					val = pdf_new_indirect(ctx, doc, opts->renumber_map[o], 0);
				pdf_dict_put_drop(ctx, obj, key, val);
			}
			else
			{
				renumberobj(ctx, doc, opts, val);
			}
		}
	}

	else if (pdf_is_array(ctx, obj))
	{
		int n = pdf_array_len(ctx, obj);
		for (i = 0; i < n; i++)
		{
			pdf_obj *val = pdf_array_get(ctx, obj, i);
			if (pdf_is_indirect(ctx, val))
			{
				int o = pdf_to_num(ctx, val);
				if (o >= xref_len || o <= 0 || opts->renumber_map[o] == 0)
					val = PDF_NULL;
				else
					val = pdf_new_indirect(ctx, doc, opts->renumber_map[o], 0);
				pdf_array_put_drop(ctx, obj, i, val);
			}
			else
			{
				renumberobj(ctx, doc, opts, val);
			}
		}
	}
}