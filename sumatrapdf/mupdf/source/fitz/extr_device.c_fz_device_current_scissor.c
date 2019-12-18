#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_rect ;
struct TYPE_5__ {int container_len; TYPE_1__* container; } ;
typedef  TYPE_2__ fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int /*<<< orphan*/  scissor; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_infinite_rect ; 

fz_rect
fz_device_current_scissor(fz_context *ctx, fz_device *dev)
{
	if (dev->container_len > 0)
		return dev->container[dev->container_len-1].scissor;
	return fz_infinite_rect;
}