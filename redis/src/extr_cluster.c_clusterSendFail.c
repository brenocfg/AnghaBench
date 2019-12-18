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
struct TYPE_7__ {int /*<<< orphan*/  nodename; } ;
struct TYPE_8__ {TYPE_1__ about; } ;
struct TYPE_9__ {TYPE_2__ fail; } ;
struct TYPE_10__ {int /*<<< orphan*/  totlen; TYPE_3__ data; } ;
typedef  TYPE_4__ clusterMsg ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_TYPE_FAIL ; 
 int /*<<< orphan*/  CLUSTER_NAMELEN ; 
 int /*<<< orphan*/  clusterBroadcastMessage (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterBuildMessageHdr (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

void clusterSendFail(char *nodename) {
    clusterMsg buf[1];
    clusterMsg *hdr = (clusterMsg*) buf;

    clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_FAIL);
    memcpy(hdr->data.fail.about.nodename,nodename,CLUSTER_NAMELEN);
    clusterBroadcastMessage(buf,ntohl(hdr->totlen));
}