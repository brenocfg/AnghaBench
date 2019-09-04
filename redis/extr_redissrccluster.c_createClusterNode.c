#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  fail_reports; scalar_t__ repl_offset; scalar_t__ repl_offset_time; scalar_t__ orphaned_time; scalar_t__ voted_time; scalar_t__ cport; scalar_t__ port; int /*<<< orphan*/  ip; int /*<<< orphan*/ * link; scalar_t__ fail_time; scalar_t__ pong_received; scalar_t__ ping_sent; int /*<<< orphan*/ * slaveof; int /*<<< orphan*/ * slaves; scalar_t__ numslaves; scalar_t__ numslots; int /*<<< orphan*/  slots; scalar_t__ configEpoch; int /*<<< orphan*/  ctime; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ clusterNode ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_NAMELEN ; 
 int /*<<< orphan*/  getRandomHexChars (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listCreate () ; 
 int /*<<< orphan*/  listSetFreeMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mstime () ; 
 int /*<<< orphan*/  zfree ; 
 TYPE_1__* zmalloc (int) ; 

clusterNode *createClusterNode(char *nodename, int flags) {
    clusterNode *node = zmalloc(sizeof(*node));

    if (nodename)
        memcpy(node->name, nodename, CLUSTER_NAMELEN);
    else
        getRandomHexChars(node->name, CLUSTER_NAMELEN);
    node->ctime = mstime();
    node->configEpoch = 0;
    node->flags = flags;
    memset(node->slots,0,sizeof(node->slots));
    node->numslots = 0;
    node->numslaves = 0;
    node->slaves = NULL;
    node->slaveof = NULL;
    node->ping_sent = node->pong_received = 0;
    node->fail_time = 0;
    node->link = NULL;
    memset(node->ip,0,sizeof(node->ip));
    node->port = 0;
    node->cport = 0;
    node->fail_reports = listCreate();
    node->voted_time = 0;
    node->orphaned_time = 0;
    node->repl_offset_time = 0;
    node->repl_offset = 0;
    listSetFreeMethod(node->fail_reports,zfree);
    return node;
}