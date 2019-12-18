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
struct vlc_tls {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last; } ;
struct TYPE_3__ {int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last; } ;
struct vlc_h2_output {int failed; int closing; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  thread; scalar_t__ size; TYPE_2__ queue; TYPE_1__ prio; struct vlc_tls* tls; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_INPUT ; 
 int /*<<< orphan*/  free (struct vlc_h2_output*) ; 
 struct vlc_h2_output* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,void* (*) (void*),struct vlc_h2_output*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 void* vlc_h2_client_output_thread (void*) ; 
 void* vlc_h2_output_thread (void*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

struct vlc_h2_output *vlc_h2_output_create(struct vlc_tls *tls, bool client)
{
    struct vlc_h2_output *out = malloc(sizeof (*out));
    if (unlikely(out == NULL))
        return NULL;

    out->tls = tls;

    out->prio.first = NULL;
    out->prio.last = &out->prio.first;
    out->queue.first = NULL;
    out->queue.last = &out->queue.first;
    out->size = 0;
    out->failed = false;
    out->closing = false;

    vlc_mutex_init(&out->lock);
    vlc_cond_init(&out->wait);

    void *(*cb)(void *) = client ? vlc_h2_client_output_thread
                                 : vlc_h2_output_thread;
    if (vlc_clone(&out->thread, cb, out, VLC_THREAD_PRIORITY_INPUT))
    {
        vlc_cond_destroy(&out->wait);
        vlc_mutex_destroy(&out->lock);
        free(out);
        out = NULL;
    }
    return out;
}