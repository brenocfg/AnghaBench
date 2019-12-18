#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ encoding; } ;
typedef  TYPE_1__ robj ;
struct TYPE_20__ {int /*<<< orphan*/  longval; int /*<<< orphan*/  sz; scalar_t__ value; } ;
typedef  TYPE_2__ quicklistEntry ;
typedef  int /*<<< orphan*/  listTypeIterator ;
struct TYPE_21__ {TYPE_2__ entry; } ;
typedef  TYPE_3__ listTypeEntry ;
struct TYPE_22__ {int /*<<< orphan*/ * argv; } ;
typedef  TYPE_4__ client ;
struct TYPE_23__ {int /*<<< orphan*/  emptyarray; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  LIST_TAIL ; 
 scalar_t__ OBJ_ENCODING_QUICKLIST ; 
 int /*<<< orphan*/  OBJ_LIST ; 
 int /*<<< orphan*/  addReply (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_4__*,long) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ checkType (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_4__*,int /*<<< orphan*/ ,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listTypeInitIterator (TYPE_1__*,long,int /*<<< orphan*/ ) ; 
 long listTypeLength (TYPE_1__*) ; 
 int /*<<< orphan*/  listTypeNext (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  listTypeReleaseIterator (int /*<<< orphan*/ *) ; 
 TYPE_1__* lookupKeyReadOrReply (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 TYPE_5__ shared ; 

void lrangeCommand(client *c) {
    robj *o;
    long start, end, llen, rangelen;

    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != C_OK) ||
        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != C_OK)) return;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptyarray)) == NULL
         || checkType(c,o,OBJ_LIST)) return;
    llen = listTypeLength(o);

    /* convert negative indexes */
    if (start < 0) start = llen+start;
    if (end < 0) end = llen+end;
    if (start < 0) start = 0;

    /* Invariant: start >= 0, so this test will be true when end < 0.
     * The range is empty when start > end or start >= length. */
    if (start > end || start >= llen) {
        addReply(c,shared.emptyarray);
        return;
    }
    if (end >= llen) end = llen-1;
    rangelen = (end-start)+1;

    /* Return the result in form of a multi-bulk reply */
    addReplyArrayLen(c,rangelen);
    if (o->encoding == OBJ_ENCODING_QUICKLIST) {
        listTypeIterator *iter = listTypeInitIterator(o, start, LIST_TAIL);

        while(rangelen--) {
            listTypeEntry entry;
            listTypeNext(iter, &entry);
            quicklistEntry *qe = &entry.entry;
            if (qe->value) {
                addReplyBulkCBuffer(c,qe->value,qe->sz);
            } else {
                addReplyBulkLongLong(c,qe->longval);
            }
        }
        listTypeReleaseIterator(iter);
    } else {
        serverPanic("List encoding is not QUICKLIST!");
    }
}