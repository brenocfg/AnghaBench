#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct shadearg {int /*<<< orphan*/  color_params; TYPE_1__* shade; int /*<<< orphan*/ * dev; } ;
typedef  int /*<<< orphan*/  fz_vertex ;
typedef  int /*<<< orphan*/  fz_test_device ;
struct TYPE_2__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  use_function; } ;
typedef  TYPE_1__ fz_shade ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_test_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,float const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prepare_vertex(fz_context *ctx, void *arg_, fz_vertex *v, const float *color)
{
	struct shadearg *arg = arg_;
	fz_test_device *dev = arg->dev;
	fz_shade *shade = arg->shade;
	if (!shade->use_function)
		fz_test_color(ctx, dev, shade->colorspace, color, arg->color_params);
}