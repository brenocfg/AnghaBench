#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_17__ {int i_size; TYPE_5__* p_elems; } ;
struct TYPE_19__ {int b_draining; int b_menu; int b_flushed; int /*<<< orphan*/  p_parser; scalar_t__ b_fatal_error; TYPE_1__ events_delayed; int /*<<< orphan*/  bluray; int /*<<< orphan*/  p_out; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_20__ {int i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_21__ {scalar_t__ event; } ;
typedef  TYPE_5__ BD_EVENT ;

/* Variables and functions */
 scalar_t__ BD_EVENT_NONE ; 
 int /*<<< orphan*/  BD_READ_SIZE ; 
 int /*<<< orphan*/  ES_OUT_GET_EMPTY ; 
 int /*<<< orphan*/  ES_OUT_RESET_PCR ; 
 int VLC_DEMUXER_EGENERIC ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 scalar_t__ bd_get_event (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int bd_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bd_read_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 TYPE_4__* block_Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  blurayHandleEvent (TYPE_2__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  blurayHandleOverlays (TYPE_2__*) ; 
 scalar_t__ es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  vlc_demux_chained_Send (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_tick_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blurayDemux(demux_t *p_demux)
{
    demux_sys_t *p_sys = p_demux->p_sys;
    BD_EVENT e;

    if(p_sys->b_draining)
    {
        bool b_empty = false;
        if(es_out_Control(p_sys->p_out, ES_OUT_GET_EMPTY, &b_empty) != VLC_SUCCESS || b_empty)
        {
            es_out_Control(p_sys->p_out, ES_OUT_RESET_PCR);
            p_sys->b_draining = false;
        }
        else
        {
            msg_Dbg(p_demux, "Draining...");
            vlc_tick_sleep(VLC_TICK_FROM_MS(40));
            return VLC_DEMUXER_SUCCESS;
        }
    }

    block_t *p_block = block_Alloc(BD_READ_SIZE);
    if (!p_block)
        return VLC_DEMUXER_EGENERIC;

    int nread;

    if (p_sys->b_menu == false) {
        nread = bd_read(p_sys->bluray, p_block->p_buffer, BD_READ_SIZE);
        while (bd_get_event(p_sys->bluray, &e))
            blurayHandleEvent(p_demux, &e, false);
    } else {
        nread = bd_read_ext(p_sys->bluray, p_block->p_buffer, BD_READ_SIZE, &e);
        while (e.event != BD_EVENT_NONE) {
            blurayHandleEvent(p_demux, &e, false);
            bd_get_event(p_sys->bluray, &e);
        }
    }

    /* Process delayed selections events */
    for(int i=0; i<p_sys->events_delayed.i_size; i++)
        blurayHandleEvent(p_demux, &p_sys->events_delayed.p_elems[i], true);
    p_sys->events_delayed.i_size = 0;

    blurayHandleOverlays(p_demux);

    if (nread <= 0) {
        block_Release(p_block);
        if (p_sys->b_fatal_error || nread < 0) {
            msg_Err(p_demux, "bluray: stopping playback after fatal error\n");
            return VLC_DEMUXER_EGENERIC;
        }
        if (!p_sys->b_menu) {
            return VLC_DEMUXER_EOF;
        }
        return VLC_DEMUXER_SUCCESS;
    }

    p_block->i_buffer = nread;

    vlc_demux_chained_Send(p_sys->p_parser, p_block);

    p_sys->b_flushed = false;

    return VLC_DEMUXER_SUCCESS;
}