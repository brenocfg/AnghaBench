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
struct TYPE_5__ {struct wined3d_format* format; } ;
struct wined3d_texture {int flags; scalar_t__ target; int /*<<< orphan*/  level_count; TYPE_1__ resource; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_glTexParameteriv ) (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ;int /*<<< orphan*/  (* p_glTexParameteri ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glGenTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {TYPE_3__ gl; } ;
struct wined3d_gl_info {TYPE_4__ gl_ops; scalar_t__* supported; } ;
struct color_fixup_desc {size_t x_source; size_t y_source; size_t z_source; size_t w_source; } ;
struct wined3d_format {struct color_fixup_desc color_fixup; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct TYPE_6__ {float lod_bias; float min_lod; float max_lod; int max_anisotropy; void* mip_filter; void* min_filter; void* mag_filter; void* address_v; void* address_u; void* srgb_decode; int /*<<< orphan*/  comparison_func; void* compare; int /*<<< orphan*/  border_color; void* address_w; } ;
struct gl_texture {TYPE_2__ sampler_desc; int /*<<< orphan*/  name; scalar_t__ base_level; } ;
typedef  scalar_t__ GLint ;
typedef  scalar_t__ GLenum ;
typedef  void* BOOL ;

/* Variables and functions */
 size_t ARB_DEPTH_TEXTURE ; 
 int /*<<< orphan*/  ERR (char*) ; 
 size_t EXT_TEXTURE_SRGB_DECODE ; 
 void* FALSE ; 
#define  GL_ALPHA 133 
#define  GL_BLUE 132 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_DEPTH_TEXTURE_MODE_ARB ; 
#define  GL_GREEN 131 
 int /*<<< orphan*/  GL_INTENSITY ; 
 int /*<<< orphan*/  GL_NEAREST ; 
#define  GL_ONE 130 
#define  GL_RED 129 
 scalar_t__ GL_TEXTURE_CUBE_MAP_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MAX_LEVEL ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 scalar_t__ GL_TEXTURE_RECTANGLE_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_SWIZZLE_RGBA ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_R ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
#define  GL_ZERO 128 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_texture*,...) ; 
 void* TRUE ; 
 int /*<<< orphan*/  WINED3D_CMP_LESSEQUAL ; 
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 void* WINED3D_TADDRESS_CLAMP ; 
 void* WINED3D_TADDRESS_WRAP ; 
 void* WINED3D_TEXF_LINEAR ; 
 void* WINED3D_TEXF_NONE ; 
 void* WINED3D_TEXF_POINT ; 
 int WINED3D_TEXTURE_COND_NP2 ; 
 int WINED3D_TEXTURE_IS_SRGB ; 
 scalar_t__ can_use_texture_swizzle (struct wined3d_gl_info const*,struct wined3d_format const*) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_bind_texture (struct wined3d_context*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_identity_fixup (struct color_fixup_desc const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  needs_separate_srgb_gl_texture (struct wined3d_context*,struct wined3d_texture*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gl_texture* wined3d_texture_get_gl_texture (struct wined3d_texture*,void*) ; 
 int /*<<< orphan*/  wined3d_texture_set_dirty (struct wined3d_texture*) ; 

void wined3d_texture_bind(struct wined3d_texture *texture,
        struct wined3d_context *context, BOOL srgb)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const struct wined3d_format *format = texture->resource.format;
    const struct color_fixup_desc fixup = format->color_fixup;
    struct gl_texture *gl_tex;
    GLenum target;

    TRACE("texture %p, context %p, srgb %#x.\n", texture, context, srgb);

    if (!needs_separate_srgb_gl_texture(context, texture))
        srgb = FALSE;

    /* sRGB mode cache for preload() calls outside drawprim. */
    if (srgb)
        texture->flags |= WINED3D_TEXTURE_IS_SRGB;
    else
        texture->flags &= ~WINED3D_TEXTURE_IS_SRGB;

    gl_tex = wined3d_texture_get_gl_texture(texture, srgb);
    target = texture->target;

    if (gl_tex->name)
    {
        context_bind_texture(context, target, gl_tex->name);
        return;
    }

    gl_info->gl_ops.gl.p_glGenTextures(1, &gl_tex->name);
    checkGLcall("glGenTextures");
    TRACE("Generated texture %d.\n", gl_tex->name);

    if (!gl_tex->name)
    {
        ERR("Failed to generate a texture name.\n");
        return;
    }

    /* Initialise the state of the texture object to the OpenGL defaults, not
     * the wined3d defaults. */
    gl_tex->sampler_desc.address_u = WINED3D_TADDRESS_WRAP;
    gl_tex->sampler_desc.address_v = WINED3D_TADDRESS_WRAP;
    gl_tex->sampler_desc.address_w = WINED3D_TADDRESS_WRAP;
    memset(gl_tex->sampler_desc.border_color, 0, sizeof(gl_tex->sampler_desc.border_color));
    gl_tex->sampler_desc.mag_filter = WINED3D_TEXF_LINEAR;
    gl_tex->sampler_desc.min_filter = WINED3D_TEXF_POINT; /* GL_NEAREST_MIPMAP_LINEAR */
    gl_tex->sampler_desc.mip_filter = WINED3D_TEXF_LINEAR; /* GL_NEAREST_MIPMAP_LINEAR */
    gl_tex->sampler_desc.lod_bias = 0.0f;
    gl_tex->sampler_desc.min_lod = -1000.0f;
    gl_tex->sampler_desc.max_lod = 1000.0f;
    gl_tex->sampler_desc.max_anisotropy = 1;
    gl_tex->sampler_desc.compare = FALSE;
    gl_tex->sampler_desc.comparison_func = WINED3D_CMP_LESSEQUAL;
    if (context->gl_info->supported[EXT_TEXTURE_SRGB_DECODE])
        gl_tex->sampler_desc.srgb_decode = TRUE;
    else
        gl_tex->sampler_desc.srgb_decode = srgb;
    gl_tex->base_level = 0;
    wined3d_texture_set_dirty(texture);

    context_bind_texture(context, target, gl_tex->name);

    /* For a new texture we have to set the texture levels after binding the
     * texture. Beware that texture rectangles do not support mipmapping, but
     * set the maxmiplevel if we're relying on the partial
     * GL_ARB_texture_non_power_of_two emulation with texture rectangles.
     * (I.e., do not care about cond_np2 here, just look for
     * GL_TEXTURE_RECTANGLE_ARB.) */
    if (target != GL_TEXTURE_RECTANGLE_ARB)
    {
        TRACE("Setting GL_TEXTURE_MAX_LEVEL to %u.\n", texture->level_count - 1);
        gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, texture->level_count - 1);
        checkGLcall("glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, texture->level_count)");
    }

    if (target == GL_TEXTURE_CUBE_MAP_ARB)
    {
        /* Cubemaps are always set to clamp, regardless of the sampler state. */
        gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    if (texture->flags & WINED3D_TEXTURE_COND_NP2)
    {
        /* Conditinal non power of two textures use a different clamping
         * default. If we're using the GL_WINE_normalized_texrect partial
         * driver emulation, we're dealing with a GL_TEXTURE_2D texture which
         * has the address mode set to repeat - something that prevents us
         * from hitting the accelerated codepath. Thus manually set the GL
         * state. The same applies to filtering. Even if the texture has only
         * one mip level, the default LINEAR_MIPMAP_LINEAR filter causes a SW
         * fallback on macos. */
        gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        gl_info->gl_ops.gl.p_glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        checkGLcall("glTexParameteri");
        gl_tex->sampler_desc.address_u = WINED3D_TADDRESS_CLAMP;
        gl_tex->sampler_desc.address_v = WINED3D_TADDRESS_CLAMP;
        gl_tex->sampler_desc.mag_filter = WINED3D_TEXF_POINT;
        gl_tex->sampler_desc.min_filter = WINED3D_TEXF_POINT;
        gl_tex->sampler_desc.mip_filter = WINED3D_TEXF_NONE;
    }

    if (gl_info->supported[WINED3D_GL_LEGACY_CONTEXT] && gl_info->supported[ARB_DEPTH_TEXTURE])
    {
        gl_info->gl_ops.gl.p_glTexParameteri(target, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);
        checkGLcall("glTexParameteri(GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY)");
    }

    if (!is_identity_fixup(fixup) && can_use_texture_swizzle(gl_info, format))
    {
        static const GLenum swizzle_source[] =
        {
            GL_ZERO,  /* CHANNEL_SOURCE_ZERO */
            GL_ONE,   /* CHANNEL_SOURCE_ONE */
            GL_RED,   /* CHANNEL_SOURCE_X */
            GL_GREEN, /* CHANNEL_SOURCE_Y */
            GL_BLUE,  /* CHANNEL_SOURCE_Z */
            GL_ALPHA, /* CHANNEL_SOURCE_W */
        };
        struct
        {
            GLint x, y, z, w;
        }
        swizzle;

        swizzle.x = swizzle_source[fixup.x_source];
        swizzle.y = swizzle_source[fixup.y_source];
        swizzle.z = swizzle_source[fixup.z_source];
        swizzle.w = swizzle_source[fixup.w_source];
        gl_info->gl_ops.gl.p_glTexParameteriv(target, GL_TEXTURE_SWIZZLE_RGBA, &swizzle.x);
        checkGLcall("glTexParameteriv(GL_TEXTURE_SWIZZLE_RGBA)");
    }
}