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
typedef  int /*<<< orphan*/  Set ;

/* Variables and functions */
 int /*<<< orphan*/  HASHMAP_BASE (int /*<<< orphan*/ *) ; 
 int internal_hashmap_reserve (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int set_reserve(Set *h, unsigned entries_add) {
        return internal_hashmap_reserve(HASHMAP_BASE(h), entries_add);
}