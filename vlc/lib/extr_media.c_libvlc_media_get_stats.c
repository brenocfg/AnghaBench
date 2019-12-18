#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* p_input_item; } ;
typedef  TYPE_1__ libvlc_media_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_lost_abuffers; int /*<<< orphan*/  i_played_abuffers; int /*<<< orphan*/  i_lost_pictures; int /*<<< orphan*/  i_displayed_pictures; int /*<<< orphan*/  i_decoded_audio; int /*<<< orphan*/  i_decoded_video; int /*<<< orphan*/  i_demux_discontinuity; int /*<<< orphan*/  i_demux_corrupted; int /*<<< orphan*/  f_demux_bitrate; int /*<<< orphan*/  i_demux_read_bytes; int /*<<< orphan*/  f_input_bitrate; int /*<<< orphan*/  i_read_bytes; } ;
typedef  TYPE_2__ libvlc_media_stats_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_lost_abuffers; int /*<<< orphan*/  i_played_abuffers; int /*<<< orphan*/  i_lost_pictures; int /*<<< orphan*/  i_displayed_pictures; int /*<<< orphan*/  i_decoded_audio; int /*<<< orphan*/  i_decoded_video; int /*<<< orphan*/  i_demux_discontinuity; int /*<<< orphan*/  i_demux_corrupted; int /*<<< orphan*/  f_demux_bitrate; int /*<<< orphan*/  i_demux_read_bytes; int /*<<< orphan*/  f_input_bitrate; int /*<<< orphan*/  i_read_bytes; } ;
typedef  TYPE_3__ input_stats_t ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_3__* p_stats; } ;
typedef  TYPE_4__ input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

bool libvlc_media_get_stats(libvlc_media_t *p_md,
                            libvlc_media_stats_t *p_stats)
{
    input_item_t *item = p_md->p_input_item;

    if( !p_md->p_input_item )
        return false;

    vlc_mutex_lock( &item->lock );

    input_stats_t *p_itm_stats = p_md->p_input_item->p_stats;
    if( p_itm_stats == NULL )
    {
        vlc_mutex_unlock( &item->lock );
        return false;
    }

    p_stats->i_read_bytes = p_itm_stats->i_read_bytes;
    p_stats->f_input_bitrate = p_itm_stats->f_input_bitrate;

    p_stats->i_demux_read_bytes = p_itm_stats->i_demux_read_bytes;
    p_stats->f_demux_bitrate = p_itm_stats->f_demux_bitrate;
    p_stats->i_demux_corrupted = p_itm_stats->i_demux_corrupted;
    p_stats->i_demux_discontinuity = p_itm_stats->i_demux_discontinuity;

    p_stats->i_decoded_video = p_itm_stats->i_decoded_video;
    p_stats->i_decoded_audio = p_itm_stats->i_decoded_audio;

    p_stats->i_displayed_pictures = p_itm_stats->i_displayed_pictures;
    p_stats->i_lost_pictures = p_itm_stats->i_lost_pictures;

    p_stats->i_played_abuffers = p_itm_stats->i_played_abuffers;
    p_stats->i_lost_abuffers = p_itm_stats->i_lost_abuffers;

    vlc_mutex_unlock( &item->lock );
    return true;
}