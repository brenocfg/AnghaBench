#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sout_stream_id_sys_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ rtsp_stream_t ;
struct TYPE_9__ {int setup_fd; int rtp_fd; int /*<<< orphan*/ * sout_id; } ;
typedef  TYPE_2__ rtsp_strack_t ;
struct TYPE_10__ {int trackc; TYPE_2__* trackv; } ;
typedef  TYPE_3__ rtsp_session_t ;

/* Variables and functions */
 TYPE_3__* RtspClientGet (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  TAB_ERASE (int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  rtp_del_sink (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void RtspTrackDetach( rtsp_stream_t *rtsp, const char *name,
                      sout_stream_id_sys_t *sout_id )
{
    rtsp_session_t *session;

    vlc_mutex_lock(&rtsp->lock);
    session = RtspClientGet(rtsp, name);

    if (session == NULL)
        goto out;

    for (int i = 0; i < session->trackc; i++)
    {
        rtsp_strack_t *tr = session->trackv + i;
        if (tr->sout_id == sout_id)
        {
            if (tr->setup_fd == -1)
            {
                /* No (more) SETUP information: better get rid of the
                 * track so that we can have new random ssrc and
                 * seq_init next time. */
                TAB_ERASE(session->trackc, session->trackv, i);
                break;
            }
            /* We keep the SETUP information of the track, but stop it */
            if (tr->rtp_fd != -1)
            {
                rtp_del_sink(tr->sout_id, tr->rtp_fd);
                tr->rtp_fd = -1;
            }
            tr->sout_id = NULL;
            break;
        }
    }

out:
    vlc_mutex_unlock(&rtsp->lock);
}