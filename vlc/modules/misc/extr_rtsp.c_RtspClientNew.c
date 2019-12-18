#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  i_throttle_users; int /*<<< orphan*/  i_connections; } ;
typedef  TYPE_1__ vod_sys_t ;
struct TYPE_10__ {TYPE_4__* p_vod; int /*<<< orphan*/  rtsp; int /*<<< orphan*/  i_rtsp; } ;
typedef  TYPE_2__ vod_media_t ;
struct TYPE_11__ {char* psz_session; scalar_t__ es; } ;
typedef  TYPE_3__ rtsp_client_t ;
struct TYPE_12__ {TYPE_1__* p_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtsp_client_t *RtspClientNew( vod_media_t *p_media, char *psz_session )
{
    rtsp_client_t *p_rtsp = calloc( 1, sizeof(rtsp_client_t) );

    if( !p_rtsp )
        return NULL;
    p_rtsp->es = 0;

    p_rtsp->psz_session = psz_session;
    TAB_APPEND( p_media->i_rtsp, p_media->rtsp, p_rtsp );

    vod_sys_t *p_sys = p_media->p_vod->p_sys;
    p_sys->i_connections++;
    msg_Dbg( p_media->p_vod, "new session: %s, connections: %d",
             psz_session, p_sys->i_throttle_users );

    return p_rtsp;
}