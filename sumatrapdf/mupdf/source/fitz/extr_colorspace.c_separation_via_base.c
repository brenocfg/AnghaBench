#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_9__ {TYPE_1__* base; int /*<<< orphan*/  tint; int /*<<< orphan*/  (* eval ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float const*,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_2__ separation; } ;
struct TYPE_11__ {TYPE_3__ u; int /*<<< orphan*/  n; } ;
typedef  TYPE_4__ fz_colorspace ;
struct TYPE_12__ {int /*<<< orphan*/  (* convert_via ) (int /*<<< orphan*/ *,TYPE_5__*,float*,float*) ;TYPE_4__* ss_via; } ;
typedef  TYPE_5__ fz_color_converter ;
struct TYPE_8__ {int /*<<< orphan*/  n; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float const*,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,TYPE_5__*,float*,float*) ; 

__attribute__((used)) static void separation_via_base(fz_context *ctx, fz_color_converter *cc, const float *src, float *dst)
{
	fz_colorspace *ss = cc->ss_via;
	float base[4];
	ss->u.separation.eval(ctx, ss->u.separation.tint, src, ss->n, base, ss->u.separation.base->n);
	cc->convert_via(ctx, cc, base, dst);
}