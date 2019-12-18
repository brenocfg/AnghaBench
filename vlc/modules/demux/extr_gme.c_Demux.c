#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * gme_err_t ;
struct TYPE_10__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_11__ {unsigned int track_id; int title_changed; int /*<<< orphan*/  pts; int /*<<< orphan*/  es; int /*<<< orphan*/  emu; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; scalar_t__ p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int SAMPLES ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 TYPE_3__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  date_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Increment (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gme_play (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  gme_start_track (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ gme_track_count (int /*<<< orphan*/ ) ; 
 scalar_t__ gme_track_ended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,unsigned int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux (demux_t *demux)
{
    demux_sys_t *sys = demux->p_sys;

    /* Next track */
    if (gme_track_ended (sys->emu))
    {
        msg_Dbg (demux, "track %u ended", sys->track_id);
        if (++sys->track_id >= (unsigned)gme_track_count (sys->emu))
            return VLC_DEMUXER_EOF;

        sys->title_changed = true;
        gme_start_track (sys->emu, sys->track_id);
    }


    block_t *block = block_Alloc (2 * 2 * SAMPLES);
    if (unlikely(block == NULL))
        return VLC_DEMUXER_EOF;

    gme_err_t ret = gme_play (sys->emu, 2 * SAMPLES, (void *)block->p_buffer);
    if (ret != NULL)
    {
        block_Release (block);
        msg_Err (demux, "%s", ret);
        return VLC_DEMUXER_EOF;
    }

    block->i_pts = block->i_dts = date_Get (&sys->pts);
    es_out_SetPCR (demux->out, block->i_pts);
    es_out_Send (demux->out, sys->es, block);
    date_Increment (&sys->pts, SAMPLES);
    return VLC_DEMUXER_SUCCESS;
}