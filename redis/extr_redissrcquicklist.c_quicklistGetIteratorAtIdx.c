#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  current; int /*<<< orphan*/ * zi; } ;
typedef  TYPE_1__ quicklistIter ;
struct TYPE_7__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  node; } ;
typedef  TYPE_2__ quicklistEntry ;
typedef  int /*<<< orphan*/  quicklist ;

/* Variables and functions */
 TYPE_1__* quicklistGetIterator (int /*<<< orphan*/  const*,int const) ; 
 scalar_t__ quicklistIndex (int /*<<< orphan*/  const*,long long const,TYPE_2__*) ; 

quicklistIter *quicklistGetIteratorAtIdx(const quicklist *quicklist,
                                         const int direction,
                                         const long long idx) {
    quicklistEntry entry;

    if (quicklistIndex(quicklist, idx, &entry)) {
        quicklistIter *base = quicklistGetIterator(quicklist, direction);
        base->zi = NULL;
        base->current = entry.node;
        base->offset = entry.offset;
        return base;
    } else {
        return NULL;
    }
}