#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {scalar_t__ pulse; int /*<<< orphan*/  tick; int /*<<< orphan*/  es; int /*<<< orphan*/  pts; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_10__ {int* p_buffer; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 scalar_t__ ReadEvents (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TICK ; 
 scalar_t__ UINT64_MAX ; 
 int VLC_DEMUXER_EGENERIC ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 int VLC_ENOMEM ; 
 TYPE_3__* block_Alloc (int) ; 
 int /*<<< orphan*/  date_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux (demux_t *demux)
{
    demux_sys_t *sys = demux->p_sys;

    /* MIDI Tick emulation (ping the decoder every 10ms) */
    if (sys->tick <= date_Get (&sys->pts))
    {
        block_t *tick = block_Alloc (1);
        if (unlikely(tick == NULL))
            return VLC_ENOMEM;

        tick->p_buffer[0] = 0xF9;
        tick->i_dts = tick->i_pts = sys->tick;

        es_out_Send (demux->out, sys->es, tick);
        es_out_SetPCR (demux->out, sys->tick);

        sys->tick += TICK;
        return VLC_DEMUXER_SUCCESS;
    }

    /* MIDI events in chronological order across all tracks */
    uint64_t pulse = sys->pulse;

    if (ReadEvents (demux, &pulse, demux->out))
        return VLC_DEMUXER_EGENERIC;

    if (pulse == UINT64_MAX)
        return VLC_DEMUXER_EOF; /* all tracks are done */

    sys->pulse = pulse;
    return VLC_DEMUXER_SUCCESS;
}