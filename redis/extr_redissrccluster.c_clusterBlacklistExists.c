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
typedef  int /*<<< orphan*/  sds ;
struct TYPE_4__ {TYPE_1__* cluster; } ;
struct TYPE_3__ {int /*<<< orphan*/  nodes_black_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_NAMELEN ; 
 int /*<<< orphan*/  clusterBlacklistCleanup () ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnewlen (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 

int clusterBlacklistExists(char *nodeid) {
    sds id = sdsnewlen(nodeid,CLUSTER_NAMELEN);
    int retval;

    clusterBlacklistCleanup();
    retval = dictFind(server.cluster->nodes_black_list,id) != NULL;
    sdsfree(id);
    return retval;
}