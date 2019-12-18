#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int pt; } ;
struct RTPMessage {TYPE_1__ header; } ;
struct TYPE_4__ {void* linfts; int lcfd; int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/  vbuf_raw; } ;
typedef  TYPE_2__ VCSession ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_WARNING (char*) ; 
 void* current_time_monotonic () ; 
 int /*<<< orphan*/  free (struct RTPMessage*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 struct RTPMessage* rb_write (int /*<<< orphan*/ ,struct RTPMessage*) ; 
 int rtp_TypeVideo ; 

int vc_queue_message(void *vcp, struct RTPMessage *msg)
{
    /* This function does the reconstruction of video packets.
     * See more info about video splitting in docs
     */
    if (!vcp || !msg)
        return -1;

    if (msg->header.pt == (rtp_TypeVideo + 2) % 128) {
        LOGGER_WARNING("Got dummy!");
        free(msg);
        return 0;
    }

    if (msg->header.pt != rtp_TypeVideo % 128) {
        LOGGER_WARNING("Invalid payload type!");
        free(msg);
        return -1;
    }

    VCSession *vc = vcp;

    pthread_mutex_lock(vc->queue_mutex);
    free(rb_write(vc->vbuf_raw, msg));
    {
        /* Calculate time took for peer to send us this frame */
        uint32_t t_lcfd = current_time_monotonic() - vc->linfts;
        vc->lcfd = t_lcfd > 100 ? vc->lcfd : t_lcfd;
        vc->linfts = current_time_monotonic();
    }
    pthread_mutex_unlock(vc->queue_mutex);

    return 0;
}