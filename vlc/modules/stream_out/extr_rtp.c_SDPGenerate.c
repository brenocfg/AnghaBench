#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct vlc_memstream {char* ptr; } ;
struct sockaddr_storage {int ss_len; int /*<<< orphan*/  ss_family; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_11__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ sout_stream_t ;
struct TYPE_12__ {int i_es; int proto; int /*<<< orphan*/  lock_es; scalar_t__ rtcp_mux; TYPE_5__** es; int /*<<< orphan*/ * psz_destination; } ;
typedef  TYPE_4__ sout_stream_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/ * fd; } ;
struct TYPE_14__ {int cat; int /*<<< orphan*/  fmtp; int /*<<< orphan*/  channels; int /*<<< orphan*/  clock_rate; int /*<<< orphan*/  ptname; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  payload_type; } ;
struct TYPE_13__ {int i_port; TYPE_2__ listen; int /*<<< orphan*/  rtsp_id; TYPE_6__ rtp_fmt; TYPE_1__* sinkv; } ;
typedef  TYPE_5__ sout_stream_id_sys_t ;
typedef  int socklen_t ;
typedef  TYPE_6__ rtp_format_t ;
typedef  int /*<<< orphan*/  dst ;
struct TYPE_9__ {int /*<<< orphan*/  rtp_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
#define  AUDIO_ES 134 
#define  IPPROTO_DCCP 133 
#define  IPPROTO_TCP 132 
#define  IPPROTO_UDP 131 
#define  IPPROTO_UDPLITE 130 
 char* RtspAppendTrackPath (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  SOUT_CFG_PREFIX ; 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getpeername (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdp_AddAttribute (struct vlc_memstream*,char*,char*,...) ; 
 int /*<<< orphan*/  sdp_AddMedia (struct vlc_memstream*,char const*,char const*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 char* toupper (unsigned char) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_sdp_Start (struct vlc_memstream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

char *SDPGenerate( sout_stream_t *p_stream, const char *rtsp_url )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    struct vlc_memstream sdp;
    struct sockaddr_storage dst;
    char *psz_sdp = NULL;
    socklen_t dstlen;
    int i;
    /*
     * When we have a fixed destination (typically when we do multicast),
     * we need to put the actual port numbers in the SDP.
     * When there is no fixed destination, we only support RTSP unicast
     * on-demand setup, so we should rather let the clients decide which ports
     * to use.
     * When there is both a fixed destination and RTSP unicast, we need to
     * put port numbers used by the fixed destination, otherwise the SDP would
     * become totally incorrect for multicast use. It should be noted that
     * port numbers from SDP with RTSP are only "recommendation" from the
     * server to the clients (per RFC2326), so only broken clients will fail
     * to handle this properly. There is no solution but to use two differents
     * output chain with two different RTSP URLs if you need to handle this
     * scenario.
     */
    int inclport;

    vlc_mutex_lock( &p_sys->lock_es );
    if( unlikely(p_sys->i_es == 0 || (rtsp_url != NULL && !p_sys->es[0]->rtsp_id)) )
        goto out; /* hmm... */

    if( p_sys->psz_destination != NULL )
    {
        inclport = 1;

        /* Oh boy, this is really ugly! */
        dstlen = sizeof( dst );
        if( p_sys->es[0]->listen.fd != NULL )
            getsockname( p_sys->es[0]->listen.fd[0],
                         (struct sockaddr *)&dst, &dstlen );
        else
            getpeername( p_sys->es[0]->sinkv[0].rtp_fd,
                         (struct sockaddr *)&dst, &dstlen );
    }
    else
    {
        inclport = 0;

        /* Check against URL format rtsp://[<ipv6>]:<port>/<path> */
        bool ipv6 = rtsp_url != NULL && strlen( rtsp_url ) > 7
                    && rtsp_url[7] == '[';

        /* Dummy destination address for RTSP */
        dstlen = ipv6 ? sizeof( struct sockaddr_in6 )
                      : sizeof( struct sockaddr_in );
        memset (&dst, 0, dstlen);
        dst.ss_family = ipv6 ? AF_INET6 : AF_INET;
#ifdef HAVE_SA_LEN
        dst.ss_len = dstlen;
#endif
    }

    if( vlc_sdp_Start( &sdp, VLC_OBJECT( p_stream ), SOUT_CFG_PREFIX,
                       NULL, 0, (struct sockaddr *)&dst, dstlen ) )
        goto out;

    /* TODO: a=source-filter */
    if( p_sys->rtcp_mux )
        sdp_AddAttribute( &sdp, "rtcp-mux", NULL );

    if( rtsp_url != NULL )
        sdp_AddAttribute ( &sdp, "control", "%s", rtsp_url );

    const char *proto = "RTP/AVP"; /* protocol */
    if( rtsp_url == NULL )
    {
        switch( p_sys->proto )
        {
            case IPPROTO_UDP:
                break;
            case IPPROTO_TCP:
                proto = "TCP/RTP/AVP";
                break;
            case IPPROTO_DCCP:
                proto = "DCCP/RTP/AVP";
                break;
            case IPPROTO_UDPLITE:
                return psz_sdp;
        }
    }

    for( i = 0; i < p_sys->i_es; i++ )
    {
        sout_stream_id_sys_t *id = p_sys->es[i];
        rtp_format_t *rtp_fmt = &id->rtp_fmt;
        const char *mime_major; /* major MIME type */

        switch( rtp_fmt->cat )
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

        sdp_AddMedia( &sdp, mime_major, proto, inclport * id->i_port,
                      rtp_fmt->payload_type, false, rtp_fmt->bitrate,
                      rtp_fmt->ptname, rtp_fmt->clock_rate, rtp_fmt->channels,
                      rtp_fmt->fmtp);

        /* cf RFC4566 §5.14 */
        if( inclport && !p_sys->rtcp_mux && (id->i_port & 1) )
            sdp_AddAttribute( &sdp, "rtcp", "%u", id->i_port + 1 );

        if( rtsp_url != NULL )
        {
            char *track_url = RtspAppendTrackPath( id->rtsp_id, rtsp_url );
            if( track_url != NULL )
            {
                sdp_AddAttribute( &sdp, "control", "%s", track_url );
                free( track_url );
            }
        }
        else
        {
            if( id->listen.fd != NULL )
                sdp_AddAttribute( &sdp, "setup", "passive" );
            if( p_sys->proto == IPPROTO_DCCP )
                sdp_AddAttribute( &sdp, "dccp-service-code", "SC:RTP%c",
                                  toupper( (unsigned char)mime_major[0] ) );
        }
    }

    if( vlc_memstream_close( &sdp ) == 0 )
        psz_sdp = sdp.ptr;
out:
    vlc_mutex_unlock( &p_sys->lock_es );
    return psz_sdp;
}