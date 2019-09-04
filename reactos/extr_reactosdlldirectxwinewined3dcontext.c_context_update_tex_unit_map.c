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
struct wined3d_state {int dummy; } ;
struct TYPE_2__ {scalar_t__ graphics_samplers; } ;
struct wined3d_gl_info {TYPE_1__ limits; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ MAX_COMBINED_SAMPLERS ; 
 int /*<<< orphan*/  context_map_fixed_function_samplers (struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  context_map_psamplers (struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  context_map_vsamplers (struct wined3d_context*,scalar_t__,struct wined3d_state const*) ; 
 int /*<<< orphan*/  context_update_fixed_function_usage_map (struct wined3d_context*,struct wined3d_state const*) ; 
 scalar_t__ use_ps (struct wined3d_state const*) ; 
 scalar_t__ use_vs (struct wined3d_state const*) ; 

__attribute__((used)) static void context_update_tex_unit_map(struct wined3d_context *context, const struct wined3d_state *state)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    BOOL vs = use_vs(state);
    BOOL ps = use_ps(state);

    if (!ps)
        context_update_fixed_function_usage_map(context, state);

    /* Try to go for a 1:1 mapping of the samplers when possible. Pixel shaders
     * need a 1:1 map at the moment.
     * When the mapping of a stage is changed, sampler and ALL texture stage
     * states have to be reset. */

    if (gl_info->limits.graphics_samplers >= MAX_COMBINED_SAMPLERS)
        return;

    if (ps)
        context_map_psamplers(context, state);
    else
        context_map_fixed_function_samplers(context, state);

    if (vs)
        context_map_vsamplers(context, ps, state);
}