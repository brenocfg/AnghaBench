#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ clusterMsg ;
struct TYPE_9__ {int /*<<< orphan*/  sndbuf; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ clusterLink ;
struct TYPE_10__ {TYPE_1__* cluster; int /*<<< orphan*/  el; } ;
struct TYPE_7__ {int /*<<< orphan*/ * stats_bus_messages_sent; } ;

/* Variables and functions */
 int AE_BARRIER ; 
 int AE_WRITABLE ; 
 size_t CLUSTERMSG_TYPE_COUNT ; 
 int /*<<< orphan*/  aeCreateFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  clusterWriteHandler ; 
 size_t ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 scalar_t__ sdslen (int /*<<< orphan*/ ) ; 
 TYPE_4__ server ; 

void clusterSendMessage(clusterLink *link, unsigned char *msg, size_t msglen) {
    if (sdslen(link->sndbuf) == 0 && msglen != 0)
        aeCreateFileEvent(server.el,link->fd,AE_WRITABLE|AE_BARRIER,
                    clusterWriteHandler,link);

    link->sndbuf = sdscatlen(link->sndbuf, msg, msglen);

    /* Populate sent messages stats. */
    clusterMsg *hdr = (clusterMsg*) msg;
    uint16_t type = ntohs(hdr->type);
    if (type < CLUSTERMSG_TYPE_COUNT)
        server.cluster->stats_bus_messages_sent[type]++;
}