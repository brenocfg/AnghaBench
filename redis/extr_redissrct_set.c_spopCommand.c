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
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  char* sds ;
struct TYPE_26__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_27__ {int argc; size_t resp; int /*<<< orphan*/ * argv; TYPE_5__* db; } ;
typedef  TYPE_2__ client ;
struct TYPE_29__ {int /*<<< orphan*/ * null; int /*<<< orphan*/  syntaxerr; } ;
struct TYPE_28__ {int /*<<< orphan*/  id; } ;
struct TYPE_25__ {int /*<<< orphan*/  dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTIFY_GENERIC ; 
 int /*<<< orphan*/  NOTIFY_SET ; 
 int OBJ_ENCODING_INTSET ; 
 int /*<<< orphan*/  OBJ_SET ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* createStringObject (char*,int) ; 
 TYPE_1__* createStringObjectFromLongLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbDelete (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 int /*<<< orphan*/  intsetRemove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* lookupKeyWriteOrReply (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteClientCommandVector (TYPE_2__*,int,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sdslen (char*) ; 
 TYPE_10__ server ; 
 int setTypeRandomElement (TYPE_1__*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setTypeRemove (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ setTypeSize (TYPE_1__*) ; 
 TYPE_6__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spopWithCountCommand (TYPE_2__*) ; 

void spopCommand(client *c) {
    robj *set, *ele, *aux;
    sds sdsele;
    int64_t llele;
    int encoding;

    if (c->argc == 3) {
        spopWithCountCommand(c);
        return;
    } else if (c->argc > 3) {
        addReply(c,shared.syntaxerr);
        return;
    }

    /* Make sure a key with the name inputted exists, and that it's type is
     * indeed a set */
    if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.null[c->resp]))
         == NULL || checkType(c,set,OBJ_SET)) return;

    /* Get a random element from the set */
    encoding = setTypeRandomElement(set,&sdsele,&llele);

    /* Remove the element from the set */
    if (encoding == OBJ_ENCODING_INTSET) {
        ele = createStringObjectFromLongLong(llele);
        set->ptr = intsetRemove(set->ptr,llele,NULL);
    } else {
        ele = createStringObject(sdsele,sdslen(sdsele));
        setTypeRemove(set,ele->ptr);
    }

    notifyKeyspaceEvent(NOTIFY_SET,"spop",c->argv[1],c->db->id);

    /* Replicate/AOF this command as an SREM operation */
    aux = createStringObject("SREM",4);
    rewriteClientCommandVector(c,3,aux,c->argv[1],ele);
    decrRefCount(aux);

    /* Add the element to the reply */
    addReplyBulk(c,ele);
    decrRefCount(ele);

    /* Delete the set if it's empty */
    if (setTypeSize(set) == 0) {
        dbDelete(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
    }

    /* Set has been modified */
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
}