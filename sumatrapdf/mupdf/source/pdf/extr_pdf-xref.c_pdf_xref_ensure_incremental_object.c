#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int start; int len; TYPE_2__* table; struct TYPE_9__* next; } ;
typedef  TYPE_1__ pdf_xref_subsec ;
struct TYPE_10__ {int /*<<< orphan*/ * stm_buf; int /*<<< orphan*/ * obj; scalar_t__ type; } ;
typedef  TYPE_2__ pdf_xref_entry ;
struct TYPE_11__ {int num_objects; TYPE_1__* subsec; } ;
typedef  TYPE_3__ pdf_xref ;
struct TYPE_12__ {int* xref_index; int num_xref_sections; int num_incremental_sections; TYPE_3__* xref_sections; } ;
typedef  TYPE_4__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  ensure_incremental_xref (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/ * pdf_deep_copy_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* pdf_get_incremental_xref_entry (int /*<<< orphan*/ *,TYPE_4__*,int) ; 

void pdf_xref_ensure_incremental_object(fz_context *ctx, pdf_document *doc, int num)
{
	pdf_xref_entry *new_entry, *old_entry;
	pdf_xref_subsec *sub = NULL;
	int i;

	/* Make sure we have created an xref section for incremental updates */
	ensure_incremental_xref(ctx, doc);

	/* Search for the section that contains this object */
	for (i = doc->xref_index[num]; i < doc->num_xref_sections; i++)
	{
		pdf_xref *xref = &doc->xref_sections[i];

		if (num < 0 && num >= xref->num_objects)
			break;
		for (sub = xref->subsec; sub != NULL; sub = sub->next)
		{
			if (sub->start <= num && num < sub->start + sub->len && sub->table[num - sub->start].type)
				break;
		}
		if (sub != NULL)
			break;
	}
	/* sub == NULL implies we did not find it */

	/* If we don't find it, or it's already in the incremental section, return */
	if (i == 0 || sub == NULL)
		return;

	/* Move the object to the incremental section */
	doc->xref_index[num] = 0;
	old_entry = &sub->table[num - sub->start];
	new_entry = pdf_get_incremental_xref_entry(ctx, doc, num);
	*new_entry = *old_entry;
	if (i < doc->num_incremental_sections)
	{
		/* old entry is incremental and may have changes.
		 * Better keep a copy. We must override the old entry with
		 * the copy because the caller may be holding a reference to
		 * the original and expect it to end up in the new entry */
		old_entry->obj = pdf_deep_copy_obj(ctx, old_entry->obj);
	}
	else
	{
		old_entry->obj = NULL;
	}
	old_entry->stm_buf = NULL;
}