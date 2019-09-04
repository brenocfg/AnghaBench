#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ encoding; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  quicklist ;
struct TYPE_18__ {TYPE_3__* db; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_21__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_20__ {int /*<<< orphan*/  ok; int /*<<< orphan*/  outofrangeerr; int /*<<< orphan*/  nokeyerr; } ;
struct TYPE_19__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  NOTIFY_LIST ; 
 scalar_t__ OBJ_ENCODING_QUICKLIST ; 
 int /*<<< orphan*/  OBJ_LIST ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_2__*,TYPE_1__*,long*,int /*<<< orphan*/ *) ; 
 TYPE_1__* lookupKeyWriteOrReply (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int quicklistReplaceAtIndex (int /*<<< orphan*/ *,long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ *) ; 
 TYPE_6__ server ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 TYPE_5__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_3__*,TYPE_1__*) ; 

void lsetCommand(client *c) {
    robj *o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr);
    if (o == NULL || checkType(c,o,OBJ_LIST)) return;
    long index;
    robj *value = c->argv[3];

    if ((getLongFromObjectOrReply(c, c->argv[2], &index, NULL) != C_OK))
        return;

    if (o->encoding == OBJ_ENCODING_QUICKLIST) {
        quicklist *ql = o->ptr;
        int replaced = quicklistReplaceAtIndex(ql, index,
                                               value->ptr, sdslen(value->ptr));
        if (!replaced) {
            addReply(c,shared.outofrangeerr);
        } else {
            addReply(c,shared.ok);
            signalModifiedKey(c->db,c->argv[1]);
            notifyKeyspaceEvent(NOTIFY_LIST,"lset",c->argv[1],c->db->id);
            server.dirty++;
        }
    } else {
        serverPanic("Unknown list encoding");
    }
}