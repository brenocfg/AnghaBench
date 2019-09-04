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
struct wined3d_gl_info {int quirks; unsigned int format_count; struct wined3d_format* formats; scalar_t__* supported; } ;
struct TYPE_4__ {int numerator; int denominator; } ;
struct wined3d_format {int* flags; void* color_fixup; void* gl_vtx_type; int /*<<< orphan*/  gl_vtx_format; scalar_t__ glInternal; TYPE_1__ height_scale; } ;
struct wined3d_adapter {TYPE_3__* fragment_pipe; TYPE_2__* shader_backend; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* color_fixup_supported ) (void*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* shader_color_fixup_supported ) (void*) ;} ;

/* Variables and functions */
 size_t APPLE_YCBCR_422 ; 
 size_t ARB_FRAGMENT_PROGRAM ; 
 size_t ARB_FRAGMENT_SHADER ; 
 size_t ARB_FRAMEBUFFER_OBJECT ; 
 size_t ARB_HALF_FLOAT_PIXEL ; 
 size_t ARB_HALF_FLOAT_VERTEX ; 
 size_t ARB_TEXTURE_COMPRESSION_RGTC ; 
 size_t ARB_TEXTURE_RG ; 
 size_t ARB_VERTEX_ARRAY_BGRA ; 
 size_t ARB_VERTEX_PROGRAM ; 
 size_t ARB_VERTEX_SHADER ; 
 size_t ATI_TEXTURE_COMPRESSION_3DC ; 
 int /*<<< orphan*/  CHANNEL_SOURCE_ONE ; 
 int /*<<< orphan*/  CHANNEL_SOURCE_W ; 
 int /*<<< orphan*/  CHANNEL_SOURCE_X ; 
 int /*<<< orphan*/  CHANNEL_SOURCE_Y ; 
 int /*<<< orphan*/  CHANNEL_SOURCE_Z ; 
 int /*<<< orphan*/  CHANNEL_SOURCE_ZERO ; 
 int /*<<< orphan*/  COMPLEX_FIXUP_NV12 ; 
 int /*<<< orphan*/  COMPLEX_FIXUP_P8 ; 
 int /*<<< orphan*/  COMPLEX_FIXUP_UYVY ; 
 int /*<<< orphan*/  COMPLEX_FIXUP_YUY2 ; 
 int /*<<< orphan*/  COMPLEX_FIXUP_YV12 ; 
 size_t EXT_DEPTH_BOUNDS_TEST ; 
 size_t EXT_TEXTURE_COMPRESSION_RGTC ; 
 size_t EXT_TEXTURE_SNORM ; 
 int /*<<< orphan*/  GL_BGRA ; 
 void* GL_FLOAT ; 
 size_t NV_TEXTURE_SHADER ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WINED3DFMT_A8_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_ATI1N ; 
 int /*<<< orphan*/  WINED3DFMT_ATI2N ; 
 int /*<<< orphan*/  WINED3DFMT_B8G8R8A8_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_BC1_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_BC1_UNORM_SRGB ; 
 int /*<<< orphan*/  WINED3DFMT_BC2_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_BC2_UNORM_SRGB ; 
 int /*<<< orphan*/  WINED3DFMT_BC3_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_BC3_UNORM_SRGB ; 
 int /*<<< orphan*/  WINED3DFMT_BC4_SNORM ; 
 int /*<<< orphan*/  WINED3DFMT_BC4_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_BC5_SNORM ; 
 int /*<<< orphan*/  WINED3DFMT_BC5_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_DXT1 ; 
 int /*<<< orphan*/  WINED3DFMT_DXT2 ; 
 int /*<<< orphan*/  WINED3DFMT_DXT3 ; 
 int /*<<< orphan*/  WINED3DFMT_DXT4 ; 
 int /*<<< orphan*/  WINED3DFMT_DXT5 ; 
 int WINED3DFMT_FLAG_HEIGHT_SCALE ; 
 int WINED3DFMT_FLAG_RENDERTARGET ; 
 int WINED3DFMT_FLAG_TEXTURE ; 
 int /*<<< orphan*/  WINED3DFMT_INST ; 
 int /*<<< orphan*/  WINED3DFMT_INTZ ; 
 int /*<<< orphan*/  WINED3DFMT_L16_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_L4A4_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_L8A8_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_L8_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_NV12 ; 
 int /*<<< orphan*/  WINED3DFMT_NVDB ; 
 int /*<<< orphan*/  WINED3DFMT_P8_UINT ; 
 int /*<<< orphan*/  WINED3DFMT_R16G16B16A16_FLOAT ; 
 int /*<<< orphan*/  WINED3DFMT_R16G16B16A16_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_R16G16_FLOAT ; 
 int /*<<< orphan*/  WINED3DFMT_R16G16_SNORM ; 
 int /*<<< orphan*/  WINED3DFMT_R16G16_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_R16_FLOAT ; 
 int /*<<< orphan*/  WINED3DFMT_R32G32_FLOAT ; 
 int /*<<< orphan*/  WINED3DFMT_R32_FLOAT ; 
 int /*<<< orphan*/  WINED3DFMT_R5G5_SNORM_L6_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_R8G8B8A8_SNORM ; 
 int /*<<< orphan*/  WINED3DFMT_R8G8_SNORM ; 
 int /*<<< orphan*/  WINED3DFMT_R8G8_SNORM_L8X8_UNORM ; 
 int /*<<< orphan*/  WINED3DFMT_RESZ ; 
 int /*<<< orphan*/  WINED3DFMT_UYVY ; 
 int /*<<< orphan*/  WINED3DFMT_YUY2 ; 
 int /*<<< orphan*/  WINED3DFMT_YV12 ; 
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 size_t WINED3D_GL_RES_TYPE_TEX_2D ; 
 size_t WINED3D_GL_RES_TYPE_TEX_3D ; 
 int WINED3D_QUIRK_BROKEN_RGBA16 ; 
 void* create_color_fixup_desc (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* create_complex_fixup_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_color_fixup_desc (void*) ; 
 int /*<<< orphan*/  format_clear_flag (struct wined3d_format*,int) ; 
 int /*<<< orphan*/  format_set_flag (struct wined3d_format*,int) ; 
 int get_format_idx (int /*<<< orphan*/ ) ; 
 scalar_t__ is_identity_fixup (void*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

__attribute__((used)) static void apply_format_fixups(struct wined3d_adapter *adapter, struct wined3d_gl_info *gl_info)
{
    unsigned int i;
    int idx;

    idx = get_format_idx(WINED3DFMT_R16_FLOAT);
    gl_info->formats[idx].color_fixup = create_color_fixup_desc(
            0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_W);

    idx = get_format_idx(WINED3DFMT_R32_FLOAT);
    gl_info->formats[idx].color_fixup = create_color_fixup_desc(
            0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_W);

    idx = get_format_idx(WINED3DFMT_R16G16_UNORM);
    gl_info->formats[idx].color_fixup = create_color_fixup_desc(
            0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_Y, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_W);

    idx = get_format_idx(WINED3DFMT_R16G16_FLOAT);
    gl_info->formats[idx].color_fixup = create_color_fixup_desc(
            0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_Y, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_W);

    idx = get_format_idx(WINED3DFMT_R32G32_FLOAT);
    gl_info->formats[idx].color_fixup = create_color_fixup_desc(
            0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_Y, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_W);

    /* GL_ATI_envmap_bumpmap in theory supports R8G8_SNORM but is no longer supported by
     * any driver. */
    if (gl_info->supported[NV_TEXTURE_SHADER] || gl_info->supported[EXT_TEXTURE_SNORM])
    {
        /* R8G8_SNORM and R16G16_SNORM need a fixup of the undefined blue channel. OpenGL
         * returns 0.0 when sampling from it, DirectX 1.0. So we always have in-shader
         * conversion for this format. */
        idx = get_format_idx(WINED3DFMT_R8G8_SNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_Y, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_ONE);
        idx = get_format_idx(WINED3DFMT_R16G16_SNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_Y, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_ONE);
    }
    else
    {
        /* Emulate using unsigned formats. This requires load-time conversion in addition to the
         * fixups here. */
        idx = get_format_idx(WINED3DFMT_R8G8_SNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                1, CHANNEL_SOURCE_X, 1, CHANNEL_SOURCE_Y, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_ONE);
        idx = get_format_idx(WINED3DFMT_R16G16_SNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                1, CHANNEL_SOURCE_X, 1, CHANNEL_SOURCE_Y, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_ONE);
        idx = get_format_idx(WINED3DFMT_R8G8B8A8_SNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                1, CHANNEL_SOURCE_X, 1, CHANNEL_SOURCE_Y, 1, CHANNEL_SOURCE_Z, 1, CHANNEL_SOURCE_W);
        idx = get_format_idx(WINED3DFMT_R5G5_SNORM_L6_UNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                1, CHANNEL_SOURCE_X, 1, CHANNEL_SOURCE_Z, 0, CHANNEL_SOURCE_Y, 0, CHANNEL_SOURCE_ONE);
    }

    if (!gl_info->supported[NV_TEXTURE_SHADER])
    {
        idx = get_format_idx(WINED3DFMT_R8G8_SNORM_L8X8_UNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                1, CHANNEL_SOURCE_X, 1, CHANNEL_SOURCE_Y, 0, CHANNEL_SOURCE_Z, 0, CHANNEL_SOURCE_W);
    }

    if (gl_info->supported[ARB_TEXTURE_COMPRESSION_RGTC] || gl_info->supported[EXT_TEXTURE_COMPRESSION_RGTC])
    {
        idx = get_format_idx(WINED3DFMT_ATI1N);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X);

        idx = get_format_idx(WINED3DFMT_ATI2N);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                0, CHANNEL_SOURCE_Y, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_ONE);
    }
    else if (gl_info->supported[ATI_TEXTURE_COMPRESSION_3DC])
    {
        idx = get_format_idx(WINED3DFMT_ATI2N);
        gl_info->formats[idx].color_fixup= create_color_fixup_desc(
                0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_W, 0, CHANNEL_SOURCE_ONE, 0, CHANNEL_SOURCE_ONE);
    }

    if (!gl_info->supported[APPLE_YCBCR_422] && (gl_info->supported[ARB_FRAGMENT_PROGRAM]
            || (gl_info->supported[ARB_FRAGMENT_SHADER] && gl_info->supported[ARB_VERTEX_SHADER])))
    {
        idx = get_format_idx(WINED3DFMT_YUY2);
        gl_info->formats[idx].color_fixup = create_complex_fixup_desc(COMPLEX_FIXUP_YUY2);

        idx = get_format_idx(WINED3DFMT_UYVY);
        gl_info->formats[idx].color_fixup = create_complex_fixup_desc(COMPLEX_FIXUP_UYVY);
    }
    else if (!gl_info->supported[APPLE_YCBCR_422] && (!gl_info->supported[ARB_FRAGMENT_PROGRAM]
            && (!gl_info->supported[ARB_FRAGMENT_SHADER] || !gl_info->supported[ARB_VERTEX_SHADER])))
    {
        idx = get_format_idx(WINED3DFMT_YUY2);
        gl_info->formats[idx].glInternal = 0;

        idx = get_format_idx(WINED3DFMT_UYVY);
        gl_info->formats[idx].glInternal = 0;
    }

    if (gl_info->supported[ARB_FRAGMENT_PROGRAM]
            || (gl_info->supported[ARB_FRAGMENT_SHADER] && gl_info->supported[ARB_VERTEX_SHADER]))
    {
        idx = get_format_idx(WINED3DFMT_YV12);
        format_set_flag(&gl_info->formats[idx], WINED3DFMT_FLAG_HEIGHT_SCALE);
        gl_info->formats[idx].height_scale.numerator = 3;
        gl_info->formats[idx].height_scale.denominator = 2;
        gl_info->formats[idx].color_fixup = create_complex_fixup_desc(COMPLEX_FIXUP_YV12);

        idx = get_format_idx(WINED3DFMT_NV12);
        format_set_flag(&gl_info->formats[idx], WINED3DFMT_FLAG_HEIGHT_SCALE);
        gl_info->formats[idx].height_scale.numerator = 3;
        gl_info->formats[idx].height_scale.denominator = 2;
        gl_info->formats[idx].color_fixup = create_complex_fixup_desc(COMPLEX_FIXUP_NV12);
    }
    else
    {
        idx = get_format_idx(WINED3DFMT_YV12);
        gl_info->formats[idx].glInternal = 0;

        idx = get_format_idx(WINED3DFMT_NV12);
        gl_info->formats[idx].glInternal = 0;
    }

    if (!gl_info->supported[WINED3D_GL_LEGACY_CONTEXT])
    {
        idx = get_format_idx(WINED3DFMT_A8_UNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                0, CHANNEL_SOURCE_ZERO, 0, CHANNEL_SOURCE_ZERO, 0, CHANNEL_SOURCE_ZERO, 0, CHANNEL_SOURCE_X);
        idx = get_format_idx(WINED3DFMT_L8A8_UNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_Y);
        idx = get_format_idx(WINED3DFMT_L4A4_UNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_Y);
        idx = get_format_idx(WINED3DFMT_L16_UNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_ONE);
        idx = get_format_idx(WINED3DFMT_INTZ);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X);
    }

    if (gl_info->supported[ARB_TEXTURE_RG])
    {
        idx = get_format_idx(WINED3DFMT_L8_UNORM);
        gl_info->formats[idx].color_fixup = create_color_fixup_desc(
                0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_X, 0, CHANNEL_SOURCE_ONE);
    }

    if (gl_info->supported[ARB_FRAGMENT_PROGRAM] || gl_info->supported[ARB_FRAGMENT_SHADER])
    {
        idx = get_format_idx(WINED3DFMT_P8_UINT);
        gl_info->formats[idx].color_fixup = create_complex_fixup_desc(COMPLEX_FIXUP_P8);
    }

    if (gl_info->supported[ARB_VERTEX_ARRAY_BGRA])
    {
        idx = get_format_idx(WINED3DFMT_B8G8R8A8_UNORM);
        gl_info->formats[idx].gl_vtx_format = GL_BGRA;
    }

    if (!gl_info->supported[ARB_HALF_FLOAT_VERTEX])
    {
        /* Do not change the size of the type, it is CPU side. We have to change the GPU-side information though.
         * It is the job of the vertex buffer code to make sure that the vbos have the right format */
        idx = get_format_idx(WINED3DFMT_R16G16_FLOAT);
        gl_info->formats[idx].gl_vtx_type = GL_FLOAT;

        idx = get_format_idx(WINED3DFMT_R16G16B16A16_FLOAT);
        gl_info->formats[idx].gl_vtx_type = GL_FLOAT;
    }

    if (!gl_info->supported[ARB_HALF_FLOAT_PIXEL])
    {
        idx = get_format_idx(WINED3DFMT_R16_FLOAT);
        format_clear_flag(&gl_info->formats[idx], WINED3DFMT_FLAG_TEXTURE);

        idx = get_format_idx(WINED3DFMT_R16G16_FLOAT);
        format_clear_flag(&gl_info->formats[idx], WINED3DFMT_FLAG_TEXTURE);

        idx = get_format_idx(WINED3DFMT_R16G16B16A16_FLOAT);
        format_clear_flag(&gl_info->formats[idx], WINED3DFMT_FLAG_TEXTURE);
    }

    if (gl_info->quirks & WINED3D_QUIRK_BROKEN_RGBA16)
    {
        idx = get_format_idx(WINED3DFMT_R16G16B16A16_UNORM);
        format_clear_flag(&gl_info->formats[idx], WINED3DFMT_FLAG_TEXTURE);
    }

    /* ATI instancing hack: Although ATI cards do not support Shader Model
     * 3.0, they support instancing. To query if the card supports instancing
     * CheckDeviceFormat() with the special format MAKEFOURCC('I','N','S','T')
     * is used. Should an application check for this, provide a proper return
     * value. We can do instancing with all shader versions, but we need
     * vertex shaders.
     *
     * Additionally applications have to set the D3DRS_POINTSIZE render state
     * to MAKEFOURCC('I','N','S','T') once to enable instancing. Wined3d
     * doesn't need that and just ignores it.
     *
     * With Shader Model 3.0 capable cards Instancing 'just works' in Windows. */
    /* FIXME: This should just check the shader backend caps. */
    if (gl_info->supported[ARB_VERTEX_PROGRAM] || gl_info->supported[ARB_VERTEX_SHADER])
    {
        idx = get_format_idx(WINED3DFMT_INST);
        format_set_flag(&gl_info->formats[idx], WINED3DFMT_FLAG_TEXTURE);
    }

    /* Depth bound test. To query if the card supports it CheckDeviceFormat()
     * with the special format MAKEFOURCC('N','V','D','B') is used. It is
     * enabled by setting D3DRS_ADAPTIVETESS_X render state to
     * MAKEFOURCC('N','V','D','B') and then controlled by setting
     * D3DRS_ADAPTIVETESS_Z (zMin) and D3DRS_ADAPTIVETESS_W (zMax) to test
     * value. */
    if (gl_info->supported[EXT_DEPTH_BOUNDS_TEST])
    {
        idx = get_format_idx(WINED3DFMT_NVDB);
        format_set_flag(&gl_info->formats[idx], WINED3DFMT_FLAG_TEXTURE);
    }

    /* RESZ aka AMD DX9-level hack for multisampled depth buffer resolve. You query for RESZ
     * support by checking for availability of MAKEFOURCC('R','E','S','Z') surfaces with
     * RENDERTARGET usage. */
    if (gl_info->supported[ARB_FRAMEBUFFER_OBJECT])
    {
        idx = get_format_idx(WINED3DFMT_RESZ);
        format_set_flag(&gl_info->formats[idx], WINED3DFMT_FLAG_TEXTURE | WINED3DFMT_FLAG_RENDERTARGET);
    }

    for (i = 0; i < gl_info->format_count; ++i)
    {
        struct wined3d_format *format = &gl_info->formats[i];

        if (!(format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_TEXTURE))
            continue;

        if (is_identity_fixup(format->color_fixup))
            continue;

        TRACE("Checking support for fixup:\n");
        dump_color_fixup_desc(format->color_fixup);
        if (!adapter->shader_backend->shader_color_fixup_supported(format->color_fixup)
                || !adapter->fragment_pipe->color_fixup_supported(format->color_fixup))
        {
            TRACE("[FAILED]\n");
            format_clear_flag(format, WINED3DFMT_FLAG_TEXTURE);
        }
        else
        {
            TRACE("[OK]\n");
        }
    }

    /* GL_EXT_texture_compression_s3tc does not support 3D textures. Some Windows drivers
     * for dx9 GPUs support it, some do not, so not supporting DXTn volumes is OK for d3d9.
     *
     * Note that GL_NV_texture_compression_vtc adds this functionality to OpenGL, but the
     * block layout is not compatible with the one used by d3d. See volume_dxt5_test. */
    idx = get_format_idx(WINED3DFMT_DXT1);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_DXT2);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_DXT3);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_DXT4);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_DXT5);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_BC1_UNORM);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_BC1_UNORM_SRGB);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_BC2_UNORM);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_BC2_UNORM_SRGB);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_BC3_UNORM);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_BC3_UNORM_SRGB);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    /* Similarly with ATI1N / ATI2N and GL_ARB_texture_compression_rgtc. */
    idx = get_format_idx(WINED3DFMT_ATI1N);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_ATI2N);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_BC4_UNORM);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_BC4_SNORM);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_BC5_UNORM);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
    idx = get_format_idx(WINED3DFMT_BC5_SNORM);
    gl_info->formats[idx].flags[WINED3D_GL_RES_TYPE_TEX_3D] &= ~WINED3DFMT_FLAG_TEXTURE;
}