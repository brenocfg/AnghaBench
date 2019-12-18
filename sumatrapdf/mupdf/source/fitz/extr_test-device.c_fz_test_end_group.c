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
struct TYPE_2__ {scalar_t__ passthrough; } ;
typedef  TYPE_1__ fz_test_device ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_end_group (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
fz_test_end_group(fz_context *ctx, fz_device *dev_)
{
	fz_test_device *dev = (fz_test_device*)dev_;

	if (dev->passthrough)
		fz_end_group(ctx, dev->passthrough);
}