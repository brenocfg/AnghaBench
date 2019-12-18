#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {int i_width; size_t i_idx_left; size_t i_idx_right; int /*<<< orphan*/  i_nb_chans; } ;
typedef  TYPE_2__ visual_effect_t ;
typedef  int uint8_t ;
struct TYPE_10__ {TYPE_1__* p; } ;
typedef  TYPE_3__ picture_t ;
typedef  int int8_t ;
struct TYPE_11__ {scalar_t__ i_nb_samples; scalar_t__ p_buffer; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_8__ {int* p_pixels; int i_lines; int i_pitch; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int __MIN (int,int) ; 

__attribute__((used)) static int scope_Run(visual_effect_t * p_effect, vlc_object_t *p_aout,
                     const block_t * p_buffer , picture_t * p_picture)
{
    VLC_UNUSED(p_aout);

    int i_index;
    float *p_sample ;
    uint8_t *ppp_area[2][3];

    for( i_index = 0 ; i_index < 2 ; i_index++ )
    {
        for( int j = 0 ; j < 3 ; j++ )
        {
            ppp_area[i_index][j] =
                p_picture->p[j].p_pixels + (i_index * 2 + 1) * p_picture->p[j].i_lines
                / 4 * p_picture->p[j].i_pitch;
        }
    }

    for( i_index = 0, p_sample = (float *)p_buffer->p_buffer;
            i_index < __MIN( p_effect->i_width, (int)p_buffer->i_nb_samples );
            i_index++ )
    {
        int8_t i_value;

        /* Left channel */
        i_value =  p_sample[p_effect->i_idx_left] * 127;
        *(ppp_area[0][0]
                + p_picture->p[0].i_pitch * i_index / p_effect->i_width
                + p_picture->p[0].i_lines * i_value / 512
                * p_picture->p[0].i_pitch) = 0xbf;
        *(ppp_area[0][1]
                + p_picture->p[1].i_pitch * i_index / p_effect->i_width
                + p_picture->p[1].i_lines * i_value / 512
                * p_picture->p[1].i_pitch) = 0xff;


        /* Right channel */
        i_value = p_sample[p_effect->i_idx_right] * 127;
        *(ppp_area[1][0]
                + p_picture->p[0].i_pitch * i_index / p_effect->i_width
                + p_picture->p[0].i_lines * i_value / 512
                * p_picture->p[0].i_pitch) = 0x9f;
        *(ppp_area[1][2]
                + p_picture->p[2].i_pitch * i_index / p_effect->i_width
                + p_picture->p[2].i_lines * i_value / 512
                * p_picture->p[2].i_pitch) = 0xdd;

        p_sample += p_effect->i_nb_chans;
    }
    return 0;
}