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
typedef  int /*<<< orphan*/  OrderedHashmap ;
typedef  int /*<<< orphan*/  IteratedCache ;

/* Variables and functions */
 int /*<<< orphan*/  HASHMAP_BASE (int /*<<< orphan*/ *) ; 
 scalar_t__ internal_hashmap_iterated_cache_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline IteratedCache *ordered_hashmap_iterated_cache_new(OrderedHashmap *h) {
        return (IteratedCache*) internal_hashmap_iterated_cache_new(HASHMAP_BASE(h));
}