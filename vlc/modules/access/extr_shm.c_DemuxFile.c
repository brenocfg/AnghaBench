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
struct TYPE_6__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {int /*<<< orphan*/  es; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 TYPE_3__* block_File (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static void DemuxFile (void *data)
{
    demux_t *demux = data;
    demux_sys_t *sys = demux->p_sys;

    /* Copy frame */
    block_t *block = block_File(sys->fd, true);
    if (block == NULL)
        return;
    block->i_pts = block->i_dts = vlc_tick_now ();

    /* Send block */
    es_out_SetPCR(demux->out, block->i_pts);
    es_out_Send (demux->out, sys->es, block);
}