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
typedef  int /*<<< orphan*/  quicklistEntry ;
typedef  int /*<<< orphan*/  quicklist ;

/* Variables and functions */
 int /*<<< orphan*/  _quicklistInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t const,int) ; 

void quicklistInsertAfter(quicklist *quicklist, quicklistEntry *entry,
                          void *value, const size_t sz) {
    _quicklistInsert(quicklist, entry, value, sz, 1);
}