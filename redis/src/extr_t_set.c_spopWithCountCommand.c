#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  setTypeIterator ;
typedef  char* sds ;
struct TYPE_41__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_42__ {size_t resp; TYPE_1__** argv; TYPE_6__* db; } ;
typedef  TYPE_2__ client ;
struct TYPE_44__ {int /*<<< orphan*/  del; int /*<<< orphan*/ * emptyset; int /*<<< orphan*/ * null; int /*<<< orphan*/  outofrangeerr; } ;
struct TYPE_43__ {int /*<<< orphan*/  id; } ;
struct TYPE_40__ {scalar_t__ dirty; int /*<<< orphan*/  sremCommand; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  NOTIFY_GENERIC ; 
 int /*<<< orphan*/  NOTIFY_SET ; 
 int OBJ_ENCODING_INTSET ; 
 int /*<<< orphan*/  OBJ_SET ; 
 int PROPAGATE_AOF ; 
 int PROPAGATE_REPL ; 
 int /*<<< orphan*/  SET_OP_UNION ; 
 unsigned long SPOP_MOVE_STRATEGY_MUL ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplySetLen (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  alsoPropagate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int,int) ; 
 scalar_t__ checkType (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* createStringObject (char*,int) ; 
 TYPE_1__* createStringObjectFromLongLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbDelete (TYPE_6__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dbOverwrite (TYPE_6__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_2__*,TYPE_1__*,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intsetRemove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* lookupKeyWriteOrReply (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preventCommandPropagation (TYPE_2__*) ; 
 int /*<<< orphan*/  rewriteClientCommandVector (TYPE_2__*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* sdsdup (char*) ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 char* sdsfromlonglong (int /*<<< orphan*/ ) ; 
 int sdslen (char*) ; 
 TYPE_15__ server ; 
 int /*<<< orphan*/  setTypeAdd (TYPE_1__*,char*) ; 
 TYPE_1__* setTypeCreate (char*) ; 
 int /*<<< orphan*/ * setTypeInitIterator (TYPE_1__*) ; 
 int setTypeNext (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int setTypeRandomElement (TYPE_1__*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setTypeReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setTypeRemove (TYPE_1__*,char*) ; 
 unsigned long setTypeSize (TYPE_1__*) ; 
 TYPE_8__ shared ; 
 int /*<<< orphan*/  signalModifiedKey (TYPE_6__*,TYPE_1__*) ; 
 int /*<<< orphan*/  sunionDiffGenericCommand (TYPE_2__*,TYPE_1__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void spopWithCountCommand(client *c) {
    long l;
    unsigned long count, size;
    robj *set;

    /* Get the count argument */
    if (getLongFromObjectOrReply(c,c->argv[2],&l,NULL) != C_OK) return;
    if (l >= 0) {
        count = (unsigned long) l;
    } else {
        addReply(c,shared.outofrangeerr);
        return;
    }

    /* Make sure a key with the name inputted exists, and that it's type is
     * indeed a set. Otherwise, return nil */
    if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.null[c->resp]))
        == NULL || checkType(c,set,OBJ_SET)) return;

    /* If count is zero, serve an empty set ASAP to avoid special
     * cases later. */
    if (count == 0) {
        addReply(c,shared.emptyset[c->resp]);
        return;
    }

    size = setTypeSize(set);

    /* Generate an SPOP keyspace notification */
    notifyKeyspaceEvent(NOTIFY_SET,"spop",c->argv[1],c->db->id);
    server.dirty += count;

    /* CASE 1:
     * The number of requested elements is greater than or equal to
     * the number of elements inside the set: simply return the whole set. */
    if (count >= size) {
        /* We just return the entire set */
        sunionDiffGenericCommand(c,c->argv+1,1,NULL,SET_OP_UNION);

        /* Delete the set as it is now empty */
        dbDelete(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);

        /* Propagate this command as an DEL operation */
        rewriteClientCommandVector(c,2,shared.del,c->argv[1]);
        signalModifiedKey(c->db,c->argv[1]);
        server.dirty++;
        return;
    }

    /* Case 2 and 3 require to replicate SPOP as a set of SREM commands.
     * Prepare our replication argument vector. Also send the array length
     * which is common to both the code paths. */
    robj *propargv[3];
    propargv[0] = createStringObject("SREM",4);
    propargv[1] = c->argv[1];
    addReplySetLen(c,count);

    /* Common iteration vars. */
    sds sdsele;
    robj *objele;
    int encoding;
    int64_t llele;
    unsigned long remaining = size-count; /* Elements left after SPOP. */

    /* If we are here, the number of requested elements is less than the
     * number of elements inside the set. Also we are sure that count < size.
     * Use two different strategies.
     *
     * CASE 2: The number of elements to return is small compared to the
     * set size. We can just extract random elements and return them to
     * the set. */
    if (remaining*SPOP_MOVE_STRATEGY_MUL > count) {
        while(count--) {
            /* Emit and remove. */
            encoding = setTypeRandomElement(set,&sdsele,&llele);
            if (encoding == OBJ_ENCODING_INTSET) {
                addReplyBulkLongLong(c,llele);
                objele = createStringObjectFromLongLong(llele);
                set->ptr = intsetRemove(set->ptr,llele,NULL);
            } else {
                addReplyBulkCBuffer(c,sdsele,sdslen(sdsele));
                objele = createStringObject(sdsele,sdslen(sdsele));
                setTypeRemove(set,sdsele);
            }

            /* Replicate/AOF this command as an SREM operation */
            propargv[2] = objele;
            alsoPropagate(server.sremCommand,c->db->id,propargv,3,
                PROPAGATE_AOF|PROPAGATE_REPL);
            decrRefCount(objele);
        }
    } else {
    /* CASE 3: The number of elements to return is very big, approaching
     * the size of the set itself. After some time extracting random elements
     * from such a set becomes computationally expensive, so we use
     * a different strategy, we extract random elements that we don't
     * want to return (the elements that will remain part of the set),
     * creating a new set as we do this (that will be stored as the original
     * set). Then we return the elements left in the original set and
     * release it. */
        robj *newset = NULL;

        /* Create a new set with just the remaining elements. */
        while(remaining--) {
            encoding = setTypeRandomElement(set,&sdsele,&llele);
            if (encoding == OBJ_ENCODING_INTSET) {
                sdsele = sdsfromlonglong(llele);
            } else {
                sdsele = sdsdup(sdsele);
            }
            if (!newset) newset = setTypeCreate(sdsele);
            setTypeAdd(newset,sdsele);
            setTypeRemove(set,sdsele);
            sdsfree(sdsele);
        }

        /* Transfer the old set to the client. */
        setTypeIterator *si;
        si = setTypeInitIterator(set);
        while((encoding = setTypeNext(si,&sdsele,&llele)) != -1) {
            if (encoding == OBJ_ENCODING_INTSET) {
                addReplyBulkLongLong(c,llele);
                objele = createStringObjectFromLongLong(llele);
            } else {
                addReplyBulkCBuffer(c,sdsele,sdslen(sdsele));
                objele = createStringObject(sdsele,sdslen(sdsele));
            }

            /* Replicate/AOF this command as an SREM operation */
            propargv[2] = objele;
            alsoPropagate(server.sremCommand,c->db->id,propargv,3,
                PROPAGATE_AOF|PROPAGATE_REPL);
            decrRefCount(objele);
        }
        setTypeReleaseIterator(si);

        /* Assign the new set as the key value. */
        dbOverwrite(c->db,c->argv[1],newset);
    }

    /* Don't propagate the command itself even if we incremented the
     * dirty counter. We don't want to propagate an SPOP command since
     * we propagated the command as a set of SREMs operations using
     * the alsoPropagate() API. */
    decrRefCount(propargv[0]);
    preventCommandPropagation(c);
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
}