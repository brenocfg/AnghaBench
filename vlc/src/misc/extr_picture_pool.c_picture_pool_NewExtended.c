#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_6__ {unsigned long long available; unsigned long long picture_count; int canceled; int /*<<< orphan*/  picture; int /*<<< orphan*/  refs; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  pic_unlock; int /*<<< orphan*/  pic_lock; } ;
typedef  TYPE_1__ picture_pool_t ;
struct TYPE_7__ {int picture_count; int /*<<< orphan*/  picture; int /*<<< orphan*/  unlock; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ picture_pool_configuration_t ;

/* Variables and functions */
 int POOL_MAX ; 
 TYPE_1__* aligned_alloc (int,size_t) ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

picture_pool_t *picture_pool_NewExtended(const picture_pool_configuration_t *cfg)
{
    if (unlikely(cfg->picture_count > POOL_MAX))
        return NULL;

    picture_pool_t *pool;
    size_t size = sizeof (*pool) + cfg->picture_count * sizeof (picture_t *);

    size += (-size) & (POOL_MAX - 1);
    pool = aligned_alloc(POOL_MAX, size);
    if (unlikely(pool == NULL))
        return NULL;

    pool->pic_lock   = cfg->lock;
    pool->pic_unlock = cfg->unlock;
    vlc_mutex_init(&pool->lock);
    vlc_cond_init(&pool->wait);
    if (cfg->picture_count == POOL_MAX)
        pool->available = ~0ULL;
    else
        pool->available = (1ULL << cfg->picture_count) - 1;
    atomic_init(&pool->refs,  1);
    pool->picture_count = cfg->picture_count;
    memcpy(pool->picture, cfg->picture,
           cfg->picture_count * sizeof (picture_t *));
    pool->canceled = false;
    return pool;
}