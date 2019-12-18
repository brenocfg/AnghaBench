#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* outline; struct TYPE_5__* name; struct TYPE_5__* next; } ;
typedef  TYPE_1__ xps_fixdoc ;
struct TYPE_6__ {int /*<<< orphan*/ * last_fixdoc; TYPE_1__* first_fixdoc; } ;
typedef  TYPE_2__ xps_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
xps_drop_fixed_documents(fz_context *ctx, xps_document *doc)
{
	xps_fixdoc *fixdoc = doc->first_fixdoc;
	while (fixdoc)
	{
		xps_fixdoc *next = fixdoc->next;
		fz_free(ctx, fixdoc->name);
		fz_free(ctx, fixdoc->outline);
		fz_free(ctx, fixdoc);
		fixdoc = next;
	}
	doc->first_fixdoc = NULL;
	doc->last_fixdoc = NULL;
}