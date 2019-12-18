#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int len; TYPE_5__* signer; scalar_t__ field; struct TYPE_8__* next; struct TYPE_8__* unsaved_sigs; scalar_t__ trailer; scalar_t__ pre_repair_trailer; struct TYPE_8__* table; int /*<<< orphan*/  stm_buf; scalar_t__ obj; struct TYPE_8__* subsec; } ;
typedef  TYPE_1__ pdf_xref_subsec ;
typedef  TYPE_1__ pdf_xref_entry ;
typedef  TYPE_1__ pdf_xref ;
typedef  TYPE_1__ pdf_unsaved_sig ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_9__ {int /*<<< orphan*/  (* drop ) (TYPE_5__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static void pdf_drop_xref_sections_imp(fz_context *ctx, pdf_document *doc, pdf_xref *xref_sections, int num_xref_sections)
{
	pdf_unsaved_sig *usig;
	int x, e;

	for (x = 0; x < num_xref_sections; x++)
	{
		pdf_xref *xref = &xref_sections[x];
		pdf_xref_subsec *sub = xref->subsec;

		while (sub != NULL)
		{
			pdf_xref_subsec *next_sub = sub->next;
			for (e = 0; e < sub->len; e++)
			{
				pdf_xref_entry *entry = &sub->table[e];
				if (entry->obj)
				{
					pdf_drop_obj(ctx, entry->obj);
					fz_drop_buffer(ctx, entry->stm_buf);
				}
			}
			fz_free(ctx, sub->table);
			fz_free(ctx, sub);
			sub = next_sub;
		}

		pdf_drop_obj(ctx, xref->pre_repair_trailer);
		pdf_drop_obj(ctx, xref->trailer);

		while ((usig = xref->unsaved_sigs) != NULL)
		{
			xref->unsaved_sigs = usig->next;
			pdf_drop_obj(ctx, usig->field);
			usig->signer->drop(usig->signer);
			fz_free(ctx, usig);
		}
	}

	fz_free(ctx, xref_sections);
}