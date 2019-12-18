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
struct TYPE_8__ {int* data; } ;
typedef  TYPE_1__ vbi_sliced ;
typedef  int uint8_t ;
struct TYPE_9__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_10__ {int i_aspect; int /*<<< orphan*/  p_wss_buffer; int /*<<< orphan*/  rd_wss; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int VOUT_ASPECT_FACTOR ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  parity (int) ; 
 scalar_t__ vbi_raw_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void DecodeWSS( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    vbi_sliced p_sliced[1];

    if ( vbi_raw_decode( &p_sys->rd_wss, p_sys->p_wss_buffer, p_sliced ) == 0 )
    {
        p_sys->i_aspect = 4 * VOUT_ASPECT_FACTOR / 3;
    }
    else
    {
        unsigned int i_old_aspect = p_sys->i_aspect;
        uint8_t *p = p_sliced[0].data;
        int i_aspect = p[0] & 7;

        if ( !parity(p[0] & 15) )
            msg_Warn( p_demux, "WSS parity error" );
        else if ( i_aspect == 7 )
            p_sys->i_aspect = 16 * VOUT_ASPECT_FACTOR / 9;
        else
            p_sys->i_aspect = 4 * VOUT_ASPECT_FACTOR / 3;

        if ( p_sys->i_aspect != i_old_aspect )
            msg_Dbg( p_demux, "new WSS information (ra=%x md=%x cod=%x hlp=%x rvd=%x sub=%x pos=%x srd=%x c=%x cp=%x)",
                     i_aspect, (p[0] & 0x10) >> 4, (p[0] & 0x20) >> 5,
                     (p[0] & 0x40) >> 6, (p[0] & 0x80) >> 7, p[1] & 0x01,
                     (p[1] >> 1) & 3, (p[1] & 0x08) >> 3, (p[1] & 0x10) >> 4,
                     (p[1] & 0x20) >> 5 );
    }
}