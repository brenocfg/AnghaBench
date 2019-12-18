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
struct TYPE_9__ {unsigned char* lookup; int high; TYPE_1__* base; } ;
struct TYPE_10__ {TYPE_2__ indexed; } ;
struct TYPE_11__ {TYPE_3__ u; } ;
typedef  TYPE_4__ fz_colorspace ;
struct TYPE_12__ {int /*<<< orphan*/  (* convert_via ) (int /*<<< orphan*/ *,TYPE_5__*,float*,float*) ;TYPE_4__* ss_via; } ;
typedef  TYPE_5__ fz_color_converter ;
struct TYPE_8__ {int n; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ FZ_COLORSPACE_LAB ; 
 int fz_clampi (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_5__*,float*,float*) ; 

__attribute__((used)) static void indexed_via_base(fz_context *ctx, fz_color_converter *cc, const float *src, float *dst)
{
	fz_colorspace *ss = cc->ss_via;
	const unsigned char *lookup = ss->u.indexed.lookup;
	int high = ss->u.indexed.high;
	int n = ss->u.indexed.base->n;
	float base[4];
	int i, k;

	i = src[0] * 255;
	i = fz_clampi(i, 0, high);
	if (ss->u.indexed.base->type == FZ_COLORSPACE_LAB)
	{
		base[0] = lookup[i * 3 + 0] * 100 / 255.0f;
		base[1] = lookup[i * 3 + 1] - 128;
		base[2] = lookup[i * 3 + 2] - 128;
	}
	else
	{
		for (k = 0; k < n; ++k)
			base[k] = lookup[i * n + k] / 255.0f;
	}

	cc->convert_via(ctx, cc, base, dst);
}