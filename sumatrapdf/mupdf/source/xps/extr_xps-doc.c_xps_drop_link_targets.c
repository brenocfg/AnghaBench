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
struct TYPE_5__ {struct TYPE_5__* name; struct TYPE_5__* next; } ;
typedef  TYPE_1__ xps_target ;
struct TYPE_6__ {TYPE_1__* target; } ;
typedef  TYPE_2__ xps_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
xps_drop_link_targets(fz_context *ctx, xps_document *doc)
{
	xps_target *target = doc->target, *next;
	while (target)
	{
		next = target->next;
		fz_free(ctx, target->name);
		fz_free(ctx, target);
		target = next;
	}
}