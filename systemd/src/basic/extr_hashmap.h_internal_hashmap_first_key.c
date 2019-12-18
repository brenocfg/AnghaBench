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
typedef  int /*<<< orphan*/  HashmapBase ;

/* Variables and functions */
 int /*<<< orphan*/  HASHMAP_BASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  internal_hashmap_first_key_and_value (int /*<<< orphan*/ ,int,void**) ; 

__attribute__((used)) static inline void *internal_hashmap_first_key(HashmapBase *h, bool remove) {
        void *key = NULL;

        (void) internal_hashmap_first_key_and_value(HASHMAP_BASE(h), remove, &key);
        return key;
}