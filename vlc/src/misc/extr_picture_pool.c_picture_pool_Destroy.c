#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ picture_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  aligned_free (TYPE_1__*) ; 
 int atomic_fetch_sub_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_thread_fence (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_acquire ; 
 int /*<<< orphan*/  memory_order_release ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void picture_pool_Destroy(picture_pool_t *pool)
{
    if (atomic_fetch_sub_explicit(&pool->refs, 1, memory_order_release) != 1)
        return;

    atomic_thread_fence(memory_order_acquire);
    vlc_cond_destroy(&pool->wait);
    vlc_mutex_destroy(&pool->lock);
    aligned_free(pool);
}