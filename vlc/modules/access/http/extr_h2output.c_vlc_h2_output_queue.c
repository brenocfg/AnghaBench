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
struct vlc_h2_queue {struct vlc_h2_frame** last; } ;
struct vlc_h2_output {scalar_t__ size; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; scalar_t__ failed; } ;
struct vlc_h2_frame {struct vlc_h2_frame* next; } ;

/* Variables and functions */
 scalar_t__ VLC_H2_MAX_QUEUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vlc_h2_frame*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_h2_frame_size (struct vlc_h2_frame*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlc_h2_output_queue(struct vlc_h2_output *out,
                               struct vlc_h2_queue *q, struct vlc_h2_frame *f)
{
    if (unlikely(f == NULL))
        return -1; /* memory error */

    /* Iterate the list to count size and find tail pointer */
    struct vlc_h2_frame **lastp = &f;
    size_t len = 0;

    do
    {
        struct vlc_h2_frame *n = *lastp;

        len += vlc_h2_frame_size(n);
        lastp = &n->next;
    }
    while (*lastp != NULL);

    vlc_mutex_lock(&out->lock);
    if (out->failed)
        goto error;

    out->size += len;
    if (out->size >= VLC_H2_MAX_QUEUE)
    {   /* The queue is full. This should never happen but it can be triggered
         * by an evil peer at the other end (e.g. sending a lot of pings and
         * never receiving pongs. Returning an error is better than filling
         * all memory. */
        out->size -= len;
        goto error;
    }

    assert(*(q->last) == NULL);
    *(q->last) = f;
    q->last = lastp;
    vlc_cond_signal(&out->wait);
    vlc_mutex_unlock(&out->lock);
    return 0;

error:
    vlc_mutex_unlock(&out->lock);
    while (f != NULL)
    {
        struct vlc_h2_frame *n = f->next;

        free(f);
        f = n;
    }
    return -1;
}