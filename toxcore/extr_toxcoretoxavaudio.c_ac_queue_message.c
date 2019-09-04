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
struct TYPE_3__ {int pt; } ;
struct RTPMessage {TYPE_1__ header; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/  j_buf; } ;
typedef  TYPE_2__ ACSession ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_WARNING (char*) ; 
 int /*<<< orphan*/  free (struct RTPMessage*) ; 
 int jbuf_write (int /*<<< orphan*/ ,struct RTPMessage*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int rtp_TypeAudio ; 

int ac_queue_message(void *acp, struct RTPMessage *msg)
{
    if (!acp || !msg)
        return -1;

    if ((msg->header.pt & 0x7f) == (rtp_TypeAudio + 2) % 128) {
        LOGGER_WARNING("Got dummy!");
        free(msg);
        return 0;
    }

    if ((msg->header.pt & 0x7f) != rtp_TypeAudio % 128) {
        LOGGER_WARNING("Invalid payload type!");
        free(msg);
        return -1;
    }

    ACSession *ac = acp;

    pthread_mutex_lock(ac->queue_mutex);
    int rc = jbuf_write(ac->j_buf, msg);
    pthread_mutex_unlock(ac->queue_mutex);

    if (rc == -1) {
        LOGGER_WARNING("Could not queue the message!");
        free(msg);
        return -1;
    }

    return 0;
}