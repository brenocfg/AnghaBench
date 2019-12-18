#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_16__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_multiview_mode_t ;
struct TYPE_20__ {int /*<<< orphan*/  MaxFALL; int /*<<< orphan*/  MaxCLL; } ;
struct TYPE_33__ {int /*<<< orphan*/  min_luminance; int /*<<< orphan*/  max_luminance; int /*<<< orphan*/ * white_point; int /*<<< orphan*/ * primaries; } ;
struct TYPE_22__ {TYPE_11__ lighting; TYPE_8__ mastering; int /*<<< orphan*/  multiview_mode; } ;
typedef  TYPE_13__ video_format_t ;
struct TYPE_21__ {int /*<<< orphan*/  MaxFALL; int /*<<< orphan*/  MaxCLL; } ;
struct TYPE_34__ {int /*<<< orphan*/  min_luminance; int /*<<< orphan*/  max_luminance; int /*<<< orphan*/ * white_point; int /*<<< orphan*/ * primaries; } ;
struct TYPE_32__ {int /*<<< orphan*/  type; } ;
struct TYPE_29__ {int /*<<< orphan*/  i_frames; } ;
struct TYPE_26__ {int /*<<< orphan*/  i_data; int /*<<< orphan*/  p_data; } ;
struct TYPE_27__ {TYPE_1__ cc; } ;
struct TYPE_28__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct TYPE_23__ {int i_type; TYPE_12__ content_light_lvl; TYPE_9__ colour_volume; TYPE_7__ frame_packing; TYPE_4__ recovery; TYPE_3__ itu_t35; int /*<<< orphan*/  p_bs; } ;
typedef  TYPE_14__ hxxx_sei_data_t ;
struct TYPE_19__ {TYPE_13__ video; } ;
struct TYPE_30__ {int /*<<< orphan*/  multiview_mode; } ;
struct TYPE_31__ {TYPE_5__ video; } ;
struct TYPE_24__ {TYPE_10__ fmt_out; TYPE_6__ fmt_in; TYPE_16__* p_sys; } ;
typedef  TYPE_15__ decoder_t ;
struct TYPE_25__ {int b_recovery_point; int /*<<< orphan*/  p_ccs; int /*<<< orphan*/  p_active_sps; int /*<<< orphan*/  p_timing; } ;
typedef  TYPE_16__ decoder_sys_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
#define  FRAME_PACKING_INTERLEAVED_CHECKERBOARD 140 
#define  FRAME_PACKING_INTERLEAVED_COLUMN 139 
#define  FRAME_PACKING_INTERLEAVED_ROW 138 
#define  FRAME_PACKING_SIDE_BY_SIDE 137 
#define  FRAME_PACKING_TEMPORAL 136 
#define  FRAME_PACKING_TILED 135 
#define  FRAME_PACKING_TOP_BOTTOM 134 
 int /*<<< orphan*/  HXXX_ITU_T35_TYPE_CC ; 
