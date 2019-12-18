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
 void* hashmap_get2 (int /*<<< orphan*/ ,void const*,void**) ; 

__attribute__((used)) static inline void *ordered_hashmap_get2(OrderedHashmap *h, const void *key, void **rkey) {
        return hashmap_get2(PLAIN_HASHMAP(h), key, rkey);
}