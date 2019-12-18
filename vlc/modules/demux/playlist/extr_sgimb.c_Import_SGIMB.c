#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_2__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {int b_rtsp_kasenna; int b_concert; scalar_t__ i_sid; scalar_t__ i_port; scalar_t__ i_duration; scalar_t__ i_packet_size; scalar_t__ i_mcast_port; int /*<<< orphan*/ * psz_mcast_ip; int /*<<< orphan*/ * psz_password; int /*<<< orphan*/ * psz_user; int /*<<< orphan*/ * psz_name; int /*<<< orphan*/ * psz_location; int /*<<< orphan*/ * psz_server; int /*<<< orphan*/ * psz_uri; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FILE (TYPE_1__*) ; 
 int /*<<< orphan*/  MAX_LINE ; 
 int /*<<< orphan*/  ReadDir ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  access_vaDirectoryControlHelper ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 scalar_t__ strncasecmp (char*,char*,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 

int Import_SGIMB( vlc_object_t * p_this )
{
    stream_t *p_demux = (stream_t *)p_this;
    const uint8_t *p_peek;
    int i_size;

    CHECK_FILE(p_demux);
    /* Lets check the content to see if this is a sgi mediabase file */
    i_size = vlc_stream_Peek( p_demux->s, &p_peek, MAX_LINE );
    i_size -= sizeof("sgiNameServerHost=") - 1;
    if ( i_size > 0 )
    {
        unsigned int i_len = sizeof("sgiNameServerHost=") - 1;
        while ( i_size && strncasecmp( (char *)p_peek, "sgiNameServerHost=", i_len ) )
        {
            p_peek++;
            i_size--;
        }
        if ( !strncasecmp( (char *)p_peek, "sgiNameServerHost=", i_len ) )
        {
            demux_sys_t *p_sys = malloc(sizeof (*p_sys));
            if( unlikely(p_sys == NULL) )
                return VLC_ENOMEM;

            msg_Dbg( p_demux, "using SGIMB playlist reader" );
            p_demux->pf_readdir = ReadDir;
            p_demux->pf_control = access_vaDirectoryControlHelper;
            p_demux->p_sys = p_sys;
            p_sys->psz_uri = NULL;
            p_sys->psz_server = NULL;
            p_sys->psz_location = NULL;
            p_sys->psz_name = NULL;
            p_sys->psz_user = NULL;
            p_sys->psz_password = NULL;
            p_sys->psz_mcast_ip = NULL;
            p_sys->i_mcast_port = 0;
            p_sys->i_packet_size = 0;
            p_sys->i_duration = 0;
            p_sys->i_port = 0;
            p_sys->i_sid = 0;
            p_sys->b_rtsp_kasenna = false;
            p_sys->b_concert = false;

            return VLC_SUCCESS;
        }
    }
    return VLC_EGENERIC;
}