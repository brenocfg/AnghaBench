#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_14__ ;

/* Type definitions */
struct TYPE_38__ {scalar_t__ delivery_time; scalar_t__ delivery_count; TYPE_1__* consumer; int /*<<< orphan*/ * pel; } ;
typedef  TYPE_2__ streamNACK ;
typedef  int /*<<< orphan*/  streamID ;
typedef  TYPE_2__ streamConsumer ;
struct TYPE_39__ {int /*<<< orphan*/ * pel; int /*<<< orphan*/ * consumers; } ;
typedef  TYPE_4__ streamCG ;
typedef  int /*<<< orphan*/  startkey ;
struct TYPE_40__ {scalar_t__ ptr; } ;
typedef  TYPE_5__ robj ;
struct TYPE_41__ {int /*<<< orphan*/  key; TYPE_2__* data; int /*<<< orphan*/  key_len; } ;
typedef  TYPE_6__ raxIterator ;
typedef  int /*<<< orphan*/  rax ;
typedef  scalar_t__ mstime_t ;
struct TYPE_42__ {int argc; TYPE_5__** argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_7__ client ;
struct TYPE_37__ {int /*<<< orphan*/  name; } ;
struct TYPE_36__ {int /*<<< orphan*/  syntaxerr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  OBJ_STREAM ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  addReply (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_7__*,int) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkLongLong (TYPE_7__*,scalar_t__) ; 
 void* addReplyDeferredLen (TYPE_7__*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_7__*,char*,char*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_7__*) ; 
 int /*<<< orphan*/  addReplyNullArray (TYPE_7__*) ; 
 int /*<<< orphan*/  addReplyStreamID (TYPE_7__*,int /*<<< orphan*/ *) ; 
 scalar_t__ checkType (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_7__*,TYPE_5__*,long long*,int /*<<< orphan*/ *) ; 
 TYPE_5__* lookupKeyRead (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mstime () ; 
 scalar_t__ raxNext (TYPE_6__*) ; 
 int /*<<< orphan*/  raxSeek (TYPE_6__*,char*,unsigned char*,int) ; 
 scalar_t__ raxSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxStart (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxStop (TYPE_6__*) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setDeferredArrayLen (TYPE_7__*,void*,size_t) ; 
 TYPE_14__ shared ; 
 int /*<<< orphan*/  streamDecodeID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamEncodeID (unsigned char*,int /*<<< orphan*/ *) ; 
 TYPE_4__* streamLookupCG (scalar_t__,scalar_t__) ; 
 TYPE_2__* streamLookupConsumer (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ streamParseIDOrReply (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void xpendingCommand(client *c) {
    int justinfo = c->argc == 3; /* Without the range just outputs general
                                    informations about the PEL. */
    robj *key = c->argv[1];
    robj *groupname = c->argv[2];
    robj *consumername = (c->argc == 7) ? c->argv[6] : NULL;
    streamID startid, endid;
    long long count;

    /* Start and stop, and the consumer, can be omitted. */
    if (c->argc != 3 && c->argc != 6 && c->argc != 7) {
        addReply(c,shared.syntaxerr);
        return;
    }

    /* Parse start/end/count arguments ASAP if needed, in order to report
     * syntax errors before any other error. */
    if (c->argc >= 6) {
        if (getLongLongFromObjectOrReply(c,c->argv[5],&count,NULL) == C_ERR)
            return;
        if (count < 0) count = 0;
        if (streamParseIDOrReply(c,c->argv[3],&startid,0) == C_ERR)
            return;
        if (streamParseIDOrReply(c,c->argv[4],&endid,UINT64_MAX) == C_ERR)
            return;
    }

    /* Lookup the key and the group inside the stream. */
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    streamCG *group;

    if (o && checkType(c,o,OBJ_STREAM)) return;
    if (o == NULL ||
        (group = streamLookupCG(o->ptr,groupname->ptr)) == NULL)
    {
        addReplyErrorFormat(c, "-NOGROUP No such key '%s' or consumer "
                               "group '%s'",
                               (char*)key->ptr,(char*)groupname->ptr);
        return;
    }

    /* XPENDING <key> <group> variant. */
    if (justinfo) {
        addReplyArrayLen(c,4);
        /* Total number of messages in the PEL. */
        addReplyLongLong(c,raxSize(group->pel));
        /* First and last IDs. */
        if (raxSize(group->pel) == 0) {
            addReplyNull(c); /* Start. */
            addReplyNull(c); /* End. */
            addReplyNullArray(c); /* Clients. */
        } else {
            /* Start. */
            raxIterator ri;
            raxStart(&ri,group->pel);
            raxSeek(&ri,"^",NULL,0);
            raxNext(&ri);
            streamDecodeID(ri.key,&startid);
            addReplyStreamID(c,&startid);

            /* End. */
            raxSeek(&ri,"$",NULL,0);
            raxNext(&ri);
            streamDecodeID(ri.key,&endid);
            addReplyStreamID(c,&endid);
            raxStop(&ri);

            /* Consumers with pending messages. */
            raxStart(&ri,group->consumers);
            raxSeek(&ri,"^",NULL,0);
            void *arraylen_ptr = addReplyDeferredLen(c);
            size_t arraylen = 0;
            while(raxNext(&ri)) {
                streamConsumer *consumer = ri.data;
                if (raxSize(consumer->pel) == 0) continue;
                addReplyArrayLen(c,2);
                addReplyBulkCBuffer(c,ri.key,ri.key_len);
                addReplyBulkLongLong(c,raxSize(consumer->pel));
                arraylen++;
            }
            setDeferredArrayLen(c,arraylen_ptr,arraylen);
            raxStop(&ri);
        }
    }
    /* XPENDING <key> <group> <start> <stop> <count> [<consumer>] variant. */
    else {
        streamConsumer *consumer = consumername ?
                                streamLookupConsumer(group,consumername->ptr,0):
                                NULL;

        /* If a consumer name was mentioned but it does not exist, we can
         * just return an empty array. */
        if (consumername && consumer == NULL) {
            addReplyArrayLen(c,0);
            return;
        }

        rax *pel = consumer ? consumer->pel : group->pel;
        unsigned char startkey[sizeof(streamID)];
        unsigned char endkey[sizeof(streamID)];
        raxIterator ri;
        mstime_t now = mstime();

        streamEncodeID(startkey,&startid);
        streamEncodeID(endkey,&endid);
        raxStart(&ri,pel);
        raxSeek(&ri,">=",startkey,sizeof(startkey));
        void *arraylen_ptr = addReplyDeferredLen(c);
        size_t arraylen = 0;

        while(count && raxNext(&ri) && memcmp(ri.key,endkey,ri.key_len) <= 0) {
            streamNACK *nack = ri.data;

            arraylen++;
            count--;
            addReplyArrayLen(c,4);

            /* Entry ID. */
            streamID id;
            streamDecodeID(ri.key,&id);
            addReplyStreamID(c,&id);

            /* Consumer name. */
            addReplyBulkCBuffer(c,nack->consumer->name,
                                sdslen(nack->consumer->name));

            /* Milliseconds elapsed since last delivery. */
            mstime_t elapsed = now - nack->delivery_time;
            if (elapsed < 0) elapsed = 0;
            addReplyLongLong(c,elapsed);

            /* Number of deliveries. */
            addReplyLongLong(c,nack->delivery_count);
        }
        raxStop(&ri);
        setDeferredArrayLen(c,arraylen_ptr,arraylen);
    }
}