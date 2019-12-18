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
struct TYPE_5__ {int n; int /*<<< orphan*/ * comp; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ fz_halftone ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_drop_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
fz_drop_halftone(fz_context *ctx, fz_halftone *ht)
{
	int i;
	if (fz_drop_imp(ctx, ht, &ht->refs))
	{
		for (i = 0; i < ht->n; i++)
			fz_drop_pixmap(ctx, ht->comp[i]);
		fz_free(ctx, ht);
	}
}