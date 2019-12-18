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
typedef  int /*<<< orphan*/  fz_rasterizer ;
struct TYPE_2__ {scalar_t__ alen; scalar_t__ len; } ;
typedef  TYPE_1__ fz_gel ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static int
fz_reset_gel(fz_context *ctx, fz_rasterizer *rast)
{
	fz_gel *gel = (fz_gel *)rast;

	gel->len = 0;
	gel->alen = 0;

	return 0;
}