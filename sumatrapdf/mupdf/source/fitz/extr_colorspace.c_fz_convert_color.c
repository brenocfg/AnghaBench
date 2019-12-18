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
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;
struct TYPE_5__ {int /*<<< orphan*/  (* convert ) (int /*<<< orphan*/ *,TYPE_1__*,float const*,float*) ;} ;
typedef  TYPE_1__ fz_color_converter ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_color_converter (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_find_color_converter (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,float const*,float*) ; 

void
fz_convert_color(fz_context *ctx, fz_colorspace *ss, const float *sv, fz_colorspace *ds, float *dv, fz_colorspace *is, fz_color_params params)
{
	fz_color_converter cc;
	fz_find_color_converter(ctx, &cc, ss, ds, is, params);
	cc.convert(ctx, &cc, sv, dv);
	fz_drop_color_converter(ctx, &cc);
}