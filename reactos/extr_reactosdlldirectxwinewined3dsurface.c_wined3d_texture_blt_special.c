#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ type; int access; TYPE_3__* format; TYPE_2__* device; } ;
struct wined3d_texture {unsigned int level_count; TYPE_4__ resource; struct wined3d_swapchain* swapchain; } ;
struct wined3d_swapchain {int dummy; } ;
struct wined3d_rendertarget_view {unsigned int sub_resource_idx; TYPE_4__* resource; } ;
struct wined3d_blt_fx {int dummy; } ;
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
struct TYPE_17__ {unsigned int right; unsigned int left; unsigned int bottom; unsigned int top; } ;
struct TYPE_15__ {scalar_t__ id; } ;
struct TYPE_13__ {struct wined3d_rendertarget_view** render_targets; } ;
struct TYPE_14__ {TYPE_1__ fb; } ;
typedef  TYPE_5__ RECT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WINED3DERR_INVALIDCALL ; 
 scalar_t__ WINED3DFMT_P8_UINT ; 
 int WINED3D_BLT_DST_CKEY ; 
 int WINED3D_BLT_DST_CKEY_OVERRIDE ; 
 int WINED3D_BLT_SRC_CKEY ; 
 int WINED3D_BLT_SRC_CKEY_OVERRIDE ; 
 int /*<<< orphan*/  WINED3D_OK ; 
 int WINED3D_RESOURCE_ACCESS_GPU ; 
 scalar_t__ WINED3D_RTYPE_TEXTURE_2D ; 
 int /*<<< orphan*/  debug_d3dresourcetype (scalar_t__) ; 
 int /*<<< orphan*/  debug_d3dtexturefiltertype (int) ; 
 int /*<<< orphan*/  fb_copy_to_texture_direct (struct wined3d_texture*,unsigned int,TYPE_5__ const*,struct wined3d_texture*,unsigned int,TYPE_5__ const*,int) ; 
 int /*<<< orphan*/  fb_copy_to_texture_hwstretch (struct wined3d_texture*,unsigned int,TYPE_5__ const*,struct wined3d_texture*,unsigned int,TYPE_5__ const*,int) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_5__ const*) ; 
 unsigned int wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 

