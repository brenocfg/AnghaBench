#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_11__ {size_t resp; int /*<<< orphan*/ * argv; TYPE_2__* db; } ;
typedef  TYPE_1__ client ;
struct TYPE_14__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_13__ {int /*<<< orphan*/ * null; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int LIST_HEAD ; 
 int /*<<< orphan*/  NOTIFY_GENERIC ; 
 int /*<<< orphan*/  NOTIFY_LIST ; 
 int /*<<< orphan*/  OBJ_LIST ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_1__*) ; 
 scalar_t__ checkType (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbDelete (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 scalar_t__ listTypeLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listTypePop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lookupKeyWriteOrReply (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ server ; 
 TYPE_3__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_2__*,int /*<<< orphan*/ ) ; 

void popGenericCommand(client *c, int where) {
    robj *o = lookupKeyWriteOrReply(c,c->argv[1],shared.null[c->resp]);
    if (o == NULL || checkType(c,o,OBJ_LIST)) return;

    robj *value = listTypePop(o,where);
    if (value == NULL) {
        addReplyNull(c);
    } else {
        char *event = (where == LIST_HEAD) ? "lpop" : "rpop";

        addReplyBulk(c,value);
        decrRefCount(value);
        notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
        if (listTypeLength(o) == 0) {
            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",
                                c->argv[1],c->db->id);
            dbDelete(c->db,c->argv[1]);
        }
        signalModifiedKey(c->db,c->argv[1]);
        server.dirty++;
    }
}