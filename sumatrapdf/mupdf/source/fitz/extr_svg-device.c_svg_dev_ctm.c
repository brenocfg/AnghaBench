#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ svg_device ;
typedef  int /*<<< orphan*/  fz_output ;
struct TYPE_6__ {float a; float d; int /*<<< orphan*/  f; int /*<<< orphan*/  e; int /*<<< orphan*/  c; int /*<<< orphan*/  b; } ;
typedef  TYPE_2__ fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
svg_dev_ctm(fz_context *ctx, svg_device *sdev, fz_matrix ctm)
{
	fz_output *out = sdev->out;

	if (ctm.a != 1.0f || ctm.b != 0 || ctm.c != 0 || ctm.d != 1.0f || ctm.e != 0 || ctm.f != 0)
	{
		fz_write_printf(ctx, out, " transform=\"matrix(%g,%g,%g,%g,%g,%g)\"",
			ctm.a, ctm.b, ctm.c, ctm.d, ctm.e, ctm.f);
	}
}