__attribute__((used)) static HRESULT wined3d_texture_blt_special(struct wined3d_texture *dst_texture, unsigned int dst_sub_resource_idx,
        const RECT *dst_rect, struct wined3d_texture *src_texture, unsigned int src_sub_resource_idx,
        const RECT *src_rect, DWORD flags, const struct wined3d_blt_fx *fx, enum wined3d_texture_filter_type filter)
{
    struct wined3d_swapchain *src_swapchain, *dst_swapchain;
    const struct wined3d_rendertarget_view *rtv;

    TRACE("dst_texture %p, dst_sub_resource_idx %u, dst_rect %s, src_texture %p, "
            "src_sub_resource_idx %u, src_rect %s, flags %#x, fx %p, filter %s.\n",
            dst_texture, dst_sub_resource_idx, wine_dbgstr_rect(dst_rect), src_texture, src_sub_resource_idx,
            wine_dbgstr_rect(src_rect), flags, fx, debug_d3dtexturefiltertype(filter));

    if (dst_texture->resource.type != WINED3D_RTYPE_TEXTURE_2D)
    {
        FIXME("Not implemented for %s resources.\n", debug_d3dresourcetype(dst_texture->resource.type));
        return WINED3DERR_INVALIDCALL;
    }

    /* Get the swapchain. One of the surfaces has to be a primary surface. */
    if (!(dst_texture->resource.access & WINED3D_RESOURCE_ACCESS_GPU))
    {
        WARN("Destination resource is not GPU accessible, rejecting GL blit.\n");
        return WINED3DERR_INVALIDCALL;
    }

    if (!(src_texture->resource.access & WINED3D_RESOURCE_ACCESS_GPU))
    {
        WARN("Source resource is not GPU accessible, rejecting GL blit.\n");
        return WINED3DERR_INVALIDCALL;
    }

    src_swapchain = src_texture->swapchain;
    dst_swapchain = dst_texture->swapchain;

    /* Early sort out of cases where no render target is used */
    if (!(rtv = dst_texture->resource.device->fb.render_targets[0]) || (!src_swapchain && !dst_swapchain
            && (&src_texture->resource != rtv->resource || src_sub_resource_idx != rtv->sub_resource_idx)
            && (&dst_texture->resource != rtv->resource || dst_sub_resource_idx != rtv->sub_resource_idx)))
    {
        TRACE("No surface is render target, not using hardware blit.\n");
        return WINED3DERR_INVALIDCALL;
    }

    /* No destination color keying supported */
    if (flags & (WINED3D_BLT_DST_CKEY | WINED3D_BLT_DST_CKEY_OVERRIDE))
    {
        /* Can we support that with glBlendFunc if blitting to the frame buffer? */
        TRACE("Destination color key not supported in accelerated Blit, falling back to software\n");
        return WINED3DERR_INVALIDCALL;
    }

    if (dst_swapchain && dst_swapchain == src_swapchain)
    {
        FIXME("Implement hardware blit between two surfaces on the same swapchain\n");
        return WINED3DERR_INVALIDCALL;
    }

    if (dst_swapchain && src_swapchain)
    {
        FIXME("Implement hardware blit between two different swapchains\n");
        return WINED3DERR_INVALIDCALL;
    }

    if (dst_swapchain)
    {
        /* Handled with regular texture -> swapchain blit */
        if (&src_texture->resource == rtv->resource && src_sub_resource_idx == rtv->sub_resource_idx)
            TRACE("Blit from active render target to a swapchain\n");
    }
    else if (src_swapchain && &dst_texture->resource == rtv->resource
            && dst_sub_resource_idx == rtv->sub_resource_idx)
    {
        FIXME("Implement blit from a swapchain to the active render target\n");
        return WINED3DERR_INVALIDCALL;
    }

    if (!dst_swapchain && (src_swapchain || (&src_texture->resource == rtv->resource
            && src_sub_resource_idx == rtv->sub_resource_idx)))
    {
        unsigned int src_level, src_width, src_height;
        /* Blit from render target to texture */
        BOOL stretchx;

        /* P8 read back is not implemented */
        if (src_texture->resource.format->id == WINED3DFMT_P8_UINT
                || dst_texture->resource.format->id == WINED3DFMT_P8_UINT)
        {
            TRACE("P8 read back not supported by frame buffer to texture blit\n");
            return WINED3DERR_INVALIDCALL;
        }

        if (flags & (WINED3D_BLT_SRC_CKEY | WINED3D_BLT_SRC_CKEY_OVERRIDE))
        {
            TRACE("Color keying not supported by frame buffer to texture blit\n");
            return WINED3DERR_INVALIDCALL;
            /* Destination color key is checked above */
        }

        if (dst_rect->right - dst_rect->left != src_rect->right - src_rect->left)
            stretchx = TRUE;
        else
            stretchx = FALSE;

        /* Blt is a pretty powerful call, while glCopyTexSubImage2D is not. glCopyTexSubImage cannot
         * flip the image nor scale it.
         *
         * -> If the app asks for an unscaled, upside down copy, just perform one glCopyTexSubImage2D call
         * -> If the app wants an image width an unscaled width, copy it line per line
         * -> If the app wants an image that is scaled on the x axis, and the destination rectangle is smaller
         *    than the frame buffer, draw an upside down scaled image onto the fb, read it back and restore the
         *    back buffer. This is slower than reading line per line, thus not used for flipping
         * -> If the app wants a scaled image with a dest rect that is bigger than the fb, it has to be copied
         *    pixel by pixel. */
        src_level = src_sub_resource_idx % src_texture->level_count;
        src_width = wined3d_texture_get_level_width(src_texture, src_level);
        src_height = wined3d_texture_get_level_height(src_texture, src_level);
        if (!stretchx || dst_rect->right - dst_rect->left > src_width
                || dst_rect->bottom - dst_rect->top > src_height)
        {
            TRACE("No stretching in x direction, using direct framebuffer -> texture copy.\n");
            fb_copy_to_texture_direct(dst_texture, dst_sub_resource_idx, dst_rect,
                    src_texture, src_sub_resource_idx, src_rect, filter);
        }
        else
        {
            TRACE("Using hardware stretching to flip / stretch the texture.\n");
            fb_copy_to_texture_hwstretch(dst_texture, dst_sub_resource_idx, dst_rect,
                    src_texture, src_sub_resource_idx, src_rect, filter);
        }

        return WINED3D_OK;
    }

    /* Default: Fall back to the generic blt. Not an error, a TRACE is enough */
    TRACE("Didn't find any usable render target setup for hw blit, falling back to software\n");
    return WINED3DERR_INVALIDCALL;
}