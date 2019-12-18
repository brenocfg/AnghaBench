#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* psz_rtsp_control_v6; char* psz_rtsp_control_v4; scalar_t__ i_length; int i_es; TYPE_3__** es; int /*<<< orphan*/  p_vod; } ;
typedef  TYPE_2__ vod_media_t ;
struct vlc_memstream {char* ptr; } ;
struct sockaddr_storage {int ss_len; int /*<<< orphan*/  ss_family; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
struct TYPE_7__ {int i_cat; } ;
struct TYPE_9__ {int /*<<< orphan*/  psz_fmtp; int /*<<< orphan*/  i_channels; int /*<<< orphan*/  i_clock_rate; int /*<<< orphan*/  psz_ptname; int /*<<< orphan*/  i_payload_type; TYPE_1__ fmt; } ;
typedef  TYPE_3__ media_es_t ;
struct TYPE_10__ {scalar_t__ rem; int /*<<< orphan*/  quot; } ;
typedef  TYPE_4__ lldiv_t ;
typedef  int /*<<< orphan*/  httpd_client_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
#define  AUDIO_ES 130 
 int /*<<< orphan*/  MS_FROM_VLC_TICK (scalar_t__) ; 
 int NI_MAXNUMERICHOST ; 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/ * httpd_ServerIP (int /*<<< orphan*/ *,char*,int*) ; 
 TYPE_4__ lldiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdp_AddAttribute (struct vlc_memstream*,char*,char const*,char*,int,...) ; 
 int /*<<< orphan*/  sdp_AddMedia (struct vlc_memstream*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 scalar_t__ vlc_sdp_Start (struct vlc_memstream*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

__attribute__((used)) static char *SDPGenerate( const vod_media_t *p_media, httpd_client_t *cl )
{
    struct vlc_memstream sdp;
    char ip[NI_MAXNUMERICHOST];
    const char *psz_control;
    int port;

    if( httpd_ServerIP( cl, ip, &port ) == NULL )
        return NULL;

    bool ipv6 = ( strchr( ip, ':' ) != NULL );

    psz_control = ipv6 ? p_media->psz_rtsp_control_v6
                       : p_media->psz_rtsp_control_v4;

    /* Dummy destination address for RTSP */
    struct sockaddr_storage dst;
    socklen_t dstlen = ipv6 ? sizeof( struct sockaddr_in6 )
                            : sizeof( struct sockaddr_in );
    memset (&dst, 0, dstlen);
    dst.ss_family = ipv6 ? AF_INET6 : AF_INET;
#ifdef HAVE_SA_LEN
    dst.ss_len = dstlen;
#endif

    if( vlc_sdp_Start( &sdp, VLC_OBJECT( p_media->p_vod ), "sout-rtp-",
                       NULL, 0, (struct sockaddr *)&dst, dstlen ) )
        return NULL;

    if( p_media->i_length > 0 )
    {
        lldiv_t d = lldiv( MS_FROM_VLC_TICK(p_media->i_length), VLC_TICK_FROM_MS(1) );
        sdp_AddAttribute( &sdp, "range","npt=0-%lld.%03u", d.quot,
                          (unsigned)d.rem );
    }

    for( int i = 0; i < p_media->i_es; i++ )
    {
        media_es_t *p_es = p_media->es[i];
        const char *mime_major; /* major MIME type */

        switch( p_es->fmt.i_cat )
        {
            case VIDEO_ES:
                mime_major = "video";
                break;
            case AUDIO_ES:
                mime_major = "audio";
                break;
            case SPU_ES:
                mime_major = "text";
                break;
            default:
                continue;
        }

        sdp_AddMedia( &sdp, mime_major, "RTP/AVP", 0 /* p_es->i_port */,
                      p_es->i_payload_type, false, 0,
                      p_es->psz_ptname, p_es->i_clock_rate, p_es->i_channels,
                      p_es->psz_fmtp );

        sdp_AddAttribute( &sdp, "control", psz_control, ip, port, i );
    }

    return vlc_memstream_close( &sdp ) ? NULL : sdp.ptr;
}