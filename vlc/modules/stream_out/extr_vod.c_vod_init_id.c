#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int i_es; int /*<<< orphan*/  rtsp; TYPE_3__** es; int /*<<< orphan*/ * psz_mux; } ;
typedef  TYPE_1__ vod_media_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sout_stream_id_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  fmtp; } ;
typedef  TYPE_2__ rtp_format_t ;
struct TYPE_11__ {int /*<<< orphan*/ * fmtp; } ;
struct TYPE_10__ {int es_id; int /*<<< orphan*/  rtsp_id; TYPE_7__ rtp_fmt; } ;
typedef  TYPE_3__ media_es_t ;

/* Variables and functions */
 int RtspTrackAttach (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ *) ; 

int vod_init_id(vod_media_t *p_media, const char *psz_session, int es_id,
                sout_stream_id_sys_t *sout_id, rtp_format_t *rtp_fmt,
                uint32_t *ssrc, uint16_t *seq_init)
{
    media_es_t *p_es;

    if (p_media->psz_mux != NULL)
    {
        assert(p_media->i_es == 1);
        p_es = p_media->es[0];
    }
    else
    {
        p_es = NULL;
        /* No locking needed, the ES table can't be modified now */
        for (int i = 0; i < p_media->i_es; i++)
        {
            if (p_media->es[i]->es_id == es_id)
            {
                p_es = p_media->es[i];
                break;
            }
        }
        if (p_es == NULL)
            return VLC_EGENERIC;
    }

    memcpy(rtp_fmt, &p_es->rtp_fmt, sizeof(*rtp_fmt));
    if (p_es->rtp_fmt.fmtp != NULL)
        rtp_fmt->fmtp = strdup(p_es->rtp_fmt.fmtp);

    return RtspTrackAttach(p_media->rtsp, psz_session, p_es->rtsp_id,
                           sout_id, ssrc, seq_init);
}