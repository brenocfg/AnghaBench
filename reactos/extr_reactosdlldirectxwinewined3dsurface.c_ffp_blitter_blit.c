#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  struct wined3d_color_key {scalar_t__ color_space_low_value; } const wined3d_color_key ;
struct TYPE_11__ {int color_key_flags; struct wined3d_color_key const src_blt_color_key; } ;
struct wined3d_resource {int access; TYPE_3__* format; int /*<<< orphan*/  multisample_quality; int /*<<< orphan*/  multisample_type; struct wined3d_device* device; } ;
struct wined3d_texture {unsigned int level_count; TYPE_1__* swapchain; TYPE_4__ async; struct wined3d_resource resource; int /*<<< orphan*/  target; } ;
struct wined3d_resource_desc {scalar_t__ format; int access; int depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ size; int /*<<< orphan*/  usage; int /*<<< orphan*/  multisample_quality; int /*<<< orphan*/  multisample_type; int /*<<< orphan*/  resource_type; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* p_glFlush ) () ;int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glAlphaFunc ) (int /*<<< orphan*/ ,float) ;int /*<<< orphan*/  (* p_glEnable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {TYPE_6__ gl; } ;
struct wined3d_gl_info {TYPE_5__ gl_ops; scalar_t__* supported; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {int /*<<< orphan*/  win_handle; struct wined3d_gl_info* gl_info; } ;
struct wined3d_box {int dummy; } ;
struct wined3d_blitter {TYPE_2__* ops; struct wined3d_blitter* next; } ;
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
typedef  enum wined3d_blit_op { ____Placeholder_wined3d_blit_op } wined3d_blit_op ;
struct TYPE_14__ {scalar_t__ offscreen_rendering_mode; } ;
struct TYPE_10__ {scalar_t__ id; } ;
struct TYPE_9__ {int (* blitter_blit ) (struct wined3d_blitter*,int,struct wined3d_context*,struct wined3d_texture*,unsigned int,int,int /*<<< orphan*/  const*,struct wined3d_texture*,unsigned int,int,int /*<<< orphan*/  const*,struct wined3d_color_key const*,int) ;} ;
struct TYPE_8__ {struct wined3d_texture* front_buffer; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int DWORD ;

/* Variables and functions */
 size_t ARB_TEXTURE_CUBE_MAP ; 
 size_t ARB_TEXTURE_RECTANGLE ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_ALPHA_TEST ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_NOTEQUAL ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_RECTANGLE_ARB ; 
 scalar_t__ ORM_FBO ; 
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ WINED3DFMT_P8_UINT ; 
 int /*<<< orphan*/  WINED3DUSAGE_PRIVATE ; 
 int WINED3D_BLIT_OP_COLOR_BLIT_ALPHATEST ; 
 int WINED3D_CKEY_SRC_BLT ; 
 int WINED3D_LOCATION_DRAWABLE ; 
 int WINED3D_RESOURCE_ACCESS_GPU ; 
 int /*<<< orphan*/  WINED3D_RTYPE_TEXTURE_2D ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_apply_fbo_state_blit (struct wined3d_context*,int /*<<< orphan*/ ,struct wined3d_resource*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  context_apply_ffp_blit_state (struct wined3d_context*,struct wined3d_device*) ; 
 int /*<<< orphan*/  context_check_fbo_status (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_draw_textured_quad (struct wined3d_context*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_set_draw_buffer (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffp_blit_supported (int,struct wined3d_context*,struct wined3d_resource*,int,struct wined3d_resource*,int) ; 
 int stub1 (struct wined3d_blitter*,int,struct wined3d_context*,struct wined3d_texture*,unsigned int,int,int /*<<< orphan*/  const*,struct wined3d_texture*,unsigned int,int,int /*<<< orphan*/  const*,struct wined3d_color_key const*,int) ; 
 int /*<<< orphan*/  stub10 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_box_set (struct wined3d_box*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wined3d_null_parent_ops ; 
 TYPE_7__ wined3d_settings ; 
 int /*<<< orphan*/  wined3d_texture_create (struct wined3d_device*,struct wined3d_resource_desc*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wined3d_texture**) ; 
 int /*<<< orphan*/  wined3d_texture_decref (struct wined3d_texture*) ; 
 int /*<<< orphan*/  wined3d_texture_get_gl_buffer (struct wined3d_texture*) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_load (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_set_color_key (struct wined3d_texture*,int,struct wined3d_color_key const*) ; 
 int /*<<< orphan*/  wined3d_texture_translate_drawable_coords (struct wined3d_texture*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_texture_upload_from_texture (struct wined3d_texture*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wined3d_texture*,unsigned int,struct wined3d_box*) ; 

__attribute__((used)) static DWORD ffp_blitter_blit(struct wined3d_blitter *blitter, enum wined3d_blit_op op,
        struct wined3d_context *context, struct wined3d_texture *src_texture, unsigned int src_sub_resource_idx,
        DWORD src_location, const RECT *src_rect, struct wined3d_texture *dst_texture,
        unsigned int dst_sub_resource_idx, DWORD dst_location, const RECT *dst_rect,
        const struct wined3d_color_key *color_key, enum wined3d_texture_filter_type filter)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct wined3d_resource *src_resource, *dst_resource;
    struct wined3d_texture *staging_texture = NULL;
    struct wined3d_color_key old_blt_key;
    struct wined3d_device *device;
    struct wined3d_blitter *next;
    DWORD old_color_key_flags;
    RECT r;

    src_resource = &src_texture->resource;
    dst_resource = &dst_texture->resource;
    device = dst_resource->device;

    if (!ffp_blit_supported(op, context, src_resource, src_location, dst_resource, dst_location))
    {
        if ((next = blitter->next))
            return next->ops->blitter_blit(next, op, context, src_texture, src_sub_resource_idx, src_location,
                    src_rect, dst_texture, dst_sub_resource_idx, dst_location, dst_rect, color_key, filter);
    }

    TRACE("Blt from texture %p, %u to rendertarget %p, %u.\n",
            src_texture, src_sub_resource_idx, dst_texture, dst_sub_resource_idx);

    old_blt_key = src_texture->async.src_blt_color_key;
    old_color_key_flags = src_texture->async.color_key_flags;
    wined3d_texture_set_color_key(src_texture, WINED3D_CKEY_SRC_BLT, color_key);

    if (!(src_texture->resource.access & WINED3D_RESOURCE_ACCESS_GPU))
    {
        struct wined3d_resource_desc desc;
        struct wined3d_box upload_box;
        unsigned int src_level;
        HRESULT hr;

        TRACE("Source texture is not GPU accessible, creating a staging texture.\n");

        src_level = src_sub_resource_idx % src_texture->level_count;
        desc.resource_type = WINED3D_RTYPE_TEXTURE_2D;
        desc.format = src_texture->resource.format->id;
        desc.multisample_type = src_texture->resource.multisample_type;
        desc.multisample_quality = src_texture->resource.multisample_quality;
        desc.usage = WINED3DUSAGE_PRIVATE;
        desc.access = WINED3D_RESOURCE_ACCESS_GPU;
        desc.width = wined3d_texture_get_level_width(src_texture, src_level);
        desc.height = wined3d_texture_get_level_height(src_texture, src_level);
        desc.depth = 1;
        desc.size = 0;

        if (FAILED(hr = wined3d_texture_create(device, &desc, 1, 1, 0,
                NULL, NULL, &wined3d_null_parent_ops, &staging_texture)))
        {
            ERR("Failed to create staging texture, hr %#x.\n", hr);
            return dst_location;
        }

        wined3d_box_set(&upload_box, 0, 0, desc.width, desc.height, 0, desc.depth);
        wined3d_texture_upload_from_texture(staging_texture, 0, 0, 0, 0,
                src_texture, src_sub_resource_idx, &upload_box);

        src_texture = staging_texture;
        src_sub_resource_idx = 0;
    }
    else
    {
        /* Make sure the surface is up-to-date. This should probably use
         * surface_load_location() and worry about the destination surface
         * too, unless we're overwriting it completely. */
        wined3d_texture_load(src_texture, context, FALSE);
    }

    context_apply_ffp_blit_state(context, device);

    if (dst_location == WINED3D_LOCATION_DRAWABLE)
    {
        r = *dst_rect;
        wined3d_texture_translate_drawable_coords(dst_texture, context->win_handle, &r);
        dst_rect = &r;
    }

    if (wined3d_settings.offscreen_rendering_mode == ORM_FBO)
    {
        GLenum buffer;

        if (dst_location == WINED3D_LOCATION_DRAWABLE)
        {
            TRACE("Destination texture %p is onscreen.\n", dst_texture);
            buffer = wined3d_texture_get_gl_buffer(dst_texture);
        }
        else
        {
            TRACE("Destination texture %p is offscreen.\n", dst_texture);
            buffer = GL_COLOR_ATTACHMENT0;
        }
        context_apply_fbo_state_blit(context, GL_DRAW_FRAMEBUFFER,
                dst_resource, dst_sub_resource_idx, NULL, 0, dst_location);
        context_set_draw_buffer(context, buffer);
        context_check_fbo_status(context, GL_DRAW_FRAMEBUFFER);
        context_invalidate_state(context, STATE_FRAMEBUFFER);
    }

    gl_info->gl_ops.gl.p_glEnable(src_texture->target);
    checkGLcall("glEnable(target)");

    if (op == WINED3D_BLIT_OP_COLOR_BLIT_ALPHATEST || color_key)
    {
        gl_info->gl_ops.gl.p_glEnable(GL_ALPHA_TEST);
        checkGLcall("glEnable(GL_ALPHA_TEST)");
    }

    if (color_key)
    {
        /* For P8 surfaces, the alpha component contains the palette index.
         * Which means that the colorkey is one of the palette entries. In
         * other cases pixels that should be masked away have alpha set to 0. */
        if (src_texture->resource.format->id == WINED3DFMT_P8_UINT)
            gl_info->gl_ops.gl.p_glAlphaFunc(GL_NOTEQUAL,
                    (float)src_texture->async.src_blt_color_key.color_space_low_value / 255.0f);
        else
            gl_info->gl_ops.gl.p_glAlphaFunc(GL_NOTEQUAL, 0.0f);
        checkGLcall("glAlphaFunc");
    }

    context_draw_textured_quad(context, src_texture, src_sub_resource_idx, src_rect, dst_rect, filter);

    if (op == WINED3D_BLIT_OP_COLOR_BLIT_ALPHATEST || color_key)
    {
        gl_info->gl_ops.gl.p_glDisable(GL_ALPHA_TEST);
        checkGLcall("glDisable(GL_ALPHA_TEST)");
    }

    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_2D);
    checkGLcall("glDisable(GL_TEXTURE_2D)");
    if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
    {
        gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_CUBE_MAP_ARB);
        checkGLcall("glDisable(GL_TEXTURE_CUBE_MAP_ARB)");
    }
    if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
    {
        gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_RECTANGLE_ARB);
        checkGLcall("glDisable(GL_TEXTURE_RECTANGLE_ARB)");
    }

    if (dst_texture->swapchain && dst_texture->swapchain->front_buffer == dst_texture)
        gl_info->gl_ops.gl.p_glFlush();

    /* Restore the color key parameters */
    wined3d_texture_set_color_key(src_texture, WINED3D_CKEY_SRC_BLT,
            (old_color_key_flags & WINED3D_CKEY_SRC_BLT) ? &old_blt_key : NULL);

    if (staging_texture)
        wined3d_texture_decref(staging_texture);

    return dst_location;
}