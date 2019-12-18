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
struct TYPE_5__ {int num_separations; int /*<<< orphan*/ * cs; struct TYPE_5__** name; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ fz_separations ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_drop_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void fz_drop_separations(fz_context *ctx, fz_separations *sep)
{
	if (fz_drop_imp(ctx, sep, &sep->refs))
	{
		int i;
		for (i = 0; i < sep->num_separations; i++)
		{
			fz_free(ctx, sep->name[i]);
			fz_drop_colorspace(ctx, sep->cs[i]);
		}
		fz_free(ctx, sep);
	}
}