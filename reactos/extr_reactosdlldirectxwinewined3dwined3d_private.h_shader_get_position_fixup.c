#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {TYPE_2__* viewports; } ;
struct wined3d_context {scalar_t__ render_offscreen; TYPE_1__* d3d_info; } ;
struct TYPE_4__ {float width; float height; } ;
struct TYPE_3__ {int wined3d_creation_flags; } ;

/* Variables and functions */
 int WINED3D_PIXEL_CENTER_INTEGER ; 

__attribute__((used)) static inline void shader_get_position_fixup(const struct wined3d_context *context,
        const struct wined3d_state *state, unsigned int fixup_count, float *position_fixup)
{
    float center_offset;
    unsigned int i;

    if (context->d3d_info->wined3d_creation_flags & WINED3D_PIXEL_CENTER_INTEGER)
        center_offset = 63.0f / 64.0f;
    else
        center_offset = -1.0f / 64.0f;

    for (i = 0; i < fixup_count; ++i)
    {
        position_fixup[4 * i    ] = 1.0f;
        position_fixup[4 * i + 1] = 1.0f;
        position_fixup[4 * i + 2] = center_offset / state->viewports[i].width;
        position_fixup[4 * i + 3] = -center_offset / state->viewports[i].height;

        if (context->render_offscreen)
        {
            position_fixup[4 * i + 1] *= -1.0f;
            position_fixup[4 * i + 3] *= -1.0f;
        }
    }
}