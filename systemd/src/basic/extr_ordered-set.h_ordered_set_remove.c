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
typedef  int /*<<< orphan*/  OrderedSet ;
typedef  int /*<<< orphan*/  OrderedHashmap ;

/* Variables and functions */
 void* ordered_hashmap_remove (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static inline void* ordered_set_remove(OrderedSet *s, void *p) {
        return ordered_hashmap_remove((OrderedHashmap*) s, p);
}