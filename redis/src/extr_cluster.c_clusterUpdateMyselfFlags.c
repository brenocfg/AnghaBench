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
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {scalar_t__ cluster_slave_no_failover; } ;

/* Variables and functions */
 int CLUSTER_NODE_NOFAILOVER ; 
 int CLUSTER_TODO_SAVE_CONFIG ; 
 int CLUSTER_TODO_UPDATE_STATE ; 
 int /*<<< orphan*/  clusterDoBeforeSleep (int) ; 
 TYPE_2__* myself ; 
 TYPE_1__ server ; 

void clusterUpdateMyselfFlags(void) {
    int oldflags = myself->flags;
    int nofailover = server.cluster_slave_no_failover ?
                     CLUSTER_NODE_NOFAILOVER : 0;
    myself->flags &= ~CLUSTER_NODE_NOFAILOVER;
    myself->flags |= nofailover;
    if (myself->flags != oldflags) {
        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                             CLUSTER_TODO_UPDATE_STATE);
    }
}