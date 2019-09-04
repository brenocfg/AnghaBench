#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_7__ {int port; int cport; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ clusterNode ;
struct TYPE_8__ {TYPE_1__* cluster; } ;
struct TYPE_6__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 TYPE_2__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodeInHandshake (TYPE_2__*) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

int clusterHandshakeInProgress(char *ip, int port, int cport) {
    dictIterator *di;
    dictEntry *de;

    di = dictGetSafeIterator(server.cluster->nodes);
    while((de = dictNext(di)) != NULL) {
        clusterNode *node = dictGetVal(de);

        if (!nodeInHandshake(node)) continue;
        if (!strcasecmp(node->ip,ip) &&
            node->port == port &&
            node->cport == cport) break;
    }
    dictReleaseIterator(di);
    return de != NULL;
}