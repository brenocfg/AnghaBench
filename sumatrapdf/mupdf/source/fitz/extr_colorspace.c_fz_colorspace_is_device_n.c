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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ fz_colorspace ;

/* Variables and functions */
 scalar_t__ FZ_COLORSPACE_SEPARATION ; 

int fz_colorspace_is_device_n(fz_context *ctx, fz_colorspace *cs)
{
	return cs && (cs->type == FZ_COLORSPACE_SEPARATION);
}