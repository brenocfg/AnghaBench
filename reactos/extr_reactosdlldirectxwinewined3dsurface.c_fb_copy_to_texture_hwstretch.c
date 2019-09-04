#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ name; } ;
struct TYPE_18__ {struct wined3d_device* device; } ;
struct wined3d_texture {unsigned int level_count; int flags; TYPE_3__ texture_rgb; TYPE_2__* swapchain; TYPE_1__* sub_resources; TYPE_8__ resource; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* p_glDeleteTextures ) (int,scalar_t__*) ;int /*<<< orphan*/  (* p_glDisable ) (scalar_t__) ;int /*<<< orphan*/  (* p_glEnd ) () ;int /*<<< orphan*/  (* p_glVertex2i ) (unsigned int,unsigned int) ;int /*<<< orphan*/  (* p_glTexCoord2f ) (float,float) ;int /*<<< orphan*/  (* p_glBegin ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glEnable ) (scalar_t__) ;int /*<<< orphan*/  (* p_glCopyTexSubImage2D ) (scalar_t__,int /*<<< orphan*/ ,float,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,unsigned int) ;int /*<<< orphan*/  (* p_glReadBuffer ) (scalar_t__) ;int /*<<< orphan*/  (* p_glTexParameteri ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexImage2D ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glGenTextures ) (int,scalar_t__*) ;} ;
struct TYPE_15__ {TYPE_4__ gl; } ;
struct wined3d_gl_info {TYPE_5__ gl_ops; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {int aux_buffers; struct wined3d_gl_info* gl_info; } ;
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
typedef  unsigned int UINT ;
struct TYPE_17__ {scalar_t__ offscreen_rendering_mode; } ;
struct TYPE_16__ {unsigned int top; unsigned int bottom; float left; float right; } ;
struct TYPE_12__ {struct wined3d_texture** back_buffers; } ;
struct TYPE_11__ {int /*<<< orphan*/  locations; } ;
typedef  TYPE_6__ RECT ;
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLenum ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ GL_AUX0 ; 
 scalar_t__ GL_AUX1 ; 
 scalar_t__ GL_BACK ; 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 scalar_t__ GL_FRONT ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_QUADS ; 
 int /*<<< orphan*/  GL_RGBA ; 
 scalar_t__ GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 scalar_t__ ORM_FBO ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  WINED3D_LOCATION_TEXTURE_RGB ; 
 int /*<<< orphan*/  WINED3D_TEXF_NONE ; 
 int WINED3D_TEXTURE_NORMALIZED_COORDS ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  context_apply_ffp_blit_state (struct wined3d_context*,struct wined3d_device*) ; 
 int /*<<< orphan*/  context_bind_texture (struct wined3d_context*,scalar_t__,scalar_t__) ; 
 scalar_t__ context_get_offscreen_gl_buffer (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_set_draw_buffer (struct wined3d_context*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int,scalar_t__*) ; 
 int /*<<< orphan*/  stub10 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (scalar_t__,int /*<<< orphan*/ ,float,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub12 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (scalar_t__) ; 
 int /*<<< orphan*/  stub15 (scalar_t__) ; 
 int /*<<< orphan*/  stub16 (scalar_t__) ; 
 int /*<<< orphan*/  stub17 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub19 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub20 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub21 (float,float) ; 
 int /*<<< orphan*/  stub22 (float,unsigned int) ; 
 int /*<<< orphan*/  stub23 (float,float) ; 
 int /*<<< orphan*/  stub24 (float,unsigned int) ; 
 int /*<<< orphan*/  stub25 (float,float) ; 
 int /*<<< orphan*/  stub26 (float,unsigned int) ; 
 int /*<<< orphan*/  stub27 (float,float) ; 
 int /*<<< orphan*/  stub28 (float,unsigned int) ; 
 int /*<<< orphan*/  stub29 () ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 
 int /*<<< orphan*/  stub30 (scalar_t__) ; 
 int /*<<< orphan*/  stub31 (scalar_t__) ; 
 int /*<<< orphan*/  stub32 (scalar_t__,int /*<<< orphan*/ ,float,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,unsigned int) ; 
 int /*<<< orphan*/  stub33 (scalar_t__) ; 
 int /*<<< orphan*/  stub34 (scalar_t__) ; 
 int /*<<< orphan*/  stub35 (scalar_t__) ; 
 int /*<<< orphan*/  stub36 (scalar_t__) ; 
 int /*<<< orphan*/  stub37 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub38 (float,float) ; 
 int /*<<< orphan*/  stub39 (float,unsigned int) ; 
 int /*<<< orphan*/  stub4 (scalar_t__) ; 
 int /*<<< orphan*/  stub40 (float,float) ; 
 int /*<<< orphan*/  stub41 (float,unsigned int) ; 
 int /*<<< orphan*/  stub42 (float,float) ; 
 int /*<<< orphan*/  stub43 (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub44 (float,float) ; 
 int /*<<< orphan*/  stub45 (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub46 () ; 
 int /*<<< orphan*/  stub47 (scalar_t__) ; 
 int /*<<< orphan*/  stub48 (int,scalar_t__*) ; 
 int /*<<< orphan*/  stub49 (int,scalar_t__*) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,int /*<<< orphan*/ ,float,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub6 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (scalar_t__) ; 
 int /*<<< orphan*/  stub9 (int,scalar_t__*) ; 
 int /*<<< orphan*/  wined3d_gl_mag_filter (int) ; 
 int /*<<< orphan*/  wined3d_gl_min_mip_filter (int,int /*<<< orphan*/ ) ; 
 int wined3d_resource_is_offscreen (TYPE_8__*) ; 
 TYPE_7__ wined3d_settings ; 
 scalar_t__ wined3d_texture_get_gl_buffer (struct wined3d_texture*) ; 
 unsigned int wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_pow2_height (struct wined3d_texture*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_pow2_width (struct wined3d_texture*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 
 scalar_t__ wined3d_texture_get_sub_resource_target (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_invalidate_location (struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_load (struct wined3d_texture*,struct wined3d_context*,int) ; 
 int /*<<< orphan*/  wined3d_texture_validate_location (struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fb_copy_to_texture_hwstretch(struct wined3d_texture *dst_texture, unsigned int dst_sub_resource_idx,
        const RECT *dst_rect_in, struct wined3d_texture *src_texture, unsigned int src_sub_resource_idx,
        const RECT *src_rect, enum wined3d_texture_filter_type filter)
{
    unsigned int src_width, src_height, src_pow2_width, src_pow2_height, src_level;
    struct wined3d_device *device = dst_texture->resource.device;
    GLenum src_target, dst_target, texture_target;
    GLuint src, backup = 0;
    float left, right, top, bottom; /* Texture coordinates */
    const struct wined3d_gl_info *gl_info;
    struct wined3d_context *context;
    GLenum drawBuffer = GL_BACK;
    GLenum offscreen_buffer;
    BOOL noBackBufferBackup;
    BOOL src_offscreen;
    BOOL upsidedown = FALSE;
    RECT dst_rect = *dst_rect_in;

    TRACE("Using hwstretch blit\n");

    src_target = wined3d_texture_get_sub_resource_target(src_texture, src_sub_resource_idx);
    dst_target = wined3d_texture_get_sub_resource_target(dst_texture, dst_sub_resource_idx);

    /* Activate the Proper context for reading from the source surface, set it up for blitting */
    context = context_acquire(device, src_texture, src_sub_resource_idx);
    gl_info = context->gl_info;
    context_apply_ffp_blit_state(context, device);
    wined3d_texture_load(dst_texture, context, FALSE);

    offscreen_buffer = context_get_offscreen_gl_buffer(context);
    src_level = src_sub_resource_idx % src_texture->level_count;
    src_width = wined3d_texture_get_level_width(src_texture, src_level);
    src_height = wined3d_texture_get_level_height(src_texture, src_level);
    src_pow2_width = wined3d_texture_get_level_pow2_width(src_texture, src_level);
    src_pow2_height = wined3d_texture_get_level_pow2_height(src_texture, src_level);

    src_offscreen = wined3d_resource_is_offscreen(&src_texture->resource);
    noBackBufferBackup = src_offscreen && wined3d_settings.offscreen_rendering_mode == ORM_FBO;
    if (!noBackBufferBackup && !src_texture->texture_rgb.name)
    {
        /* Get it a description */
        wined3d_texture_load(src_texture, context, FALSE);
    }

    /* Try to use an aux buffer for drawing the rectangle. This way it doesn't need restoring.
     * This way we don't have to wait for the 2nd readback to finish to leave this function.
     */
    if (context->aux_buffers >= 2)
    {
        /* Got more than one aux buffer? Use the 2nd aux buffer */
        drawBuffer = GL_AUX1;
    }
    else if ((!src_offscreen || offscreen_buffer == GL_BACK) && context->aux_buffers >= 1)
    {
        /* Only one aux buffer, but it isn't used (Onscreen rendering, or non-aux orm)? Use it! */
        drawBuffer = GL_AUX0;
    }

    if (noBackBufferBackup)
    {
        gl_info->gl_ops.gl.p_glGenTextures(1, &backup);
        checkGLcall("glGenTextures");
        context_bind_texture(context, GL_TEXTURE_2D, backup);
        texture_target = GL_TEXTURE_2D;
    }
    else
    {
        /* Backup the back buffer and copy the source buffer into a texture to draw an upside down stretched quad. If
         * we are reading from the back buffer, the backup can be used as source texture
         */
        texture_target = src_target;
        context_bind_texture(context, texture_target, src_texture->texture_rgb.name);
        gl_info->gl_ops.gl.p_glEnable(texture_target);
        checkGLcall("glEnable(texture_target)");

        /* For now invalidate the texture copy of the back buffer. Drawable and sysmem copy are untouched */
        src_texture->sub_resources[src_sub_resource_idx].locations &= ~WINED3D_LOCATION_TEXTURE_RGB;
    }

    /* Make sure that the top pixel is always above the bottom pixel, and keep a separate upside down flag
     * glCopyTexSubImage is a bit picky about the parameters we pass to it
     */
    if(dst_rect.top > dst_rect.bottom) {
        UINT tmp = dst_rect.bottom;
        dst_rect.bottom = dst_rect.top;
        dst_rect.top = tmp;
        upsidedown = TRUE;
    }

    if (src_offscreen)
    {
        TRACE("Reading from an offscreen target\n");
        upsidedown = !upsidedown;
        gl_info->gl_ops.gl.p_glReadBuffer(offscreen_buffer);
    }
    else
    {
        gl_info->gl_ops.gl.p_glReadBuffer(wined3d_texture_get_gl_buffer(src_texture));
    }

    /* TODO: Only back up the part that will be overwritten */
    gl_info->gl_ops.gl.p_glCopyTexSubImage2D(texture_target, 0, 0, 0, 0, 0, src_width, src_height);

    checkGLcall("glCopyTexSubImage2D");

    /* No issue with overriding these - the sampler is dirty due to blit usage */
    gl_info->gl_ops.gl.p_glTexParameteri(texture_target, GL_TEXTURE_MAG_FILTER, wined3d_gl_mag_filter(filter));
    checkGLcall("glTexParameteri");
    gl_info->gl_ops.gl.p_glTexParameteri(texture_target, GL_TEXTURE_MIN_FILTER,
            wined3d_gl_min_mip_filter(filter, WINED3D_TEXF_NONE));
    checkGLcall("glTexParameteri");

    if (!src_texture->swapchain || src_texture == src_texture->swapchain->back_buffers[0])
    {
        src = backup ? backup : src_texture->texture_rgb.name;
    }
    else
    {
        gl_info->gl_ops.gl.p_glReadBuffer(GL_FRONT);
        checkGLcall("glReadBuffer(GL_FRONT)");

        gl_info->gl_ops.gl.p_glGenTextures(1, &src);
        checkGLcall("glGenTextures(1, &src)");
        context_bind_texture(context, GL_TEXTURE_2D, src);

        /* TODO: Only copy the part that will be read. Use src_rect->left,
         * src_rect->bottom as origin, but with the width watch out for power
         * of 2 sizes. */
        gl_info->gl_ops.gl.p_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, src_pow2_width,
                src_pow2_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        checkGLcall("glTexImage2D");
        gl_info->gl_ops.gl.p_glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, src_width, src_height);

        gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        checkGLcall("glTexParameteri");
        gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        checkGLcall("glTexParameteri");

        gl_info->gl_ops.gl.p_glReadBuffer(GL_BACK);
        checkGLcall("glReadBuffer(GL_BACK)");

        if (texture_target != GL_TEXTURE_2D)
        {
            gl_info->gl_ops.gl.p_glDisable(texture_target);
            gl_info->gl_ops.gl.p_glEnable(GL_TEXTURE_2D);
            texture_target = GL_TEXTURE_2D;
        }
    }
    checkGLcall("glEnd and previous");

    left = src_rect->left;
    right = src_rect->right;

    if (!upsidedown)
    {
        top = src_height - src_rect->top;
        bottom = src_height - src_rect->bottom;
    }
    else
    {
        top = src_height - src_rect->bottom;
        bottom = src_height - src_rect->top;
    }

    if (src_texture->flags & WINED3D_TEXTURE_NORMALIZED_COORDS)
    {
        left /= src_pow2_width;
        right /= src_pow2_width;
        top /= src_pow2_height;
        bottom /= src_pow2_height;
    }

    /* draw the source texture stretched and upside down. The correct surface is bound already */
    gl_info->gl_ops.gl.p_glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl_info->gl_ops.gl.p_glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    context_set_draw_buffer(context, drawBuffer);
    gl_info->gl_ops.gl.p_glReadBuffer(drawBuffer);

    gl_info->gl_ops.gl.p_glBegin(GL_QUADS);
        /* bottom left */
        gl_info->gl_ops.gl.p_glTexCoord2f(left, bottom);
        gl_info->gl_ops.gl.p_glVertex2i(0, 0);

        /* top left */
        gl_info->gl_ops.gl.p_glTexCoord2f(left, top);
        gl_info->gl_ops.gl.p_glVertex2i(0, dst_rect.bottom - dst_rect.top);

        /* top right */
        gl_info->gl_ops.gl.p_glTexCoord2f(right, top);
        gl_info->gl_ops.gl.p_glVertex2i(dst_rect.right - dst_rect.left, dst_rect.bottom - dst_rect.top);

        /* bottom right */
        gl_info->gl_ops.gl.p_glTexCoord2f(right, bottom);
        gl_info->gl_ops.gl.p_glVertex2i(dst_rect.right - dst_rect.left, 0);
    gl_info->gl_ops.gl.p_glEnd();
    checkGLcall("glEnd and previous");

    if (texture_target != dst_target)
    {
        gl_info->gl_ops.gl.p_glDisable(texture_target);
        gl_info->gl_ops.gl.p_glEnable(dst_target);
        texture_target = dst_target;
    }

    /* Now read the stretched and upside down image into the destination texture */
    context_bind_texture(context, texture_target, dst_texture->texture_rgb.name);
    gl_info->gl_ops.gl.p_glCopyTexSubImage2D(texture_target,
                        0,
                        dst_rect.left, dst_rect.top, /* xoffset, yoffset */
                        0, 0, /* We blitted the image to the origin */
                        dst_rect.right - dst_rect.left, dst_rect.bottom - dst_rect.top);
    checkGLcall("glCopyTexSubImage2D");

    if (drawBuffer == GL_BACK)
    {
        /* Write the back buffer backup back. */
        if (backup)
        {
            if (texture_target != GL_TEXTURE_2D)
            {
                gl_info->gl_ops.gl.p_glDisable(texture_target);
                gl_info->gl_ops.gl.p_glEnable(GL_TEXTURE_2D);
                texture_target = GL_TEXTURE_2D;
            }
            context_bind_texture(context, GL_TEXTURE_2D, backup);
        }
        else
        {
            if (texture_target != src_target)
            {
                gl_info->gl_ops.gl.p_glDisable(texture_target);
                gl_info->gl_ops.gl.p_glEnable(src_target);
                texture_target = src_target;
            }
            context_bind_texture(context, src_target, src_texture->texture_rgb.name);
        }

        gl_info->gl_ops.gl.p_glBegin(GL_QUADS);
            /* top left */
            gl_info->gl_ops.gl.p_glTexCoord2f(0.0f, 0.0f);
            gl_info->gl_ops.gl.p_glVertex2i(0, src_height);

            /* bottom left */
            gl_info->gl_ops.gl.p_glTexCoord2f(0.0f, (float)src_height / (float)src_pow2_height);
            gl_info->gl_ops.gl.p_glVertex2i(0, 0);

            /* bottom right */
            gl_info->gl_ops.gl.p_glTexCoord2f((float)src_width / (float)src_pow2_width,
                    (float)src_height / (float)src_pow2_height);
            gl_info->gl_ops.gl.p_glVertex2i(src_width, 0);

            /* top right */
            gl_info->gl_ops.gl.p_glTexCoord2f((float)src_width / (float)src_pow2_width, 0.0f);
            gl_info->gl_ops.gl.p_glVertex2i(src_width, src_height);
        gl_info->gl_ops.gl.p_glEnd();
    }
    gl_info->gl_ops.gl.p_glDisable(texture_target);
    checkGLcall("glDisable(texture_target)");

    /* Cleanup */
    if (src != src_texture->texture_rgb.name && src != backup)
    {
        gl_info->gl_ops.gl.p_glDeleteTextures(1, &src);
        checkGLcall("glDeleteTextures(1, &src)");
    }
    if (backup)
    {
        gl_info->gl_ops.gl.p_glDeleteTextures(1, &backup);
        checkGLcall("glDeleteTextures(1, &backup)");
    }

    context_release(context);

    /* The texture is now most up to date - If the surface is a render target
     * and has a drawable, this path is never entered. */
    wined3d_texture_validate_location(dst_texture, dst_sub_resource_idx, WINED3D_LOCATION_TEXTURE_RGB);
    wined3d_texture_invalidate_location(dst_texture, dst_sub_resource_idx, ~WINED3D_LOCATION_TEXTURE_RGB);
}