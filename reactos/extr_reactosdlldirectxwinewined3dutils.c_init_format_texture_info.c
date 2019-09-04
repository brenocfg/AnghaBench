#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct wined3d_gl_info {scalar_t__* supported; } ;
struct TYPE_11__ {int numerator; int denominator; } ;
struct wined3d_format {int* flags; scalar_t__ glInternal; scalar_t__ glGammaInternal; scalar_t__ id; int /*<<< orphan*/  download; int /*<<< orphan*/  upload; int /*<<< orphan*/  conv_byte_count; TYPE_3__ height_scale; int /*<<< orphan*/  color_fixup; int /*<<< orphan*/  glType; int /*<<< orphan*/  glFormat; int /*<<< orphan*/  rtInternal; } ;
struct TYPE_12__ {int wined3d_creation_flags; } ;
struct wined3d_adapter {TYPE_4__ d3d_info; TYPE_2__* shader_backend; TYPE_1__* fragment_pipe; } ;
struct shader_caps {int wined3d_caps; } ;
struct fragment_caps {int wined3d_caps; } ;
struct TYPE_13__ {size_t extension; scalar_t__ gl_internal; scalar_t__ gl_srgb_internal; int flags; scalar_t__ base_format_id; int /*<<< orphan*/  srgb_format_id; int /*<<< orphan*/  download; int /*<<< orphan*/  upload; int /*<<< orphan*/  conv_byte_count; int /*<<< orphan*/  gl_type; int /*<<< orphan*/  gl_format; int /*<<< orphan*/  gl_rt_internal; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* shader_get_caps ) (struct wined3d_gl_info*,struct shader_caps*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* get_caps ) (struct wined3d_gl_info*,struct fragment_caps*) ;} ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARB_TEXTURE_CUBE_MAP ; 
 size_t ARB_TEXTURE_FLOAT ; 
 size_t ARB_TEXTURE_RECTANGLE ; 
 unsigned int ARRAY_SIZE (TYPE_5__*) ; 
 int /*<<< orphan*/  COLOR_FIXUP_IDENTITY ; 
 size_t EXT_TEXTURE3D ; 
 size_t EXT_TEXTURE_INTEGER ; 
 size_t EXT_TEXTURE_SRGB ; 
 int FALSE ; 
 int TRUE ; 
 int WINED3DFMT_FLAG_DEPTH ; 
 int WINED3DFMT_FLAG_FLOAT ; 
 int WINED3DFMT_FLAG_INTEGER ; 
 int WINED3DFMT_FLAG_SRGB_READ ; 
 int WINED3DFMT_FLAG_SRGB_WRITE ; 
 int WINED3DFMT_FLAG_STENCIL ; 
 int WINED3DFMT_FLAG_TEXTURE ; 
 int WINED3D_FRAGMENT_CAP_SRGB_WRITE ; 
 size_t WINED3D_GL_RES_TYPE_BUFFER ; 
 size_t WINED3D_GL_RES_TYPE_RB ; 
 size_t WINED3D_GL_RES_TYPE_TEX_1D ; 
 size_t WINED3D_GL_RES_TYPE_TEX_2D ; 
 size_t WINED3D_GL_RES_TYPE_TEX_3D ; 
 size_t WINED3D_GL_RES_TYPE_TEX_CUBE ; 
 size_t WINED3D_GL_RES_TYPE_TEX_RECT ; 
 int WINED3D_SHADER_CAP_SRGB_WRITE ; 
 int WINED3D_SRGB_READ_WRITE_CONTROL ; 
 int /*<<< orphan*/  copy_format (struct wined3d_format*,struct wined3d_format*) ; 
 int /*<<< orphan*/  format_clear_flag (struct wined3d_format*,int) ; 
 int /*<<< orphan*/  format_set_flag (struct wined3d_format*,int) ; 
 TYPE_5__* format_srgb_info ; 
 TYPE_5__* format_texture_info ; 
 struct wined3d_format* get_format_internal (struct wined3d_gl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_internal_format (struct wined3d_adapter*,struct wined3d_format*,TYPE_5__*,struct wined3d_gl_info*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct wined3d_gl_info*,struct fragment_caps*) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_gl_info*,struct shader_caps*) ; 

