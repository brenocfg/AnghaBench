#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pf_packetize; int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_1__ decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  PacketizeClosed ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  avparser_ClosePacketizer (int /*<<< orphan*/ ) ; 
 int avparser_OpenPacketizer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int) ; 

__attribute__((used)) static void FlushPacketizer( decoder_t *p_dec )
{
    avparser_ClosePacketizer( VLC_OBJECT( p_dec ) );
    p_dec->p_sys = NULL;
    int res = avparser_OpenPacketizer( VLC_OBJECT( p_dec ) );
    if ( res != VLC_SUCCESS )
    {
        msg_Err( p_dec, "failed to flush with error %d", res );
        p_dec->pf_packetize = PacketizeClosed;
    }
}