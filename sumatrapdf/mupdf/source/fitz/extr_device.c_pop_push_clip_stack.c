#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int container_len; TYPE_1__* container; } ;
typedef  TYPE_2__ fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_disable_device (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
pop_push_clip_stack(fz_context *ctx, fz_device *dev, int pop_type, int push_type)
{
	if (dev->container_len == 0 || dev->container[dev->container_len-1].type != pop_type)
	{
		fz_disable_device(ctx, dev);
		fz_throw(ctx, FZ_ERROR_GENERIC, "device calls unbalanced");
	}
	dev->container[dev->container_len-1].type = push_type;
}