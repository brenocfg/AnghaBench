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

/* Variables and functions */
 int /*<<< orphan*/  PLAIN_HASHMAP (int /*<<< orphan*/ *) ; 
 int hashmap_remove_and_put (int /*<<< orphan*/ ,void const*,void const*,void*) ; 

__attribute__((used)) static inline int ordered_hashmap_remove_and_put(OrderedHashmap *h, const void *old_key, const void *new_key, void *value) {
        return hashmap_remove_and_put(PLAIN_HASHMAP(h), old_key, new_key, value);
}