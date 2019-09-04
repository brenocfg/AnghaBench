#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  streamIterator ;
typedef  int /*<<< orphan*/  streamID ;
struct TYPE_17__ {scalar_t__ length; int /*<<< orphan*/  last_id; } ;
typedef  TYPE_2__ stream ;
struct TYPE_18__ {TYPE_2__* ptr; } ;
typedef  TYPE_3__ robj ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_19__ {TYPE_1__* db; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_4__ client ;
struct TYPE_21__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_20__ {int /*<<< orphan*/  ok; int /*<<< orphan*/  nokeyerr; } ;
struct TYPE_16__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  NOTIFY_STREAM ; 
 int /*<<< orphan*/  OBJ_STREAM ; 
 int /*<<< orphan*/  addReply (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_4__*,char*) ; 
 scalar_t__ checkType (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* lookupKeyWriteOrReply (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifyKeyspaceEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ server ; 
 TYPE_8__ shared ; 
 scalar_t__ streamCompareID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamIteratorGetID (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamIteratorStart (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  streamIteratorStop (int /*<<< orphan*/ *) ; 
 scalar_t__ streamParseStrictIDOrReply (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void xsetidCommand(client *c) {
    robj *o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr);
    if (o == NULL || checkType(c,o,OBJ_STREAM)) return;

    stream *s = o->ptr;
    streamID id;
    if (streamParseStrictIDOrReply(c,c->argv[2],&id,0) != C_OK) return;

    /* If the stream has at least one item, we want to check that the user
     * is setting a last ID that is equal or greater than the current top
     * item, otherwise the fundamental ID monotonicity assumption is violated. */
    if (s->length > 0) {
        streamID maxid;
        streamIterator si;
        streamIteratorStart(&si,s,NULL,NULL,1);
        int64_t numfields;
        streamIteratorGetID(&si,&maxid,&numfields);
        streamIteratorStop(&si);

        if (streamCompareID(&id,&maxid) < 0) {
            addReplyError(c,"The ID specified in XSETID is smaller than the "
                            "target stream top item");
            return;
        }
    }
    s->last_id = id;
    addReply(c,shared.ok);
    server.dirty++;
    notifyKeyspaceEvent(NOTIFY_STREAM,"xsetid",c->argv[1],c->db->id);
}