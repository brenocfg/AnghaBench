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
struct quicklist {int fill; scalar_t__ compress; scalar_t__ count; scalar_t__ len; int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;
typedef  struct quicklist quicklist ;

/* Variables and functions */
 struct quicklist* zmalloc (int) ; 

quicklist *quicklistCreate(void) {
    struct quicklist *quicklist;

    quicklist = zmalloc(sizeof(*quicklist));
    quicklist->head = quicklist->tail = NULL;
    quicklist->len = 0;
    quicklist->count = 0;
    quicklist->compress = 0;
    quicklist->fill = -2;
    return quicklist;
}