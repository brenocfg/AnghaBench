#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ clusterNode ;
struct TYPE_9__ {TYPE_1__* gossip; } ;
struct TYPE_10__ {TYPE_2__ ping; } ;
struct TYPE_12__ {TYPE_3__ data; } ;
typedef  TYPE_5__ clusterMsg ;
struct TYPE_8__ {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_NAMELEN ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int clusterNodeIsInGossipSection(clusterMsg *hdr, int count, clusterNode *n) {
    int j;
    for (j = 0; j < count; j++) {
        if (memcmp(hdr->data.ping.gossip[j].nodename,n->name,
                CLUSTER_NAMELEN) == 0) break;
    }
    return j != count;
}