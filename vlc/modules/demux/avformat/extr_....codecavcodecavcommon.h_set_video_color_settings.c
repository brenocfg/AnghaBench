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
struct TYPE_5__ {int color_range; int space; int transfer; int primaries; int chroma_location; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_6__ {int /*<<< orphan*/  chroma_sample_location; int /*<<< orphan*/  color_primaries; void* color_trc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  color_range; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVCHROMA_LOC_BOTTOM ; 
 int /*<<< orphan*/  AVCHROMA_LOC_BOTTOMLEFT ; 
 int /*<<< orphan*/  AVCHROMA_LOC_CENTER ; 
 int /*<<< orphan*/  AVCHROMA_LOC_LEFT ; 
 int /*<<< orphan*/  AVCHROMA_LOC_TOP ; 
 int /*<<< orphan*/  AVCHROMA_LOC_TOPLEFT ; 
 int /*<<< orphan*/  AVCHROMA_LOC_UNSPECIFIED ; 
 int /*<<< orphan*/  AVCOL_PRI_BT2020 ; 
 int /*<<< orphan*/  AVCOL_PRI_BT470BG ; 
 int /*<<< orphan*/  AVCOL_PRI_BT470M ; 
 int /*<<< orphan*/  AVCOL_PRI_BT709 ; 
 int /*<<< orphan*/  AVCOL_PRI_SMPTE170M ; 
 int /*<<< orphan*/  AVCOL_PRI_UNSPECIFIED ; 
 int /*<<< orphan*/  AVCOL_RANGE_JPEG ; 
 int /*<<< orphan*/  AVCOL_RANGE_MPEG ; 
 int /*<<< orphan*/  AVCOL_RANGE_UNSPECIFIED ; 
 int /*<<< orphan*/  AVCOL_SPC_BT2020_CL ; 
 int /*<<< orphan*/  AVCOL_SPC_BT470BG ; 
 int /*<<< orphan*/  AVCOL_SPC_BT709 ; 
 int /*<<< orphan*/  AVCOL_SPC_UNSPECIFIED ; 
 void* AVCOL_TRC_BT709 ; 
 void* AVCOL_TRC_GAMMA22 ; 
 void* AVCOL_TRC_GAMMA28 ; 
 void* AVCOL_TRC_LINEAR ; 
 void* AVCOL_TRC_SMPTE240M ; 
 void* AVCOL_TRC_SMPTEST2084 ; 
 void* AVCOL_TRC_UNSPECIFIED ; 
#define  CHROMA_LOCATION_BOTTOM_CENTER 151 
#define  CHROMA_LOCATION_BOTTOM_LEFT 150 
#define  CHROMA_LOCATION_CENTER 149 
#define  CHROMA_LOCATION_LEFT 148 
#define  CHROMA_LOCATION_TOP_CENTER 147 
#define  CHROMA_LOCATION_TOP_LEFT 146 
#define  COLOR_PRIMARIES_BT2020 145 
#define  COLOR_PRIMARIES_BT601_525 144 
#define  COLOR_PRIMARIES_BT601_625 143 
#define  COLOR_PRIMARIES_BT709 142 
#define  COLOR_PRIMARIES_FCC1953 141 
#define  COLOR_RANGE_FULL 140 
#define  COLOR_RANGE_LIMITED 139 
#define  COLOR_RANGE_UNDEF 138 
#define  COLOR_SPACE_BT2020 137 
#define  COLOR_SPACE_BT601 136 
#define  COLOR_SPACE_BT709 135 
#define  TRANSFER_FUNC_BT470_BG 134 
#define  TRANSFER_FUNC_BT470_M 133 
#define  TRANSFER_FUNC_BT709 132 
#define  TRANSFER_FUNC_LINEAR 131 
#define  TRANSFER_FUNC_SMPTE_240 130 
#define  TRANSFER_FUNC_SMPTE_ST2084 129 
#define  TRANSFER_FUNC_SRGB 128 

__attribute__((used)) static inline void set_video_color_settings( const video_format_t *p_fmt, AVCodecContext *p_context )
{
    switch( p_fmt->color_range )
    {
    case COLOR_RANGE_FULL:
        p_context->color_range = AVCOL_RANGE_JPEG;
        break;
    case COLOR_RANGE_LIMITED:
        p_context->color_range = AVCOL_RANGE_MPEG;
    case COLOR_RANGE_UNDEF: /* do nothing */
        break;
    default:
        p_context->color_range = AVCOL_RANGE_UNSPECIFIED;
        break;
    }

    switch( p_fmt->space )
    {
        case COLOR_SPACE_BT709:
            p_context->colorspace = AVCOL_SPC_BT709;
            break;
        case COLOR_SPACE_BT601:
            p_context->colorspace = AVCOL_SPC_BT470BG;
            break;
        case COLOR_SPACE_BT2020:
            p_context->colorspace = AVCOL_SPC_BT2020_CL;
            break;
        default:
            p_context->colorspace = AVCOL_SPC_UNSPECIFIED;
            break;
    }

    switch( p_fmt->transfer )
    {
        case TRANSFER_FUNC_LINEAR:
            p_context->color_trc = AVCOL_TRC_LINEAR;
            break;
        case TRANSFER_FUNC_SRGB:
            p_context->color_trc = AVCOL_TRC_GAMMA22;
            break;
        case TRANSFER_FUNC_BT470_BG:
            p_context->color_trc = AVCOL_TRC_GAMMA28;
            break;
        case TRANSFER_FUNC_BT470_M:
            p_context->color_trc = AVCOL_TRC_GAMMA22;
            break;
        case TRANSFER_FUNC_BT709:
            p_context->color_trc = AVCOL_TRC_BT709;
            break;
        case TRANSFER_FUNC_SMPTE_ST2084:
            p_context->color_trc = AVCOL_TRC_SMPTEST2084;
            break;
        case TRANSFER_FUNC_SMPTE_240:
            p_context->color_trc = AVCOL_TRC_SMPTE240M;
            break;
        default:
            p_context->color_trc = AVCOL_TRC_UNSPECIFIED;
            break;
    }
    switch( p_fmt->primaries )
    {
        case COLOR_PRIMARIES_BT601_525:
            p_context->color_primaries = AVCOL_PRI_SMPTE170M;
            break;
        case COLOR_PRIMARIES_BT601_625:
            p_context->color_primaries = AVCOL_PRI_BT470BG;
            break;
        case COLOR_PRIMARIES_BT709:
            p_context->color_primaries = AVCOL_PRI_BT709;
            break;
        case COLOR_PRIMARIES_BT2020:
            p_context->color_primaries = AVCOL_PRI_BT2020;
            break;
        case COLOR_PRIMARIES_FCC1953:
            p_context->color_primaries = AVCOL_PRI_BT470M;
            break;
        default:
            p_context->color_primaries = AVCOL_PRI_UNSPECIFIED;
            break;
    }
    switch( p_fmt->chroma_location )
    {
        case CHROMA_LOCATION_LEFT:
            p_context->chroma_sample_location = AVCHROMA_LOC_LEFT;
            break;
        case CHROMA_LOCATION_CENTER:
            p_context->chroma_sample_location = AVCHROMA_LOC_CENTER;
            break;
        case CHROMA_LOCATION_TOP_LEFT:
            p_context->chroma_sample_location = AVCHROMA_LOC_TOPLEFT;
            break;
        case CHROMA_LOCATION_TOP_CENTER:
            p_context->chroma_sample_location = AVCHROMA_LOC_TOP;
            break;
        case CHROMA_LOCATION_BOTTOM_LEFT:
            p_context->chroma_sample_location = AVCHROMA_LOC_BOTTOMLEFT;
            break;
        case CHROMA_LOCATION_BOTTOM_CENTER:
            p_context->chroma_sample_location = AVCHROMA_LOC_BOTTOM;
            break;
        default:
            p_context->chroma_sample_location = AVCHROMA_LOC_UNSPECIFIED;
            break;
    }
}