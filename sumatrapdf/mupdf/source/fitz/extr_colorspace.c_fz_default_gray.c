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
struct TYPE_3__ {int /*<<< orphan*/ * gray; } ;
typedef  TYPE_1__ fz_default_colorspaces ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_device_gray (int /*<<< orphan*/ *) ; 

fz_colorspace *fz_default_gray(fz_context *ctx, const fz_default_colorspaces *default_cs)
{
	return default_cs ? default_cs->gray : fz_device_gray(ctx);
}