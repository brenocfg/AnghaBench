#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  replid; scalar_t__ second_replid_offset; int /*<<< orphan*/  replid2; scalar_t__ master_repl_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  changeReplicationId () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void shiftReplicationId(void) {
    memcpy(server.replid2,server.replid,sizeof(server.replid));
    /* We set the second replid offset to the master offset + 1, since
     * the slave will ask for the first byte it has not yet received, so
     * we need to add one to the offset: for example if, as a slave, we are
     * sure we have the same history as the master for 50 bytes, after we
     * are turned into a master, we can accept a PSYNC request with offset
     * 51, since the slave asking has the same history up to the 50th
     * byte, and is asking for the new bytes starting at offset 51. */
    server.second_replid_offset = server.master_repl_offset+1;
    changeReplicationId();
    serverLog(LL_WARNING,"Setting secondary replication ID to %s, valid up to offset: %lld. New replication ID is %s", server.replid2, server.second_replid_offset, server.replid);
}