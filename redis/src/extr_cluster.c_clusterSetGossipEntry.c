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
struct TYPE_10__ {int ping_sent; int pong_received; int /*<<< orphan*/  flags; int /*<<< orphan*/  cport; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ clusterNode ;
struct TYPE_11__ {scalar_t__ notused1; void* flags; void* cport; void* port; int /*<<< orphan*/  ip; void* pong_received; void* ping_sent; int /*<<< orphan*/  nodename; } ;
typedef  TYPE_4__ clusterMsgDataGossip ;
struct TYPE_8__ {TYPE_4__* gossip; } ;
struct TYPE_9__ {TYPE_1__ ping; } ;
struct TYPE_12__ {TYPE_2__ data; } ;
typedef  TYPE_5__ clusterMsg ;

/* Variables and functions */
 int CLUSTER_NAMELEN ; 
 void* htonl (int) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void clusterSetGossipEntry(clusterMsg *hdr, int i, clusterNode *n) {
    clusterMsgDataGossip *gossip;
    gossip = &(hdr->data.ping.gossip[i]);
    memcpy(gossip->nodename,n->name,CLUSTER_NAMELEN);
    gossip->ping_sent = htonl(n->ping_sent/1000);
    gossip->pong_received = htonl(n->pong_received/1000);
    memcpy(gossip->ip,n->ip,sizeof(n->ip));
    gossip->port = htons(n->port);
    gossip->cport = htons(n->cport);
    gossip->flags = htons(n->flags);
    gossip->notused1 = 0;
}