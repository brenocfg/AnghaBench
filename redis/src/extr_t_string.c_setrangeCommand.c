#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sds ;
struct TYPE_29__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_30__ {TYPE_4__* db; TYPE_5__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_34__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_33__ {int /*<<< orphan*/  czero; } ;
struct TYPE_32__ {scalar_t__ ptr; } ;
struct TYPE_31__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  NOTIFY_STRING ; 
 int /*<<< orphan*/  OBJ_STRING ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,long) ; 
 scalar_t__ checkStringLength (TYPE_2__*,long) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* createObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbAdd (TYPE_4__*,TYPE_5__*,TYPE_1__*) ; 
 TYPE_1__* dbUnshareStringValue (TYPE_4__*,TYPE_5__*,TYPE_1__*) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_2__*,TYPE_5__*,long*,int /*<<< orphan*/ *) ; 
 TYPE_1__* lookupKeyWrite (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,long) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sdsgrowzero (scalar_t__,long) ; 
 long sdslen (scalar_t__) ; 
 int /*<<< orphan*/  sdsnewlen (int /*<<< orphan*/ *,long) ; 
 TYPE_8__ server ; 
 TYPE_6__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_4__*,TYPE_5__*) ; 
 size_t stringObjectLen (TYPE_1__*) ; 

void setrangeCommand(client *c) {
    robj *o;
    long offset;
    sds value = c->argv[3]->ptr;

    if (getLongFromObjectOrReply(c,c->argv[2],&offset,NULL) != C_OK)
        return;

    if (offset < 0) {
        addReplyError(c,"offset is out of range");
        return;
    }

    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        /* Return 0 when setting nothing on a non-existing string */
        if (sdslen(value) == 0) {
            addReply(c,shared.czero);
            return;
        }

        /* Return when the resulting string exceeds allowed size */
        if (checkStringLength(c,offset+sdslen(value)) != C_OK)
            return;

        o = createObject(OBJ_STRING,sdsnewlen(NULL, offset+sdslen(value)));
        dbAdd(c->db,c->argv[1],o);
    } else {
        size_t olen;

        /* Key exists, check type */
        if (checkType(c,o,OBJ_STRING))
            return;

        /* Return existing string length when setting nothing */
        olen = stringObjectLen(o);
        if (sdslen(value) == 0) {
            addReplyLongLong(c,olen);
            return;
        }

        /* Return when the resulting string exceeds allowed size */
        if (checkStringLength(c,offset+sdslen(value)) != C_OK)
            return;

        /* Create a copy when the object is shared or encoded. */
        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }

    if (sdslen(value) > 0) {
        o->ptr = sdsgrowzero(o->ptr,offset+sdslen(value));
        memcpy((char*)o->ptr+offset,value,sdslen(value));
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_STRING,
            "setrange",c->argv[1],c->db->id);
        server.dirty++;
    }
    addReplyLongLong(c,sdslen(o->ptr));
}