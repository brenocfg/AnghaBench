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
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int b_rtsp_kasenna; int i_mcast_port; int i_packet_size; int i_port; int i_sid; int b_concert; int /*<<< orphan*/  i_duration; void* psz_mcast_ip; void* psz_name; void* psz_password; void* psz_user; void* psz_location; void* psz_server; void* psz_uri; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_FROM_US (scalar_t__) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/ * strcasestr (char*,char*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ParseLine ( stream_t *p_demux, char *psz_line )
{
    char        *psz_bol;
    demux_sys_t *p_sys = p_demux->p_sys;

    psz_bol = psz_line;

    /* Remove unnecessary tabs or spaces at the beginning of line */
    while( *psz_bol == ' ' || *psz_bol == '\t' ||
           *psz_bol == '\n' || *psz_bol == '\r' )
    {
        psz_bol++;
    }

    if( !strncasecmp( psz_bol, "rtsp://", sizeof("rtsp://") - 1 ) )
    {
        /* We found the link, it was inside a sgiQTFileBegin */
        free( p_sys->psz_uri );
        p_sys->psz_uri = strdup( psz_bol );
    }
    else if( !strncasecmp( psz_bol, "Stream=\"", sizeof("Stream=\"") - 1 ) )
    {
        psz_bol += sizeof("Stream=\"") - 1;
        char* psz_tmp = strrchr( psz_bol, '"' );
        if( !psz_tmp )
            return 0;
        psz_tmp[0] = '\0';
        /* We cheat around xdma. for some reason xdma links work different then rtsp */
        if( !strncasecmp( psz_bol, "xdma://", sizeof("xdma://") - 1 ) )
        {
            psz_bol[0] = 'r';
            psz_bol[1] = 't';
            psz_bol[2] = 's';
            psz_bol[3] = 'p';
        }
        free( p_sys->psz_uri );
        p_sys->psz_uri = strdup( psz_bol );
    }
    else if( !strncasecmp( psz_bol, "sgiNameServerHost=", sizeof("sgiNameServerHost=") - 1 ) )
    {
        psz_bol += sizeof("sgiNameServerHost=") - 1;
        free( p_sys->psz_server );
        p_sys->psz_server = strdup( psz_bol );
    }
    else if( !strncasecmp( psz_bol, "sgiMovieName=", sizeof("sgiMovieName=") - 1 ) )
    {
        psz_bol += sizeof("sgiMovieName=") - 1;
        free( p_sys->psz_location );
        p_sys->psz_location = strdup( psz_bol );
    }
    else if( !strncasecmp( psz_bol, "sgiUserAccount=", sizeof("sgiUserAccount=") - 1 ) )
    {
        psz_bol += sizeof("sgiUserAccount=") - 1;
        free( p_sys->psz_user );
        p_sys->psz_user = strdup( psz_bol );
    }
    else if( !strncasecmp( psz_bol, "sgiUserPassword=", sizeof("sgiUserPassword=") - 1 ) )
    {
        psz_bol += sizeof("sgiUserPassword=") - 1;
        free( p_sys->psz_password );
        p_sys->psz_password = strdup( psz_bol );
    }
    else if( !strncasecmp( psz_bol, "sgiShowingName=", sizeof("sgiShowingName=") - 1 ) )
    {
        psz_bol += sizeof("sgiShowingName=") - 1;
        free( p_sys->psz_name );
        p_sys->psz_name = strdup( psz_bol );
    }
    else if( !strncasecmp( psz_bol, "sgiFormatName=", sizeof("sgiFormatName=") - 1 ) )
    {
        psz_bol += sizeof("sgiFormatName=") - 1;
        if( strcasestr( psz_bol, "MPEG-4") == NULL ) /*not mpeg4 found in string */
            p_sys->b_rtsp_kasenna = true;
    }
    else if( !strncasecmp( psz_bol, "sgiMulticastAddress=", sizeof("sgiMulticastAddress=") - 1 ) )
    {
        psz_bol += sizeof("sgiMulticastAddress=") - 1;
        free( p_sys->psz_mcast_ip );
        p_sys->psz_mcast_ip = strdup( psz_bol );
    }
    else if( !strncasecmp( psz_bol, "sgiMulticastPort=", sizeof("sgiMulticastPort=") - 1 ) )
    {
        psz_bol += sizeof("sgiMulticastPort=") - 1;
        p_sys->i_mcast_port = (int) strtol( psz_bol, NULL, 0 );
    }
    else if( !strncasecmp( psz_bol, "sgiPacketSize=", sizeof("sgiPacketSize=") - 1 ) )
    {
        psz_bol += sizeof("sgiPacketSize=") - 1;
        p_sys->i_packet_size = (int) strtol( psz_bol, NULL, 0 );
    }
    else if( !strncasecmp( psz_bol, "sgiDuration=", sizeof("sgiDuration=") - 1 ) )
    {
        psz_bol += sizeof("sgiDuration=") - 1;
        p_sys->i_duration = VLC_TICK_FROM_US( strtol( psz_bol, NULL, 0 ) );
    }
    else if( !strncasecmp( psz_bol, "sgiRtspPort=", sizeof("sgiRtspPort=") - 1 ) )
    {
        psz_bol += sizeof("sgiRtspPort=") - 1;
        p_sys->i_port = (int) strtol( psz_bol, NULL, 0 );
    }
    else if( !strncasecmp( psz_bol, "sgiSid=", sizeof("sgiSid=") - 1 ) )
    {
        psz_bol += sizeof("sgiSid=") - 1;
        p_sys->i_sid = (int) strtol( psz_bol, NULL, 0 );
    }
    else if( !strncasecmp( psz_bol, "DeliveryService=cds", sizeof("DeliveryService=cds") - 1 ) )
    {
        p_sys->b_concert = true;
    }
    else
    {
        /* This line isn't really important */
        return 0;
    }
    return VLC_SUCCESS;
}