#define  HXXX_SEI_CONTENT_LIGHT_LEVEL 133 
#define  HXXX_SEI_FRAME_PACKING_ARRANGEMENT 132 
#define  HXXX_SEI_MASTERING_DISPLAY_COLOUR_VOLUME 131 
#define  HXXX_SEI_PIC_TIMING 130 
#define  HXXX_SEI_RECOVERY_POINT 129 
#define  HXXX_SEI_USER_DATA_REGISTERED_ITU_T_T35 128 
 int /*<<< orphan*/  MULTIVIEW_2D ; 
 int /*<<< orphan*/  MULTIVIEW_STEREO_CHECKERBOARD ; 
 int /*<<< orphan*/  MULTIVIEW_STEREO_COL ; 
 int /*<<< orphan*/  MULTIVIEW_STEREO_FRAME ; 
 int /*<<< orphan*/  MULTIVIEW_STEREO_ROW ; 
 int /*<<< orphan*/  MULTIVIEW_STEREO_SBS ; 
 int /*<<< orphan*/  MULTIVIEW_STEREO_TB ; 
 int /*<<< orphan*/  cc_storage_append (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hevc_decode_sei_pic_timing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hevc_release_sei_pic_timing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_15__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ParseSEICallback( const hxxx_sei_data_t *p_sei_data, void *cbdata )
{
    decoder_t *p_dec = (decoder_t *) cbdata;
    decoder_sys_t *p_sys = p_dec->p_sys;

    switch( p_sei_data->i_type )
    {
        case HXXX_SEI_PIC_TIMING:
        {
            if( p_sys->p_active_sps )
            {
                hevc_release_sei_pic_timing( p_sys->p_timing );
                p_sys->p_timing = hevc_decode_sei_pic_timing( p_sei_data->p_bs,
                                                              p_sys->p_active_sps );
            }
        } break;
        case HXXX_SEI_USER_DATA_REGISTERED_ITU_T_T35:
        {
            if( p_sei_data->itu_t35.type == HXXX_ITU_T35_TYPE_CC )
            {
                cc_storage_append( p_sys->p_ccs, true, p_sei_data->itu_t35.u.cc.p_data,
                                                       p_sei_data->itu_t35.u.cc.i_data );
            }
        } break;
        case HXXX_SEI_RECOVERY_POINT:
        {
            if( !p_sys->b_recovery_point )
            {
                msg_Dbg( p_dec, "Seen SEI recovery point, %d recovery frames", p_sei_data->recovery.i_frames );
                p_sys->b_recovery_point = true;
            }
        } break;
        case HXXX_SEI_FRAME_PACKING_ARRANGEMENT:
        {
            if( p_dec->fmt_in.video.multiview_mode == MULTIVIEW_2D )
            {
                video_multiview_mode_t mode;
                switch( p_sei_data->frame_packing.type )
                {
                    case FRAME_PACKING_INTERLEAVED_CHECKERBOARD:
                        mode = MULTIVIEW_STEREO_CHECKERBOARD; break;
                    case FRAME_PACKING_INTERLEAVED_COLUMN:
                        mode = MULTIVIEW_STEREO_COL; break;
                    case FRAME_PACKING_INTERLEAVED_ROW:
                        mode = MULTIVIEW_STEREO_ROW; break;
                    case FRAME_PACKING_SIDE_BY_SIDE:
                        mode = MULTIVIEW_STEREO_SBS; break;
                    case FRAME_PACKING_TOP_BOTTOM:
                        mode = MULTIVIEW_STEREO_TB; break;
                    case FRAME_PACKING_TEMPORAL:
                        mode = MULTIVIEW_STEREO_FRAME; break;
                    case FRAME_PACKING_TILED:
                    default:
                        mode = MULTIVIEW_2D; break;
                }
                p_dec->fmt_out.video.multiview_mode = mode;
            }
        } break;
        case HXXX_SEI_MASTERING_DISPLAY_COLOUR_VOLUME:
        {
            video_format_t *p_fmt = &p_dec->fmt_out.video;
            for (size_t i=0; i<ARRAY_SIZE(p_sei_data->colour_volume.primaries); ++i)
                p_fmt->mastering.primaries[i] = p_sei_data->colour_volume.primaries[i];
            for (size_t i=0; i<ARRAY_SIZE(p_sei_data->colour_volume.white_point); ++i)
                p_fmt->mastering.white_point[i] = p_sei_data->colour_volume.white_point[i];
            p_fmt->mastering.max_luminance = p_sei_data->colour_volume.max_luminance;
            p_fmt->mastering.min_luminance = p_sei_data->colour_volume.min_luminance;
        } break;
        case HXXX_SEI_CONTENT_LIGHT_LEVEL:
        {
            video_format_t *p_fmt = &p_dec->fmt_out.video;
            p_fmt->lighting.MaxCLL = p_sei_data->content_light_lvl.MaxCLL;
            p_fmt->lighting.MaxFALL = p_sei_data->content_light_lvl.MaxFALL;
        } break;
    }

    return true;
}