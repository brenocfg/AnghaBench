#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct wined3d_texture {unsigned int level_count; TYPE_8__ texture_rgb; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_glTexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* p_glEnd ) () ;int /*<<< orphan*/  (* p_glVertex2i ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexCoord3fv ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glBegin ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexEnvi ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glEnable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_3__ gl_ops; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct wined3d_blt_info {int /*<<< orphan*/  bind_target; TYPE_1__* texcoords; } ;
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
struct TYPE_12__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct TYPE_9__ {int /*<<< orphan*/  x; } ;
typedef  TYPE_4__ RECT ;

/* Variables and functions */
 int /*<<< orphan*/  GL_REPLACE ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV_MODE ; 
 int /*<<< orphan*/  GL_TEXTURE_MAX_LEVEL ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 int /*<<< orphan*/  apply_texture_blit_state (struct wined3d_gl_info const*,TYPE_8__*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_bind_texture (struct wined3d_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 () ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  texture2d_get_blt_info (struct wined3d_texture*,unsigned int,TYPE_4__ const*,struct wined3d_blt_info*) ; 

void context_draw_textured_quad(struct wined3d_context *context, struct wined3d_texture *texture,
        unsigned int sub_resource_idx, const RECT *src_rect, const RECT *dst_rect,
        enum wined3d_texture_filter_type filter)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct wined3d_blt_info info;
    unsigned int level;

    texture2d_get_blt_info(texture, sub_resource_idx, src_rect, &info);

    gl_info->gl_ops.gl.p_glEnable(info.bind_target);
    checkGLcall("glEnable(bind_target)");

    level = sub_resource_idx % texture->level_count;
    context_bind_texture(context, info.bind_target, texture->texture_rgb.name);
    apply_texture_blit_state(gl_info, &texture->texture_rgb, info.bind_target, level, filter);
    gl_info->gl_ops.gl.p_glTexParameteri(info.bind_target, GL_TEXTURE_MAX_LEVEL, level);
    gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    checkGLcall("glTexEnvi");

    /* Draw a quad. */
    gl_info->gl_ops.gl.p_glBegin(GL_TRIANGLE_STRIP);
    gl_info->gl_ops.gl.p_glTexCoord3fv(&info.texcoords[0].x);
    gl_info->gl_ops.gl.p_glVertex2i(dst_rect->left, dst_rect->top);

    gl_info->gl_ops.gl.p_glTexCoord3fv(&info.texcoords[1].x);
    gl_info->gl_ops.gl.p_glVertex2i(dst_rect->right, dst_rect->top);

    gl_info->gl_ops.gl.p_glTexCoord3fv(&info.texcoords[2].x);
    gl_info->gl_ops.gl.p_glVertex2i(dst_rect->left, dst_rect->bottom);

    gl_info->gl_ops.gl.p_glTexCoord3fv(&info.texcoords[3].x);
    gl_info->gl_ops.gl.p_glVertex2i(dst_rect->right, dst_rect->bottom);
    gl_info->gl_ops.gl.p_glEnd();

    gl_info->gl_ops.gl.p_glTexParameteri(info.bind_target, GL_TEXTURE_MAX_LEVEL, texture->level_count - 1);
    context_bind_texture(context, info.bind_target, 0);
}