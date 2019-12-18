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
struct TYPE_5__ {struct TYPE_5__* uri; struct TYPE_5__* title; struct TYPE_5__* down; struct TYPE_5__* next; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ fz_outline ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_drop_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
fz_drop_outline(fz_context *ctx, fz_outline *outline)
{
	while (fz_drop_imp(ctx, outline, &outline->refs))
	{
		fz_outline *next = outline->next;
		fz_drop_outline(ctx, outline->down);
		fz_free(ctx, outline->title);
		fz_free(ctx, outline->uri);
		fz_free(ctx, outline);
		outline = next;
	}
}