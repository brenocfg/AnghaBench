#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  delivery_count; int /*<<< orphan*/  delivery_time; } ;
typedef  TYPE_1__ streamNACK ;
typedef  int /*<<< orphan*/  streamID ;
struct TYPE_10__ {int /*<<< orphan*/  pel; } ;
typedef  TYPE_2__ streamConsumer ;
typedef  int /*<<< orphan*/  stream ;
typedef  int /*<<< orphan*/  startkey ;
struct TYPE_11__ {TYPE_1__* data; int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;
typedef  TYPE_3__ raxIterator ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_RWR_RAWENTRIES ; 
 int /*<<< orphan*/  addReplyArrayLen (int /*<<< orphan*/ *,int) ; 
 void* addReplyDeferredLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyNullArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyStreamID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mstime () ; 
 scalar_t__ raxNext (TYPE_3__*) ; 
 int /*<<< orphan*/  raxSeek (TYPE_3__*,char*,unsigned char*,int) ; 
 int /*<<< orphan*/  raxStart (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStop (TYPE_3__*) ; 
 int /*<<< orphan*/  setDeferredArrayLen (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  streamDecodeID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamEncodeID (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ streamReplyWithRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

size_t streamReplyWithRangeFromConsumerPEL(client *c, stream *s, streamID *start, streamID *end, size_t count, streamConsumer *consumer) {
    raxIterator ri;
    unsigned char startkey[sizeof(streamID)];
    unsigned char endkey[sizeof(streamID)];
    streamEncodeID(startkey,start);
    if (end) streamEncodeID(endkey,end);

    size_t arraylen = 0;
    void *arraylen_ptr = addReplyDeferredLen(c);
    raxStart(&ri,consumer->pel);
    raxSeek(&ri,">=",startkey,sizeof(startkey));
    while(raxNext(&ri) && (!count || arraylen < count)) {
        if (end && memcmp(ri.key,end,ri.key_len) > 0) break;
        streamID thisid;
        streamDecodeID(ri.key,&thisid);
        if (streamReplyWithRange(c,s,&thisid,&thisid,1,0,NULL,NULL,
                                 STREAM_RWR_RAWENTRIES,NULL) == 0)
        {
            /* Note that we may have a not acknowledged entry in the PEL
             * about a message that's no longer here because was removed
             * by the user by other means. In that case we signal it emitting
             * the ID but then a NULL entry for the fields. */
            addReplyArrayLen(c,2);
            streamID id;
            streamDecodeID(ri.key,&id);
            addReplyStreamID(c,&id);
            addReplyNullArray(c);
        } else {
            streamNACK *nack = ri.data;
            nack->delivery_time = mstime();
            nack->delivery_count++;
        }
        arraylen++;
    }
    raxStop(&ri);
    setDeferredArrayLen(c,arraylen_ptr,arraylen);
    return arraylen;
}