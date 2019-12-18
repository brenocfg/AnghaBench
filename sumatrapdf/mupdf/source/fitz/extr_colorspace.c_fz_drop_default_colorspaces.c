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
struct TYPE_5__ {int /*<<< orphan*/  oi; int /*<<< orphan*/  cmyk; int /*<<< orphan*/  rgb; int /*<<< orphan*/  gray; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ fz_default_colorspaces ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_drop_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
fz_drop_default_colorspaces(fz_context *ctx, fz_default_colorspaces *default_cs)
{
	if (fz_drop_imp(ctx, default_cs, &default_cs->refs))
	{
		fz_drop_colorspace(ctx, default_cs->gray);
		fz_drop_colorspace(ctx, default_cs->rgb);
		fz_drop_colorspace(ctx, default_cs->cmyk);
		fz_drop_colorspace(ctx, default_cs->oi);
		fz_free(ctx, default_cs);
	}
}