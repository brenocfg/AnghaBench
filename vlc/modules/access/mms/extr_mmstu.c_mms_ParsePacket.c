#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_6__ {int i_header_packet_id_type; int i_media_packet_id_type; int i_packet_seq_num; int* p_header; size_t i_header; int* p_media; size_t i_media; scalar_t__ i_media_used; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int GetDWLE (int*) ; 
 size_t GetWLE (int*) ; 
 int MMS_PACKET_HEADER ; 
 int MMS_PACKET_MEDIA ; 
 int MMS_PACKET_UDP_TIMING ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,...) ; 
 int* realloc (int*,size_t) ; 

__attribute__((used)) static int  mms_ParsePacket( stream_t *p_access,
                             uint8_t *p_data, size_t i_data,
                             size_t *pi_used )
{
    access_sys_t        *p_sys = p_access->p_sys;
    int i_packet_seq_num;
    size_t i_packet_length;
    uint32_t i_packet_id;

    *pi_used = i_data; /* default */
    if( i_data <= 8 )
    {
        msg_Warn( p_access, "truncated packet (header incomplete)" );
        return -1;
    }

    i_packet_id = p_data[4];
    i_packet_seq_num = GetDWLE( p_data );
    i_packet_length = GetWLE( p_data + 6 );

    //msg_Warn( p_access, "------->i_packet_length=%d, i_data=%d", i_packet_length, i_data );

    if( i_packet_length > i_data || i_packet_length <= 8)
    {
     /*   msg_Dbg( p_access,
                 "truncated packet (Declared %d bytes, Actual %d bytes)",
                 i_packet_length, i_data  ); */
        *pi_used = 0;
        return -1;
    }
    else if( i_packet_length < i_data )
    {
        *pi_used = i_packet_length;
    }

    if( i_packet_id == 0xff )
    {
        msg_Warn( p_access,
                  "receive MMS UDP pair timing" );
        return( MMS_PACKET_UDP_TIMING );
    }

    if( i_packet_id != p_sys->i_header_packet_id_type &&
        i_packet_id != p_sys->i_media_packet_id_type )
    {
        msg_Warn( p_access, "incorrect Packet Id Type (0x%x)", i_packet_id );
        return -1;
    }

    /* we now have a media or a header packet */
    if( i_packet_seq_num != p_sys->i_packet_seq_num )
    {
#if 0
        /* FIXME for udp could be just wrong order ? */
        msg_Warn( p_access,
                  "detected packet lost (%d != %d)",
                  i_packet_seq_num,
                  p_sys->i_packet_seq_num );
#endif
    }
    p_sys->i_packet_seq_num = i_packet_seq_num + 1;

    if( i_packet_id == p_sys->i_header_packet_id_type )
    {
        uint8_t *p_reaced = realloc( p_sys->p_header,
                                     p_sys->i_header + i_packet_length - 8 );
        if( !p_reaced )
            return VLC_ENOMEM;

        memcpy( &p_reaced[p_sys->i_header], p_data + 8, i_packet_length - 8 );
        p_sys->p_header = p_reaced;
        p_sys->i_header += i_packet_length - 8;

/*        msg_Dbg( p_access,
                 "receive header packet (%d bytes)",
                 i_packet_length - 8 ); */

        return MMS_PACKET_HEADER;
    }
    else
    {
        free( p_sys->p_media );
        p_sys->i_media = 0;
        p_sys->i_media_used = 0;

        p_sys->p_media = malloc( i_packet_length - 8 ); // don't bother with preheader
        if( !p_sys->p_media )
            return VLC_ENOMEM;

        p_sys->i_media = i_packet_length - 8;
        memcpy( p_sys->p_media, p_data + 8, p_sys->i_media );
/*        msg_Dbg( p_access,
                 "receive media packet (%d bytes)",
                 i_packet_length - 8 ); */

        return MMS_PACKET_MEDIA;
    }
}