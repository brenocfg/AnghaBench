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
typedef  unsigned long uint32_t ;
typedef  int /*<<< orphan*/  spl_kmem_cache_t ;

/* Variables and functions */
 int fls64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_obj_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint32_t
spl_offslab_size(spl_kmem_cache_t *skc)
{
	return (1UL << (fls64(spl_obj_size(skc)) + 1));
}