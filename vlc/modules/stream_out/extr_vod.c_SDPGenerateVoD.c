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
struct TYPE_7__ {scalar_t__ i_length; int i_es; TYPE_3__** es; int /*<<< orphan*/  p_vod; } ;
typedef  TYPE_1__ vod_media_t ;
struct vlc_memstream {char* ptr; } ;
struct sockaddr_storage {int ss_len; int /*<<< orphan*/  ss_family; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
struct TYPE_8__ {int cat; int /*<<< orphan*/  fmtp; int /*<<< orphan*/  channels; int /*<<< orphan*/  clock_rate; int /*<<< orphan*/  ptname; int /*<<< orphan*/  payload_type; } ;
typedef  TYPE_2__ rtp_format_t ;
struct TYPE_9__ {int /*<<< orphan*/  rtsp_id; TYPE_2__ rtp_fmt; } ;
typedef  TYPE_3__ media_es_t ;
struct TYPE_10__ {scalar_t__ rem; int /*<<< orphan*/  quot; } ;
typedef  TYPE_4__ lldiv_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
#define  AUDIO_ES 130 
 int /*<<< orphan*/  MS_FROM_VLC_TICK (scalar_t__) ; 
 char* RtspAppendTrackPath (int /*<<< orphan*/ ,char const*) ; 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_4__ lldiv (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdp_AddAttribute (struct vlc_memstream*,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  sdp_AddMedia (struct vlc_memstream*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 scalar_t__ vlc_sdp_Start (struct vlc_memstream*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

char *SDPGenerateVoD( const vod_media_t *p_media, const char *rtsp_url )
{
    assert(rtsp_url != NULL);
    /* Check against URL format rtsp://[<ipv6>]:<port>/<path> */
    bool ipv6 = strlen( rtsp_url ) > 7 && rtsp_url[7] == '[';

    /* Dummy destination address for RTSP */
    struct sockaddr_storage dst;
    socklen_t dstlen = ipv6 ? sizeof( struct sockaddr_in6 )
                            : sizeof( struct sockaddr_in );
    memset (&dst, 0, dstlen);
    dst.ss_family = ipv6 ? AF_INET6 : AF_INET;
#ifdef HAVE_SA_LEN
    dst.ss_len = dstlen;
#endif

    struct vlc_memstream sdp;

    if( vlc_sdp_Start( &sdp, VLC_OBJECT( p_media->p_vod ), "sout-rtp-",
                       NULL, 0, (struct sockaddr *)&dst, dstlen ) )
        return NULL;

    if( p_media->i_length > 0 )
    {
        lldiv_t d = lldiv( MS_FROM_VLC_TICK(p_media->i_length), 1000 );
        sdp_AddAttribute( &sdp, "range"," npt=0-%lld.%03u", d.quot,
                          (unsigned)d.rem );
    }

    sdp_AddAttribute( &sdp, "control", "%s", rtsp_url );

    /* No locking needed, the ES table can't be modified now */
    for( int i = 0; i < p_media->i_es; i++ )
    {
        media_es_t *p_es = p_media->es[i];
        rtp_format_t *rtp_fmt = &p_es->rtp_fmt;
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

        sdp_AddMedia( &sdp, mime_major, "RTP/AVP", 0,
                      rtp_fmt->payload_type, false, 0,
                      rtp_fmt->ptname, rtp_fmt->clock_rate, rtp_fmt->channels,
                      rtp_fmt->fmtp );

        char *track_url = RtspAppendTrackPath( p_es->rtsp_id, rtsp_url );
        if( track_url != NULL )
        {
            sdp_AddAttribute( &sdp, "control", "%s", track_url );
            free( track_url );
        }
    }

    return vlc_memstream_close( &sdp ) ? NULL : sdp.ptr;
}