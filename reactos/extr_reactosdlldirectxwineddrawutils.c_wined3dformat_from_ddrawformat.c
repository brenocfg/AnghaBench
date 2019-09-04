#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum wined3d_format_id { ____Placeholder_wined3d_format_id } wined3d_format_id ;
struct TYPE_13__ {int dwBBitMask; int dwBumpLuminanceBitMask; } ;
struct TYPE_12__ {int dwGBitMask; int dwZBitMask; int dwBumpDvBitMask; } ;
struct TYPE_11__ {int dwRBitMask; int dwStencilBitDepth; int dwBumpDuBitMask; } ;
struct TYPE_10__ {int dwRGBBitCount; int dwAlphaBitDepth; int dwLuminanceBitCount; int dwZBufferBitDepth; int dwBumpBitCount; } ;
struct TYPE_9__ {int dwRGBAlphaBitMask; } ;
struct TYPE_14__ {int dwFlags; int dwFourCC; TYPE_5__ u4; TYPE_4__ u3; TYPE_3__ u2; TYPE_2__ u1; TYPE_1__ u5; } ;
typedef  TYPE_6__ DDPIXELFORMAT ;

/* Variables and functions */
 int DDPF_ALPHA ; 
 int DDPF_ALPHAPIXELS ; 
 int DDPF_BUMPDUDV ; 
 int DDPF_FOURCC ; 
 int DDPF_LUMINANCE ; 
 int DDPF_PALETTEINDEXED1 ; 
 int DDPF_PALETTEINDEXED2 ; 
 int DDPF_PALETTEINDEXED4 ; 
 int DDPF_PALETTEINDEXED8 ; 
 int DDPF_RGB ; 
 int DDPF_STENCILBUFFER ; 
 int DDPF_ZBUFFER ; 
 int /*<<< orphan*/  DDRAW_dump_pixelformat (TYPE_6__ const*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int WINED3DFMT_A8_UNORM ; 
 int WINED3DFMT_B2G3R3A8_UNORM ; 
 int WINED3DFMT_B2G3R3_UNORM ; 
 int WINED3DFMT_B4G4R4A4_UNORM ; 
 int WINED3DFMT_B4G4R4X4_UNORM ; 
 int WINED3DFMT_B5G5R5A1_UNORM ; 
 int WINED3DFMT_B5G5R5X1_UNORM ; 
 int WINED3DFMT_B5G6R5_UNORM ; 
 int WINED3DFMT_B8G8R8A8_UNORM ; 
 int WINED3DFMT_B8G8R8X8_UNORM ; 
 int WINED3DFMT_B8G8R8_UNORM ; 
 int WINED3DFMT_D16_UNORM ; 
 int WINED3DFMT_D24_UNORM_S8_UINT ; 
 int WINED3DFMT_D32_UNORM ; 
 int WINED3DFMT_L4A4_UNORM ; 
 int WINED3DFMT_L8A8_UNORM ; 
 int WINED3DFMT_L8_UNORM ; 
 int WINED3DFMT_P8_UINT ; 
 int WINED3DFMT_R5G5_SNORM_L6_UNORM ; 
 int WINED3DFMT_R8G8_SNORM ; 
 int WINED3DFMT_R8G8_SNORM_L8X8_UNORM ; 
 int WINED3DFMT_S1_UINT_D15_UNORM ; 
 int WINED3DFMT_S4X4_UINT_D24_UNORM ; 
 int WINED3DFMT_UNKNOWN ; 
 int WINED3DFMT_X8D24_UNORM ; 
 int /*<<< orphan*/  ddraw ; 

enum wined3d_format_id wined3dformat_from_ddrawformat(const DDPIXELFORMAT *DDPixelFormat)
{
    TRACE("Convert a DirectDraw Pixelformat to a WineD3D Pixelformat\n");
    if(TRACE_ON(ddraw))
    {
        DDRAW_dump_pixelformat(DDPixelFormat);
    }

    if(DDPixelFormat->dwFlags & DDPF_PALETTEINDEXED8)
    {
        return WINED3DFMT_P8_UINT;
    }
    else if(DDPixelFormat->dwFlags & (DDPF_PALETTEINDEXED1 | DDPF_PALETTEINDEXED2 | DDPF_PALETTEINDEXED4) )
    {
        FIXME("DDPF_PALETTEINDEXED1 to DDPF_PALETTEINDEXED4 are not supported by WineD3D (yet). Returning WINED3DFMT_P8\n");
        return WINED3DFMT_P8_UINT;
    }
    else if(DDPixelFormat->dwFlags & DDPF_RGB)
    {
        switch(DDPixelFormat->u1.dwRGBBitCount)
        {
            case 8:
                /* This is the only format that can match here */
                return WINED3DFMT_B2G3R3_UNORM;

            case 16:
                /* Read the Color masks */
                if( (DDPixelFormat->u2.dwRBitMask == 0xF800) &&
                    (DDPixelFormat->u3.dwGBitMask == 0x07E0) &&
                    (DDPixelFormat->u4.dwBBitMask == 0x001F) )
                {
                    return WINED3DFMT_B5G6R5_UNORM;
                }

                if( (DDPixelFormat->u2.dwRBitMask == 0x7C00) &&
                    (DDPixelFormat->u3.dwGBitMask == 0x03E0) &&
                    (DDPixelFormat->u4.dwBBitMask == 0x001F) )
                {
                    if( (DDPixelFormat->dwFlags & DDPF_ALPHAPIXELS) &&
                        (DDPixelFormat->u5.dwRGBAlphaBitMask == 0x8000))
                        return WINED3DFMT_B5G5R5A1_UNORM;
                    else
                        return WINED3DFMT_B5G5R5X1_UNORM;
                }

                if( (DDPixelFormat->u2.dwRBitMask == 0x0F00) &&
                    (DDPixelFormat->u3.dwGBitMask == 0x00F0) &&
                    (DDPixelFormat->u4.dwBBitMask == 0x000F) )
                {
                    if( (DDPixelFormat->dwFlags & DDPF_ALPHAPIXELS) &&
                        (DDPixelFormat->u5.dwRGBAlphaBitMask == 0xF000))
                        return WINED3DFMT_B4G4R4A4_UNORM;
                    else
                        return WINED3DFMT_B4G4R4X4_UNORM;
                }

                if( (DDPixelFormat->dwFlags & DDPF_ALPHAPIXELS) &&
                    (DDPixelFormat->u5.dwRGBAlphaBitMask == 0xFF00) &&
                    (DDPixelFormat->u2.dwRBitMask == 0x00E0) &&
                    (DDPixelFormat->u3.dwGBitMask == 0x001C) &&
                    (DDPixelFormat->u4.dwBBitMask == 0x0003) )
                {
                    return WINED3DFMT_B2G3R3A8_UNORM;
                }
                WARN("16 bit RGB Pixel format does not match.\n");
                return WINED3DFMT_UNKNOWN;

            case 24:
                return WINED3DFMT_B8G8R8_UNORM;

            case 32:
                /* Read the Color masks */
                if( (DDPixelFormat->u2.dwRBitMask == 0x00FF0000) &&
                    (DDPixelFormat->u3.dwGBitMask == 0x0000FF00) &&
                    (DDPixelFormat->u4.dwBBitMask == 0x000000FF) )
                {
                    if( (DDPixelFormat->dwFlags & DDPF_ALPHAPIXELS) &&
                        (DDPixelFormat->u5.dwRGBAlphaBitMask == 0xFF000000))
                        return WINED3DFMT_B8G8R8A8_UNORM;
                    else
                        return WINED3DFMT_B8G8R8X8_UNORM;

                }
                WARN("32 bit RGB pixel format does not match.\n");
                return WINED3DFMT_UNKNOWN;

            default:
                WARN("Invalid dwRGBBitCount in Pixelformat structure.\n");
                return WINED3DFMT_UNKNOWN;
        }
    }
    else if( (DDPixelFormat->dwFlags & DDPF_ALPHA) )
    {
        /* Alpha only Pixelformat */
        switch(DDPixelFormat->u1.dwAlphaBitDepth)
        {
            case 8:
                return WINED3DFMT_A8_UNORM;

            default:
                WARN("Invalid AlphaBitDepth in Alpha-Only Pixelformat.\n");
                return WINED3DFMT_UNKNOWN;
        }
    }
    else if(DDPixelFormat->dwFlags & DDPF_LUMINANCE)
    {
        /* Luminance-only or luminance-alpha */
        if(DDPixelFormat->dwFlags & DDPF_ALPHAPIXELS)
        {
            /* Luminance with Alpha */
            switch(DDPixelFormat->u1.dwLuminanceBitCount)
            {
                case 4:
                    if(DDPixelFormat->u1.dwAlphaBitDepth == 4)
                        return WINED3DFMT_L4A4_UNORM;
                    WARN("Unknown Alpha / Luminance bit depth combination.\n");
                    return WINED3DFMT_UNKNOWN;

                case 6:
                    FIXME("A luminance Pixelformat shouldn't have 6 luminance bits. Returning D3DFMT_L6V5U5 for now.\n");
                    return WINED3DFMT_R5G5_SNORM_L6_UNORM;

                case 8:
                    if(DDPixelFormat->u1.dwAlphaBitDepth == 8)
                        return WINED3DFMT_L8A8_UNORM;
                    WARN("Unknown Alpha / Lumincase bit depth combination.\n");
                    return WINED3DFMT_UNKNOWN;
            }
        }
        else
        {
            /* Luminance-only */
            switch(DDPixelFormat->u1.dwLuminanceBitCount)
            {
                case 6:
                    FIXME("A luminance Pixelformat shouldn't have 6 luminance bits. Returning D3DFMT_L6V5U5 for now.\n");
                    return WINED3DFMT_R5G5_SNORM_L6_UNORM;

                case 8:
                    return WINED3DFMT_L8_UNORM;

                default:
                    WARN("Unknown luminance-only bit depth 0x%x.\n", DDPixelFormat->u1.dwLuminanceBitCount);
                    return WINED3DFMT_UNKNOWN;
             }
        }
    }
    else if(DDPixelFormat->dwFlags & DDPF_ZBUFFER)
    {
        /* Z buffer */
        if(DDPixelFormat->dwFlags & DDPF_STENCILBUFFER)
        {
            switch(DDPixelFormat->u1.dwZBufferBitDepth)
            {
                case 16:
                    if (DDPixelFormat->u2.dwStencilBitDepth == 1) return WINED3DFMT_S1_UINT_D15_UNORM;
                    WARN("Unknown depth stencil format: 16 z bits, %u stencil bits.\n",
                            DDPixelFormat->u2.dwStencilBitDepth);
                    return WINED3DFMT_UNKNOWN;

                case 32:
                    if (DDPixelFormat->u2.dwStencilBitDepth == 8) return WINED3DFMT_D24_UNORM_S8_UINT;
                    else if (DDPixelFormat->u2.dwStencilBitDepth == 4) return WINED3DFMT_S4X4_UINT_D24_UNORM;
                    WARN("Unknown depth stencil format: 32 z bits, %u stencil bits.\n",
                            DDPixelFormat->u2.dwStencilBitDepth);
                    return WINED3DFMT_UNKNOWN;

                default:
                    WARN("Unknown depth stencil format: %u z bits, %u stencil bits.\n",
                            DDPixelFormat->u1.dwZBufferBitDepth, DDPixelFormat->u2.dwStencilBitDepth);
                    return WINED3DFMT_UNKNOWN;
            }
        }
        else
        {
            switch(DDPixelFormat->u1.dwZBufferBitDepth)
            {
                case 16:
                    return WINED3DFMT_D16_UNORM;

                case 24:
                    return WINED3DFMT_X8D24_UNORM;

                case 32:
                    if (DDPixelFormat->u3.dwZBitMask == 0x00FFFFFF) return WINED3DFMT_X8D24_UNORM;
                    else if (DDPixelFormat->u3.dwZBitMask == 0xFFFFFF00) return WINED3DFMT_X8D24_UNORM;
                    else if (DDPixelFormat->u3.dwZBitMask == 0xFFFFFFFF) return WINED3DFMT_D32_UNORM;
                    WARN("Unknown depth-only format: 32 z bits, mask 0x%08x\n",
                            DDPixelFormat->u3.dwZBitMask);
                    return WINED3DFMT_UNKNOWN;

                default:
                    WARN("Unknown depth-only format: %u z bits, mask 0x%08x\n",
                            DDPixelFormat->u1.dwZBufferBitDepth, DDPixelFormat->u3.dwZBitMask);
                    return WINED3DFMT_UNKNOWN;
            }
        }
    }
    else if(DDPixelFormat->dwFlags & DDPF_FOURCC)
    {
        return DDPixelFormat->dwFourCC;
    }
    else if(DDPixelFormat->dwFlags & DDPF_BUMPDUDV)
    {
        if( (DDPixelFormat->u1.dwBumpBitCount         == 16        ) &&
            (DDPixelFormat->u2.dwBumpDuBitMask        == 0x000000ff) &&
            (DDPixelFormat->u3.dwBumpDvBitMask        == 0x0000ff00) &&
            (DDPixelFormat->u4.dwBumpLuminanceBitMask == 0x00000000) )
        {
            return WINED3DFMT_R8G8_SNORM;
        }
        else if ( (DDPixelFormat->u1.dwBumpBitCount         == 16        ) &&
                  (DDPixelFormat->u2.dwBumpDuBitMask        == 0x0000001f) &&
                  (DDPixelFormat->u3.dwBumpDvBitMask        == 0x000003e0) &&
                  (DDPixelFormat->u4.dwBumpLuminanceBitMask == 0x0000fc00) )
        {
            return WINED3DFMT_R5G5_SNORM_L6_UNORM;
        }
        else if ( (DDPixelFormat->u1.dwBumpBitCount         == 32        ) &&
                  (DDPixelFormat->u2.dwBumpDuBitMask        == 0x000000ff) &&
                  (DDPixelFormat->u3.dwBumpDvBitMask        == 0x0000ff00) &&
                  (DDPixelFormat->u4.dwBumpLuminanceBitMask == 0x00ff0000) )
        {
            return WINED3DFMT_R8G8_SNORM_L8X8_UNORM;
        }
    }

    WARN("Unknown Pixelformat.\n");
    return WINED3DFMT_UNKNOWN;
}