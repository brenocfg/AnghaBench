#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; TYPE_2__* table; struct TYPE_6__* next; } ;
typedef  TYPE_1__ pdf_xref_subsec ;
struct TYPE_7__ {int /*<<< orphan*/ * obj; int /*<<< orphan*/ * stm_buf; } ;
typedef  TYPE_2__ pdf_xref_entry ;
struct TYPE_8__ {TYPE_1__* subsec; } ;
typedef  TYPE_3__ pdf_xref ;
struct TYPE_9__ {int num_xref_sections; TYPE_3__* xref_sections; } ;
typedef  TYPE_4__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_obj_refs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void pdf_clear_xref(fz_context *ctx, pdf_document *doc)
{
	int x, e;

	for (x = 0; x < doc->num_xref_sections; x++)
	{
		pdf_xref *xref = &doc->xref_sections[x];
		pdf_xref_subsec *sub;

		for (sub = xref->subsec; sub != NULL; sub = sub->next)
		{
			for (e = 0; e < sub->len; e++)
			{
				pdf_xref_entry *entry = &sub->table[e];
				/* We cannot drop objects if the stream
				 * buffer has been updated */
				if (entry->obj != NULL && entry->stm_buf == NULL)
				{
					if (pdf_obj_refs(ctx, entry->obj) == 1)
					{
						pdf_drop_obj(ctx, entry->obj);
						entry->obj = NULL;
					}
				}
			}
		}
	}
}