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
typedef  void* uint32_t ;
struct TYPE_3__ {int num_separations; void** cmyk; void** rgba; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ fz_separations ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int FZ_MAX_SEPARATIONS ; 
 int /*<<< orphan*/  fz_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void fz_add_separation_equivalents(fz_context *ctx, fz_separations *sep, uint32_t rgba, uint32_t cmyk, const char *name)
{
	int n;

	if (!sep)
		fz_throw(ctx, FZ_ERROR_GENERIC, "can't add to non-existent separations");

	n = sep->num_separations;
	if (n == FZ_MAX_SEPARATIONS)
		fz_throw(ctx, FZ_ERROR_GENERIC, "too many separations");

	sep->name[n] = fz_strdup(ctx, name);
	sep->rgba[n] = rgba;
	sep->cmyk[n] = cmyk;

	sep->num_separations++;
}