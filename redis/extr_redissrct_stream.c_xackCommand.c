#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_1__* consumer; } ;
typedef  TYPE_2__ streamNACK ;
typedef  int /*<<< orphan*/  streamID ;
struct TYPE_25__ {int /*<<< orphan*/  pel; } ;
typedef  TYPE_3__ streamCG ;
struct TYPE_26__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_4__ robj ;
struct TYPE_27__ {int argc; TYPE_8__** argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_5__ client ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_28__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_23__ {int /*<<< orphan*/  pel; } ;
struct TYPE_22__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_21__ {int /*<<< orphan*/  czero; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  OBJ_STREAM ; 
 int /*<<< orphan*/  addReply (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_5__*,int) ; 
 scalar_t__ checkType (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* lookupKeyRead (int /*<<< orphan*/ ,TYPE_8__*) ; 
 TYPE_2__* raxFind (int /*<<< orphan*/ ,unsigned char*,int) ; 
 TYPE_2__* raxNotFound ; 
 int /*<<< orphan*/  raxRemove (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *) ; 
 TYPE_12__ server ; 
 TYPE_11__ shared ; 
 int /*<<< orphan*/  streamEncodeID (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamFreeNACK (TYPE_2__*) ; 
 TYPE_3__* streamLookupCG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ streamParseStrictIDOrReply (TYPE_5__*,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void xackCommand(client *c) {
    streamCG *group = NULL;
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    if (o) {
        if (checkType(c,o,OBJ_STREAM)) return; /* Type error. */
        group = streamLookupCG(o->ptr,c->argv[2]->ptr);
    }

    /* No key or group? Nothing to ack. */
    if (o == NULL || group == NULL) {
        addReply(c,shared.czero);
        return;
    }

    int acknowledged = 0;
    for (int j = 3; j < c->argc; j++) {
        streamID id;
        unsigned char buf[sizeof(streamID)];
        if (streamParseStrictIDOrReply(c,c->argv[j],&id,0) != C_OK) return;
        streamEncodeID(buf,&id);

        /* Lookup the ID in the group PEL: it will have a reference to the
         * NACK structure that will have a reference to the consumer, so that
         * we are able to remove the entry from both PELs. */
        streamNACK *nack = raxFind(group->pel,buf,sizeof(buf));
        if (nack != raxNotFound) {
            raxRemove(group->pel,buf,sizeof(buf),NULL);
            raxRemove(nack->consumer->pel,buf,sizeof(buf),NULL);
            streamFreeNACK(nack);
            acknowledged++;
            server.dirty++;
        }
    }
    addReplyLongLong(c,acknowledged);
}