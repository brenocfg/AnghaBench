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
typedef  void OrderedHashmap ;

/* Variables and functions */
 int /*<<< orphan*/  HASHMAP_BASE (void*) ; 
 int /*<<< orphan*/  free ; 
 scalar_t__ internal_hashmap_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline OrderedHashmap *ordered_hashmap_free_free_key(OrderedHashmap *h) {
        return (void*) internal_hashmap_free(HASHMAP_BASE(h), free, NULL);
}