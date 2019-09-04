#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  witness_rank_t ;
struct TYPE_3__ {int /*<<< orphan*/ * mutexes; } ;
typedef  TYPE_1__ mutex_pool_t ;

/* Variables and functions */
 int MUTEX_POOL_SIZE ; 
 int /*<<< orphan*/  malloc_mutex_address_ordered ; 
 scalar_t__ malloc_mutex_init (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
mutex_pool_init(mutex_pool_t *pool, const char *name, witness_rank_t rank) {
	for (int i = 0; i < MUTEX_POOL_SIZE; ++i) {
		if (malloc_mutex_init(&pool->mutexes[i], name, rank,
		    malloc_mutex_address_ordered)) {
			return true;
		}
	}
	return false;
}