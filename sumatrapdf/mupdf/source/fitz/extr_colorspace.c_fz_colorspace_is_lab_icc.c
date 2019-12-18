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
struct TYPE_3__ {scalar_t__ type; int flags; } ;
typedef  TYPE_1__ fz_colorspace ;

/* Variables and functions */
 int FZ_COLORSPACE_IS_ICC ; 
 scalar_t__ FZ_COLORSPACE_LAB ; 

int fz_colorspace_is_lab_icc(fz_context *ctx, fz_colorspace *cs)
{
	return cs && (cs->type == FZ_COLORSPACE_LAB) && (cs->flags & FZ_COLORSPACE_IS_ICC);
}