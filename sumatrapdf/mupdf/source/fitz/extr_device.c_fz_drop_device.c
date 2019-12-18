#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* container; int /*<<< orphan*/  (* drop_device ) (int /*<<< orphan*/ *,TYPE_1__*) ;scalar_t__ close_device; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_drop_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
fz_drop_device(fz_context *ctx, fz_device *dev)
{
	if (fz_drop_imp(ctx, dev, &dev->refs))
	{
		if (dev->close_device)
			fz_warn(ctx, "dropping unclosed device");
		if (dev->drop_device)
			dev->drop_device(ctx, dev);
		fz_free(ctx, dev->container);
		fz_free(ctx, dev);
	}
}