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

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int TASKQ_DYNAMIC ; 
 int TASKQ_PREPOPULATE ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maxclsyspri ; 
 int spl_kmem_cache_kmem_threads ; 
 int /*<<< orphan*/  spl_kmem_cache_list ; 
 int /*<<< orphan*/  spl_kmem_cache_sem ; 
 int /*<<< orphan*/  spl_kmem_cache_shrinker ; 
 int /*<<< orphan*/  spl_kmem_cache_taskq ; 
 int /*<<< orphan*/  spl_register_shrinker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_create (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

int
spl_kmem_cache_init(void)
{
	init_rwsem(&spl_kmem_cache_sem);
	INIT_LIST_HEAD(&spl_kmem_cache_list);
	spl_kmem_cache_taskq = taskq_create("spl_kmem_cache",
	    spl_kmem_cache_kmem_threads, maxclsyspri,
	    spl_kmem_cache_kmem_threads * 8, INT_MAX,
	    TASKQ_PREPOPULATE | TASKQ_DYNAMIC);
	spl_register_shrinker(&spl_kmem_cache_shrinker);

	return (0);
}