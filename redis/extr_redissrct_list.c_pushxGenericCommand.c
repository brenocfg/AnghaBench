#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_9__ {int argc; TYPE_2__* db; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_12__ {int dirty; } ;
struct TYPE_11__ {int /*<<< orphan*/  czero; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int LIST_HEAD ; 
 int /*<<< orphan*/  NOTIFY_LIST ; 
 int /*<<< orphan*/  OBJ_LIST ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ checkType (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listTypeLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listTypePush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * lookupKeyWriteOrReply (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ server ; 
 TYPE_3__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_2__*,int /*<<< orphan*/ ) ; 

void pushxGenericCommand(client *c, int where) {
    int j, pushed = 0;
    robj *subject;

    if ((subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,subject,OBJ_LIST)) return;

    for (j = 2; j < c->argc; j++) {
        listTypePush(subject,c->argv[j],where);
        pushed++;
    }

    addReplyLongLong(c,listTypeLength(subject));

    if (pushed) {
        char *event = (where == LIST_HEAD) ? "lpush" : "rpush";
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
    }
    server.dirty += pushed;
}