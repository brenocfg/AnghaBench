#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct recorder {int failed; int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; struct record_packet* previous; scalar_t__ stopped; int /*<<< orphan*/  queue_cond; } ;
struct TYPE_2__ {int duration; int pts; } ;
struct record_packet {TYPE_1__ packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGD (char*) ; 
 int /*<<< orphan*/  LOGE (char*) ; 
 int /*<<< orphan*/  LOGW (char*) ; 
 int /*<<< orphan*/  cond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 scalar_t__ queue_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_take (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct record_packet**) ; 
 int /*<<< orphan*/  record_packet_delete (struct record_packet*) ; 
 int /*<<< orphan*/  recorder_queue_clear (int /*<<< orphan*/ *) ; 
 int recorder_write (struct recorder*,TYPE_1__*) ; 

__attribute__((used)) static int
run_recorder(void *data) {
    struct recorder *recorder = data;

    for (;;) {
        mutex_lock(recorder->mutex);

        while (!recorder->stopped && queue_is_empty(&recorder->queue)) {
            cond_wait(recorder->queue_cond, recorder->mutex);
        }

        // if stopped is set, continue to process the remaining events (to
        // finish the recording) before actually stopping

        if (recorder->stopped && queue_is_empty(&recorder->queue)) {
            mutex_unlock(recorder->mutex);
            struct record_packet *last = recorder->previous;
            if (last) {
                // assign an arbitrary duration to the last packet
                last->packet.duration = 100000;
                bool ok = recorder_write(recorder, &last->packet);
                if (!ok) {
                    // failing to write the last frame is not very serious, no
                    // future frame may depend on it, so the resulting file
                    // will still be valid
                    LOGW("Could not record last packet");
                }
                record_packet_delete(last);
            }
            break;
        }

        struct record_packet *rec;
        queue_take(&recorder->queue, next, &rec);

        mutex_unlock(recorder->mutex);

        // recorder->previous is only written from this thread, no need to lock
        struct record_packet *previous = recorder->previous;
        recorder->previous = rec;

        if (!previous) {
            // we just received the first packet
            continue;
        }

        // we now know the duration of the previous packet
        previous->packet.duration = rec->packet.pts - previous->packet.pts;

        bool ok = recorder_write(recorder, &previous->packet);
        record_packet_delete(previous);
        if (!ok) {
            LOGE("Could not record packet");

            mutex_lock(recorder->mutex);
            recorder->failed = true;
            // discard pending packets
            recorder_queue_clear(&recorder->queue);
            mutex_unlock(recorder->mutex);
            break;
        }

    }

    LOGD("Recorder thread ended");

    return 0;
}