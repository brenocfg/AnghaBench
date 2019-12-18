#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* unsaved_sigs; } ;
typedef  TYPE_1__ pdf_xref ;
struct TYPE_6__ {int /*<<< orphan*/ * field; struct TYPE_6__* next; } ;
typedef  TYPE_2__ pdf_unsaved_sig ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_7__ {int num_incremental_sections; TYPE_1__* xref_sections; } ;
typedef  TYPE_3__ pdf_document ;

/* Variables and functions */

int pdf_xref_obj_is_unsaved_signature(pdf_document *doc, pdf_obj *obj)
{
	int i;
	for (i = 0; i < doc->num_incremental_sections; i++)
	{
		pdf_xref *xref = &doc->xref_sections[i];
		pdf_unsaved_sig *usig;

		for (usig = xref->unsaved_sigs; usig; usig = usig->next)
		{
			if (usig->field == obj)
				return 1;
		}
	}

	return 0;
}