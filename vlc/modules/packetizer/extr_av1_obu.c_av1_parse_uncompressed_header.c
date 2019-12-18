#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct av1_uncompressed_header_s {int show_frame; void* frame_type; void* frame_presentation_time; void* show_existing_frame; } ;
typedef  void* obu_u3_t ;
typedef  void* obu_u32_t ;
typedef  int /*<<< orphan*/  bs_t ;
struct TYPE_6__ {int frame_presentation_time_length_minus_1; } ;
struct TYPE_5__ {int /*<<< orphan*/  equal_picture_interval; } ;
struct TYPE_7__ {int additional_frame_id_length_minus_1; int delta_frame_id_length_minus_2; scalar_t__ film_grain_params_present; scalar_t__ frame_id_numbers_present_flag; TYPE_2__ decoder_model_info; TYPE_1__ timing_info; scalar_t__ decoder_model_info_present_flag; scalar_t__ reduced_still_picture_header; } ;
typedef  TYPE_3__ av1_OBU_sequence_header_t ;

/* Variables and functions */
 void* AV1_FRAME_TYPE_KEY ; 
 int /*<<< orphan*/  VLC_UNUSED (void* const) ; 
 void* bs_read (int /*<<< orphan*/ *,int const) ; 
 void* bs_read1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool av1_parse_uncompressed_header(bs_t *p_bs, struct av1_uncompressed_header_s *p_uh,
                                          const av1_OBU_sequence_header_t *p_seq)
{
    if(p_seq->reduced_still_picture_header)
    {
        p_uh->frame_type = AV1_FRAME_TYPE_KEY;
        p_uh->show_frame = 1;
    }
    else
    {
        p_uh->show_existing_frame = bs_read1(p_bs);
        if(p_uh->show_existing_frame)
        {
            const obu_u3_t frame_to_show_map_idx = bs_read(p_bs, 3);
            VLC_UNUSED(frame_to_show_map_idx);
            if(p_seq->decoder_model_info_present_flag && !p_seq->timing_info.equal_picture_interval)
            {
                /* temporal_point_info() */
                p_uh->frame_presentation_time =
                        bs_read(p_bs, 1 + p_seq->decoder_model_info.frame_presentation_time_length_minus_1);
            }
            if(p_seq->frame_id_numbers_present_flag)
            {
                const uint8_t idLen = p_seq->additional_frame_id_length_minus_1 +
                                      p_seq->delta_frame_id_length_minus_2 + 3;
                const obu_u32_t display_frame_id = bs_read(p_bs, idLen);
                VLC_UNUSED(display_frame_id);
            }
            if(p_seq->film_grain_params_present)
            {
                /* load_grain */
            }
        }
        p_uh->frame_type = bs_read(p_bs, 2);
        p_uh->show_frame = bs_read1(p_bs);
    }

    return true;
}