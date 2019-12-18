#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_17__ {int /*<<< orphan*/  psz_name; int /*<<< orphan*/  psz_url; TYPE_3__* p_sys; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_block; int /*<<< orphan*/ * pf_read; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_16__ {scalar_t__ i_data_packets_count; } ;
struct TYPE_19__ {char* psz_host; int i_port; } ;
struct TYPE_18__ {scalar_t__ i_packet_count; int i_flags_broadcast; int b_seekable; int i_size; int b_keep_alive; scalar_t__ i_packet_length; scalar_t__ i_header; TYPE_1__ asfh; TYPE_4__ url; int /*<<< orphan*/  lock_netwrite; int /*<<< orphan*/  i_timeout; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Block ; 
 int /*<<< orphan*/  Control ; 
 int MMSOpen (TYPE_2__*,TYPE_4__*,int) ; 
 scalar_t__ MMSStart (TYPE_2__*,int) ; 
 int /*<<< orphan*/  MMSTUClose (TYPE_2__*) ; 
 int MMS_PROTO_AUTO ; 
 int MMS_PROTO_TCP ; 
 int MMS_PROTO_UDP ; 
 int /*<<< orphan*/  Seek ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,char*,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  var_CreateGetInteger (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  vlc_UrlClean (TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_UrlParse (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

int  MMSTUOpen( stream_t *p_access )
{
    access_sys_t   *p_sys;
    int             i_proto;
    int             i_status;

    /* Set up p_access */
    p_access->pf_read = NULL;
    p_access->pf_block = Block;
    p_access->pf_control = Control;
    p_access->pf_seek = Seek;

    p_access->p_sys = p_sys = calloc( 1, sizeof( access_sys_t ) );
    if( !p_sys ) return VLC_ENOMEM;

    p_sys->i_timeout = var_CreateGetInteger( p_access, "mms-timeout" );

    vlc_mutex_init( &p_sys->lock_netwrite );

    /* *** Parse URL and get server addr/port and path *** */
    vlc_UrlParse( &p_sys->url, p_access->psz_url );
    if( p_sys->url.psz_host == NULL || *p_sys->url.psz_host == '\0' )
    {
        msg_Err( p_access, "invalid server name" );
        vlc_UrlClean( &p_sys->url );
        vlc_mutex_destroy( &p_sys->lock_netwrite );
        free( p_sys );
        return VLC_EGENERIC;
    }
    if( p_sys->url.i_port <= 0 )
    {
        p_sys->url.i_port = 1755;
    }

    /* *** connect to this server *** */
    /* look at  requested protocol (udp/tcp) */
    i_proto = MMS_PROTO_AUTO;
    if( !strncmp( p_access->psz_name, "mmsu", 4 ) )
    {
        i_proto = MMS_PROTO_UDP;
    }
    else if( !strncmp( p_access->psz_name, "mmst", 4 ) )
    {
        i_proto = MMS_PROTO_TCP;
    }

    /* connect */
    if( i_proto == MMS_PROTO_AUTO )
    {   /* first try with TCP and then UDP*/
        i_status = MMSOpen( p_access, &p_sys->url, MMS_PROTO_TCP );
        if( i_status )
            i_status = MMSOpen( p_access, &p_sys->url, MMS_PROTO_UDP );
    }
    else
    {
        i_status = MMSOpen( p_access, &p_sys->url, i_proto );
    }

    if( i_status )
    {
        msg_Err( p_access, "cannot connect to server" );
        vlc_UrlClean( &p_sys->url );
        vlc_mutex_destroy( &p_sys->lock_netwrite );
        free( p_sys );
        return VLC_EGENERIC;
    }

    msg_Dbg( p_access, "connected to %s:%d", p_sys->url.psz_host, p_sys->url.i_port );
    /*
     * i_flags_broadcast
     *  yy xx ?? ??
     *  broadcast    yy=0x02, xx= 0x00
     *  pre-recorded yy=0x01, xx= 0x80 if video, 0x00 no video
     */
    if( p_sys->i_packet_count <= 0 && p_sys->asfh.i_data_packets_count > 0 )
    {
        p_sys->i_packet_count = p_sys->asfh.i_data_packets_count;
    }
    if( p_sys->i_packet_count <= 0 || ( p_sys->i_flags_broadcast >> 24 ) == 0x02 )
    {
        p_sys->b_seekable = false;
    }
    else
    {
        p_sys->b_seekable = true;
        p_sys->i_size =
            (uint64_t)p_sys->i_header +
            (uint64_t)p_sys->i_packet_count * (uint64_t)p_sys->i_packet_length;
    }
    p_sys->b_keep_alive = false;

    /* *** Start stream *** */
    if( MMSStart( p_access, 0xffffffff ) < 0 )
    {
        msg_Err( p_access, "cannot start stream" );
        MMSTUClose ( p_access );
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}