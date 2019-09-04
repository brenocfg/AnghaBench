#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int glsl_varyings; } ;
struct wined3d_gl_info {struct wined3d_format* formats; TYPE_1__ limits; scalar_t__* supported; } ;
struct wined3d_format {int /*<<< orphan*/  glInternal; } ;
typedef  enum wined3d_pci_vendor { ____Placeholder_wined3d_pci_vendor } wined3d_pci_vendor ;
typedef  enum wined3d_format_id { ____Placeholder_wined3d_format_id } wined3d_format_id ;
struct TYPE_4__ {scalar_t__ offscreen_rendering_mode; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARB_INTERNALFORMAT_QUERY2 ; 
 size_t ARB_TEXTURE_FLOAT ; 
 unsigned int ARRAY_SIZE (int const*) ; 
 scalar_t__ FALSE ; 
 int HW_VENDOR_NVIDIA ; 
 scalar_t__ ORM_FBO ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WINED3DFMT_FLAG_FILTERING ; 
#define  WINED3DFMT_R16G16B16A16_FLOAT 130 
#define  WINED3DFMT_R16G16_FLOAT 129 
#define  WINED3DFMT_R16_FLOAT 128 
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 scalar_t__ check_filter (struct wined3d_gl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_d3dformat (int const) ; 
 int /*<<< orphan*/  format_set_flag (struct wined3d_format*,int /*<<< orphan*/ ) ; 
 unsigned int get_format_idx (int const) ; 
 TYPE_2__ wined3d_settings ; 

__attribute__((used)) static void init_format_filter_info(struct wined3d_gl_info *gl_info, enum wined3d_pci_vendor vendor)
{
    struct wined3d_format *format;
    unsigned int fmt_idx, i;
    static const enum wined3d_format_id fmts16[] =
    {
        WINED3DFMT_R16_FLOAT,
        WINED3DFMT_R16G16_FLOAT,
        WINED3DFMT_R16G16B16A16_FLOAT,
    };
    BOOL filtered;

    if (gl_info->supported[ARB_INTERNALFORMAT_QUERY2])
        /* This was already handled by init_format_texture_info(). */
        return;

    if (wined3d_settings.offscreen_rendering_mode != ORM_FBO
            || !gl_info->supported[WINED3D_GL_LEGACY_CONTEXT])
    {
        WARN("No FBO support, or no FBO ORM, guessing filter info from GL caps\n");
        if (vendor == HW_VENDOR_NVIDIA && gl_info->supported[ARB_TEXTURE_FLOAT])
        {
            TRACE("Nvidia card with texture_float support: Assuming float16 blending\n");
            filtered = TRUE;
        }
        else if (gl_info->limits.glsl_varyings > 44)
        {
            TRACE("More than 44 GLSL varyings - assuming d3d10 card with float16 blending\n");
            filtered = TRUE;
        }
        else
        {
            TRACE("Assuming no float16 blending\n");
            filtered = FALSE;
        }

        if (filtered)
        {
            for (i = 0; i < ARRAY_SIZE(fmts16); ++i)
            {
                fmt_idx = get_format_idx(fmts16[i]);
                format_set_flag(&gl_info->formats[fmt_idx], WINED3DFMT_FLAG_FILTERING);
            }
        }
        return;
    }

    for (i = 0; i < ARRAY_SIZE(fmts16); ++i)
    {
        fmt_idx = get_format_idx(fmts16[i]);
        format = &gl_info->formats[fmt_idx];
        if (!format->glInternal) continue; /* Not supported by GL */

        filtered = check_filter(gl_info, gl_info->formats[fmt_idx].glInternal);
        if (filtered)
        {
            TRACE("Format %s supports filtering\n", debug_d3dformat(fmts16[i]));
            format_set_flag(format, WINED3DFMT_FLAG_FILTERING);
        }
        else
        {
            TRACE("Format %s does not support filtering\n", debug_d3dformat(fmts16[i]));
        }
    }
}