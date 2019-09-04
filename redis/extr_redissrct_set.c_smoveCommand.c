#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_12__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_27__ {TYPE_4__* db; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_29__ {int /*<<< orphan*/  cone; int /*<<< orphan*/  czero; } ;
struct TYPE_28__ {int /*<<< orphan*/  id; } ;
struct TYPE_25__ {int /*<<< orphan*/  dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTIFY_GENERIC ; 
 int /*<<< orphan*/  NOTIFY_SET ; 
 int /*<<< orphan*/  OBJ_SET ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbAdd (TYPE_4__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dbDelete (TYPE_4__*,TYPE_1__*) ; 
 TYPE_1__* lookupKeyWrite (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_12__ server ; 
 scalar_t__ setTypeAdd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* setTypeCreate (int /*<<< orphan*/ ) ; 
 scalar_t__ setTypeIsMember (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setTypeRemove (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ setTypeSize (TYPE_1__*) ; 
 TYPE_6__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_4__*,TYPE_1__*) ; 

void smoveCommand(client *c) {
    robj *srcset, *dstset, *ele;
    srcset = lookupKeyWrite(c->db,c->argv[1]);
    dstset = lookupKeyWrite(c->db,c->argv[2]);
    ele = c->argv[3];

    /* If the source key does not exist return 0 */
    if (srcset == NULL) {
        addReply(c,shared.czero);
        return;
    }

    /* If the source key has the wrong type, or the destination key
     * is set and has the wrong type, return with an error. */
    if (checkType(c,srcset,OBJ_SET) ||
        (dstset && checkType(c,dstset,OBJ_SET))) return;

    /* If srcset and dstset are equal, SMOVE is a no-op */
    if (srcset == dstset) {
        addReply(c,setTypeIsMember(srcset,ele->ptr) ?
            shared.cone : shared.czero);
        return;
    }

    /* If the element cannot be removed from the src set, return 0. */
    if (!setTypeRemove(srcset,ele->ptr)) {
        addReply(c,shared.czero);
        return;
    }
    notifyKeyspaceEvent(NOTIFY_SET,"srem",c->argv[1],c->db->id);

    /* Remove the src set from the database when empty */
    if (setTypeSize(srcset) == 0) {
        dbDelete(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
    }

    /* Create the destination set when it doesn't exist */
    if (!dstset) {
        dstset = setTypeCreate(ele->ptr);
        dbAdd(c->db,c->argv[2],dstset);
    }

    signalModifiedKey(c->db,c->argv[1]);
    signalModifiedKey(c->db,c->argv[2]);
    server.dirty++;

    /* An extra key has changed when ele was successfully added to dstset */
    if (setTypeAdd(dstset,ele->ptr)) {
        server.dirty++;
        notifyKeyspaceEvent(NOTIFY_SET,"sadd",c->argv[2],c->db->id);
    }
    addReply(c,shared.cone);
}