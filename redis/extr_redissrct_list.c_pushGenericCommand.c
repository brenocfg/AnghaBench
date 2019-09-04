#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ type; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_17__ {int argc; TYPE_3__* db; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_20__ {int dirty; int /*<<< orphan*/  list_compress_depth; int /*<<< orphan*/  list_max_ziplist_size; } ;
struct TYPE_19__ {int /*<<< orphan*/  wrongtypeerr; } ;
struct TYPE_18__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int LIST_HEAD ; 
 int /*<<< orphan*/  NOTIFY_LIST ; 
 scalar_t__ OBJ_LIST ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* createQuicklistObject () ; 
 int /*<<< orphan*/  dbAdd (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  listTypeLength (TYPE_1__*) ; 
 int /*<<< orphan*/  listTypePush (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* lookupKeyWrite (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicklistSetOptions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ server ; 
 TYPE_4__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_3__*,int /*<<< orphan*/ ) ; 

void pushGenericCommand(client *c, int where) {
    int j, pushed = 0;
    robj *lobj = lookupKeyWrite(c->db,c->argv[1]);

    if (lobj && lobj->type != OBJ_LIST) {
        addReply(c,shared.wrongtypeerr);
        return;
    }

    for (j = 2; j < c->argc; j++) {
        if (!lobj) {
            lobj = createQuicklistObject();
            quicklistSetOptions(lobj->ptr, server.list_max_ziplist_size,
                                server.list_compress_depth);
            dbAdd(c->db,c->argv[1],lobj);
        }
        listTypePush(lobj,c->argv[j],where);
        pushed++;
    }
    addReplyLongLong(c, (lobj ? listTypeLength(lobj) : 0));
    if (pushed) {
        char *event = (where == LIST_HEAD) ? "lpush" : "rpush";

        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
    }
    server.dirty += pushed;
}