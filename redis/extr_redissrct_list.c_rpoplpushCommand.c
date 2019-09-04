#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_15__ {size_t resp; int /*<<< orphan*/ ** argv; TYPE_1__* cmd; TYPE_3__* db; } ;
typedef  TYPE_2__ client ;
struct TYPE_18__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_17__ {int /*<<< orphan*/  rpoplpush; int /*<<< orphan*/ * null; } ;
struct TYPE_16__ {int /*<<< orphan*/  id; } ;
struct TYPE_14__ {scalar_t__ proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_TAIL ; 
 int /*<<< orphan*/  NOTIFY_GENERIC ; 
 int /*<<< orphan*/  NOTIFY_LIST ; 
 int /*<<< orphan*/  OBJ_LIST ; 
 int /*<<< orphan*/  addReplyNull (TYPE_2__*) ; 
 scalar_t__ brpoplpushCommand ; 
 scalar_t__ checkType (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbDelete (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ *) ; 
 scalar_t__ listTypeLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listTypePop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lookupKeyWrite (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupKeyWriteOrReply (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteClientCommandVector (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpoplpushHandlePush (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__ server ; 
 TYPE_4__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_3__*,int /*<<< orphan*/ *) ; 

void rpoplpushCommand(client *c) {
    robj *sobj, *value;
    if ((sobj = lookupKeyWriteOrReply(c,c->argv[1],shared.null[c->resp]))
        == NULL || checkType(c,sobj,OBJ_LIST)) return;

    if (listTypeLength(sobj) == 0) {
        /* This may only happen after loading very old RDB files. Recent
         * versions of Redis delete keys of empty lists. */
        addReplyNull(c);
    } else {
        robj *dobj = lookupKeyWrite(c->db,c->argv[2]);
        robj *touchedkey = c->argv[1];

        if (dobj && checkType(c,dobj,OBJ_LIST)) return;
        value = listTypePop(sobj,LIST_TAIL);
        /* We saved touched key, and protect it, since rpoplpushHandlePush
         * may change the client command argument vector (it does not
         * currently). */
        incrRefCount(touchedkey);
        rpoplpushHandlePush(c,c->argv[2],dobj,value);

        /* listTypePop returns an object with its refcount incremented */
        decrRefCount(value);

        /* Delete the source list when it is empty */
        notifyKeyspaceEvent(NOTIFY_LIST,"rpop",touchedkey,c->db->id);
        if (listTypeLength(sobj) == 0) {
            dbDelete(c->db,touchedkey);
            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",
                                touchedkey,c->db->id);
        }
        signalModifiedKey(c->db,touchedkey);
        decrRefCount(touchedkey);
        server.dirty++;
        if (c->cmd->proc == brpoplpushCommand) {
            rewriteClientCommandVector(c,3,shared.rpoplpush,c->argv[1],c->argv[2]);
        }
    }
}