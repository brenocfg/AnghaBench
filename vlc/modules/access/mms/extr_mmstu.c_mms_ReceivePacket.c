#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_10__ {scalar_t__ i_buffer_tcp; scalar_t__ i_proto; int i_buffer_udp; int i_command; scalar_t__ buffer_udp; scalar_t__ buffer_tcp; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int GetDWLE (scalar_t__) ; 
 scalar_t__ GetWLE (scalar_t__) ; 
 size_t MMS_BUFFER_SIZE ; 
 scalar_t__ MMS_CMD_HEADERSIZE ; 
 int MMS_PACKET_CMD ; 
 scalar_t__ MMS_PROTO_UDP ; 
 scalar_t__ NetFillBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  mms_CommandSend (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mms_ParseCommand (TYPE_1__*,scalar_t__,scalar_t__,size_t*) ; 
 int mms_ParsePacket (TYPE_1__*,scalar_t__,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 

__attribute__((used)) static int mms_ReceivePacket( stream_t *p_access )
{
    access_sys_t *p_sys = p_access->p_sys;
    int i_packet_tcp_type;
    int i_packet_udp_type;

    for( ;; )
    {
        bool b_refill = true;

        /* first if we need to refill buffer */
        if( p_sys->i_buffer_tcp >= MMS_CMD_HEADERSIZE )
        {
            if( GetDWLE( p_sys->buffer_tcp + 4 ) == 0xb00bface  )
            {
                if( GetDWLE( p_sys->buffer_tcp + 8 ) + 16 <=
                    (size_t)p_sys->i_buffer_tcp )
                {
                    b_refill = false;
                }
            }
            else if( GetWLE( p_sys->buffer_tcp + 6 ) <= p_sys->i_buffer_tcp )
            {
                b_refill = false;
            }
        }
        if( p_sys->i_proto == MMS_PROTO_UDP && p_sys->i_buffer_udp >= 8 &&
            GetWLE( p_sys->buffer_udp + 6 ) <= p_sys->i_buffer_udp )
        {
            b_refill = false;
        }

        if( b_refill && NetFillBuffer( p_access ) < 0 )
        {
            msg_Warn( p_access, "cannot fill buffer" );
            return -1;
        }

        i_packet_tcp_type = -1;
        i_packet_udp_type = -1;

        if( p_sys->i_buffer_tcp > 0 )
        {
            size_t i_used;

            if( GetDWLE( p_sys->buffer_tcp + 4 ) == 0xb00bface )
            {
                i_packet_tcp_type =
                    mms_ParseCommand( p_access, p_sys->buffer_tcp,
                                      p_sys->i_buffer_tcp, &i_used );

            }
            else
            {
                i_packet_tcp_type =
                    mms_ParsePacket( p_access, p_sys->buffer_tcp,
                                     p_sys->i_buffer_tcp, &i_used );
            }
            if( i_used > 0 && i_used < MMS_BUFFER_SIZE )
            {
                memmove( p_sys->buffer_tcp, p_sys->buffer_tcp + i_used,
                         MMS_BUFFER_SIZE - i_used );
            }
            p_sys->i_buffer_tcp -= i_used;
        }
        else if( p_sys->i_buffer_udp > 0 )
        {
            size_t i_used;

            i_packet_udp_type =
                mms_ParsePacket( p_access, p_sys->buffer_udp,
                                 p_sys->i_buffer_udp, &i_used );

            if( i_used > 0 && i_used < MMS_BUFFER_SIZE )
            {
                memmove( p_sys->buffer_udp, p_sys->buffer_udp + i_used,
                         MMS_BUFFER_SIZE - i_used );
            }
            p_sys->i_buffer_udp -= i_used;
        }

        if( i_packet_tcp_type == MMS_PACKET_CMD && p_sys->i_command == 0x1b )
        {
            mms_CommandSend( p_access, 0x1b, 0, 0, NULL, 0 );
            i_packet_tcp_type = -1;
        }

        if( i_packet_tcp_type != -1 )
        {
            return i_packet_tcp_type;
        }
        else if( i_packet_udp_type != -1 )
        {
            return i_packet_udp_type;
        }
    }
}