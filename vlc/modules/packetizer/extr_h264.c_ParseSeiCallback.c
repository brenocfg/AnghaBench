#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_multiview_mode_t ;
struct TYPE_18__ {int /*<<< orphan*/  i_frames; } ;
struct TYPE_29__ {int /*<<< orphan*/  type; } ;
struct TYPE_24__ {int /*<<< orphan*/  i_data; int /*<<< orphan*/  p_data; } ;
struct TYPE_25__ {TYPE_2__ cc; } ;
struct TYPE_26__ {TYPE_3__ u; int /*<<< orphan*/  type; } ;
struct TYPE_19__ {int i_type; TYPE_10__ recovery; TYPE_7__ frame_packing; TYPE_4__ itu_t35; int /*<<< orphan*/  p_bs; } ;
typedef  TYPE_11__ hxxx_sei_data_t ;
struct TYPE_23__ {int /*<<< orphan*/  b_pic_struct_present_flag; int /*<<< orphan*/  i_dpb_output_delay_length_minus1; int /*<<< orphan*/  i_cpb_removal_delay_length_minus1; int /*<<< orphan*/  b_hrd_parameters_present_flag; int /*<<< orphan*/  b_valid; } ;
struct TYPE_20__ {TYPE_1__ vui; } ;
typedef  TYPE_12__ h264_sequence_parameter_set_t ;
struct TYPE_30__ {int /*<<< orphan*/  multiview_mode; } ;
struct TYPE_31__ {TYPE_8__ video; } ;
struct TYPE_27__ {int /*<<< orphan*/  multiview_mode; } ;
struct TYPE_28__ {TYPE_5__ video; } ;
struct TYPE_21__ {TYPE_9__ fmt_out; TYPE_6__ fmt_in; TYPE_14__* p_sys; } ;
typedef  TYPE_13__ decoder_t ;
struct TYPE_22__ {int /*<<< orphan*/  i_recovery_frame_cnt; int /*<<< orphan*/  b_recovered; int /*<<< orphan*/  p_ccs; void* i_pic_struct; void* i_dpb_output_delay; TYPE_12__* p_active_sps; } ;
typedef  TYPE_14__ decoder_sys_t ;

/* Variables and functions */
#define  FRAME_PACKING_INTERLEAVED_CHECKERBOARD 138 
#define  FRAME_PACKING_INTERLEAVED_COLUMN 137 
#define  FRAME_PACKING_INTERLEAVED_ROW 136 
#define  FRAME_PACKING_SIDE_BY_SIDE 135 
#define  FRAME_PACKING_TEMPORAL 134 
#define  FRAME_PACKING_TILED 133 
#define  FRAME_PACKING_TOP_BOTTOM 132 
 int /*<<< orphan*/  HXXX_ITU_T35_TYPE_CC ; 
#define  HXXX_SEI_FRAME_PACKING_ARRANGEMENT 131 
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
 int /*<<< orphan*/  assert (TYPE_12__ const*) ; 
 void* bs_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cc_storage_append (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_13__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ParseSeiCallback( const hxxx_sei_data_t *p_sei_data, void *cbdata )
{
    decoder_t *p_dec = (decoder_t *) cbdata;
    decoder_sys_t *p_sys = p_dec->p_sys;

    switch( p_sei_data->i_type )
    {
        /* Look for pic timing */
        case HXXX_SEI_PIC_TIMING:
        {
            const h264_sequence_parameter_set_t *p_sps = p_sys->p_active_sps;
            if( unlikely( p_sps == NULL ) )
            {
                assert( p_sps );
                break;
            }

            if( p_sps->vui.b_valid )
            {
                if( p_sps->vui.b_hrd_parameters_present_flag )
                {
                    bs_read( p_sei_data->p_bs, p_sps->vui.i_cpb_removal_delay_length_minus1 + 1 );
                    p_sys->i_dpb_output_delay =
                            bs_read( p_sei_data->p_bs, p_sps->vui.i_dpb_output_delay_length_minus1 + 1 );
                }

                if( p_sps->vui.b_pic_struct_present_flag )
                    p_sys->i_pic_struct = bs_read( p_sei_data->p_bs, 4 );
                /* + unparsed remains */
            }
        } break;

            /* Look for user_data_registered_itu_t_t35 */
        case HXXX_SEI_USER_DATA_REGISTERED_ITU_T_T35:
        {
            if( p_sei_data->itu_t35.type == HXXX_ITU_T35_TYPE_CC )
            {
                cc_storage_append( p_sys->p_ccs, true, p_sei_data->itu_t35.u.cc.p_data,
                                                       p_sei_data->itu_t35.u.cc.i_data );
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

            /* Look for SEI recovery point */
        case HXXX_SEI_RECOVERY_POINT:
        {
            if( !p_sys->b_recovered )
                msg_Dbg( p_dec, "Seen SEI recovery point, %d recovery frames", p_sei_data->recovery.i_frames );
            p_sys->i_recovery_frame_cnt = p_sei_data->recovery.i_frames;
        } break;

        default:
            /* Will skip */
            break;
    }

    return true;
}