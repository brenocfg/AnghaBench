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
struct TYPE_7__ {int len; scalar_t__ start; TYPE_1__* table; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ pdf_xref_subsec ;
struct TYPE_8__ {int num_objects; TYPE_2__* subsec; } ;
typedef  TYPE_3__ pdf_xref ;
struct TYPE_9__ {size_t xref_base; TYPE_3__* xref_sections; } ;
typedef  TYPE_4__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int pdf_xref_is_incremental(fz_context *ctx, pdf_document *doc, int num)
{
	pdf_xref *xref = &doc->xref_sections[doc->xref_base];
	pdf_xref_subsec *sub = xref->subsec;

	assert(sub != NULL && sub->next == NULL && sub->len == xref->num_objects && sub->start == 0);

	return num < xref->num_objects && sub->table[num].type;
}