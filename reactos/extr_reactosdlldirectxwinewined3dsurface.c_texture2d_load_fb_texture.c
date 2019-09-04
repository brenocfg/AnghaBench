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
struct TYPE_8__ {struct wined3d_device* device; } ;
struct wined3d_texture {unsigned int level_count; TYPE_4__ resource; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* p_glCopyTexSubImage2D ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glReadBuffer ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_3__ gl_ops; } ;
struct wined3d_device {int dummy; } ;
struct TYPE_5__ {unsigned int sub_resource_idx; struct wined3d_texture* texture; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; TYPE_1__ current_rt; } ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  context_get_offscreen_gl_buffer (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_restore (struct wined3d_context*,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  device_invalidate_state (struct wined3d_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wined3d_resource_is_offscreen (TYPE_4__*) ; 
 int /*<<< orphan*/  wined3d_texture_bind_and_dirtify (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_get_gl_buffer (struct wined3d_texture*) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_sub_resource_target (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_prepare_texture (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 

void texture2d_load_fb_texture(struct wined3d_texture *texture,
        unsigned int sub_resource_idx, BOOL srgb, struct wined3d_context *context)
{
    struct wined3d_device *device = texture->resource.device;
    struct wined3d_texture *restore_texture;
    const struct wined3d_gl_info *gl_info;
    unsigned int restore_idx, level;
    GLenum target;

    restore_texture = context->current_rt.texture;
    restore_idx = context->current_rt.sub_resource_idx;
    if (restore_texture != texture || restore_idx != sub_resource_idx)
        context = context_acquire(device, texture, sub_resource_idx);
    else
        restore_texture = NULL;

    gl_info = context->gl_info;
    device_invalidate_state(device, STATE_FRAMEBUFFER);

    wined3d_texture_prepare_texture(texture, context, srgb);
    wined3d_texture_bind_and_dirtify(texture, context, srgb);

    TRACE("Reading back offscreen render target %p, %u.\n", texture, sub_resource_idx);

    if (wined3d_resource_is_offscreen(&texture->resource))
        gl_info->gl_ops.gl.p_glReadBuffer(context_get_offscreen_gl_buffer(context));
    else
        gl_info->gl_ops.gl.p_glReadBuffer(wined3d_texture_get_gl_buffer(texture));
    checkGLcall("glReadBuffer");

    level = sub_resource_idx % texture->level_count;
    target = wined3d_texture_get_sub_resource_target(texture, sub_resource_idx);
    gl_info->gl_ops.gl.p_glCopyTexSubImage2D(target, level, 0, 0, 0, 0,
            wined3d_texture_get_level_width(texture, level),
            wined3d_texture_get_level_height(texture, level));
    checkGLcall("glCopyTexSubImage2D");

    if (restore_texture)
        context_restore(context, restore_texture, restore_idx);
}