__attribute__((used)) static BOOL init_format_texture_info(struct wined3d_adapter *adapter, struct wined3d_gl_info *gl_info)
{
    struct wined3d_format *format, *srgb_format;
    struct fragment_caps fragment_caps;
    struct shader_caps shader_caps;
    unsigned int i, j;
    BOOL srgb_write;

    adapter->fragment_pipe->get_caps(gl_info, &fragment_caps);
    adapter->shader_backend->shader_get_caps(gl_info, &shader_caps);
    srgb_write = (fragment_caps.wined3d_caps & WINED3D_FRAGMENT_CAP_SRGB_WRITE)
            && (shader_caps.wined3d_caps & WINED3D_SHADER_CAP_SRGB_WRITE);

    for (i = 0; i < ARRAY_SIZE(format_texture_info); ++i)
    {
        if (!(format = get_format_internal(gl_info, format_texture_info[i].id)))
            return FALSE;

        if (!gl_info->supported[format_texture_info[i].extension])
            continue;

        /* ARB_texture_rg defines floating point formats, but only if
         * ARB_texture_float is also supported. */
        if (!gl_info->supported[ARB_TEXTURE_FLOAT]
                && (format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_FLOAT))
            continue;

        /* ARB_texture_rg defines integer formats if EXT_texture_integer is also supported. */
        if (!gl_info->supported[EXT_TEXTURE_INTEGER]
                && (format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_INTEGER))
            continue;

        format->glInternal = format_texture_info[i].gl_internal;
        format->glGammaInternal = format_texture_info[i].gl_srgb_internal;
        format->rtInternal = format_texture_info[i].gl_rt_internal;
        format->glFormat = format_texture_info[i].gl_format;
        format->glType = format_texture_info[i].gl_type;
        format->color_fixup = COLOR_FIXUP_IDENTITY;
        format->height_scale.numerator = 1;
        format->height_scale.denominator = 1;

        format->flags[WINED3D_GL_RES_TYPE_TEX_1D] |= format_texture_info[i].flags;
        format->flags[WINED3D_GL_RES_TYPE_TEX_2D] |= format_texture_info[i].flags;
        format->flags[WINED3D_GL_RES_TYPE_BUFFER] |= format_texture_info[i].flags;

        /* GL_ARB_depth_texture does not support 3D textures. It also says "cube textures are
         * problematic", but doesn't explicitly mandate that an error is generated. */
        if (gl_info->supported[EXT_TEXTURE3D]
                && !(format_texture_info[i].flags & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL)))
            format->flags[WINED3D_GL_RES_TYPE_TEX_3D] |= format_texture_info[i].flags;

        if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
            format->flags[WINED3D_GL_RES_TYPE_TEX_CUBE] |= format_texture_info[i].flags;

        if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
            format->flags[WINED3D_GL_RES_TYPE_TEX_RECT] |= format_texture_info[i].flags;

        format->flags[WINED3D_GL_RES_TYPE_RB] |= format_texture_info[i].flags;
        format->flags[WINED3D_GL_RES_TYPE_RB] &= ~WINED3DFMT_FLAG_TEXTURE;

        if (format->glGammaInternal != format->glInternal
                && !(adapter->d3d_info.wined3d_creation_flags & WINED3D_SRGB_READ_WRITE_CONTROL))
        {
            format->glGammaInternal = format->glInternal;
            format_clear_flag(format, WINED3DFMT_FLAG_SRGB_READ | WINED3DFMT_FLAG_SRGB_WRITE);
        }

        query_internal_format(adapter, format, &format_texture_info[i], gl_info, srgb_write, FALSE);

        /* Texture conversion stuff */
        format->conv_byte_count = format_texture_info[i].conv_byte_count;
        format->upload = format_texture_info[i].upload;
        format->download = format_texture_info[i].download;

        srgb_format = NULL;
        for (j = 0; j < ARRAY_SIZE(format_srgb_info); ++j)
        {
            if (format_srgb_info[j].base_format_id == format->id)
            {
                if (!(srgb_format = get_format_internal(gl_info, format_srgb_info[j].srgb_format_id)))
                    return FALSE;
                break;
            }
        }
        if (!srgb_format)
            continue;

        copy_format(srgb_format, format);

        if (gl_info->supported[EXT_TEXTURE_SRGB]
                && !(adapter->d3d_info.wined3d_creation_flags & WINED3D_SRGB_READ_WRITE_CONTROL))
        {
            srgb_format->glInternal = format_texture_info[i].gl_srgb_internal;
            srgb_format->glGammaInternal = format_texture_info[i].gl_srgb_internal;
            format_set_flag(srgb_format, WINED3DFMT_FLAG_SRGB_READ | WINED3DFMT_FLAG_SRGB_WRITE);
            query_internal_format(adapter, srgb_format, &format_texture_info[i], gl_info, srgb_write, TRUE);
        }
    }

    return TRUE;
}