#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  streamID ;
typedef  int /*<<< orphan*/  stream ;
struct TYPE_13__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_14__ {int argc; TYPE_5__* db; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_17__ {int dirty; } ;
struct TYPE_16__ {int /*<<< orphan*/  czero; } ;
struct TYPE_15__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  NOTIFY_STREAM ; 
 int /*<<< orphan*/  OBJ_STREAM ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,int) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* lookupKeyWriteOrReply (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ server ; 
 TYPE_6__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ streamDeleteItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ streamParseStrictIDOrReply (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void xdelCommand(client *c) {
    robj *o;

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL
        || checkType(c,o,OBJ_STREAM)) return;
    stream *s = o->ptr;

    /* We need to sanity check the IDs passed to start. Even if not
     * a big issue, it is not great that the command is only partially
     * executed because at some point an invalid ID is parsed. */
    streamID id;
    for (int j = 2; j < c->argc; j++) {
        if (streamParseStrictIDOrReply(c,c->argv[j],&id,0) != C_OK) return;
    }

    /* Actually apply the command. */
    int deleted = 0;
    for (int j = 2; j < c->argc; j++) {
        streamParseStrictIDOrReply(c,c->argv[j],&id,0); /* Retval already checked. */
        deleted += streamDeleteItem(s,&id);
    }

    /* Propagate the write if needed. */
    if (deleted) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_STREAM,"xdel",c->argv[1],c->db->id);
        server.dirty += deleted;
    }
    addReplyLongLong(c,deleted);
}