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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  spl_kmem_cache_t ;

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MIN (scalar_t__,int) ; 
 int PAGE_SIZE ; 
 scalar_t__ spl_kmem_cache_magazine_size ; 
 int spl_obj_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
spl_magazine_size(spl_kmem_cache_t *skc)
{
	uint32_t obj_size = spl_obj_size(skc);
	int size;

	if (spl_kmem_cache_magazine_size > 0)
		return (MAX(MIN(spl_kmem_cache_magazine_size, 256), 2));

	/* Per-magazine sizes below assume a 4Kib page size */
	if (obj_size > (PAGE_SIZE * 256))
		size = 4;  /* Minimum 4Mib per-magazine */
	else if (obj_size > (PAGE_SIZE * 32))
		size = 16; /* Minimum 2Mib per-magazine */
	else if (obj_size > (PAGE_SIZE))
		size = 64; /* Minimum 256Kib per-magazine */
	else if (obj_size > (PAGE_SIZE / 4))
		size = 128; /* Minimum 128Kib per-magazine */
	else
		size = 256;

	return (size);
}