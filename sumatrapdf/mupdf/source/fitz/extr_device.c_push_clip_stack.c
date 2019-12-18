#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_rect ;
struct TYPE_5__ {int container_len; int container_cap; TYPE_3__* container; } ;
typedef  TYPE_1__ fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {int type; scalar_t__ user; int /*<<< orphan*/  scissor; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_device_container_stack ; 
 int /*<<< orphan*/  fz_intersect_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* fz_realloc_array (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
push_clip_stack(fz_context *ctx, fz_device *dev, fz_rect rect, int type)
{
	if (dev->container_len == dev->container_cap)
	{
		int newmax = dev->container_cap * 2;
		if (newmax == 0)
			newmax = 4;
		dev->container = fz_realloc_array(ctx, dev->container, newmax, fz_device_container_stack);
		dev->container_cap = newmax;
	}
	if (dev->container_len == 0)
		dev->container[0].scissor = rect;
	else
	{
		dev->container[dev->container_len].scissor = fz_intersect_rect(dev->container[dev->container_len-1].scissor, rect);
	}
	dev->container[dev->container_len].type = type;
	dev->container[dev->container_len].user = 0;
	dev->container_len++;
}