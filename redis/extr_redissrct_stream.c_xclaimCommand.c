#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_58__   TYPE_6__ ;
typedef  struct TYPE_57__   TYPE_5__ ;
typedef  struct TYPE_56__   TYPE_4__ ;
typedef  struct TYPE_55__   TYPE_3__ ;
typedef  struct TYPE_54__   TYPE_35__ ;
typedef  struct TYPE_53__   TYPE_2__ ;
typedef  struct TYPE_52__   TYPE_1__ ;
typedef  struct TYPE_51__   TYPE_12__ ;

/* Type definitions */
struct TYPE_52__ {int delivery_time; long long delivery_count; TYPE_3__* consumer; } ;
typedef  TYPE_1__ streamNACK ;
typedef  int /*<<< orphan*/  streamIterator ;
struct TYPE_53__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ streamID ;
struct TYPE_55__ {int /*<<< orphan*/  pel; } ;
typedef  TYPE_3__ streamConsumer ;
struct TYPE_56__ {int /*<<< orphan*/  pel; TYPE_2__ last_id; } ;
typedef  TYPE_4__ streamCG ;
struct TYPE_57__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_5__ robj ;
typedef  int mstime_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_58__ {int argc; TYPE_12__** argv; int /*<<< orphan*/  db; } ;
typedef  TYPE_6__ client ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_54__ {int /*<<< orphan*/  dirty; } ;
struct TYPE_51__ {char* ptr; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  OBJ_STREAM ; 
 int /*<<< orphan*/  STREAM_RWR_RAWENTRIES ; 
 void* addReplyDeferredLen (TYPE_6__*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_6__*,char*,char*,...) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_6__*) ; 
 int /*<<< orphan*/  addReplyStreamID (TYPE_6__*,TYPE_2__*) ; 
 scalar_t__ checkType (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_6__*,TYPE_12__*,...) ; 
 TYPE_5__* lookupKeyRead (int /*<<< orphan*/ ,TYPE_12__*) ; 
 int mstime () ; 
 int /*<<< orphan*/  preventCommandPropagation (TYPE_6__*) ; 
 TYPE_1__* raxFind (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ ,unsigned char*,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* raxNotFound ; 
 int /*<<< orphan*/  raxRemove (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *) ; 
 TYPE_35__ server ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/  setDeferredArrayLen (TYPE_6__*,void*,size_t) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ streamCompareID (TYPE_2__*,TYPE_2__*) ; 
 TYPE_1__* streamCreateNACK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamEncodeID (unsigned char*,TYPE_2__*) ; 
 scalar_t__ streamIteratorGetID (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamIteratorStart (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streamIteratorStop (int /*<<< orphan*/ *) ; 
 TYPE_4__* streamLookupCG (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* streamLookupConsumer (TYPE_4__*,char*,int) ; 
 scalar_t__ streamParseStrictIDOrReply (TYPE_6__*,TYPE_12__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streamPropagateGroupID (TYPE_6__*,TYPE_12__*,TYPE_4__*,TYPE_12__*) ; 
 int /*<<< orphan*/  streamPropagateXCLAIM (TYPE_6__*,TYPE_12__*,TYPE_4__*,TYPE_12__*,TYPE_12__*,TYPE_1__*) ; 
 size_t streamReplyWithRange (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void xclaimCommand(client *c) {
    streamCG *group = NULL;
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    long long minidle; /* Minimum idle time argument. */
    long long retrycount = -1;   /* -1 means RETRYCOUNT option not given. */
    mstime_t deliverytime = -1;  /* -1 means IDLE/TIME options not given. */
    int force = 0;
    int justid = 0;

    if (o) {
        if (checkType(c,o,OBJ_STREAM)) return; /* Type error. */
        group = streamLookupCG(o->ptr,c->argv[2]->ptr);
    }

    /* No key or group? Send an error given that the group creation
     * is mandatory. */
    if (o == NULL || group == NULL) {
        addReplyErrorFormat(c,"-NOGROUP No such key '%s' or "
                              "consumer group '%s'", (char*)c->argv[1]->ptr,
                              (char*)c->argv[2]->ptr);
        return;
    }

    if (getLongLongFromObjectOrReply(c,c->argv[4],&minidle,
        "Invalid min-idle-time argument for XCLAIM")
        != C_OK) return;
    if (minidle < 0) minidle = 0;

    /* Start parsing the IDs, so that we abort ASAP if there is a syntax
     * error: the return value of this command cannot be an error in case
     * the client successfully claimed some message, so it should be
     * executed in a "all or nothing" fashion. */
    int j;
    for (j = 5; j < c->argc; j++) {
        streamID id;
        if (streamParseStrictIDOrReply(NULL,c->argv[j],&id,0) != C_OK) break;
    }
    int last_id_arg = j-1; /* Next time we iterate the IDs we now the range. */

    /* If we stopped because some IDs cannot be parsed, perhaps they
     * are trailing options. */
    mstime_t now = mstime();
    streamID last_id = {0,0};
    int propagate_last_id = 0;
    for (; j < c->argc; j++) {
        int moreargs = (c->argc-1) - j; /* Number of additional arguments. */
        char *opt = c->argv[j]->ptr;
        if (!strcasecmp(opt,"FORCE")) {
            force = 1;
        } else if (!strcasecmp(opt,"JUSTID")) {
            justid = 1;
        } else if (!strcasecmp(opt,"IDLE") && moreargs) {
            j++;
            if (getLongLongFromObjectOrReply(c,c->argv[j],&deliverytime,
                "Invalid IDLE option argument for XCLAIM")
                != C_OK) return;
            deliverytime = now - deliverytime;
        } else if (!strcasecmp(opt,"TIME") && moreargs) {
            j++;
            if (getLongLongFromObjectOrReply(c,c->argv[j],&deliverytime,
                "Invalid TIME option argument for XCLAIM")
                != C_OK) return;
        } else if (!strcasecmp(opt,"RETRYCOUNT") && moreargs) {
            j++;
            if (getLongLongFromObjectOrReply(c,c->argv[j],&retrycount,
                "Invalid RETRYCOUNT option argument for XCLAIM")
                != C_OK) return;
        } else if (!strcasecmp(opt,"LASTID") && moreargs) {
            j++;
            if (streamParseStrictIDOrReply(c,c->argv[j],&last_id,0) != C_OK) return;
        } else {
            addReplyErrorFormat(c,"Unrecognized XCLAIM option '%s'",opt);
            return;
        }
    }

    if (streamCompareID(&last_id,&group->last_id) > 0) {
        group->last_id = last_id;
        propagate_last_id = 1;
    }

    if (deliverytime != -1) {
        /* If a delivery time was passed, either with IDLE or TIME, we
         * do some sanity check on it, and set the deliverytime to now
         * (which is a sane choice usually) if the value is bogus.
         * To raise an error here is not wise because clients may compute
         * the idle time doing some math starting from their local time,
         * and this is not a good excuse to fail in case, for instance,
         * the computer time is a bit in the future from our POV. */
        if (deliverytime < 0 || deliverytime > now) deliverytime = now;
    } else {
        /* If no IDLE/TIME option was passed, we want the last delivery
         * time to be now, so that the idle time of the message will be
         * zero. */
        deliverytime = now;
    }

    /* Do the actual claiming. */
    streamConsumer *consumer = streamLookupConsumer(group,c->argv[3]->ptr,1);
    void *arraylenptr = addReplyDeferredLen(c);
    size_t arraylen = 0;
    for (int j = 5; j <= last_id_arg; j++) {
        streamID id;
        unsigned char buf[sizeof(streamID)];
        if (streamParseStrictIDOrReply(c,c->argv[j],&id,0) != C_OK)
            serverPanic("StreamID invalid after check. Should not be possible.");
        streamEncodeID(buf,&id);

        /* Lookup the ID in the group PEL. */
        streamNACK *nack = raxFind(group->pel,buf,sizeof(buf));

        /* If FORCE is passed, let's check if at least the entry
         * exists in the Stream. In such case, we'll crate a new
         * entry in the PEL from scratch, so that XCLAIM can also
         * be used to create entries in the PEL. Useful for AOF
         * and replication of consumer groups. */
        if (force && nack == raxNotFound) {
            streamIterator myiterator;
            streamIteratorStart(&myiterator,o->ptr,&id,&id,0);
            int64_t numfields;
            int found = 0;
            streamID item_id;
            if (streamIteratorGetID(&myiterator,&item_id,&numfields)) found = 1;
            streamIteratorStop(&myiterator);

            /* Item must exist for us to create a NACK for it. */
            if (!found) continue;

            /* Create the NACK. */
            nack = streamCreateNACK(NULL);
            raxInsert(group->pel,buf,sizeof(buf),nack,NULL);
        }

        if (nack != raxNotFound) {
            /* We need to check if the minimum idle time requested
             * by the caller is satisfied by this entry.
             *
             * Note that the nack could be created by FORCE, in this
             * case there was no pre-existing entry and minidle should
             * be ignored, but in that case nick->consumer is NULL. */
            if (nack->consumer && minidle) {
                mstime_t this_idle = now - nack->delivery_time;
                if (this_idle < minidle) continue;
            }
            /* Remove the entry from the old consumer.
             * Note that nack->consumer is NULL if we created the
             * NACK above because of the FORCE option. */
            if (nack->consumer)
                raxRemove(nack->consumer->pel,buf,sizeof(buf),NULL);
            /* Update the consumer and idle time. */
            nack->consumer = consumer;
            nack->delivery_time = deliverytime;
            /* Set the delivery attempts counter if given, otherwise 
             * autoincrement unless JUSTID option provided */
            if (retrycount >= 0) {
                nack->delivery_count = retrycount;
            } else if (!justid) {
                nack->delivery_count++;
            }
            /* Add the entry in the new consumer local PEL. */
            raxInsert(consumer->pel,buf,sizeof(buf),nack,NULL);
            /* Send the reply for this entry. */
            if (justid) {
                addReplyStreamID(c,&id);
            } else {
                size_t emitted = streamReplyWithRange(c,o->ptr,&id,&id,1,0,
                                    NULL,NULL,STREAM_RWR_RAWENTRIES,NULL);
                if (!emitted) addReplyNull(c);
            }
            arraylen++;

            /* Propagate this change. */
            streamPropagateXCLAIM(c,c->argv[1],group,c->argv[2],c->argv[j],nack);
            propagate_last_id = 0; /* Will be propagated by XCLAIM itself. */
            server.dirty++;
        }
    }
    if (propagate_last_id) {
        streamPropagateGroupID(c,c->argv[1],group,c->argv[2]);
        server.dirty++;
    }
    setDeferredArrayLen(c,arraylenptr,arraylen);
    preventCommandPropagation(c);
}