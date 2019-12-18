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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_5__ {int b_big_endian; int i_packet_size; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  A52CheckSync (int /*<<< orphan*/  const*,int*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ VLC_A52_MIN_HEADER_SIZE ; 
 int VLC_SUCCESS ; 
 scalar_t__ vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,scalar_t__) ; 

__attribute__((used)) static int A52Init( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    p_sys->b_big_endian = false;
    p_sys->i_packet_size = 1024;

    const uint8_t *p_peek;

    /* peek the begining */
    if( vlc_stream_Peek( p_demux->s, &p_peek, VLC_A52_MIN_HEADER_SIZE ) >= VLC_A52_MIN_HEADER_SIZE )
    {
        A52CheckSync( p_peek, &p_sys->b_big_endian, NULL, true );
    }
    return VLC_SUCCESS;
}