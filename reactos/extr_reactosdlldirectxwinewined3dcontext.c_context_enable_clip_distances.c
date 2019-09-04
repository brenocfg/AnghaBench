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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* p_glDisable ) (scalar_t__) ;int /*<<< orphan*/  (* p_glEnable ) (scalar_t__) ;} ;
struct TYPE_6__ {TYPE_2__ gl; } ;
struct TYPE_4__ {unsigned int user_clip_distances; } ;
struct wined3d_gl_info {TYPE_3__ gl_ops; TYPE_1__ limits; } ;
struct wined3d_context {unsigned int clip_distance_mask; struct wined3d_gl_info* gl_info; } ;

/* Variables and functions */
 scalar_t__ GL_CLIP_DISTANCE0 ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 unsigned int wined3d_bit_scan (unsigned int*) ; 

void context_enable_clip_distances(struct wined3d_context *context, unsigned int enable_mask)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    unsigned int clip_distance_count = gl_info->limits.user_clip_distances;
    unsigned int i, disable_mask, current_mask;

    disable_mask = ~enable_mask;
    enable_mask &= (1u << clip_distance_count) - 1;
    disable_mask &= (1u << clip_distance_count) - 1;
    current_mask = context->clip_distance_mask;
    context->clip_distance_mask = enable_mask;

    enable_mask &= ~current_mask;
    while (enable_mask)
    {
        i = wined3d_bit_scan(&enable_mask);
        gl_info->gl_ops.gl.p_glEnable(GL_CLIP_DISTANCE0 + i);
    }
    disable_mask &= current_mask;
    while (disable_mask)
    {
        i = wined3d_bit_scan(&disable_mask);
        gl_info->gl_ops.gl.p_glDisable(GL_CLIP_DISTANCE0 + i);
    }
    checkGLcall("toggle clip distances");
}