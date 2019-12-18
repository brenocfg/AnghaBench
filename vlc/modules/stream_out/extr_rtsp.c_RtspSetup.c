#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vod_media_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {scalar_t__ timeout; int /*<<< orphan*/ * url; int /*<<< orphan*/ * psz_path; int /*<<< orphan*/ * host; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; int /*<<< orphan*/ * vod_media; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_1__ rtsp_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTTPD_MSG_DESCRIBE ; 
 int /*<<< orphan*/  HTTPD_MSG_GETPARAMETER ; 
 int /*<<< orphan*/  HTTPD_MSG_PAUSE ; 
 int /*<<< orphan*/  HTTPD_MSG_PLAY ; 
 int /*<<< orphan*/  HTTPD_MSG_SETUP ; 
 int /*<<< orphan*/  HTTPD_MSG_TEARDOWN ; 
 int /*<<< orphan*/  RtspCallback ; 
 int /*<<< orphan*/  RtspTimeOut ; 
 int /*<<< orphan*/  RtspUnsetup (TYPE_1__*) ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  httpd_UrlCatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * httpd_UrlNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_rtsp_HostNew (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_from_sec (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_timer_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

rtsp_stream_t *RtspSetup( vlc_object_t *owner, vod_media_t *media,
                          const char *path )
{
    rtsp_stream_t *rtsp = calloc( 1, sizeof( *rtsp ) );

    if( unlikely(rtsp == NULL) )
        return NULL;

    rtsp->owner = owner;
    rtsp->vod_media = media;
    vlc_mutex_init( &rtsp->lock );

    rtsp->timeout = vlc_tick_from_sec(__MAX(0,var_InheritInteger(owner, "rtsp-timeout")));
    if (rtsp->timeout != 0)
    {
        if (vlc_timer_create(&rtsp->timer, RtspTimeOut, rtsp))
            goto error;
    }

    rtsp->psz_path = strdup( (path != NULL) ? path : "/" );
    if( rtsp->psz_path == NULL )
        goto error;

    msg_Dbg( owner, "RTSP stream at %s", rtsp->psz_path );

    rtsp->host = vlc_rtsp_HostNew( VLC_OBJECT(owner) );
    if( rtsp->host == NULL )
        goto error;

    char *user = var_InheritString(owner, "sout-rtsp-user");
    char *pwd = var_InheritString(owner, "sout-rtsp-pwd");

    rtsp->url = httpd_UrlNew( rtsp->host, rtsp->psz_path, user, pwd );
    free(user);
    free(pwd);
    if( rtsp->url == NULL )
        goto error;

    httpd_UrlCatch( rtsp->url, HTTPD_MSG_DESCRIBE, RtspCallback, (void*)rtsp );
    httpd_UrlCatch( rtsp->url, HTTPD_MSG_SETUP,    RtspCallback, (void*)rtsp );
    httpd_UrlCatch( rtsp->url, HTTPD_MSG_PLAY,     RtspCallback, (void*)rtsp );
    httpd_UrlCatch( rtsp->url, HTTPD_MSG_PAUSE,    RtspCallback, (void*)rtsp );
    httpd_UrlCatch( rtsp->url, HTTPD_MSG_GETPARAMETER, RtspCallback,
                    (void*)rtsp );
    httpd_UrlCatch( rtsp->url, HTTPD_MSG_TEARDOWN, RtspCallback, (void*)rtsp );
    return rtsp;

error:
    RtspUnsetup( rtsp );
    return NULL;
}