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
struct TYPE_8__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {scalar_t__ i_next_date; scalar_t__ i_incr; int /*<<< orphan*/  es; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_10__ {scalar_t__ i_dts; scalar_t__ i_pts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* screen_Capture (TYPE_1__*) ; 
 scalar_t__ vlc_tick_now () ; 
 int /*<<< orphan*/  vlc_tick_wait (scalar_t__) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    block_t *p_block;

    if( !p_sys->i_next_date ) p_sys->i_next_date = vlc_tick_now();

    /* Frame skipping if necessary */
    while( vlc_tick_now() >= p_sys->i_next_date + p_sys->i_incr )
        p_sys->i_next_date += p_sys->i_incr;

    vlc_tick_wait( p_sys->i_next_date );
    p_block = screen_Capture( p_demux );
    if( !p_block )
    {
        p_sys->i_next_date += p_sys->i_incr;
        return 1;
    }

    p_block->i_dts = p_block->i_pts = p_sys->i_next_date;

    es_out_SetPCR( p_demux->out, p_block->i_pts );
    es_out_Send( p_demux->out, p_sys->es, p_block );

    p_sys->i_next_date += p_sys->i_incr;

    return 1;
}