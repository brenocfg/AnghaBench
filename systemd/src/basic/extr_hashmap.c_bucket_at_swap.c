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
struct swap_entries {struct ordered_hashmap_entry* e; } ;
struct ordered_hashmap_entry {int dummy; } ;

/* Variables and functions */
 unsigned int _IDX_SWAP_BEGIN ; 

__attribute__((used)) static struct ordered_hashmap_entry *bucket_at_swap(struct swap_entries *swap, unsigned idx) {
        return &swap->e[idx - _IDX_SWAP_BEGIN];
}