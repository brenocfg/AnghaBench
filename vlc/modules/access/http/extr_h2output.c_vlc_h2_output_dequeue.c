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
struct vlc_h2_queue {struct vlc_h2_frame** last; struct vlc_h2_frame* first; } ;
struct vlc_h2_output {size_t size; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  closing; struct vlc_h2_queue queue; struct vlc_h2_queue prio; } ;
struct vlc_h2_frame {struct vlc_h2_frame* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t vlc_h2_frame_size (struct vlc_h2_frame*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static struct vlc_h2_frame *vlc_h2_output_dequeue(struct vlc_h2_output *out)
{
    struct vlc_h2_queue *q;
    struct vlc_h2_frame *frame;
    size_t len;

    vlc_mutex_lock(&out->lock);

    for (;;)
    {
        q = &out->prio;
        if (q->first != NULL)
            break;

        q = &out->queue;
        if (q->first != NULL)
            break;

        if (unlikely(out->closing))
        {
            vlc_mutex_unlock(&out->lock);
            return NULL;
        }

        int canc = vlc_savecancel();
        vlc_cond_wait(&out->wait, &out->lock);
        vlc_restorecancel(canc);
    }

    frame = q->first;
    q->first = frame->next;
    if (frame->next == NULL)
    {
        assert(q->last == &frame->next);
        q->last = &q->first;
    }
    assert(q->last != &frame->next);

    len = vlc_h2_frame_size(frame);
    assert(out->size >= len);
    out->size -= len;

    vlc_mutex_unlock(&out->lock);

    frame->next = NULL;
    return frame;
}