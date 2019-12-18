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
typedef  int /*<<< orphan*/  Iterator ;

/* Variables and functions */
 int ordered_hashmap_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool ordered_set_iterate(OrderedSet *s, Iterator *i, void **value) {
        return ordered_hashmap_iterate((OrderedHashmap*) s, i, value, NULL);
}