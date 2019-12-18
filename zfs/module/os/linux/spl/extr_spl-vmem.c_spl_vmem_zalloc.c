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
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int KM_PUBLIC_MASK ; 
 int KM_VMEM ; 
 int KM_ZERO ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 void* spl_kmem_alloc_debug (size_t,int,int /*<<< orphan*/ ) ; 
 void* spl_kmem_alloc_impl (size_t,int,int /*<<< orphan*/ ) ; 
 void* spl_kmem_alloc_track (size_t,int,char const*,int,int /*<<< orphan*/ ) ; 

void *
spl_vmem_zalloc(size_t size, int flags, const char *func, int line)
{
	ASSERT0(flags & ~KM_PUBLIC_MASK);

	flags |= (KM_VMEM | KM_ZERO);

#if !defined(DEBUG_KMEM)
	return (spl_kmem_alloc_impl(size, flags, NUMA_NO_NODE));
#elif !defined(DEBUG_KMEM_TRACKING)
	return (spl_kmem_alloc_debug(size, flags, NUMA_NO_NODE));
#else
	return (spl_kmem_alloc_track(size, flags, func, line, NUMA_NO_NODE));
#endif
}