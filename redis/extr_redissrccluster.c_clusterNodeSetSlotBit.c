#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numslots; int /*<<< orphan*/  flags; int /*<<< orphan*/  slots; } ;
typedef  TYPE_1__ clusterNode ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_NODE_MIGRATE_TO ; 
 int /*<<< orphan*/  bitmapSetBit (int /*<<< orphan*/ ,int) ; 
 int bitmapTestBit (int /*<<< orphan*/ ,int) ; 
 scalar_t__ clusterMastersHaveSlaves () ; 

int clusterNodeSetSlotBit(clusterNode *n, int slot) {
    int old = bitmapTestBit(n->slots,slot);
    bitmapSetBit(n->slots,slot);
    if (!old) {
        n->numslots++;
        /* When a master gets its first slot, even if it has no slaves,
         * it gets flagged with MIGRATE_TO, that is, the master is a valid
         * target for replicas migration, if and only if at least one of
         * the other masters has slaves right now.
         *
         * Normally masters are valid targerts of replica migration if:
         * 1. The used to have slaves (but no longer have).
         * 2. They are slaves failing over a master that used to have slaves.
         *
         * However new masters with slots assigned are considered valid
         * migration tagets if the rest of the cluster is not a slave-less.
         *
         * See https://github.com/antirez/redis/issues/3043 for more info. */
        if (n->numslots == 1 && clusterMastersHaveSlaves())
            n->flags |= CLUSTER_NODE_MIGRATE_TO;
    }
    return old;
}