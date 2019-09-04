#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_22__ {TYPE_2__* db; TYPE_3__** argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_26__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_25__ {int /*<<< orphan*/  ok; int /*<<< orphan*/  cone; int /*<<< orphan*/  czero; int /*<<< orphan*/  nokeyerr; } ;
struct TYPE_24__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_23__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTIFY_GENERIC ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbAdd (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbDelete (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 long long getExpire (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupKeyWrite (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * lookupKeyWriteOrReply (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sdscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__ server ; 
 int /*<<< orphan*/  setExpire (TYPE_1__*,TYPE_2__*,TYPE_3__*,long long) ; 
 TYPE_4__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_2__*,TYPE_3__*) ; 

void renameGenericCommand(client *c, int nx) {
    robj *o;
    long long expire;
    int samekey = 0;

    /* When source and dest key is the same, no operation is performed,
     * if the key exists, however we still return an error on unexisting key. */
    if (sdscmp(c->argv[1]->ptr,c->argv[2]->ptr) == 0) samekey = 1;

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr)) == NULL)
        return;

    if (samekey) {
        addReply(c,nx ? shared.czero : shared.ok);
        return;
    }

    incrRefCount(o);
    expire = getExpire(c->db,c->argv[1]);
    if (lookupKeyWrite(c->db,c->argv[2]) != NULL) {
        if (nx) {
            decrRefCount(o);
            addReply(c,shared.czero);
            return;
        }
        /* Overwrite: delete the old key before creating the new one
         * with the same name. */
        dbDelete(c->db,c->argv[2]);
    }
    dbAdd(c->db,c->argv[2],o);
    if (expire != -1) setExpire(c,c->db,c->argv[2],expire);
    dbDelete(c->db,c->argv[1]);
    signalModifiedKey(c->db,c->argv[1]);
    signalModifiedKey(c->db,c->argv[2]);
    notifyKeyspaceEvent(NOTIFY_GENERIC,"rename_from",
        c->argv[1],c->db->id);
    notifyKeyspaceEvent(NOTIFY_GENERIC,"rename_to",
        c->argv[2],c->db->id);
    server.dirty++;
    addReply(c,nx ? shared.cone : shared.ok);
}