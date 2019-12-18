#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sessionc; scalar_t__ timeout; int /*<<< orphan*/  lock; struct TYPE_5__* psz_path; int /*<<< orphan*/  timer; int /*<<< orphan*/ * sessionv; scalar_t__ host; scalar_t__ url; } ;
typedef  TYPE_1__ rtsp_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  RtspClientDel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  httpd_HostDelete (scalar_t__) ; 
 int /*<<< orphan*/  httpd_UrlDelete (scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_timer_destroy (int /*<<< orphan*/ ) ; 

void RtspUnsetup( rtsp_stream_t *rtsp )
{
    if( rtsp->url )
        httpd_UrlDelete( rtsp->url );

    if( rtsp->host )
        httpd_HostDelete( rtsp->host );

    while( rtsp->sessionc > 0 )
        RtspClientDel( rtsp, rtsp->sessionv[0] );

    if (rtsp->timeout != 0)
        vlc_timer_destroy(rtsp->timer);

    free( rtsp->psz_path );
    vlc_mutex_destroy( &rtsp->lock );

    free( rtsp );
}