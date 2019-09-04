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
struct wined3d_format {int block_width; int block_height; int block_byte_count; int id; } ;
struct wined3d_blt_fx {scalar_t__ fx; } ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,...) ; 
#define  WINED3DFMT_DXT1 130 
#define  WINED3DFMT_DXT2 129 
#define  WINED3DFMT_DXT3 128 
 int WINED3D_BLT_FX ; 
 int /*<<< orphan*/  WINED3D_OK ; 
 scalar_t__ WINEDDBLTFX_MIRRORUPDOWN ; 
 int /*<<< orphan*/  debug_d3dformat (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static HRESULT surface_cpu_blt_compressed(const BYTE *src_data, BYTE *dst_data,
        UINT src_pitch, UINT dst_pitch, UINT update_w, UINT update_h,
        const struct wined3d_format *format, DWORD flags, const struct wined3d_blt_fx *fx)
{
    UINT row_block_count;
    const BYTE *src_row;
    BYTE *dst_row;
    UINT x, y;

    src_row = src_data;
    dst_row = dst_data;

    row_block_count = (update_w + format->block_width - 1) / format->block_width;

    if (!flags)
    {
        for (y = 0; y < update_h; y += format->block_height)
        {
            memcpy(dst_row, src_row, row_block_count * format->block_byte_count);
            src_row += src_pitch;
            dst_row += dst_pitch;
        }

        return WINED3D_OK;
    }

    if (flags == WINED3D_BLT_FX && fx->fx == WINEDDBLTFX_MIRRORUPDOWN)
    {
        src_row += (((update_h / format->block_height) - 1) * src_pitch);

        switch (format->id)
        {
            case WINED3DFMT_DXT1:
                for (y = 0; y < update_h; y += format->block_height)
                {
                    struct block
                    {
                        WORD color[2];
                        BYTE control_row[4];
                    };

                    const struct block *s = (const struct block *)src_row;
                    struct block *d = (struct block *)dst_row;

                    for (x = 0; x < row_block_count; ++x)
                    {
                        d[x].color[0] = s[x].color[0];
                        d[x].color[1] = s[x].color[1];
                        d[x].control_row[0] = s[x].control_row[3];
                        d[x].control_row[1] = s[x].control_row[2];
                        d[x].control_row[2] = s[x].control_row[1];
                        d[x].control_row[3] = s[x].control_row[0];
                    }
                    src_row -= src_pitch;
                    dst_row += dst_pitch;
                }
                return WINED3D_OK;

            case WINED3DFMT_DXT2:
            case WINED3DFMT_DXT3:
                for (y = 0; y < update_h; y += format->block_height)
                {
                    struct block
                    {
                        WORD alpha_row[4];
                        WORD color[2];
                        BYTE control_row[4];
                    };

                    const struct block *s = (const struct block *)src_row;
                    struct block *d = (struct block *)dst_row;

                    for (x = 0; x < row_block_count; ++x)
                    {
                        d[x].alpha_row[0] = s[x].alpha_row[3];
                        d[x].alpha_row[1] = s[x].alpha_row[2];
                        d[x].alpha_row[2] = s[x].alpha_row[1];
                        d[x].alpha_row[3] = s[x].alpha_row[0];
                        d[x].color[0] = s[x].color[0];
                        d[x].color[1] = s[x].color[1];
                        d[x].control_row[0] = s[x].control_row[3];
                        d[x].control_row[1] = s[x].control_row[2];
                        d[x].control_row[2] = s[x].control_row[1];
                        d[x].control_row[3] = s[x].control_row[0];
                    }
                    src_row -= src_pitch;
                    dst_row += dst_pitch;
                }
                return WINED3D_OK;

            default:
                FIXME("Compressed flip not implemented for format %s.\n",
                        debug_d3dformat(format->id));
                return E_NOTIMPL;
        }
    }

    FIXME("Unsupported blit on compressed surface (format %s, flags %#x, DDFX %#x).\n",
            debug_d3dformat(format->id), flags, flags & WINED3D_BLT_FX ? fx->fx : 0);

    return E_NOTIMPL;
}