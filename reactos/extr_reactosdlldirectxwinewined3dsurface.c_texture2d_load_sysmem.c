#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_texture_sub_resource {int locations; } ;
struct TYPE_2__ {int usage; int draw_binding; } ;
struct wined3d_texture {TYPE_1__ resource; int /*<<< orphan*/  download_count; struct wined3d_texture_sub_resource* sub_resources; } ;
struct wined3d_context {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int WINED3DUSAGE_DEPTHSTENCIL ; 
 int WINED3D_LOCATION_DRAWABLE ; 
 int WINED3D_LOCATION_RB_MULTISAMPLE ; 
 int WINED3D_LOCATION_RB_RESOLVED ; 
 int WINED3D_LOCATION_TEXTURE_RGB ; 
 int WINED3D_LOCATION_TEXTURE_SRGB ; 
 scalar_t__ is_multisample_location (struct wined3d_texture*,int) ; 
 int /*<<< orphan*/  texture2d_download_data (struct wined3d_texture*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  texture2d_read_from_framebuffer (struct wined3d_texture*,unsigned int,struct wined3d_context*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_debug_location (int) ; 
 int /*<<< orphan*/  wined3d_texture_bind_and_dirtify (struct wined3d_texture*,struct wined3d_context*,int) ; 
 int /*<<< orphan*/  wined3d_texture_load_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int) ; 
 int /*<<< orphan*/  wined3d_texture_prepare_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ ) ; 

BOOL texture2d_load_sysmem(struct wined3d_texture *texture, unsigned int sub_resource_idx,
        struct wined3d_context *context, DWORD dst_location)
{
    struct wined3d_texture_sub_resource *sub_resource;

    sub_resource = &texture->sub_resources[sub_resource_idx];
    wined3d_texture_prepare_location(texture, sub_resource_idx, context, dst_location);

    /* We cannot download data from multisample textures directly. */
    if (is_multisample_location(texture, WINED3D_LOCATION_TEXTURE_RGB))
    {
        wined3d_texture_load_location(texture, sub_resource_idx, context, WINED3D_LOCATION_RB_RESOLVED);
        texture2d_read_from_framebuffer(texture, sub_resource_idx, context,
                WINED3D_LOCATION_RB_RESOLVED, dst_location);
        return TRUE;
    }
    else
    {
        if (sub_resource->locations & (WINED3D_LOCATION_RB_MULTISAMPLE | WINED3D_LOCATION_RB_RESOLVED))
            wined3d_texture_load_location(texture, sub_resource_idx, context, WINED3D_LOCATION_TEXTURE_RGB);

        /* Download the sub-resource to system memory. */
        if (sub_resource->locations & (WINED3D_LOCATION_TEXTURE_RGB | WINED3D_LOCATION_TEXTURE_SRGB))
        {
            wined3d_texture_bind_and_dirtify(texture, context,
                    !(sub_resource->locations & WINED3D_LOCATION_TEXTURE_RGB));
            texture2d_download_data(texture, sub_resource_idx, context, dst_location);
            ++texture->download_count;

            return TRUE;
        }
    }

    if (!(texture->resource.usage & WINED3DUSAGE_DEPTHSTENCIL)
            && (sub_resource->locations & WINED3D_LOCATION_DRAWABLE))
    {
        texture2d_read_from_framebuffer(texture, sub_resource_idx, context,
                texture->resource.draw_binding, dst_location);
        return TRUE;
    }

    FIXME("Can't load texture %p, %u with location flags %s into sysmem.\n",
            texture, sub_resource_idx, wined3d_debug_location(sub_resource->locations));
    return FALSE;
}