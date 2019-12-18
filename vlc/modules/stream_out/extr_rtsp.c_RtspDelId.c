#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int sessionc; int /*<<< orphan*/  lock; TYPE_4__** sessionv; } ;
typedef  TYPE_1__ rtsp_stream_t ;
struct TYPE_11__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_2__ rtsp_stream_id_t ;
struct TYPE_12__ {TYPE_2__* id; } ;
typedef  TYPE_3__ rtsp_strack_t ;
struct TYPE_13__ {int trackc; TYPE_3__* trackv; } ;
typedef  TYPE_4__ rtsp_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  RtspTrackClose (TYPE_3__*) ; 
 int /*<<< orphan*/  TAB_ERASE (int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  httpd_UrlDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void RtspDelId( rtsp_stream_t *rtsp, rtsp_stream_id_t *id )
{
    httpd_UrlDelete( id->url );

    vlc_mutex_lock( &rtsp->lock );
    for( int i = 0; i < rtsp->sessionc; i++ )
    {
        rtsp_session_t *ses = rtsp->sessionv[i];

        for( int j = 0; j < ses->trackc; j++ )
        {
            if( ses->trackv[j].id == id )
            {
                rtsp_strack_t *tr = ses->trackv + j;
                RtspTrackClose( tr );
                TAB_ERASE(ses->trackc, ses->trackv, j);
            }
        }
    }

    vlc_mutex_unlock( &rtsp->lock );
    free( id );
}