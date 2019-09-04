#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int color_space_low_value; int color_space_high_value; } ;
struct TYPE_12__ {int color_space_low_value; int color_space_high_value; } ;
struct TYPE_15__ {TYPE_5__ dst_blt_color_key; TYPE_3__ src_blt_color_key; } ;
struct TYPE_10__ {int map_binding; unsigned int format_flags; struct wined3d_format* format; struct wined3d_device* device; } ;
struct wined3d_texture {unsigned int level_count; TYPE_9__* swapchain; TYPE_6__ async; TYPE_2__* sub_resources; TYPE_1__ resource; } ;
struct wined3d_map_desc {int row_pitch; void* data; int /*<<< orphan*/  slice_pitch; } ;
struct wined3d_format {scalar_t__ id; unsigned int byte_count; int block_height; int block_width; int block_byte_count; } ;
struct wined3d_device {scalar_t__ d3d_initialized; } ;
struct wined3d_context {int dummy; } ;
struct wined3d_box {unsigned int bottom; int top; unsigned int right; unsigned int left; } ;
struct wined3d_bo_address {int dummy; } ;
struct TYPE_16__ {int color_space_low_value; int color_space_high_value; } ;
struct TYPE_13__ {int color_space_low_value; int color_space_high_value; } ;
struct wined3d_blt_fx {int fx; TYPE_7__ dst_color_key; TYPE_4__ src_color_key; } ;
typedef  int pixel ;
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
typedef  int WORD ;
struct TYPE_18__ {TYPE_8__* swapchain_ops; int /*<<< orphan*/  front_buffer_update; struct wined3d_texture* front_buffer; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* swapchain_frontbuffer_updated ) (TYPE_9__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  size; } ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  GL_PIXEL_UNPACK_BUFFER ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,unsigned int) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_texture*,unsigned int,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WINED3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  WINED3DERR_NOTAVAILABLE ; 
 unsigned int WINED3DFMT_FLAG_BLOCKS ; 
 int WINED3D_BLT_DST_CKEY ; 
 int WINED3D_BLT_DST_CKEY_OVERRIDE ; 
 int WINED3D_BLT_FX ; 
 int WINED3D_BLT_RAW ; 
 int WINED3D_BLT_SRC_CKEY ; 
 int WINED3D_BLT_SRC_CKEY_OVERRIDE ; 
 int WINED3D_MAP_READ ; 
 int WINED3D_MAP_WRITE ; 
 int /*<<< orphan*/  WINED3D_OK ; 
 int WINED3D_TEXF_NONE ; 
 int WINED3D_TEXF_POINT ; 
 int WINEDDBLTFX_ARITHSTRETCHY ; 
 int WINEDDBLTFX_MIRRORLEFTRIGHT ; 
 int WINEDDBLTFX_MIRRORUPDOWN ; 
 int WINEDDBLTFX_NOTEARING ; 
 int WINEDDBLTFX_ROTATE180 ; 
 int WINEDDBLTFX_ROTATE270 ; 
 int WINEDDBLTFX_ROTATE90 ; 
 int WINEDDBLTFX_ZBUFFERBASEDEST ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* context_map_bo_address (struct wined3d_context*,struct wined3d_bo_address*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_unmap_bo_address (struct wined3d_context*,struct wined3d_bo_address*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_box (struct wined3d_box const*) ; 
 int /*<<< orphan*/  debug_d3dformat (scalar_t__) ; 
 int debug_d3dtexturefiltertype (int) ; 
 int /*<<< orphan*/  get_color_masks (struct wined3d_format const*,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,unsigned int) ; 
 int /*<<< orphan*/  memmove (int*,int const*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*) ; 
 struct wined3d_texture* surface_convert_format (struct wined3d_texture*,unsigned int,struct wined3d_format const*) ; 
 int /*<<< orphan*/  surface_cpu_blt_compressed (int const*,int*,int,int,unsigned int,unsigned int,struct wined3d_format const*,int,struct wined3d_blt_fx const*) ; 
 int /*<<< orphan*/  wined3d_debug_location (int) ; 
 int /*<<< orphan*/  wined3d_texture_decref (struct wined3d_texture*) ; 
 int /*<<< orphan*/  wined3d_texture_get_memory (struct wined3d_texture*,unsigned int,struct wined3d_bo_address*,int) ; 
 int /*<<< orphan*/  wined3d_texture_get_pitch (struct wined3d_texture*,unsigned int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_texture_invalidate_location (struct wined3d_texture*,unsigned int,int) ; 
 int /*<<< orphan*/  wined3d_texture_load_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int) ; 

__attribute__((used)) static HRESULT surface_cpu_blt(struct wined3d_texture *dst_texture, unsigned int dst_sub_resource_idx,
        const struct wined3d_box *dst_box, struct wined3d_texture *src_texture, unsigned int src_sub_resource_idx,
        const struct wined3d_box *src_box, DWORD flags, const struct wined3d_blt_fx *fx,
        enum wined3d_texture_filter_type filter)
{
    unsigned int bpp, src_height, src_width, dst_height, dst_width, row_byte_count;
    struct wined3d_device *device = dst_texture->resource.device;
    const struct wined3d_format *src_format, *dst_format;
    struct wined3d_texture *converted_texture = NULL;
    struct wined3d_bo_address src_data, dst_data;
    unsigned int src_fmt_flags, dst_fmt_flags;
    struct wined3d_map_desc dst_map, src_map;
    struct wined3d_context *context = NULL;
    unsigned int x, sx, xinc, y, sy, yinc;
    unsigned int texture_level;
    HRESULT hr = WINED3D_OK;
    BOOL same_sub_resource;
    DWORD map_binding;
    const BYTE *sbase;
    const BYTE *sbuf;
    BYTE *dbuf;

    TRACE("dst_texture %p, dst_sub_resource_idx %u, dst_box %s, src_texture %p, "
            "src_sub_resource_idx %u, src_box %s, flags %#x, fx %p, filter %s.\n",
            dst_texture, dst_sub_resource_idx, debug_box(dst_box), src_texture,
            src_sub_resource_idx, debug_box(src_box), flags, fx, debug_d3dtexturefiltertype(filter));

    if (device->d3d_initialized)
        context = context_acquire(device, NULL, 0);

    if (src_texture == dst_texture && src_sub_resource_idx == dst_sub_resource_idx)
    {
        same_sub_resource = TRUE;

        map_binding = dst_texture->resource.map_binding;
        texture_level = dst_sub_resource_idx % dst_texture->level_count;
        if (!wined3d_texture_load_location(dst_texture, dst_sub_resource_idx, context, map_binding))
            ERR("Failed to load the destination sub-resource into %s.\n", wined3d_debug_location(map_binding));
        wined3d_texture_invalidate_location(dst_texture, dst_sub_resource_idx, ~map_binding);
        wined3d_texture_get_pitch(dst_texture, texture_level, &dst_map.row_pitch, &dst_map.slice_pitch);
        wined3d_texture_get_memory(dst_texture, dst_sub_resource_idx, &dst_data, map_binding);
        dst_map.data = context_map_bo_address(context, &dst_data,
                dst_texture->sub_resources[dst_sub_resource_idx].size,
                GL_PIXEL_UNPACK_BUFFER, WINED3D_MAP_READ | WINED3D_MAP_WRITE);

        src_map = dst_map;
        src_format = dst_texture->resource.format;
        dst_format = src_format;
        dst_fmt_flags = dst_texture->resource.format_flags;
        src_fmt_flags = dst_fmt_flags;
    }
    else
    {
        same_sub_resource = FALSE;
        dst_format = dst_texture->resource.format;
        dst_fmt_flags = dst_texture->resource.format_flags;
        if (!(flags & WINED3D_BLT_RAW) && dst_texture->resource.format->id != src_texture->resource.format->id)
        {
            if (!(converted_texture = surface_convert_format(src_texture, src_sub_resource_idx, dst_format)))
            {
                FIXME("Cannot convert %s to %s.\n", debug_d3dformat(src_texture->resource.format->id),
                        debug_d3dformat(dst_texture->resource.format->id));
                if (context)
                    context_release(context);
                return WINED3DERR_NOTAVAILABLE;
            }
            src_texture = converted_texture;
            src_sub_resource_idx = 0;
        }
        src_format = src_texture->resource.format;
        src_fmt_flags = src_texture->resource.format_flags;

        map_binding = src_texture->resource.map_binding;
        texture_level = src_sub_resource_idx % src_texture->level_count;
        if (!wined3d_texture_load_location(src_texture, src_sub_resource_idx, context, map_binding))
            ERR("Failed to load the source sub-resource into %s.\n", wined3d_debug_location(map_binding));
        wined3d_texture_get_pitch(src_texture, texture_level, &src_map.row_pitch, &src_map.slice_pitch);
        wined3d_texture_get_memory(src_texture, src_sub_resource_idx, &src_data, map_binding);
        src_map.data = context_map_bo_address(context, &src_data,
                src_texture->sub_resources[src_sub_resource_idx].size, GL_PIXEL_UNPACK_BUFFER, WINED3D_MAP_READ);

        map_binding = dst_texture->resource.map_binding;
        texture_level = dst_sub_resource_idx % dst_texture->level_count;
        if (!wined3d_texture_load_location(dst_texture, dst_sub_resource_idx, context, map_binding))
            ERR("Failed to load the destination sub-resource into %s.\n", wined3d_debug_location(map_binding));
        wined3d_texture_invalidate_location(dst_texture, dst_sub_resource_idx, ~map_binding);
        wined3d_texture_get_pitch(dst_texture, texture_level, &dst_map.row_pitch, &dst_map.slice_pitch);
        wined3d_texture_get_memory(dst_texture, dst_sub_resource_idx, &dst_data, map_binding);
        dst_map.data = context_map_bo_address(context, &dst_data,
                dst_texture->sub_resources[dst_sub_resource_idx].size, GL_PIXEL_UNPACK_BUFFER, WINED3D_MAP_WRITE);
    }
    flags &= ~WINED3D_BLT_RAW;

    bpp = dst_format->byte_count;
    src_height = src_box->bottom - src_box->top;
    src_width = src_box->right - src_box->left;
    dst_height = dst_box->bottom - dst_box->top;
    dst_width = dst_box->right - dst_box->left;
    row_byte_count = dst_width * bpp;

    sbase = (BYTE *)src_map.data
            + ((src_box->top / src_format->block_height) * src_map.row_pitch)
            + ((src_box->left / src_format->block_width) * src_format->block_byte_count);
    dbuf = (BYTE *)dst_map.data
            + ((dst_box->top / dst_format->block_height) * dst_map.row_pitch)
            + ((dst_box->left / dst_format->block_width) * dst_format->block_byte_count);

    if (src_fmt_flags & dst_fmt_flags & WINED3DFMT_FLAG_BLOCKS)
    {
        TRACE("%s -> %s copy.\n", debug_d3dformat(src_format->id), debug_d3dformat(dst_format->id));

        if (same_sub_resource)
        {
            FIXME("Only plain blits supported on compressed surfaces.\n");
            hr = E_NOTIMPL;
            goto release;
        }

        if (src_height != dst_height || src_width != dst_width)
        {
            WARN("Stretching not supported on compressed surfaces.\n");
            hr = WINED3DERR_INVALIDCALL;
            goto release;
        }

        hr = surface_cpu_blt_compressed(sbase, dbuf,
                src_map.row_pitch, dst_map.row_pitch, dst_width, dst_height,
                src_format, flags, fx);
        goto release;
    }

    if (filter != WINED3D_TEXF_NONE && filter != WINED3D_TEXF_POINT
            && (src_width != dst_width || src_height != dst_height))
    {
        /* Can happen when d3d9 apps do a StretchRect() call which isn't handled in GL. */
        static int once;
        if (!once++) FIXME("Filter %s not supported in software blit.\n", debug_d3dtexturefiltertype(filter));
    }

    xinc = (src_width << 16) / dst_width;
    yinc = (src_height << 16) / dst_height;

    if (!flags)
    {
        /* No effects, we can cheat here. */
        if (dst_width == src_width)
        {
            if (dst_height == src_height)
            {
                /* No stretching in either direction. This needs to be as fast
                 * as possible. */
                sbuf = sbase;

                /* Check for overlapping surfaces. */
                if (!same_sub_resource || dst_box->top < src_box->top
                        || dst_box->right <= src_box->left || src_box->right <= dst_box->left)
                {
                    /* No overlap, or dst above src, so copy from top downwards. */
                    for (y = 0; y < dst_height; ++y)
                    {
                        memcpy(dbuf, sbuf, row_byte_count);
                        sbuf += src_map.row_pitch;
                        dbuf += dst_map.row_pitch;
                    }
                }
                else if (dst_box->top > src_box->top)
                {
                    /* Copy from bottom upwards. */
                    sbuf += src_map.row_pitch * dst_height;
                    dbuf += dst_map.row_pitch * dst_height;
                    for (y = 0; y < dst_height; ++y)
                    {
                        sbuf -= src_map.row_pitch;
                        dbuf -= dst_map.row_pitch;
                        memcpy(dbuf, sbuf, row_byte_count);
                    }
                }
                else
                {
                    /* Src and dst overlapping on the same line, use memmove. */
                    for (y = 0; y < dst_height; ++y)
                    {
                        memmove(dbuf, sbuf, row_byte_count);
                        sbuf += src_map.row_pitch;
                        dbuf += dst_map.row_pitch;
                    }
                }
            }
            else
            {
                /* Stretching in y direction only. */
                for (y = sy = 0; y < dst_height; ++y, sy += yinc)
                {
                    sbuf = sbase + (sy >> 16) * src_map.row_pitch;
                    memcpy(dbuf, sbuf, row_byte_count);
                    dbuf += dst_map.row_pitch;
                }
            }
        }
        else
        {
            /* Stretching in X direction. */
            unsigned int last_sy = ~0u;
            for (y = sy = 0; y < dst_height; ++y, sy += yinc)
            {
                sbuf = sbase + (sy >> 16) * src_map.row_pitch;

                if ((sy >> 16) == (last_sy >> 16))
                {
                    /* This source row is the same as last source row -
                     * Copy the already stretched row. */
                    memcpy(dbuf, dbuf - dst_map.row_pitch, row_byte_count);
                }
                else
                {
#define STRETCH_ROW(type) \
do { \
    const type *s = (const type *)sbuf; \
    type *d = (type *)dbuf; \
    for (x = sx = 0; x < dst_width; ++x, sx += xinc) \
        d[x] = s[sx >> 16]; \
} while(0)

                    switch(bpp)
                    {
                        case 1:
                            STRETCH_ROW(BYTE);
                            break;
                        case 2:
                            STRETCH_ROW(WORD);
                            break;
                        case 4:
                            STRETCH_ROW(DWORD);
                            break;
                        case 3:
                        {
                            const BYTE *s;
                            BYTE *d = dbuf;
                            for (x = sx = 0; x < dst_width; x++, sx+= xinc)
                            {
                                DWORD pixel;

                                s = sbuf + 3 * (sx >> 16);
                                pixel = s[0] | (s[1] << 8) | (s[2] << 16);
                                d[0] = (pixel      ) & 0xff;
                                d[1] = (pixel >>  8) & 0xff;
                                d[2] = (pixel >> 16) & 0xff;
                                d += 3;
                            }
                            break;
                        }
                        default:
                            FIXME("Stretched blit not implemented for bpp %u.\n", bpp * 8);
                            hr = WINED3DERR_NOTAVAILABLE;
                            goto error;
                    }
#undef STRETCH_ROW
                }
                dbuf += dst_map.row_pitch;
                last_sy = sy;
            }
        }
    }
    else
    {
        LONG dstyinc = dst_map.row_pitch, dstxinc = bpp;
        DWORD keylow = 0xffffffff, keyhigh = 0, keymask = 0xffffffff;
        DWORD destkeylow = 0x0, destkeyhigh = 0xffffffff, destkeymask = 0xffffffff;
        if (flags & (WINED3D_BLT_SRC_CKEY | WINED3D_BLT_DST_CKEY
                | WINED3D_BLT_SRC_CKEY_OVERRIDE | WINED3D_BLT_DST_CKEY_OVERRIDE))
        {
            /* The color keying flags are checked for correctness in ddraw. */
            if (flags & WINED3D_BLT_SRC_CKEY)
            {
                keylow  = src_texture->async.src_blt_color_key.color_space_low_value;
                keyhigh = src_texture->async.src_blt_color_key.color_space_high_value;
            }
            else if (flags & WINED3D_BLT_SRC_CKEY_OVERRIDE)
            {
                keylow = fx->src_color_key.color_space_low_value;
                keyhigh = fx->src_color_key.color_space_high_value;
            }

            if (flags & WINED3D_BLT_DST_CKEY)
            {
                /* Destination color keys are taken from the source surface! */
                destkeylow = src_texture->async.dst_blt_color_key.color_space_low_value;
                destkeyhigh = src_texture->async.dst_blt_color_key.color_space_high_value;
            }
            else if (flags & WINED3D_BLT_DST_CKEY_OVERRIDE)
            {
                destkeylow = fx->dst_color_key.color_space_low_value;
                destkeyhigh = fx->dst_color_key.color_space_high_value;
            }

            if (bpp == 1)
            {
                keymask = 0xff;
            }
            else
            {
                DWORD masks[3];
                get_color_masks(src_format, masks);
                keymask = masks[0] | masks[1] | masks[2];
            }
            flags &= ~(WINED3D_BLT_SRC_CKEY | WINED3D_BLT_DST_CKEY
                    | WINED3D_BLT_SRC_CKEY_OVERRIDE | WINED3D_BLT_DST_CKEY_OVERRIDE);
        }

        if (flags & WINED3D_BLT_FX)
        {
            BYTE *dTopLeft, *dTopRight, *dBottomLeft, *dBottomRight, *tmp;
            LONG tmpxy;
            dTopLeft     = dbuf;
            dTopRight    = dbuf + ((dst_width - 1) * bpp);
            dBottomLeft  = dTopLeft + ((dst_height - 1) * dst_map.row_pitch);
            dBottomRight = dBottomLeft + ((dst_width - 1) * bpp);

            if (fx->fx & WINEDDBLTFX_ARITHSTRETCHY)
            {
                /* I don't think we need to do anything about this flag. */
                WARN("Nothing done for WINEDDBLTFX_ARITHSTRETCHY.\n");
            }
            if (fx->fx & WINEDDBLTFX_MIRRORLEFTRIGHT)
            {
                tmp          = dTopRight;
                dTopRight    = dTopLeft;
                dTopLeft     = tmp;
                tmp          = dBottomRight;
                dBottomRight = dBottomLeft;
                dBottomLeft  = tmp;
                dstxinc = dstxinc * -1;
            }
            if (fx->fx & WINEDDBLTFX_MIRRORUPDOWN)
            {
                tmp          = dTopLeft;
                dTopLeft     = dBottomLeft;
                dBottomLeft  = tmp;
                tmp          = dTopRight;
                dTopRight    = dBottomRight;
                dBottomRight = tmp;
                dstyinc = dstyinc * -1;
            }
            if (fx->fx & WINEDDBLTFX_NOTEARING)
            {
                /* I don't think we need to do anything about this flag. */
                WARN("Nothing done for WINEDDBLTFX_NOTEARING.\n");
            }
            if (fx->fx & WINEDDBLTFX_ROTATE180)
            {
                tmp          = dBottomRight;
                dBottomRight = dTopLeft;
                dTopLeft     = tmp;
                tmp          = dBottomLeft;
                dBottomLeft  = dTopRight;
                dTopRight    = tmp;
                dstxinc = dstxinc * -1;
                dstyinc = dstyinc * -1;
            }
            if (fx->fx & WINEDDBLTFX_ROTATE270)
            {
                tmp          = dTopLeft;
                dTopLeft     = dBottomLeft;
                dBottomLeft  = dBottomRight;
                dBottomRight = dTopRight;
                dTopRight    = tmp;
                tmpxy   = dstxinc;
                dstxinc = dstyinc;
                dstyinc = tmpxy;
                dstxinc = dstxinc * -1;
            }
            if (fx->fx & WINEDDBLTFX_ROTATE90)
            {
                tmp          = dTopLeft;
                dTopLeft     = dTopRight;
                dTopRight    = dBottomRight;
                dBottomRight = dBottomLeft;
                dBottomLeft  = tmp;
                tmpxy   = dstxinc;
                dstxinc = dstyinc;
                dstyinc = tmpxy;
                dstyinc = dstyinc * -1;
            }
            if (fx->fx & WINEDDBLTFX_ZBUFFERBASEDEST)
            {
                /* I don't think we need to do anything about this flag. */
                WARN("Nothing done for WINEDDBLTFX_ZBUFFERBASEDEST.\n");
            }
            dbuf = dTopLeft;
            flags &= ~(WINED3D_BLT_FX);
        }

#define COPY_COLORKEY_FX(type) \
do { \
    const type *s; \
    type *d = (type *)dbuf, *dx, tmp; \
    for (y = sy = 0; y < dst_height; ++y, sy += yinc) \
    { \
        s = (const type *)(sbase + (sy >> 16) * src_map.row_pitch); \
        dx = d; \
        for (x = sx = 0; x < dst_width; ++x, sx += xinc) \
        { \
            tmp = s[sx >> 16]; \
            if (((tmp & keymask) < keylow || (tmp & keymask) > keyhigh) \
                    && ((dx[0] & destkeymask) >= destkeylow && (dx[0] & destkeymask) <= destkeyhigh)) \
            { \
                dx[0] = tmp; \
            } \
            dx = (type *)(((BYTE *)dx) + dstxinc); \
        } \
        d = (type *)(((BYTE *)d) + dstyinc); \
    } \
} while(0)

        switch (bpp)
        {
            case 1:
                COPY_COLORKEY_FX(BYTE);
                break;
            case 2:
                COPY_COLORKEY_FX(WORD);
                break;
            case 4:
                COPY_COLORKEY_FX(DWORD);
                break;
            case 3:
            {
                const BYTE *s;
                BYTE *d = dbuf, *dx;
                for (y = sy = 0; y < dst_height; ++y, sy += yinc)
                {
                    sbuf = sbase + (sy >> 16) * src_map.row_pitch;
                    dx = d;
                    for (x = sx = 0; x < dst_width; ++x, sx+= xinc)
                    {
                        DWORD pixel, dpixel = 0;
                        s = sbuf + 3 * (sx>>16);
                        pixel = s[0] | (s[1] << 8) | (s[2] << 16);
                        dpixel = dx[0] | (dx[1] << 8 ) | (dx[2] << 16);
                        if (((pixel & keymask) < keylow || (pixel & keymask) > keyhigh)
                                && ((dpixel & keymask) >= destkeylow || (dpixel & keymask) <= keyhigh))
                        {
                            dx[0] = (pixel      ) & 0xff;
                            dx[1] = (pixel >>  8) & 0xff;
                            dx[2] = (pixel >> 16) & 0xff;
                        }
                        dx += dstxinc;
                    }
                    d += dstyinc;
                }
                break;
            }
            default:
                FIXME("%s color-keyed blit not implemented for bpp %u.\n",
                      (flags & WINED3D_BLT_SRC_CKEY) ? "Source" : "Destination", bpp * 8);
                hr = WINED3DERR_NOTAVAILABLE;
                goto error;
#undef COPY_COLORKEY_FX
        }
    }

error:
    if (flags)
        FIXME("    Unsupported flags %#x.\n", flags);

release:
    context_unmap_bo_address(context, &dst_data, GL_PIXEL_UNPACK_BUFFER);
    if (!same_sub_resource)
        context_unmap_bo_address(context, &src_data, GL_PIXEL_UNPACK_BUFFER);
    if (SUCCEEDED(hr) && dst_texture->swapchain && dst_texture->swapchain->front_buffer == dst_texture)
    {
        SetRect(&dst_texture->swapchain->front_buffer_update,
                dst_box->left, dst_box->top, dst_box->right, dst_box->bottom);
        dst_texture->swapchain->swapchain_ops->swapchain_frontbuffer_updated(dst_texture->swapchain);
    }
    if (converted_texture)
        wined3d_texture_decref(converted_texture);
    if (context)
        context_release(context);

    return hr;
}