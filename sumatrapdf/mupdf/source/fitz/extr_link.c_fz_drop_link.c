#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* uri; struct TYPE_5__* next; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ fz_link ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_drop_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
fz_drop_link(fz_context *ctx, fz_link *link)
{
	while (fz_drop_imp(ctx, link, &link->refs))
	{
		fz_link *next = link->next;
		fz_free(ctx, link->uri);
		fz_free(ctx, link);
		link = next;
	}
}