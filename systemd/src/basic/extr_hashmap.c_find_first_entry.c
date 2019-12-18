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
typedef  int /*<<< orphan*/  Iterator ;
typedef  int /*<<< orphan*/  HashmapBase ;

/* Variables and functions */
 int IDX_NIL ; 
 int /*<<< orphan*/  ITERATOR_FIRST ; 
 int hashmap_iterate_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_entries (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned find_first_entry(HashmapBase *h) {
        Iterator i = ITERATOR_FIRST;

        if (!h || !n_entries(h))
                return IDX_NIL;

        return hashmap_iterate_entry(h, &i);
}