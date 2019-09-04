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
struct wined3d_cs_set_shader {size_t type; int /*<<< orphan*/  shader; } ;
struct TYPE_2__ {int /*<<< orphan*/ * shader; } ;
struct wined3d_cs {int /*<<< orphan*/  device; TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_COMPUTE_SHADER_RESOURCE_BINDING ; 
 int /*<<< orphan*/  STATE_GRAPHICS_SHADER_RESOURCE_BINDING ; 
 int /*<<< orphan*/  STATE_SHADER (size_t) ; 
 size_t WINED3D_SHADER_TYPE_COMPUTE ; 
 int /*<<< orphan*/  device_invalidate_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_cs_exec_set_shader(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_set_shader *op = data;

    cs->state.shader[op->type] = op->shader;
    device_invalidate_state(cs->device, STATE_SHADER(op->type));
    if (op->type != WINED3D_SHADER_TYPE_COMPUTE)
        device_invalidate_state(cs->device, STATE_GRAPHICS_SHADER_RESOURCE_BINDING);
    else
        device_invalidate_state(cs->device, STATE_COMPUTE_SHADER_RESOURCE_BINDING);
}