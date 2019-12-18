#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int high; unsigned char* lookup; int /*<<< orphan*/  base; } ;
struct TYPE_9__ {TYPE_1__ indexed; } ;
struct TYPE_10__ {TYPE_2__ u; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ fz_colorspace ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_COLORSPACE_INDEXED ; 
 int /*<<< orphan*/  FZ_ERROR_SYNTAX ; 
 int /*<<< orphan*/  fz_keep_colorspace (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* fz_new_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

fz_colorspace *
fz_new_indexed_colorspace(fz_context *ctx, fz_colorspace *base, int high, unsigned char *lookup)
{
	fz_colorspace *cs;
	char name[100];
	if (high < 0 || high > 255)
		fz_throw(ctx, FZ_ERROR_SYNTAX, "invalid maximum value in indexed colorspace");
	fz_snprintf(name, sizeof name, "Indexed(%d,%s)", high, base->name);
	cs = fz_new_colorspace(ctx, FZ_COLORSPACE_INDEXED, 0, 1, name);
	cs->u.indexed.base = fz_keep_colorspace(ctx, base);
	cs->u.indexed.high = high;
	cs->u.indexed.lookup = lookup;
	return cs;
}