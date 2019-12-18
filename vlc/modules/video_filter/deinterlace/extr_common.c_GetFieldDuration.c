#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int vlc_tick_t ;
struct TYPE_7__ {scalar_t__ i_frame_rate; int /*<<< orphan*/  i_frame_rate_base; } ;
typedef  TYPE_2__ video_format_t ;
struct deinterlace_ctx {TYPE_1__* meta; } ;
struct TYPE_8__ {int date; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_6__ {scalar_t__ pi_date; scalar_t__ pi_nb_fields; } ;

/* Variables and functions */
 int METADATA_SIZE ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int vlc_tick_from_samples (int /*<<< orphan*/ ,scalar_t__) ; 

vlc_tick_t GetFieldDuration(const struct deinterlace_ctx *p_context,
                         const video_format_t *fmt, const picture_t *p_pic )
{
    vlc_tick_t i_field_dur = 0;

    /* Calculate one field duration. */
    int i = 0;
    int iend = METADATA_SIZE-1;
    /* Find oldest valid logged date.
       The current input frame doesn't count. */
    for( ; i < iend; i++ )
        if( p_context->meta[i].pi_date != VLC_TICK_INVALID )
            break;
    if( i < iend )
    {
        /* Count how many fields the valid history entries
           (except the new frame) represent. */
        int i_fields_total = 0;
        for( int j = i ; j < iend; j++ )
            i_fields_total += p_context->meta[j].pi_nb_fields;
        /* One field took this long. */
        i_field_dur = (p_pic->date - p_context->meta[i].pi_date) / i_fields_total;
    }
    else if (fmt->i_frame_rate)
        i_field_dur = vlc_tick_from_samples( fmt->i_frame_rate_base, fmt->i_frame_rate);

    /* Note that we default to field duration 0 if it could not be
       determined. This behaves the same as the old code - leaving the
       extra output frame dates the same as p_pic->date if the last cached
       date was not valid.
    */
    return i_field_dur;
}