#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vlc_h2_output {int closing; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_h2_output*) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_h2_output_flush_unlocked (struct vlc_h2_output*) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void vlc_h2_output_destroy(struct vlc_h2_output *out)
{
    vlc_mutex_lock(&out->lock);
    out->closing = true;
    vlc_cond_signal(&out->wait);
    vlc_mutex_unlock(&out->lock);

    vlc_cancel(out->thread);
    vlc_join(out->thread, NULL);

    vlc_cond_destroy(&out->wait);
    vlc_mutex_destroy(&out->lock);
    /* Flush queues in case the thread was terminated within poll() and some
     * packets were still queued. */
    vlc_h2_output_flush_unlocked(out);
    free(out);
}