#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {int /*<<< orphan*/  psz_location; int /*<<< orphan*/ * pf_seek; int /*<<< orphan*/  pf_control; int /*<<< orphan*/ * pf_block; int /*<<< orphan*/  pf_read; TYPE_2__* p_sys; scalar_t__ b_preparsing; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_9__ {int fd; int timeout; scalar_t__ length; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  Read ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char const*,int,char const*,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int net_OpenDgram (TYPE_1__*,char const*,int,char const*,int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int var_InheritInteger (TYPE_1__*,char*) ; 
 TYPE_2__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    stream_t     *p_access = (stream_t*)p_this;
    access_sys_t *sys;

    if( p_access->b_preparsing )
        return VLC_EGENERIC;

    sys = vlc_obj_malloc( p_this, sizeof( *sys ) );
    if( unlikely( sys == NULL ) )
        return VLC_ENOMEM;

    sys->length = 0;
    p_access->p_sys = sys;
    p_access->pf_read = Read;
    p_access->pf_block = NULL;
    p_access->pf_control = Control;
    p_access->pf_seek = NULL;

    char *psz_name = strdup( p_access->psz_location );
    char *psz_parser;
    const char *psz_server_addr, *psz_bind_addr = "";
    int  i_bind_port = 1234, i_server_port = 0;

    if( unlikely(psz_name == NULL) )
        return VLC_ENOMEM;

    /* Parse psz_name syntax :
     * [serveraddr[:serverport]][@[bindaddr]:[bindport]] */
    psz_parser = strchr( psz_name, '@' );
    if( psz_parser != NULL )
    {
        /* Found bind address and/or bind port */
        *psz_parser++ = '\0';
        psz_bind_addr = psz_parser;

        if( psz_bind_addr[0] == '[' )
            /* skips bracket'd IPv6 address */
            psz_parser = strchr( psz_parser, ']' );

        if( psz_parser != NULL )
        {
            psz_parser = strchr( psz_parser, ':' );
            if( psz_parser != NULL )
            {
                *psz_parser++ = '\0';
                i_bind_port = atoi( psz_parser );
            }
        }
    }

    psz_server_addr = psz_name;
    psz_parser = ( psz_server_addr[0] == '[' )
        ? strchr( psz_name, ']' ) /* skips bracket'd IPv6 address */
        : psz_name;

    if( psz_parser != NULL )
    {
        psz_parser = strchr( psz_parser, ':' );
        if( psz_parser != NULL )
        {
            *psz_parser++ = '\0';
            i_server_port = atoi( psz_parser );
        }
    }

    msg_Dbg( p_access, "opening server=%s:%d local=%s:%d",
             psz_server_addr, i_server_port, psz_bind_addr, i_bind_port );

    sys->fd = net_OpenDgram( p_access, psz_bind_addr, i_bind_port,
                             psz_server_addr, i_server_port, IPPROTO_UDP );
    free( psz_name );
    if( sys->fd == -1 )
    {
        msg_Err( p_access, "cannot open socket" );
        return VLC_EGENERIC;
    }

    sys->timeout = var_InheritInteger( p_access, "udp-timeout");
    if( sys->timeout > 0)
        sys->timeout *= 1000;

    return VLC_SUCCESS;
}