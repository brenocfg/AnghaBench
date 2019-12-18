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
 scalar_t__ is_vmalloc_addr (void const*) ; 
 int /*<<< orphan*/  kfree (void const*) ; 
 int /*<<< orphan*/  vfree (void const*) ; 

inline void
spl_kmem_free_impl(const void *buf, size_t size)
{
	if (is_vmalloc_addr(buf))
		vfree(buf);
	else
		kfree(buf);
}