#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rgb; } ;
typedef  TYPE_1__ fz_default_colorspaces ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {scalar_t__ type; int n; } ;
typedef  TYPE_2__ fz_colorspace ;

/* Variables and functions */
 scalar_t__ FZ_COLORSPACE_RGB ; 
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_keep_colorspace (int /*<<< orphan*/ *,TYPE_2__*) ; 

void fz_set_default_rgb(fz_context *ctx, fz_default_colorspaces *default_cs, fz_colorspace *cs)
{
	if (cs->type == FZ_COLORSPACE_RGB && cs->n == 3)
	{
		fz_drop_colorspace(ctx, default_cs->rgb);
		default_cs->rgb = fz_keep_colorspace(ctx, cs);
	}
}