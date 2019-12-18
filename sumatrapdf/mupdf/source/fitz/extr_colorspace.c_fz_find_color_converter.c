#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_15__ {TYPE_4__* base; } ;
struct TYPE_14__ {TYPE_4__* base; } ;
struct TYPE_16__ {TYPE_2__ separation; TYPE_1__ indexed; } ;
struct TYPE_17__ {scalar_t__ type; TYPE_3__ u; } ;
typedef  TYPE_4__ fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;
struct TYPE_18__ {TYPE_4__* ss; int /*<<< orphan*/  convert; int /*<<< orphan*/  convert_via; TYPE_4__* ss_via; int /*<<< orphan*/ * link; TYPE_4__* ds; } ;
typedef  TYPE_5__ fz_color_converter ;

/* Variables and functions */
 scalar_t__ FZ_COLORSPACE_INDEXED ; 
 scalar_t__ FZ_COLORSPACE_SEPARATION ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_init_process_color_converter (int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  indexed_via_base ; 
 int /*<<< orphan*/  separation_via_base ; 

void
fz_find_color_converter(fz_context *ctx, fz_color_converter *cc, fz_colorspace *ss, fz_colorspace *ds, fz_colorspace *is, fz_color_params params)
{
	cc->ds = ds;
#if FZ_ENABLE_ICC
	cc->link = NULL;
#endif

	if (ds->type == FZ_COLORSPACE_INDEXED)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Cannot convert into Indexed colorspace.");
	if (ds->type == FZ_COLORSPACE_SEPARATION)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Cannot convert into Separation colorspace.");

	if (ss->type == FZ_COLORSPACE_INDEXED)
	{
		cc->ss = ss->u.indexed.base;
		cc->ss_via = ss;
		fz_init_process_color_converter(ctx, cc, ss->u.indexed.base, ds, is, params);
		cc->convert_via = cc->convert;
		cc->convert = indexed_via_base;
	}
	else if (ss->type == FZ_COLORSPACE_SEPARATION)
	{
		cc->ss = ss->u.separation.base;
		cc->ss_via = ss;
		fz_init_process_color_converter(ctx, cc, ss->u.separation.base, ds, is, params);
		cc->convert_via = cc->convert;
		cc->convert = separation_via_base;
	}
	else
	{
		cc->ss = ss;
		fz_init_process_color_converter(ctx, cc, ss, ds, is, params);
	}
}