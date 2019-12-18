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
struct background_worker_config {int dummy; } ;
struct background_worker {int closing; int /*<<< orphan*/  nothreads_wait; int /*<<< orphan*/  queue_wait; int /*<<< orphan*/  queue; int /*<<< orphan*/  threads; scalar_t__ nthreads; scalar_t__ uncompleted; int /*<<< orphan*/  lock; void* owner; struct background_worker_config conf; } ;

/* Variables and functions */
 struct background_worker* malloc (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct background_worker *background_worker_Create(void *owner,
                                         struct background_worker_config *conf)
{
    struct background_worker* worker = malloc(sizeof(*worker));
    if (unlikely(!worker))
        return NULL;

    worker->conf = *conf;
    worker->owner = owner;

    vlc_mutex_init(&worker->lock);
    worker->uncompleted = 0;
    worker->nthreads = 0;
    vlc_list_init(&worker->threads);
    vlc_list_init(&worker->queue);
    vlc_cond_init(&worker->queue_wait);
    vlc_cond_init(&worker->nothreads_wait);
    worker->closing = false;
    return worker;
}