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
typedef  int /*<<< orphan*/  quicklist ;

/* Variables and functions */
 int QUICKLIST_HEAD ; 
 int QUICKLIST_TAIL ; 
 int /*<<< orphan*/  quicklistPushHead (int /*<<< orphan*/ *,void*,size_t const) ; 
 int /*<<< orphan*/  quicklistPushTail (int /*<<< orphan*/ *,void*,size_t const) ; 

void quicklistPush(quicklist *quicklist, void *value, const size_t sz,
                   int where) {
    if (where == QUICKLIST_HEAD) {
        quicklistPushHead(quicklist, value, sz);
    } else if (where == QUICKLIST_TAIL) {
        quicklistPushTail(quicklist, value, sz);
    }
}