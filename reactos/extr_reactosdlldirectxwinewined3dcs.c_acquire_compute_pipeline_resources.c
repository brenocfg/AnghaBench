#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_state {int /*<<< orphan*/ * unordered_access_view; int /*<<< orphan*/ * shader; } ;

/* Variables and functions */
 size_t WINED3D_PIPELINE_COMPUTE ; 
 unsigned int WINED3D_SHADER_TYPE_COMPUTE ; 
 int /*<<< orphan*/  acquire_shader_resources (struct wined3d_state const*,unsigned int) ; 
 int /*<<< orphan*/  acquire_unordered_access_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acquire_compute_pipeline_resources(const struct wined3d_state *state)
{
    acquire_shader_resources(state, 1u << WINED3D_SHADER_TYPE_COMPUTE);
    acquire_unordered_access_resources(state->shader[WINED3D_SHADER_TYPE_COMPUTE],
            state->unordered_access_view[WINED3D_PIPELINE_COMPUTE]);
}