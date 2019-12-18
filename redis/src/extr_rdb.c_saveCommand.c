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
typedef  int /*<<< orphan*/  rdbSaveInfo ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_4__ {int rdb_child_pid; int /*<<< orphan*/  rdb_filename; } ;
struct TYPE_3__ {int /*<<< orphan*/  err; int /*<<< orphan*/  ok; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  addReply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * rdbPopulateSaveInfo (int /*<<< orphan*/ *) ; 
 scalar_t__ rdbSave (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ server ; 
 TYPE_1__ shared ; 

void saveCommand(client *c) {
    if (server.rdb_child_pid != -1) {
        addReplyError(c,"Background save already in progress");
        return;
    }
    rdbSaveInfo rsi, *rsiptr;
    rsiptr = rdbPopulateSaveInfo(&rsi);
    if (rdbSave(server.rdb_filename,rsiptr) == C_OK) {
        addReply(c,shared.ok);
    } else {
        addReply(c,shared.err);
    }
}