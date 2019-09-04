#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_resource {scalar_t__ type; int access; struct wined3d_format* format; } ;
struct wined3d_texture {scalar_t__ target; struct wined3d_resource resource; } ;
struct wined3d_format {scalar_t__ id; int* flags; int /*<<< orphan*/  color_fixup; } ;
struct wined3d_context {int dummy; } ;
typedef  enum wined3d_blit_op { ____Placeholder_wined3d_blit_op } wined3d_blit_op ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ GL_TEXTURE_2D_MULTISAMPLE ; 
 scalar_t__ GL_TEXTURE_2D_MULTISAMPLE_ARRAY ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int TRUE ; 
 int WINED3DFMT_FLAG_COMPRESSED ; 
 int WINED3DFMT_FLAG_DEPTH ; 
 int WINED3DFMT_FLAG_STENCIL ; 
 int WINED3D_BLIT_OP_COLOR_BLIT ; 
 int WINED3D_BLIT_OP_DEPTH_BLIT ; 
 int WINED3D_BLIT_OP_RAW_BLIT ; 
 size_t WINED3D_GL_RES_TYPE_TEX_2D ; 
 scalar_t__ WINED3D_LOCATION_DRAWABLE ; 
 int WINED3D_RESOURCE_ACCESS_GPU ; 
 scalar_t__ WINED3D_RTYPE_TEXTURE_2D ; 
 int /*<<< orphan*/  is_identity_fixup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL glsl_blitter_supported(enum wined3d_blit_op blit_op, const struct wined3d_context *context,
        const struct wined3d_texture *src_texture, DWORD src_location,
        const struct wined3d_texture *dst_texture, DWORD dst_location)
{
    const struct wined3d_resource *src_resource = &src_texture->resource;
    const struct wined3d_resource *dst_resource = &dst_texture->resource;
    const struct wined3d_format *src_format = src_resource->format;
    const struct wined3d_format *dst_format = dst_resource->format;
    BOOL decompress;

    if (blit_op == WINED3D_BLIT_OP_RAW_BLIT && dst_format->id == src_format->id)
    {
        if (dst_format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL))
            blit_op = WINED3D_BLIT_OP_DEPTH_BLIT;
        else
            blit_op = WINED3D_BLIT_OP_COLOR_BLIT;
    }

    if (blit_op != WINED3D_BLIT_OP_COLOR_BLIT)
    {
        TRACE("Unsupported blit_op %#x.\n", blit_op);
        return FALSE;
    }

    if (src_resource->type != WINED3D_RTYPE_TEXTURE_2D)
        return FALSE;

    if (src_texture->target == GL_TEXTURE_2D_MULTISAMPLE
            || dst_texture->target == GL_TEXTURE_2D_MULTISAMPLE
            || src_texture->target == GL_TEXTURE_2D_MULTISAMPLE_ARRAY
            || dst_texture->target == GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
    {
        TRACE("Multi-sample textures not supported.\n");
        return FALSE;
    }

    /* We don't necessarily want to blit from resources without
     * WINED3D_RESOURCE_ACCESS_GPU, but that may be the only way to decompress
     * compressed textures. */
    decompress = src_format && (src_format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_COMPRESSED)
            && !(dst_format->flags[WINED3D_GL_RES_TYPE_TEX_2D] & WINED3DFMT_FLAG_COMPRESSED);
    if (!decompress && !(src_resource->access & dst_resource->access & WINED3D_RESOURCE_ACCESS_GPU))
    {
        TRACE("Source or destination resource does not have GPU access.\n");
        return FALSE;
    }

    if (!is_identity_fixup(dst_format->color_fixup)
            && (dst_format->id != src_format->id || dst_location != WINED3D_LOCATION_DRAWABLE))
    {
        TRACE("Destination fixups are not supported.\n");
        return FALSE;
    }

    TRACE("Returning supported.\n");
    return TRUE;
}