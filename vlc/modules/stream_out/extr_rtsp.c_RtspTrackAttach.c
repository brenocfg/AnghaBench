#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  sout_stream_id_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ rtsp_stream_t ;
typedef  int /*<<< orphan*/  rtsp_stream_id_t ;
struct TYPE_10__ {int rtp_fd; int setup_fd; scalar_t__ seq_init; scalar_t__ ssrc; int /*<<< orphan*/ * sout_id; int /*<<< orphan*/ * id; } ;
typedef  TYPE_2__ rtsp_strack_t ;
struct TYPE_11__ {int trackc; TYPE_2__* trackv; } ;
typedef  TYPE_3__ rtsp_session_t ;

/* Variables and functions */
 TYPE_3__* RtspClientGet (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  TAB_APPEND (int,TYPE_2__*,TYPE_2__) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int dup_socket (int) ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 
 int /*<<< orphan*/  rtp_add_sink (int /*<<< orphan*/ *,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_rand_bytes (scalar_t__*,int) ; 

int RtspTrackAttach( rtsp_stream_t *rtsp, const char *name,
                     rtsp_stream_id_t *id, sout_stream_id_sys_t *sout_id,
                     uint32_t *ssrc, uint16_t *seq_init )
{
    int val = VLC_EGENERIC;
    rtsp_session_t *session;

    vlc_mutex_lock(&rtsp->lock);
    session = RtspClientGet(rtsp, name);

    if (session == NULL)
        goto out;

    rtsp_strack_t *tr = NULL;
    for (int i = 0; i < session->trackc; i++)
    {
        if (session->trackv[i].id == id)
        {
            tr = session->trackv + i;
            break;
        }
    }

    if (tr != NULL)
    {
        tr->sout_id = sout_id;
        tr->rtp_fd = dup_socket(tr->setup_fd);
    }
    else
    {
        /* The track was not SETUP. We still create one because we'll
         * need the sout_id if we set it up later. */
        rtsp_strack_t track = { .id = id, .sout_id = sout_id,
                                .setup_fd = -1, .rtp_fd = -1 };
        vlc_rand_bytes (&track.seq_init, sizeof (track.seq_init));
        vlc_rand_bytes (&track.ssrc, sizeof (track.ssrc));

        TAB_APPEND(session->trackc, session->trackv, track);
        tr = session->trackv + session->trackc - 1;
    }

    *ssrc = ntohl(tr->ssrc);
    *seq_init = tr->seq_init;

    if (tr->rtp_fd != -1)
    {
        uint16_t seq;
        rtp_add_sink(tr->sout_id, tr->rtp_fd, false, &seq);
        /* To avoid race conditions, sout_id->i_seq_sent_next must
         * be set here and now. Make sure the caller did its job
         * properly when passing seq_init. */
        assert(tr->seq_init == seq);
    }

    val = VLC_SUCCESS;
out:
    vlc_mutex_unlock(&rtsp->lock);
    return val;
}