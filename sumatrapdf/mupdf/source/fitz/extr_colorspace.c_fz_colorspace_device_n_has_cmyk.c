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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ fz_colorspace ;

/* Variables and functions */
 int FZ_COLORSPACE_HAS_CMYK ; 

int fz_colorspace_device_n_has_cmyk(fz_context *ctx, fz_colorspace *cs)
{
	return cs && (cs->flags & FZ_COLORSPACE_HAS_CMYK);
}