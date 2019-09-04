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
struct wined3d_rendertarget_view {TYPE_1__* format; } ;
struct wined3d_fb_state {struct wined3d_rendertarget_view* depth_stencil; struct wined3d_rendertarget_view** render_targets; } ;
struct wined3d_device {int dummy; } ;
typedef  struct wined3d_color {float member_0; float member_1; float member_2; float member_3; } const wined3d_color ;
struct wined3d_box {scalar_t__ left; scalar_t__ top; scalar_t__ right; scalar_t__ bottom; int back; scalar_t__ front; } ;
struct wined3d_blitter {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; scalar_t__ stencil_size; scalar_t__ depth_size; } ;
typedef  TYPE_2__ RECT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int,int /*<<< orphan*/ ) ; 
 int WINED3DCLEAR_STENCIL ; 
 int WINED3DCLEAR_TARGET ; 
 int WINED3DCLEAR_ZBUFFER ; 
 int /*<<< orphan*/  debug_d3dformat (int /*<<< orphan*/ ) ; 
 void* max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  surface_cpu_blt_colour_fill (struct wined3d_rendertarget_view*,struct wined3d_box*,struct wined3d_color const*) ; 

__attribute__((used)) static void cpu_blitter_clear(struct wined3d_blitter *blitter, struct wined3d_device *device,
        unsigned int rt_count, const struct wined3d_fb_state *fb, unsigned int rect_count, const RECT *clear_rects,
        const RECT *draw_rect, DWORD flags, const struct wined3d_color *colour, float depth, DWORD stencil)
{
    struct wined3d_color c = {depth, 0.0f, 0.0f, 0.0f};
    struct wined3d_rendertarget_view *view;
    struct wined3d_box box;
    unsigned int i, j;

    if (!rect_count)
    {
        rect_count = 1;
        clear_rects = draw_rect;
    }

    for (i = 0; i < rect_count; ++i)
    {
        box.left = max(clear_rects[i].left, draw_rect->left);
        box.top = max(clear_rects[i].top, draw_rect->top);
        box.right = min(clear_rects[i].right, draw_rect->right);
        box.bottom = min(clear_rects[i].bottom, draw_rect->bottom);
        box.front = 0;
        box.back = 1;

        if (box.left >= box.right || box.top >= box.bottom)
            continue;

        if (flags & WINED3DCLEAR_TARGET)
        {
            for (j = 0; j < rt_count; ++j)
            {
                if ((view = fb->render_targets[j]))
                    surface_cpu_blt_colour_fill(view, &box, colour);
            }
        }

        if ((flags & (WINED3DCLEAR_ZBUFFER | WINED3DCLEAR_STENCIL)) && (view = fb->depth_stencil))
        {
            if ((view->format->depth_size && !(flags & WINED3DCLEAR_ZBUFFER))
                    || (view->format->stencil_size && !(flags & WINED3DCLEAR_STENCIL)))
                FIXME("Clearing %#x on %s.\n", flags, debug_d3dformat(view->format->id));

            surface_cpu_blt_colour_fill(view, &box, &c);
        }
    }
}