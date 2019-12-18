#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  scalar_t__ vlc_fourcc_t ;
typedef  scalar_t__ uint8_t ;
struct TYPE_7__ {scalar_t__ fourcc; scalar_t__ bitsPerChannel; scalar_t__ widthDenominator; scalar_t__ heightDenominator; scalar_t__ formatTexture; scalar_t__* resourceFormat; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ d3d_format_t ;
struct TYPE_8__ {int /*<<< orphan*/  d3ddevice; } ;
typedef  TYPE_2__ d3d11_device_t ;
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ DXGI_FORMAT ;

/* Variables and functions */
 scalar_t__ CanReallyUseFormat (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  D3D11_FORMAT_SUPPORT_TEXTURE2D ; 
 scalar_t__ DXGI_FORMAT_UNKNOWN ; 
 scalar_t__ DeviceSupportsFormat (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* GetRenderFormatList () ; 
 scalar_t__ is_d3d11_opaque (scalar_t__) ; 
 scalar_t__ vlc_fourcc_IsYUV (scalar_t__) ; 

const d3d_format_t *FindD3D11Format(vlc_object_t *o,
                                    d3d11_device_t *d3d_dev,
                                    vlc_fourcc_t i_src_chroma,
                                    bool rgb_only,
                                    uint8_t bits_per_channel,
                                    uint8_t widthDenominator,
                                    uint8_t heightDenominator,
                                    bool allow_opaque,
                                    UINT supportFlags)
{
    supportFlags |= D3D11_FORMAT_SUPPORT_TEXTURE2D;
    for (const d3d_format_t *output_format = GetRenderFormatList();
         output_format->name != NULL; ++output_format)
    {
        if (i_src_chroma && i_src_chroma != output_format->fourcc)
            continue;
        if (bits_per_channel && bits_per_channel > output_format->bitsPerChannel)
            continue;
        if (!allow_opaque && is_d3d11_opaque(output_format->fourcc))
            continue;
        if (rgb_only && vlc_fourcc_IsYUV(output_format->fourcc))
            continue;
        if (widthDenominator && widthDenominator < output_format->widthDenominator)
            continue;
        if (heightDenominator && heightDenominator < output_format->heightDenominator)
            continue;

        DXGI_FORMAT textureFormat;
        if (output_format->formatTexture == DXGI_FORMAT_UNKNOWN)
            textureFormat = output_format->resourceFormat[0];
        else
            textureFormat = output_format->formatTexture;

        if( DeviceSupportsFormat( d3d_dev->d3ddevice, textureFormat, supportFlags ) &&
            CanReallyUseFormat(o, d3d_dev, output_format->fourcc, output_format->formatTexture) )
            return output_format;
    }
    return NULL;
}