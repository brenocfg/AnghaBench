#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  obj; scalar_t__ state; } ;
typedef  TYPE_2__ pdf_ocg_entry ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_9__ {TYPE_1__* ocg; } ;
typedef  TYPE_3__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {int len; TYPE_2__* ocgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS ; 
 int /*<<< orphan*/  BaseState ; 
 int /*<<< orphan*/  Configs ; 
 int /*<<< orphan*/  Creator ; 
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  Intent ; 
 int /*<<< orphan*/  Locked ; 
 int /*<<< orphan*/  Name ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ON ; 
 int /*<<< orphan*/  Order ; 
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBGroups ; 
 int /*<<< orphan*/  View ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_array_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_getp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_array (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  pdf_trailer (int /*<<< orphan*/ *,TYPE_3__*) ; 

void
pdf_set_layer_config_as_default(fz_context *ctx, pdf_document *doc)
{
	pdf_obj *ocprops, *d, *order, *on, *configs, *rbgroups;
	int k;

	if (doc == NULL || doc->ocg == NULL)
		return;

	ocprops = pdf_dict_getp(ctx, pdf_trailer(ctx, doc), "Root/OCProperties");
	if (!ocprops)
		return;

	/* All files with OCGs are required to have a D entry */
	d = pdf_dict_get(ctx, ocprops, PDF_NAME(D));
	if (d == NULL)
		return;

	pdf_dict_put(ctx, d, PDF_NAME(BaseState), PDF_NAME(OFF));

	/* We are about to delete RBGroups and Order, from D. These are
	 * both the underlying defaults for other configs, so copy the
	 * current values out to any config that doesn't have one
	 * already. */
	order = pdf_dict_get(ctx, d, PDF_NAME(Order));
	rbgroups = pdf_dict_get(ctx, d, PDF_NAME(RBGroups));
	configs = pdf_dict_get(ctx, ocprops, PDF_NAME(Configs));
	if (configs)
	{
		int len = pdf_array_len(ctx, configs);
		for (k=0; k < len; k++)
		{
			pdf_obj *config = pdf_array_get(ctx, configs, k);

			if (order && !pdf_dict_get(ctx, config, PDF_NAME(Order)))
				pdf_dict_put(ctx, config, PDF_NAME(Order), order);
			if (rbgroups && !pdf_dict_get(ctx, config, PDF_NAME(RBGroups)))
				pdf_dict_put(ctx, config, PDF_NAME(RBGroups), rbgroups);
		}
	}

	/* Offer all the layers in the UI */
	order = pdf_new_array(ctx, doc, 4);
	on = pdf_new_array(ctx, doc, 4);
	for (k = 0; k < doc->ocg->len; k++)
	{
		pdf_ocg_entry *s = &doc->ocg->ocgs[k];

		pdf_array_push(ctx, order, s->obj);
		if (s->state)
			pdf_array_push(ctx, on, s->obj);
	}
	pdf_dict_put(ctx, d, PDF_NAME(Order), order);
	pdf_dict_put(ctx, d, PDF_NAME(ON), on);
	pdf_dict_del(ctx, d, PDF_NAME(OFF));
	pdf_dict_del(ctx, d, PDF_NAME(AS));
	pdf_dict_put(ctx, d, PDF_NAME(Intent), PDF_NAME(View));
	pdf_dict_del(ctx, d, PDF_NAME(Name));
	pdf_dict_del(ctx, d, PDF_NAME(Creator));
	pdf_dict_del(ctx, d, PDF_NAME(RBGroups));
	pdf_dict_del(ctx, d, PDF_NAME(Locked));

	pdf_dict_del(ctx, ocprops, PDF_NAME(Configs));
}