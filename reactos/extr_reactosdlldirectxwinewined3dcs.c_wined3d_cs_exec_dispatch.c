#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {int /*<<< orphan*/ * unordered_access_view; int /*<<< orphan*/ * shader; } ;
struct TYPE_6__ {TYPE_1__* buffer; } ;
struct TYPE_7__ {TYPE_2__ indirect; } ;
struct TYPE_8__ {TYPE_3__ u; scalar_t__ indirect; } ;
struct wined3d_cs_dispatch {TYPE_4__ parameters; } ;
struct wined3d_cs {int /*<<< orphan*/  device; struct wined3d_state state; } ;
struct TYPE_5__ {int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 size_t WINED3D_PIPELINE_COMPUTE ; 
 unsigned int WINED3D_SHADER_TYPE_COMPUTE ; 
 int /*<<< orphan*/  dispatch_compute (int /*<<< orphan*/ ,struct wined3d_state*,TYPE_4__*) ; 
 int /*<<< orphan*/  release_shader_resources (struct wined3d_state*,unsigned int) ; 
 int /*<<< orphan*/  release_unordered_access_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wined3d_cs_exec_dispatch(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_dispatch *op = data;
    struct wined3d_state *state = &cs->state;

    dispatch_compute(cs->device, state, &op->parameters);

    if (op->parameters.indirect)
        wined3d_resource_release(&op->parameters.u.indirect.buffer->resource);

    release_shader_resources(state, 1u << WINED3D_SHADER_TYPE_COMPUTE);
    release_unordered_access_resources(state->shader[WINED3D_SHADER_TYPE_COMPUTE],
            state->unordered_access_view[WINED3D_PIPELINE_COMPUTE]);
}