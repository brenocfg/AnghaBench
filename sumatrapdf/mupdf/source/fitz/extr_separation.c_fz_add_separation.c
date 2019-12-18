#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_separations; int* cs_pos; int /*<<< orphan*/ * cs; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ fz_separations ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int FZ_MAX_SEPARATIONS ; 
 int /*<<< orphan*/  fz_keep_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void fz_add_separation(fz_context *ctx, fz_separations *sep, const char *name, fz_colorspace *cs, int colorant)
{
	int n;

	if (!sep)
		fz_throw(ctx, FZ_ERROR_GENERIC, "can't add to non-existent separations");

	n = sep->num_separations;
	if (n == FZ_MAX_SEPARATIONS)
		fz_throw(ctx, FZ_ERROR_GENERIC, "too many separations");

	sep->name[n] = fz_strdup(ctx, name);
	sep->cs[n] = fz_keep_colorspace(ctx, cs);
	sep->cs_pos[n] = colorant;

	sep->num_separations++;
}