#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_5__ {int b_discontuinity; int /*<<< orphan*/  bytestream; int /*<<< orphan*/  i_prev_bytestream_pts; int /*<<< orphan*/  i_state; int /*<<< orphan*/  end_date; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_NOSYNC ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_BytestreamEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PacketizeFlush( decoder_t *p_dec )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    p_sys->b_discontuinity = true;
    date_Set( &p_sys->end_date, VLC_TICK_INVALID );
    p_sys->i_state = STATE_NOSYNC;
    p_sys->i_prev_bytestream_pts = VLC_TICK_INVALID;
    block_BytestreamEmpty( &p_sys->bytestream );
}