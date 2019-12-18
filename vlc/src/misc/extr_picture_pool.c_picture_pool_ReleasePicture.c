#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_5__ {int /*<<< orphan*/  opaque; } ;
struct TYPE_6__ {TYPE_1__ gc; } ;
typedef  TYPE_2__ picture_priv_t ;
struct TYPE_7__ {unsigned long long available; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  (* pic_unlock ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ ** picture; } ;
typedef  TYPE_3__ picture_pool_t ;

/* Variables and functions */
 int POOL_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_pool_Destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void picture_pool_ReleasePicture(picture_t *clone)
{
    picture_priv_t *priv = (picture_priv_t *)clone;
    uintptr_t sys = (uintptr_t)priv->gc.opaque;
    picture_pool_t *pool = (void *)(sys & ~(POOL_MAX - 1));
    unsigned offset = sys & (POOL_MAX - 1);
    picture_t *picture = pool->picture[offset];

    if (pool->pic_unlock != NULL)
        pool->pic_unlock(picture);
    picture_Release(picture);

    vlc_mutex_lock(&pool->lock);
    assert(!(pool->available & (1ULL << offset)));
    pool->available |= 1ULL << offset;
    vlc_cond_signal(&pool->wait);
    vlc_mutex_unlock(&pool->lock);

    picture_pool_Destroy(pool);
}