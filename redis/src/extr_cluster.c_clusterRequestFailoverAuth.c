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
typedef  union clusterMsgData {int dummy; } clusterMsgData ;
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  totlen; int /*<<< orphan*/ * mflags; } ;
typedef  TYPE_2__ clusterMsg ;
struct TYPE_8__ {TYPE_1__* cluster; } ;
struct TYPE_6__ {scalar_t__ mf_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_FLAG0_FORCEACK ; 
 int /*<<< orphan*/  CLUSTERMSG_TYPE_FAILOVER_AUTH_REQUEST ; 
 int /*<<< orphan*/  clusterBroadcastMessage (TYPE_2__*,int) ; 
 int /*<<< orphan*/  clusterBuildMessageHdr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 TYPE_3__ server ; 

void clusterRequestFailoverAuth(void) {
    clusterMsg buf[1];
    clusterMsg *hdr = (clusterMsg*) buf;
    uint32_t totlen;

    clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_FAILOVER_AUTH_REQUEST);
    /* If this is a manual failover, set the CLUSTERMSG_FLAG0_FORCEACK bit
     * in the header to communicate the nodes receiving the message that
     * they should authorized the failover even if the master is working. */
    if (server.cluster->mf_end) hdr->mflags[0] |= CLUSTERMSG_FLAG0_FORCEACK;
    totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
    hdr->totlen = htonl(totlen);
    clusterBroadcastMessage(buf,totlen);
}