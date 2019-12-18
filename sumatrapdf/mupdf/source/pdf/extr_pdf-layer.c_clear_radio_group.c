#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ state; int /*<<< orphan*/  obj; } ;
typedef  TYPE_2__ pdf_ocg_entry ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_8__ {TYPE_1__* ocg; } ;
typedef  TYPE_3__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {int len; TYPE_2__* ocgs; } ;

/* Variables and functions */
 scalar_t__ pdf_array_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_getp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pdf_objcmp_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_trailer (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void
clear_radio_group(fz_context *ctx, pdf_document *doc, pdf_obj *ocg)
{
	pdf_obj *rbgroups = pdf_dict_getp(ctx, pdf_trailer(ctx, doc), "Root/OCProperties/RBGroups");
	int len, i;

	len = pdf_array_len(ctx, rbgroups);
	for (i = 0; i < len; i++)
	{
		pdf_obj *group = pdf_array_get(ctx, rbgroups, i);

		if (pdf_array_contains(ctx, ocg, group))
		{
			int len2 = pdf_array_len(ctx, group);
			int j;

			for (j = 0; j < len2; j++)
			{
				pdf_obj *g = pdf_array_get(ctx, group, j);
				int k;
				for (k = 0; k < doc->ocg->len; k++)
				{
					pdf_ocg_entry *s = &doc->ocg->ocgs[k];

					if (!pdf_objcmp_resolve(ctx, s->obj, g))
						s->state = 0;
				}
			}
		}
	}
}