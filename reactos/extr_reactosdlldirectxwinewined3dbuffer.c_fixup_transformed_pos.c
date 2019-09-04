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
struct wined3d_vec4 {float w; float x; float y; float z; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int fixup_transformed_pos(struct wined3d_vec4 *p)
{
    /* rhw conversion like in position_float4(). */
    if (p->w != 1.0f && p->w != 0.0f)
    {
        float w = 1.0f / p->w;
        p->x *= w;
        p->y *= w;
        p->z *= w;
        p->w = w;
    }

    return sizeof(*p);
}