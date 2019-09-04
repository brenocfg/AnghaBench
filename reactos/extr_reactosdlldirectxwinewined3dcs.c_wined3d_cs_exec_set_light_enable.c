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
struct wined3d_light_info {int glIndex; } ;
struct wined3d_device {TYPE_1__* adapter; } ;
struct wined3d_cs_set_light_enable {scalar_t__ enable; int /*<<< orphan*/  idx; } ;
struct wined3d_cs {int /*<<< orphan*/  state; struct wined3d_device* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  d3d_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  STATE_ACTIVELIGHT (int) ; 
 int /*<<< orphan*/  STATE_LIGHT_TYPE ; 
 int /*<<< orphan*/  device_invalidate_state (struct wined3d_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_state_enable_light (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wined3d_light_info*,scalar_t__) ; 
 struct wined3d_light_info* wined3d_state_get_light (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_cs_exec_set_light_enable(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_set_light_enable *op = data;
    struct wined3d_device *device = cs->device;
    struct wined3d_light_info *light_info;
    int prev_idx;

    if (!(light_info = wined3d_state_get_light(&cs->state, op->idx)))
    {
        ERR("Light doesn't exist.\n");
        return;
    }

    prev_idx = light_info->glIndex;
    wined3d_state_enable_light(&cs->state, &device->adapter->d3d_info, light_info, op->enable);
    if (light_info->glIndex != prev_idx)
    {
        device_invalidate_state(device, STATE_LIGHT_TYPE);
        device_invalidate_state(device, STATE_ACTIVELIGHT(op->enable ? light_info->glIndex : prev_idx));
    }
}