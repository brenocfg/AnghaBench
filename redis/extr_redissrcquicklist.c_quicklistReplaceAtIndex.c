#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* node; int /*<<< orphan*/  zi; } ;
typedef  TYPE_1__ quicklistEntry ;
typedef  int /*<<< orphan*/  quicklist ;
struct TYPE_6__ {int /*<<< orphan*/  zl; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicklistCompress (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  quicklistIndex (int /*<<< orphan*/ *,long,TYPE_1__*) ; 
 int /*<<< orphan*/  quicklistNodeUpdateSz (TYPE_2__*) ; 
 int /*<<< orphan*/  ziplistDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ziplistInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

int quicklistReplaceAtIndex(quicklist *quicklist, long index, void *data,
                            int sz) {
    quicklistEntry entry;
    if (likely(quicklistIndex(quicklist, index, &entry))) {
        /* quicklistIndex provides an uncompressed node */
        entry.node->zl = ziplistDelete(entry.node->zl, &entry.zi);
        entry.node->zl = ziplistInsert(entry.node->zl, entry.zi, data, sz);
        quicklistNodeUpdateSz(entry.node);
        quicklistCompress(quicklist, entry.node);
        return 1;
    } else {
        return 0;
    }
}