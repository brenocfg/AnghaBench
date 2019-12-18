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
typedef  int /*<<< orphan*/  clusterNode ;
struct TYPE_4__ {int /*<<< orphan*/ * conn; int /*<<< orphan*/ * node; void* rcvbuf; void* sndbuf; int /*<<< orphan*/  ctime; } ;
typedef  TYPE_1__ clusterLink ;

/* Variables and functions */
 int /*<<< orphan*/  mstime () ; 
 void* sdsempty () ; 
 TYPE_1__* zmalloc (int) ; 

clusterLink *createClusterLink(clusterNode *node) {
    clusterLink *link = zmalloc(sizeof(*link));
    link->ctime = mstime();
    link->sndbuf = sdsempty();
    link->rcvbuf = sdsempty();
    link->node = node;
    link->conn = NULL;
    return link;
}