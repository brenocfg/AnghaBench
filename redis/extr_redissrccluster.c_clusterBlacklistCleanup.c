#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_4__ {scalar_t__ unixtime; TYPE_1__* cluster; } ;
struct TYPE_3__ {int /*<<< orphan*/  nodes_black_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 scalar_t__ dictGetUnsignedIntegerVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_2__ server ; 

void clusterBlacklistCleanup(void) {
    dictIterator *di;
    dictEntry *de;

    di = dictGetSafeIterator(server.cluster->nodes_black_list);
    while((de = dictNext(di)) != NULL) {
        int64_t expire = dictGetUnsignedIntegerVal(de);

        if (expire < server.unixtime)
            dictDelete(server.cluster->nodes_black_list,dictGetKey(de));
    }
    dictReleaseIterator(di);
}