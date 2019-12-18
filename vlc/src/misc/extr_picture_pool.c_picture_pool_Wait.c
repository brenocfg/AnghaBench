#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * p_next; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_9__ {scalar_t__ refs; unsigned long long available; scalar_t__ (* pic_lock ) (TYPE_1__*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; TYPE_1__** picture; scalar_t__ canceled; } ;
typedef  TYPE_2__ picture_pool_t ;

/* Variables and functions */
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_fetch_add_explicit (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int ctz (unsigned long long) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 TYPE_1__* picture_pool_ClonePicture (TYPE_2__*,int) ; 
 scalar_t__ stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

picture_t *picture_pool_Wait(picture_pool_t *pool)
{
    vlc_mutex_lock(&pool->lock);
    assert(pool->refs > 0);

    while (pool->available == 0)
    {
        if (pool->canceled)
        {
            vlc_mutex_unlock(&pool->lock);
            return NULL;
        }
        vlc_cond_wait(&pool->wait, &pool->lock);
    }

    int i = ctz(pool->available);
    pool->available &= ~(1ULL << i);
    vlc_mutex_unlock(&pool->lock);

    picture_t *picture = pool->picture[i];

    if (pool->pic_lock != NULL && pool->pic_lock(picture) != VLC_SUCCESS) {
        vlc_mutex_lock(&pool->lock);
        pool->available |= 1ULL << i;
        vlc_cond_signal(&pool->wait);
        vlc_mutex_unlock(&pool->lock);
        return NULL;
    }

    picture_t *clone = picture_pool_ClonePicture(pool, i);
    if (clone != NULL) {
        assert(clone->p_next == NULL);
        atomic_fetch_add_explicit(&pool->refs, 1, memory_order_relaxed);
    }
    return clone;
}