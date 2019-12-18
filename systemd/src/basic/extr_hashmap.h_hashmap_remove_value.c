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
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 int /*<<< orphan*/  HASHMAP_BASE (int /*<<< orphan*/ *) ; 
 void* internal_hashmap_remove_value (int /*<<< orphan*/ ,void const*,void*) ; 

__attribute__((used)) static inline void *hashmap_remove_value(Hashmap *h, const void *key, void *value) {
        return internal_hashmap_remove_value(HASHMAP_BASE(h), key, value);
}