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
struct wined3d_context {scalar_t__ draw_buffers_mask; TYPE_1__* current_fbo; } ;
struct TYPE_2__ {scalar_t__ rt_mask; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  context_apply_draw_buffers (struct wined3d_context*,scalar_t__) ; 
 scalar_t__ find_draw_buffers_mask (struct wined3d_context*,struct wined3d_state const*) ; 
 scalar_t__ isStateDirty (struct wined3d_context*,int /*<<< orphan*/ ) ; 

void context_state_drawbuf(struct wined3d_context *context, const struct wined3d_state *state, DWORD state_id)
{
    DWORD rt_mask, *cur_mask;

    if (isStateDirty(context, STATE_FRAMEBUFFER)) return;

    cur_mask = context->current_fbo ? &context->current_fbo->rt_mask : &context->draw_buffers_mask;
    rt_mask = find_draw_buffers_mask(context, state);
    if (rt_mask != *cur_mask)
    {
        context_apply_draw_buffers(context, rt_mask);
        *cur_mask = rt_mask;
    }
}