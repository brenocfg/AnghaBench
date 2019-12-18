#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_10__ {int i_type; int i_size; scalar_t__ i_sequence; int i_size2; int i_data; int /*<<< orphan*/ * p_data; void* i_unknown; } ;
typedef  TYPE_2__ chunk_t ;
struct TYPE_11__ {scalar_t__ i_packet_sequence; int i_packet_length; int /*<<< orphan*/ * p_packet; scalar_t__ i_packet_used; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  stream; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 scalar_t__ GetDWLE (int /*<<< orphan*/ *) ; 
 void* GetWLE (int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,...) ; 
 int vlc_tls_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int GetPacket( stream_t * p_access, chunk_t *p_ck )
{
    access_sys_t *p_sys = p_access->p_sys;
    int restsize;

    /* chunk_t */
    memset( p_ck, 0, sizeof( chunk_t ) );

    /* Read the chunk header */
    /* Some headers are short, like 0x4324. Reading 12 bytes will cause us
     * to lose synchronization with the stream. Just read to the length
     * (4 bytes), decode and then read up to 8 additional bytes to get the
     * entire header.
     */
    if( vlc_tls_Read( p_sys->stream, p_sys->buffer, 4, true ) < 4 )
    {
       msg_Err( p_access, "cannot read data 2" );
       return VLC_EGENERIC;
    }

    p_ck->i_type = GetWLE( p_sys->buffer);
    p_ck->i_size = GetWLE( p_sys->buffer + 2);

    restsize = p_ck->i_size;
    if( restsize > 8 )
        restsize = 8;

    if( vlc_tls_Read( p_sys->stream, p_sys->buffer + 4, restsize, true ) < restsize )
    {
        msg_Err( p_access, "cannot read data 3" );
        return VLC_EGENERIC;
    }
    p_ck->i_sequence  = GetDWLE( p_sys->buffer + 4);
    p_ck->i_unknown   = GetWLE( p_sys->buffer + 8);

    /* Set i_size2 to 8 if this header was short, since a real value won't be
     * present in the buffer. Using 8 avoid reading additional data for the
     * packet.
     */
    if( restsize < 8 )
        p_ck->i_size2 = 8;
    else
        p_ck->i_size2 = GetWLE( p_sys->buffer + 10);

    p_ck->p_data      = p_sys->buffer + 12;
    p_ck->i_data      = p_ck->i_size2 - 8;

    if( p_ck->i_type == 0x4524 )   // $E (End-of-Stream Notification) Packet
    {
        if( p_ck->i_sequence == 0 )
        {
            msg_Warn( p_access, "EOF" );
            return VLC_EGENERIC;
        }
        else
        {
            msg_Warn( p_access, "next stream following" );
            return VLC_EGENERIC;
        }
    }
    else if( p_ck->i_type == 0x4324 ) // $C (Stream Change Notification) Packet
    {
        /* 0x4324 is CHUNK_TYPE_RESET: a new stream will follow with a sequence of 0 */
        msg_Warn( p_access, "next stream following (reset) seq=%d", p_ck->i_sequence  );
        return VLC_EGENERIC;
    }
    else if( (p_ck->i_type != 0x4824) && (p_ck->i_type != 0x4424) )
    {
        /* Unsupported so far:
         * $M (Metadata) Packet               0x4D24
         * $P (Packet-Pair) Packet            0x5024
         * $T (Test Data Notification) Packet 0x5424
         */
        msg_Err( p_access, "unrecognized chunk FATAL (0x%x)", p_ck->i_type );
        return VLC_EGENERIC;
    }

    if( (p_ck->i_data > 0) &&
        (vlc_tls_Read( p_sys->stream, &p_sys->buffer[12], p_ck->i_data,
                       true ) < p_ck->i_data) )
    {
        msg_Err( p_access, "cannot read data 4" );
        return VLC_EGENERIC;
    }

#if 0
    if( (p_sys->i_packet_sequence != 0) &&
        (p_ck->i_sequence != p_sys->i_packet_sequence) )
    {
        msg_Warn( p_access, "packet lost ? (%d != %d)", p_ck->i_sequence, p_sys->i_packet_sequence );
    }
#endif

    p_sys->i_packet_sequence = p_ck->i_sequence + 1;
    p_sys->i_packet_used   = 0;
    p_sys->i_packet_length = p_ck->i_data;
    p_sys->p_packet        = p_ck->p_data;

    return VLC_SUCCESS;
}