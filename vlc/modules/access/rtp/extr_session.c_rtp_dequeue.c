#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_13__ {int jitter; scalar_t__ last_seq; TYPE_4__* blocks; } ;
typedef  TYPE_1__ rtp_source_t ;
struct TYPE_14__ {unsigned int srcc; TYPE_1__** srcv; } ;
typedef  TYPE_2__ rtp_session_t ;
struct TYPE_15__ {int /*<<< orphan*/  frequency; } ;
typedef  TYPE_3__ rtp_pt_t ;
typedef  scalar_t__ int16_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_16__ {scalar_t__ i_pts; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  rtp_decode (int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_1__*) ; 
 TYPE_3__* rtp_find_ptype (TYPE_2__ const*,TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ rtp_seq (TYPE_4__*) ; 
 scalar_t__ vlc_tick_from_samples (int,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_now () ; 

bool rtp_dequeue (demux_t *demux, const rtp_session_t *session,
                  vlc_tick_t *restrict deadlinep)
{
    vlc_tick_t now = vlc_tick_now ();
    bool pending = false;

    *deadlinep = INT64_MAX;

    for (unsigned i = 0, max = session->srcc; i < max; i++)
    {
        rtp_source_t *src = session->srcv[i];
        block_t *block;

        /* Because of IP packet delay variation (IPDV), we need to guesstimate
         * how long to wait for a missing packet in the RTP sequence
         * (see RFC3393 for background on IPDV).
         *
         * This situation occurs if a packet got lost, or if the network has
         * re-ordered packets. Unfortunately, the MSL is 2 minutes, orders of
         * magnitude too long for multimedia. We need a trade-off.
         * If we underestimated IPDV, we may have to discard valid but late
         * packets. If we overestimate it, we will either cause too much
         * delay, or worse, underflow our downstream buffers, as we wait for
         * definitely a lost packets.
         *
         * The rest of the "de-jitter buffer" work is done by the internal
         * LibVLC E/S-out clock synchronization. Here, we need to bother about
         * re-ordering packets, as decoders can't cope with mis-ordered data.
         */
        while (((block = src->blocks)) != NULL)
        {
            if ((int16_t)(rtp_seq (block) - (src->last_seq + 1)) <= 0)
            {   /* Next (or earlier) block ready, no need to wait */
                rtp_decode (demux, session, src);
                continue;
            }

            /* Wait for 3 times the inter-arrival delay variance (about 99.7%
             * match for random gaussian jitter).
             */
            vlc_tick_t deadline;
            const rtp_pt_t *pt = rtp_find_ptype (session, src, block, NULL);
            if (pt)
                deadline = vlc_tick_from_samples(3 * src->jitter, pt->frequency);
            else
                deadline = 0; /* no jitter estimate with no frequency :( */

            /* Make sure we wait at least for 25 msec */
            if (deadline < VLC_TICK_FROM_MS(25))
                deadline = VLC_TICK_FROM_MS(25);

            /* Additionnaly, we implicitly wait for the packetization time
             * multiplied by the number of missing packets. block is the first
             * non-missing packet (lowest sequence number). We have no better
             * estimated time of arrival, as we do not know the RTP timestamp
             * of not yet received packets. */
            deadline += block->i_pts;
            if (now >= deadline)
            {
                rtp_decode (demux, session, src);
                continue;
            }
            if (*deadlinep > deadline)
                *deadlinep = deadline;
            pending = true; /* packet pending in buffer */
            break;
        }
    }
    return pending;
}