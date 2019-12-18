#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ color_range; int space; int primaries; int transfer; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_6__ {int /*<<< orphan*/  VideoLighting; int /*<<< orphan*/  VideoTransferFunction; int /*<<< orphan*/  VideoPrimaries; int /*<<< orphan*/  VideoTransferMatrix; int /*<<< orphan*/  NominalRange; } ;
typedef  TYPE_2__ DXVA2_ExtendedFormat ;

/* Variables and functions */
#define  COLOR_PRIMARIES_BT470_BG 135 
#define  COLOR_PRIMARIES_BT709 134 
#define  COLOR_PRIMARIES_SMTPE_170 133 
 scalar_t__ COLOR_RANGE_FULL ; 
#define  COLOR_SPACE_BT601 132 
#define  COLOR_SPACE_BT709 131 
 int /*<<< orphan*/  DXVA2_NominalRange_0_255 ; 
 int /*<<< orphan*/  DXVA2_NominalRange_16_235 ; 
 int /*<<< orphan*/  DXVA2_VideoLighting_Unknown ; 
 int /*<<< orphan*/  DXVA2_VideoLighting_dim ; 
 int /*<<< orphan*/  DXVA2_VideoPrimaries_BT470_2_SysBG ; 
 int /*<<< orphan*/  DXVA2_VideoPrimaries_BT709 ; 
 int /*<<< orphan*/  DXVA2_VideoPrimaries_SMPTE170M ; 
 int /*<<< orphan*/  DXVA2_VideoPrimaries_Unknown ; 
 int /*<<< orphan*/  DXVA2_VideoTransFunc_240M ; 
 int /*<<< orphan*/  DXVA2_VideoTransFunc_709 ; 
 int /*<<< orphan*/  DXVA2_VideoTransFunc_Unknown ; 
 int /*<<< orphan*/  DXVA2_VideoTransFunc_sRGB ; 
 int /*<<< orphan*/  DXVA2_VideoTransferMatrix_BT601 ; 
 int /*<<< orphan*/  DXVA2_VideoTransferMatrix_BT709 ; 
 int /*<<< orphan*/  DXVA2_VideoTransferMatrix_Unknown ; 
#define  TRANSFER_FUNC_BT709 130 
#define  TRANSFER_FUNC_SMPTE_240 129 
#define  TRANSFER_FUNC_SRGB 128 

__attribute__((used)) static void FillExtendedFormat( const video_format_t *p_fmt,
                                DXVA2_ExtendedFormat *out )
{
    out->NominalRange = p_fmt->color_range == COLOR_RANGE_FULL ?
                DXVA2_NominalRange_0_255 : DXVA2_NominalRange_16_235;
    switch (p_fmt->space)
    {
    case COLOR_SPACE_BT601:
        out->VideoTransferMatrix = DXVA2_VideoTransferMatrix_BT601;
        break;
    case COLOR_SPACE_BT709:
        out->VideoTransferMatrix = DXVA2_VideoTransferMatrix_BT709;
        break;
    default:
        out->VideoTransferMatrix = DXVA2_VideoTransferMatrix_Unknown;
        break;
    }
    out->VideoLighting = DXVA2_VideoLighting_Unknown;
    switch (p_fmt->primaries)
    {
    case COLOR_PRIMARIES_BT709:
        out->VideoPrimaries = DXVA2_VideoPrimaries_BT709;
        break;
    case COLOR_PRIMARIES_BT470_BG:
        out->VideoPrimaries = DXVA2_VideoPrimaries_BT470_2_SysBG;
        break;
    case COLOR_PRIMARIES_SMTPE_170:
        out->VideoPrimaries = DXVA2_VideoPrimaries_SMPTE170M;
        break;
    default:
        out->VideoPrimaries = DXVA2_VideoPrimaries_Unknown;
        break;
    }
    switch (p_fmt->transfer)
    {
    case TRANSFER_FUNC_BT709:
        out->VideoTransferFunction = DXVA2_VideoTransFunc_709;
        break;
    case TRANSFER_FUNC_SMPTE_240:
        out->VideoTransferFunction = DXVA2_VideoTransFunc_240M;
        break;
    case TRANSFER_FUNC_SRGB:
        out->VideoTransferFunction = DXVA2_VideoTransFunc_sRGB;
        break;
    default:
        out->VideoTransferFunction = DXVA2_VideoTransFunc_Unknown;
        break;
    }
    out->VideoLighting = DXVA2_VideoLighting_dim;
}