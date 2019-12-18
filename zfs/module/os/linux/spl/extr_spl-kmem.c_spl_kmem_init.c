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
 int /*<<< orphan*/  KMEM_TABLE_SIZE ; 
 int /*<<< orphan*/  kmem_alloc_used_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_list ; 
 int /*<<< orphan*/  kmem_lock ; 
 int /*<<< orphan*/  spl_kmem_init_tracking (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
spl_kmem_init(void)
{

#ifdef DEBUG_KMEM
	kmem_alloc_used_set(0);



#ifdef DEBUG_KMEM_TRACKING
	spl_kmem_init_tracking(&kmem_list, &kmem_lock, KMEM_TABLE_SIZE);
#endif /* DEBUG_KMEM_TRACKING */
#endif /* DEBUG_KMEM */

	return (0);
}