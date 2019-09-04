#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  groupname; int /*<<< orphan*/  keyname; } ;
typedef  TYPE_1__ streamPropInfo ;
struct TYPE_20__ {int delivery_count; int /*<<< orphan*/  delivery_time; TYPE_3__* consumer; } ;
typedef  TYPE_2__ streamNACK ;
typedef  int /*<<< orphan*/  streamIterator ;
typedef  int /*<<< orphan*/  streamID ;
struct TYPE_21__ {int /*<<< orphan*/  pel; } ;
typedef  TYPE_3__ streamConsumer ;
struct TYPE_22__ {int /*<<< orphan*/  pel; int /*<<< orphan*/  last_id; } ;
typedef  TYPE_4__ streamCG ;
typedef  int /*<<< orphan*/  stream ;
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  client ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int STREAM_RWR_HISTORY ; 
 int STREAM_RWR_NOACK ; 
 int STREAM_RWR_RAWENTRIES ; 
 int /*<<< orphan*/  addReplyArrayLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 void* addReplyDeferredLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyMapLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyStreamID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * createObjectFromStreamID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mstime () ; 
 TYPE_2__* raxFind (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ ,unsigned char*,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* raxNotFound ; 
 int /*<<< orphan*/  raxRemove (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int raxTryInsert (int /*<<< orphan*/ ,unsigned char*,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/  setDeferredArrayLen (int /*<<< orphan*/ *,void*,size_t) ; 
 scalar_t__ streamCompareID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* streamCreateNACK (TYPE_3__*) ; 
 int /*<<< orphan*/  streamEncodeID (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamFreeNACK (TYPE_2__*) ; 
 int /*<<< orphan*/  streamIteratorGetField (int /*<<< orphan*/ *,unsigned char**,unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ streamIteratorGetID (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamIteratorStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  streamIteratorStop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamPropagateGroupID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streamPropagateXCLAIM (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 size_t streamReplyWithRangeFromConsumerPEL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,TYPE_3__*) ; 

size_t streamReplyWithRange(client *c, stream *s, streamID *start, streamID *end, size_t count, int rev, streamCG *group, streamConsumer *consumer, int flags, streamPropInfo *spi) {
    void *arraylen_ptr = NULL;
    size_t arraylen = 0;
    streamIterator si;
    int64_t numfields;
    streamID id;
    int propagate_last_id = 0;

    /* If the client is asking for some history, we serve it using a
     * different function, so that we return entries *solely* from its
     * own PEL. This ensures each consumer will always and only see
     * the history of messages delivered to it and not yet confirmed
     * as delivered. */
    if (group && (flags & STREAM_RWR_HISTORY)) {
        return streamReplyWithRangeFromConsumerPEL(c,s,start,end,count,
                                                   consumer);
    }

    if (!(flags & STREAM_RWR_RAWENTRIES))
        arraylen_ptr = addReplyDeferredLen(c);
    streamIteratorStart(&si,s,start,end,rev);
    while(streamIteratorGetID(&si,&id,&numfields)) {
        /* Update the group last_id if needed. */
        if (group && streamCompareID(&id,&group->last_id) > 0) {
            group->last_id = id;
            propagate_last_id = 1;
        }

        /* Emit a two elements array for each item. The first is
         * the ID, the second is an array of field-value pairs. */
        addReplyArrayLen(c,2);
        addReplyStreamID(c,&id);

        addReplyMapLen(c,numfields);

        /* Emit the field-value pairs. */
        while(numfields--) {
            unsigned char *key, *value;
            int64_t key_len, value_len;
            streamIteratorGetField(&si,&key,&value,&key_len,&value_len);
            addReplyBulkCBuffer(c,key,key_len);
            addReplyBulkCBuffer(c,value,value_len);
        }

        /* If a group is passed, we need to create an entry in the
         * PEL (pending entries list) of this group *and* this consumer.
         *
         * Note that we cannot be sure about the fact the message is not
         * already owned by another consumer, because the admin is able
         * to change the consumer group last delivered ID using the
         * XGROUP SETID command. So if we find that there is already
         * a NACK for the entry, we need to associate it to the new
         * consumer. */
        if (group && !(flags & STREAM_RWR_NOACK)) {
            unsigned char buf[sizeof(streamID)];
            streamEncodeID(buf,&id);

            /* Try to add a new NACK. Most of the time this will work and
             * will not require extra lookups. We'll fix the problem later
             * if we find that there is already a entry for this ID. */
            streamNACK *nack = streamCreateNACK(consumer);
            int group_inserted =
                raxTryInsert(group->pel,buf,sizeof(buf),nack,NULL);
            int consumer_inserted =
                raxTryInsert(consumer->pel,buf,sizeof(buf),nack,NULL);

            /* Now we can check if the entry was already busy, and
             * in that case reassign the entry to the new consumer,
             * or update it if the consumer is the same as before. */
            if (group_inserted == 0) {
                streamFreeNACK(nack);
                nack = raxFind(group->pel,buf,sizeof(buf));
                serverAssert(nack != raxNotFound);
                raxRemove(nack->consumer->pel,buf,sizeof(buf),NULL);
                /* Update the consumer and NACK metadata. */
                nack->consumer = consumer;
                nack->delivery_time = mstime();
                nack->delivery_count = 1;
                /* Add the entry in the new consumer local PEL. */
                raxInsert(consumer->pel,buf,sizeof(buf),nack,NULL);
            } else if (group_inserted == 1 && consumer_inserted == 0) {
                serverPanic("NACK half-created. Should not be possible.");
            }

            /* Propagate as XCLAIM. */
            if (spi) {
                robj *idarg = createObjectFromStreamID(&id);
                streamPropagateXCLAIM(c,spi->keyname,group,spi->groupname,idarg,nack);
                decrRefCount(idarg);
            }
        } else {
            if (propagate_last_id)
                streamPropagateGroupID(c,spi->keyname,group,spi->groupname);
        }

        arraylen++;
        if (count && count == arraylen) break;
    }
    streamIteratorStop(&si);
    if (arraylen_ptr) setDeferredArrayLen(c,arraylen_ptr,arraylen);
    return arraylen;
}