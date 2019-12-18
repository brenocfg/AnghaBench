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
typedef  int /*<<< orphan*/  vlc_player_track_vector ;
struct vlc_player_input {int /*<<< orphan*/  spu_track_vector; int /*<<< orphan*/  audio_track_vector; int /*<<< orphan*/  video_track_vector; } ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
#define  AUDIO_ES 130 
#define  SPU_ES 129 
#define  VIDEO_ES 128 

__attribute__((used)) static inline vlc_player_track_vector *
vlc_player_input_GetTrackVector(struct vlc_player_input *input,
                                enum es_format_category_e cat)
{
    switch (cat)
    {
        case VIDEO_ES:
            return &input->video_track_vector;
        case AUDIO_ES:
            return &input->audio_track_vector;
        case SPU_ES:
            return &input->spu_track_vector;
        default:
            return NULL;
    }
}