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
struct TYPE_7__ {int start; int len; int /*<<< orphan*/ * table; int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ pdf_xref_subsec ;
typedef  int /*<<< orphan*/  pdf_xref_entry ;
struct TYPE_8__ {int num_objects; TYPE_1__* subsec; } ;
typedef  TYPE_2__ pdf_xref ;
struct TYPE_9__ {size_t xref_base; scalar_t__* xref_index; TYPE_2__* xref_sections; } ;
typedef  TYPE_3__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ensure_incremental_xref (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  pdf_resize_xref (int /*<<< orphan*/ *,TYPE_3__*,int) ; 

__attribute__((used)) static pdf_xref_entry *pdf_get_incremental_xref_entry(fz_context *ctx, pdf_document *doc, int i)
{
	pdf_xref *xref;
	pdf_xref_subsec *sub;

	/* Make a new final xref section if we haven't already */
	ensure_incremental_xref(ctx, doc);

	xref = &doc->xref_sections[doc->xref_base];
	if (i >= xref->num_objects)
		pdf_resize_xref(ctx, doc, i + 1);

	sub = xref->subsec;
	assert(sub != NULL && sub->next == NULL);
	assert(i >= sub->start && i < sub->start + sub->len);
	doc->xref_index[i] = 0;
	return &sub->table[i - sub->start];
}