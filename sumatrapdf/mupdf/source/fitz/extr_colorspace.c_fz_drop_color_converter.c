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
struct TYPE_3__ {int /*<<< orphan*/ * link; } ;
typedef  TYPE_1__ fz_color_converter ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_icc_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
fz_drop_color_converter(fz_context *ctx, fz_color_converter *cc)
{
#if FZ_ENABLE_ICC
	if (cc->link)
	{
		fz_drop_icc_link(ctx, cc->link);
		cc->link = NULL;
	}
#endif
}