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
struct TYPE_6__ {scalar_t__ (* glCheckFramebufferStatus ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glDeleteRenderbuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* glFramebufferRenderbuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glRenderbufferStorage ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* glBindRenderbuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glGenRenderbuffers ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {scalar_t__ (* p_glGetError ) () ;int /*<<< orphan*/  (* p_glReadPixels ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* p_glGetTexImage ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* p_glBindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glEnable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glBlendFunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glViewport ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* p_glClear ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glClearColor ) (float,float,float,float) ;} ;
struct TYPE_5__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {int quirks; TYPE_3__ fbo_ops; scalar_t__* supported; TYPE_2__ gl_ops; } ;
struct wined3d_format {scalar_t__ rtInternal; int* flags; scalar_t__ glInternal; scalar_t__ id; int red_size; int alpha_size; scalar_t__ glGammaInternal; int /*<<< orphan*/  glType; int /*<<< orphan*/  glFormat; } ;
struct wined3d_color {float member_0; float member_1; float member_2; float member_3; } ;
struct wined3d_caps_gl_ctx {struct wined3d_gl_info* gl_info; } ;
typedef  enum wined3d_gl_resource_type { ____Placeholder_wined3d_gl_resource_type } wined3d_gl_resource_type ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ GLenum ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARB_FRAMEBUFFER_OBJECT ; 
 int ARRAY_SIZE (int*) ; 
 size_t EXT_PACKED_DEPTH_STENCIL ; 
 size_t EXT_TEXTURE_SRGB_DECODE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_BGRA ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DEPTH24_STENCIL8 ; 
 int /*<<< orphan*/  GL_DEPTH_ATTACHMENT ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 scalar_t__ GL_FRAMEBUFFER_COMPLETE ; 
 scalar_t__ GL_INVALID_FRAMEBUFFER_OPERATION ; 
 int /*<<< orphan*/  GL_LUMINANCE ; 
 int /*<<< orphan*/  GL_LUMINANCE_ALPHA ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_RENDERBUFFER ; 
 int /*<<< orphan*/  GL_RGBA8 ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_STENCIL_ATTACHMENT ; 
 int /*<<< orphan*/  GL_TEXTURE_1D ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT_8_8_8_8_REV ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,...) ; 
 int WINED3DFMT_FLAG_DEPTH ; 
 int WINED3DFMT_FLAG_FBO_ATTACHABLE ; 
 int WINED3DFMT_FLAG_FBO_ATTACHABLE_SRGB ; 
 int WINED3DFMT_FLAG_INTEGER ; 
 int WINED3DFMT_FLAG_POSTPIXELSHADER_BLENDING ; 
 int WINED3DFMT_FLAG_RENDERTARGET ; 
 int WINED3DFMT_FLAG_SRGB_WRITE ; 
 int WINED3DFMT_FLAG_STENCIL ; 
 scalar_t__ WINED3DFMT_NULL ; 
 scalar_t__ WINED3DFMT_P8_UINT ; 
#define  WINED3D_GL_RES_TYPE_BUFFER 135 
#define  WINED3D_GL_RES_TYPE_COUNT 134 
#define  WINED3D_GL_RES_TYPE_RB 133 
#define  WINED3D_GL_RES_TYPE_TEX_1D 132 
#define  WINED3D_GL_RES_TYPE_TEX_2D 131 
#define  WINED3D_GL_RES_TYPE_TEX_3D 130 
#define  WINED3D_GL_RES_TYPE_TEX_CUBE 129 
#define  WINED3D_GL_RES_TYPE_TEX_RECT 128 
 int WINED3D_QUIRK_LIMITED_TEX_FILTERING ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  create_and_bind_fbo_attachment (struct wined3d_gl_info const*,int,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_d3dformat (scalar_t__) ; 
 int /*<<< orphan*/  delete_fbo_attachment (struct wined3d_gl_info const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_test_quad (struct wined3d_caps_gl_ctx*,int /*<<< orphan*/ *,struct wined3d_color const*) ; 
 int /*<<< orphan*/  format_clear_flag (struct wined3d_format*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (float,float,float,float) ; 
 int /*<<< orphan*/  stub18 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub19 () ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub20 () ; 
 int /*<<< orphan*/  stub21 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub22 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub23 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub25 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub26 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub27 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub28 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub29 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub30 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub31 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub33 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub34 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub35 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub36 (int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub37 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub38 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub39 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub7 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub8 () ; 
 scalar_t__ stub9 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_gl_type_to_enum (int) ; 

__attribute__((used)) static void check_fbo_compat(struct wined3d_caps_gl_ctx *ctx, struct wined3d_format *format)
{
    /* Check if the default internal format is supported as a frame buffer
     * target, otherwise fall back to the render target internal.
     *
     * Try to stick to the standard format if possible, this limits precision differences. */
    static const struct wined3d_color black = {0.0f, 0.0f, 0.0f, 1.0f};
    static const struct wined3d_color half_transparent_red = {1.0f, 0.0f, 0.0f, 0.5f};
    const struct wined3d_gl_info *gl_info = ctx->gl_info;
    GLenum status, rt_internal = format->rtInternal;
    GLuint object, color_rb;
    enum wined3d_gl_resource_type type;
    BOOL fallback_fmt_used = FALSE, regular_fmt_used = FALSE;

    gl_info->gl_ops.gl.p_glDisable(GL_BLEND);

    for (type = 0; type < ARRAY_SIZE(format->flags); ++type)
    {
        const char *type_string = "color";

        if (type == WINED3D_GL_RES_TYPE_BUFFER)
            continue;

        create_and_bind_fbo_attachment(gl_info, format->flags[type], type, &object, format->glInternal,
                format->glFormat, format->glType);

        if (format->flags[type] & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL))
        {
            gl_info->fbo_ops.glGenRenderbuffers(1, &color_rb);
            gl_info->fbo_ops.glBindRenderbuffer(GL_RENDERBUFFER, color_rb);
            if (type == WINED3D_GL_RES_TYPE_TEX_1D)
                gl_info->fbo_ops.glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, 16, 1);
            else
                gl_info->fbo_ops.glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, 16, 16);

            gl_info->fbo_ops.glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                    GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, color_rb);
            checkGLcall("Create and attach color rb attachment");
            type_string = "depth / stencil";
        }

        status = gl_info->fbo_ops.glCheckFramebufferStatus(GL_FRAMEBUFFER);
        checkGLcall("Framebuffer format check");

        if (status == GL_FRAMEBUFFER_COMPLETE)
        {
            TRACE("Format %s is supported as FBO %s attachment, type %u.\n",
                    debug_d3dformat(format->id), type_string, type);
            format->flags[type] |= WINED3DFMT_FLAG_FBO_ATTACHABLE;
            format->rtInternal = format->glInternal;
            regular_fmt_used = TRUE;
        }
        else
        {
            if (!rt_internal)
            {
                if (format->flags[type] & WINED3DFMT_FLAG_RENDERTARGET)
                {
                    WARN("Format %s with rendertarget flag is not supported as FBO color attachment (type %u),"
                            " and no fallback specified.\n", debug_d3dformat(format->id), type);
                    format->flags[type] &= ~WINED3DFMT_FLAG_RENDERTARGET;
                }
                else
                {
                    TRACE("Format %s is not supported as FBO %s attachment, type %u.\n",
                            debug_d3dformat(format->id), type_string, type);
                }
                format->rtInternal = format->glInternal;
            }
            else
            {
                TRACE("Format %s is not supported as FBO %s attachment (type %u),"
                        " trying rtInternal format as fallback.\n",
                        debug_d3dformat(format->id), type_string, type);

                while (gl_info->gl_ops.gl.p_glGetError());

                delete_fbo_attachment(gl_info, type, object);
                create_and_bind_fbo_attachment(gl_info, format->flags[type], type, &object, format->rtInternal,
                        format->glFormat, format->glType);

                status = gl_info->fbo_ops.glCheckFramebufferStatus(GL_FRAMEBUFFER);
                checkGLcall("Framebuffer format check");

                if (status == GL_FRAMEBUFFER_COMPLETE)
                {
                    TRACE("Format %s rtInternal format is supported as FBO %s attachment, type %u.\n",
                            debug_d3dformat(format->id), type_string, type);
                    fallback_fmt_used = TRUE;
                }
                else
                {
                    WARN("Format %s rtInternal format is not supported as FBO %s attachment, type %u.\n",
                            debug_d3dformat(format->id), type_string, type);
                    format->flags[type] &= ~WINED3DFMT_FLAG_RENDERTARGET;
                }
            }
        }

        if (status == GL_FRAMEBUFFER_COMPLETE
                && ((format->flags[type] & WINED3DFMT_FLAG_POSTPIXELSHADER_BLENDING)
                || !(gl_info->quirks & WINED3D_QUIRK_LIMITED_TEX_FILTERING))
                && !(format->flags[type] & WINED3DFMT_FLAG_INTEGER)
                && format->id != WINED3DFMT_NULL && format->id != WINED3DFMT_P8_UINT
                && format->glFormat != GL_LUMINANCE && format->glFormat != GL_LUMINANCE_ALPHA
                && (format->red_size || format->alpha_size))
        {
            DWORD readback[16 * 16 * 16], color, r_range, a_range;
            BYTE r, a;
            BOOL match = TRUE;
            GLuint rb;

            if (gl_info->supported[ARB_FRAMEBUFFER_OBJECT]
                    || gl_info->supported[EXT_PACKED_DEPTH_STENCIL])
            {
                gl_info->fbo_ops.glGenRenderbuffers(1, &rb);
                gl_info->fbo_ops.glBindRenderbuffer(GL_RENDERBUFFER, rb);
                if (type == WINED3D_GL_RES_TYPE_TEX_1D)
                    gl_info->fbo_ops.glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 16, 1);
                else
                    gl_info->fbo_ops.glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 16, 16);
                gl_info->fbo_ops.glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb);
                gl_info->fbo_ops.glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rb);
                checkGLcall("RB attachment");
            }

            gl_info->gl_ops.gl.p_glEnable(GL_BLEND);
            gl_info->gl_ops.gl.p_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            gl_info->gl_ops.gl.p_glClear(GL_COLOR_BUFFER_BIT);
            if (gl_info->gl_ops.gl.p_glGetError() == GL_INVALID_FRAMEBUFFER_OPERATION)
            {
                while (gl_info->gl_ops.gl.p_glGetError());
                TRACE("Format %s doesn't support post-pixelshader blending, type %u.\n",
                        debug_d3dformat(format->id), type);
                format->flags[type] &= ~WINED3DFMT_FLAG_POSTPIXELSHADER_BLENDING;
            }
            else
            {
                gl_info->gl_ops.gl.p_glDisable(GL_BLEND);
                if (type == WINED3D_GL_RES_TYPE_TEX_1D)
                    gl_info->gl_ops.gl.p_glViewport(0, 0, 16, 1);
                else
                    gl_info->gl_ops.gl.p_glViewport(0, 0, 16, 16);
                gl_info->gl_ops.gl.p_glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                draw_test_quad(ctx, NULL, &black);

                gl_info->gl_ops.gl.p_glEnable(GL_BLEND);

                draw_test_quad(ctx, NULL, &half_transparent_red);

                gl_info->gl_ops.gl.p_glDisable(GL_BLEND);

                switch (type)
                {
                    case WINED3D_GL_RES_TYPE_TEX_1D:
                        /* Rebinding texture to workaround a fglrx bug. */
                        gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_1D, object);
                        gl_info->gl_ops.gl.p_glGetTexImage(GL_TEXTURE_1D, 0, GL_BGRA,
                                GL_UNSIGNED_INT_8_8_8_8_REV, readback);
                        color = readback[7];
                        break;

                    case WINED3D_GL_RES_TYPE_TEX_2D:
                    case WINED3D_GL_RES_TYPE_TEX_3D:
                    case WINED3D_GL_RES_TYPE_TEX_RECT:
                        /* Rebinding texture to workaround a fglrx bug. */
                        gl_info->gl_ops.gl.p_glBindTexture(wined3d_gl_type_to_enum(type), object);
                        gl_info->gl_ops.gl.p_glGetTexImage(wined3d_gl_type_to_enum(type), 0, GL_BGRA,
                                GL_UNSIGNED_INT_8_8_8_8_REV, readback);
                        color = readback[7 * 16 + 7];
                        break;

                    case WINED3D_GL_RES_TYPE_TEX_CUBE:
                        /* Rebinding texture to workaround a fglrx bug. */
                        gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, object);
                        gl_info->gl_ops.gl.p_glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, 0, GL_BGRA,
                                GL_UNSIGNED_INT_8_8_8_8_REV, readback);
                        color = readback[7 * 16 + 7];
                        break;

                    case WINED3D_GL_RES_TYPE_RB:
                        gl_info->gl_ops.gl.p_glReadPixels(0, 0, 16, 16,
                                GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, readback);
                        color = readback[7 * 16 + 7];
                        break;

                    case WINED3D_GL_RES_TYPE_BUFFER:
                    case WINED3D_GL_RES_TYPE_COUNT:
                        color = 0;
                        break;
                }
                checkGLcall("Post-pixelshader blending check");

                a = color >> 24;
                r = (color & 0x00ff0000u) >> 16;

                r_range = format->red_size < 8 ? 1u << (8 - format->red_size) : 1;
                a_range = format->alpha_size < 8 ? 1u << (8 - format->alpha_size) : 1;
                if (format->red_size && (r < 0x7f - r_range || r > 0x7f + r_range))
                    match = FALSE;
                else if (format->alpha_size > 1 && (a < 0xbf - a_range || a > 0xbf + a_range))
                    match = FALSE;
                if (!match)
                {
                    TRACE("Format %s doesn't support post-pixelshader blending, type %u.\n",
                            debug_d3dformat(format->id), type);
                    TRACE("Color output: %#x\n", color);
                    format->flags[type] &= ~WINED3DFMT_FLAG_POSTPIXELSHADER_BLENDING;
                }
                else
                {
                    TRACE("Format %s supports post-pixelshader blending, type %u.\n",
                            debug_d3dformat(format->id), type);
                    TRACE("Color output: %#x\n", color);
                    format->flags[type] |= WINED3DFMT_FLAG_POSTPIXELSHADER_BLENDING;
                }
            }

            if (gl_info->supported[ARB_FRAMEBUFFER_OBJECT]
                    || gl_info->supported[EXT_PACKED_DEPTH_STENCIL])
            {
                gl_info->fbo_ops.glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
                gl_info->fbo_ops.glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, 0);
                gl_info->fbo_ops.glDeleteRenderbuffers(1, &rb);
                checkGLcall("RB cleanup");
            }
        }

        if (format->glInternal != format->glGammaInternal)
        {
            delete_fbo_attachment(gl_info, type, object);
            create_and_bind_fbo_attachment(gl_info, format->flags[type], type, &object, format->glGammaInternal,
                    format->glFormat, format->glType);

            status = gl_info->fbo_ops.glCheckFramebufferStatus(GL_FRAMEBUFFER);
            checkGLcall("Framebuffer format check");

            if (status == GL_FRAMEBUFFER_COMPLETE)
            {
                TRACE("Format %s's sRGB format is FBO attachable, type %u.\n",
                        debug_d3dformat(format->id), type);
                format->flags[type] |= WINED3DFMT_FLAG_FBO_ATTACHABLE_SRGB;
                if (gl_info->supported[EXT_TEXTURE_SRGB_DECODE])
                    format->glInternal = format->glGammaInternal;
            }
            else
            {
                WARN("Format %s's sRGB format is not FBO attachable, type %u.\n",
                        debug_d3dformat(format->id), type);
                format_clear_flag(format, WINED3DFMT_FLAG_SRGB_WRITE);
            }
        }
        else if (status == GL_FRAMEBUFFER_COMPLETE)
            format->flags[type] |= WINED3DFMT_FLAG_FBO_ATTACHABLE_SRGB;

        if (format->flags[type] & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL))
        {
            gl_info->fbo_ops.glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, 0);
            gl_info->fbo_ops.glDeleteRenderbuffers(1, &color_rb);
        }

        delete_fbo_attachment(gl_info, type, object);
        checkGLcall("Framebuffer format check cleanup");
    }

    if (fallback_fmt_used && regular_fmt_used)
    {
        FIXME("Format %s needs different render target formats for different resource types.\n",
                debug_d3dformat(format->id));
        format_clear_flag(format, WINED3DFMT_FLAG_RENDERTARGET | WINED3DFMT_FLAG_FBO_ATTACHABLE
                | WINED3DFMT_FLAG_FBO_ATTACHABLE_SRGB | WINED3DFMT_FLAG_POSTPIXELSHADER_BLENDING);
    }
}