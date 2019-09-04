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
typedef  int /*<<< orphan*/  bstr_cache_entry_t ;
typedef  unsigned int SIZE_T ;

/* Variables and functions */
 unsigned int BUCKET_SIZE ; 
 int /*<<< orphan*/ * get_cache_entry_from_idx (unsigned int) ; 

__attribute__((used)) static inline bstr_cache_entry_t *get_cache_entry_from_alloc_size(SIZE_T alloc_size)
{
    unsigned cache_idx;
    if (alloc_size < BUCKET_SIZE) return NULL;
    cache_idx = (alloc_size - BUCKET_SIZE) / BUCKET_SIZE;
    return get_cache_entry_from_idx(cache_idx);
}