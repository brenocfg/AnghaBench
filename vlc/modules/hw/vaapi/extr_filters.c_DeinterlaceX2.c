#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int vlc_tick_t ;
struct TYPE_20__ {int /*<<< orphan*/  i_frame_rate; scalar_t__ i_frame_rate_base; } ;
typedef  TYPE_4__ video_format_t ;
struct TYPE_18__ {scalar_t__ num_pics; scalar_t__ sz; } ;
struct deint_data {unsigned int cur_frame; TYPE_3__* meta; TYPE_2__ history; } ;
struct TYPE_21__ {unsigned int date; int i_nb_fields; int b_progressive; struct TYPE_21__* p_next; } ;
typedef  TYPE_5__ picture_t ;
struct TYPE_17__ {TYPE_4__ video; } ;
struct TYPE_22__ {TYPE_1__ fmt_out; TYPE_7__* p_sys; } ;
typedef  TYPE_6__ filter_t ;
struct TYPE_23__ {struct deint_data* p_data; } ;
typedef  TYPE_7__ filter_sys_t ;
struct TYPE_19__ {unsigned int date; int i_nb_fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  Deinterlace_UpdateFilterParams ; 
 TYPE_5__* Deinterlace_UpdateHistory (struct deint_data* const,TYPE_5__*) ; 
 int /*<<< orphan*/  Deinterlace_UpdatePipelineParams ; 
 int /*<<< orphan*/  Deinterlace_UpdateReferenceFrames ; 
 TYPE_5__* Filter (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int METADATA_SIZE ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  picture_Release (TYPE_5__*) ; 
 unsigned int vlc_tick_from_samples (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static picture_t *
DeinterlaceX2(filter_t * filter, picture_t * src)
{
    filter_sys_t *const         filter_sys = filter->p_sys;
    struct deint_data *const    p_deint_data = filter_sys->p_data;
    const video_format_t *      fmt = &filter->fmt_out.video;

    /* TODO: could use the meta array and calculation from deinterlace/common
       but then it would also be appropriate to use the picture history array
       too and the callback system...so a rewrite of this module basically.*/
    for (unsigned int i = 1; i < METADATA_SIZE; ++i)
        p_deint_data->meta[i-1] = p_deint_data->meta[i];
    p_deint_data->meta[METADATA_SIZE-1].date        = src->date;
    p_deint_data->meta[METADATA_SIZE-1].i_nb_fields = src->i_nb_fields;

    picture_t * cur = Deinterlace_UpdateHistory(p_deint_data, src);
    if (p_deint_data->history.num_pics < p_deint_data->history.sz)
        return NULL;

    vlc_tick_t i_field_dur = 0;
    unsigned int i = 0;
    for ( ; i < METADATA_SIZE-1; i ++)
        if (p_deint_data->meta[i].date != VLC_TICK_INVALID)
            break;
    if (i < METADATA_SIZE-1) {
        unsigned int i_fields_total = 0;
        for (unsigned int j = i; j < METADATA_SIZE-1; ++j)
            i_fields_total += p_deint_data->meta[j].i_nb_fields;
        i_field_dur = (src->date - p_deint_data->meta[i].date) / i_fields_total;
    }
    else if (fmt->i_frame_rate_base)
        i_field_dur = vlc_tick_from_samples(fmt->i_frame_rate_base, fmt->i_frame_rate);

    picture_t *dest[2] = {NULL, NULL};
    for (i = 0; i < 2; ++i)
    {
        p_deint_data->cur_frame = i;
        dest[i] = Filter(filter, cur,
                         Deinterlace_UpdateFilterParams,
                         Deinterlace_UpdateReferenceFrames,
                         Deinterlace_UpdatePipelineParams);
        if (!dest[i])
           goto error;

        dest[i]->b_progressive = true;
        dest[i]->i_nb_fields = 1;
    }

    dest[0]->p_next = dest[1];
    dest[0]->date = cur->date;
    if (dest[0]->date != VLC_TICK_INVALID)
        dest[1]->date = dest[0]->date + i_field_dur;
    else
        dest[1]->date = VLC_TICK_INVALID;

    return dest[0];

error:
    for (i = 0; i < 2; ++i)
        if (dest[i])
            picture_Release(dest[i]);

    return NULL;
}