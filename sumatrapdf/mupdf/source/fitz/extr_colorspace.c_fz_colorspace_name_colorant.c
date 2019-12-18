#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int /*<<< orphan*/ ** colorant; } ;
struct TYPE_6__ {TYPE_1__ separation; } ;
struct TYPE_7__ {int n; scalar_t__ type; int /*<<< orphan*/  flags; TYPE_2__ u; } ;
typedef  TYPE_3__ fz_colorspace ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_COLORSPACE_HAS_CMYK ; 
 int /*<<< orphan*/  FZ_COLORSPACE_HAS_SPOTS ; 
 scalar_t__ FZ_COLORSPACE_SEPARATION ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

void fz_colorspace_name_colorant(fz_context *ctx, fz_colorspace *cs, int i, const char *name)
{
	if (i < 0 || i >= cs->n)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Attempt to name out of range colorant");
	if (cs->type != FZ_COLORSPACE_SEPARATION)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Attempt to name colorant for non-separation colorspace");

	fz_free(ctx, cs->u.separation.colorant[i]);
	cs->u.separation.colorant[i] = NULL;
	cs->u.separation.colorant[i] = fz_strdup(ctx, name);

	if (!strcmp(name, "Cyan") || !strcmp(name, "Magenta") || !strcmp(name, "Yellow") || !strcmp(name, "Black"))
		cs->flags |= FZ_COLORSPACE_HAS_CMYK;
	else
		cs->flags |= FZ_COLORSPACE_HAS_SPOTS;
}