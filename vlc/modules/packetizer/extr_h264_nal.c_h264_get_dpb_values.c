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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  b_bitstream_restriction_flag; int /*<<< orphan*/  i_max_num_reorder_frames; } ;
struct TYPE_6__ {int i_profile; int i_constraint_set_flags; TYPE_1__ vui; } ;
typedef  TYPE_2__ h264_sequence_parameter_set_t ;

/* Variables and functions */
 int H264_CONSTRAINT_SET_FLAG (int) ; 
#define  PROFILE_H264_BASELINE 134 
#define  PROFILE_H264_CAVLC_INTRA 133 
#define  PROFILE_H264_HIGH 132 
#define  PROFILE_H264_HIGH_10 131 
#define  PROFILE_H264_HIGH_422 130 
#define  PROFILE_H264_HIGH_444_PREDICTIVE 129 
#define  PROFILE_H264_SVC_HIGH 128 
 int /*<<< orphan*/  h264_get_max_dpb_frames (TYPE_2__ const*) ; 

bool h264_get_dpb_values( const h264_sequence_parameter_set_t *p_sps,
                          uint8_t *pi_depth, unsigned *pi_delay )
{
    uint8_t i_max_num_reorder_frames = p_sps->vui.i_max_num_reorder_frames;
    if( !p_sps->vui.b_bitstream_restriction_flag )
    {
        switch( p_sps->i_profile ) /* E-2.1 */
        {
            case PROFILE_H264_BASELINE:
                i_max_num_reorder_frames = 0; /* only I & P */
                break;
            case PROFILE_H264_CAVLC_INTRA:
            case PROFILE_H264_SVC_HIGH:
            case PROFILE_H264_HIGH:
            case PROFILE_H264_HIGH_10:
            case PROFILE_H264_HIGH_422:
            case PROFILE_H264_HIGH_444_PREDICTIVE:
                if( p_sps->i_constraint_set_flags & H264_CONSTRAINT_SET_FLAG(3) )
                {
                    i_max_num_reorder_frames = 0; /* all IDR */
                    break;
                }
                /* fallthrough */
            default:
                i_max_num_reorder_frames = h264_get_max_dpb_frames( p_sps );
                break;
        }
    }

    *pi_depth = i_max_num_reorder_frames;
    *pi_delay = 0;

    return true;
}