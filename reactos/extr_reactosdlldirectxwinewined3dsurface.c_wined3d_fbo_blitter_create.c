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
struct TYPE_3__ {int /*<<< orphan*/  glBlitFramebuffer; } ;
struct wined3d_gl_info {TYPE_1__ fbo_ops; } ;
struct wined3d_blitter {struct wined3d_blitter* next; int /*<<< orphan*/ * ops; } ;
struct TYPE_4__ {scalar_t__ offscreen_rendering_mode; } ;

/* Variables and functions */
 scalar_t__ ORM_FBO ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_blitter*) ; 
 int /*<<< orphan*/  fbo_blitter_ops ; 
 struct wined3d_blitter* heap_alloc (int) ; 
 TYPE_2__ wined3d_settings ; 

void wined3d_fbo_blitter_create(struct wined3d_blitter **next, const struct wined3d_gl_info *gl_info)
{
    struct wined3d_blitter *blitter;

    if ((wined3d_settings.offscreen_rendering_mode != ORM_FBO) || !gl_info->fbo_ops.glBlitFramebuffer)
        return;

    if (!(blitter = heap_alloc(sizeof(*blitter))))
        return;

    TRACE("Created blitter %p.\n", blitter);

    blitter->ops = &fbo_blitter_ops;
    blitter->next = *next;
    *next = blitter;
}