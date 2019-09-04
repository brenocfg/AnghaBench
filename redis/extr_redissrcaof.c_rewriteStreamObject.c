#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ pel; scalar_t__ consumers; int /*<<< orphan*/  last_id; } ;
typedef  TYPE_1__ streamNACK ;
typedef  int /*<<< orphan*/  streamIterator ;
typedef  int /*<<< orphan*/  streamID ;
typedef  TYPE_1__ streamConsumer ;
typedef  TYPE_1__ streamCG ;
struct TYPE_19__ {scalar_t__ cgroups; int /*<<< orphan*/  last_id; scalar_t__ length; } ;
typedef  TYPE_4__ stream ;
struct TYPE_20__ {TYPE_4__* ptr; } ;
typedef  TYPE_5__ robj ;
typedef  int /*<<< orphan*/  rio ;
struct TYPE_21__ {int key_len; scalar_t__ key; TYPE_1__* data; } ;
typedef  TYPE_6__ raxIterator ;
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ raxNext (TYPE_6__*) ; 
 int /*<<< orphan*/  raxSeek (TYPE_6__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStart (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  raxStop (TYPE_6__*) ; 
 scalar_t__ rioWriteBulkCount (int /*<<< orphan*/ *,char,int) ; 
 scalar_t__ rioWriteBulkObject (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ rioWriteBulkStreamID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rioWriteBulkString (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ rioWriteStreamPendingEntry (int /*<<< orphan*/ *,TYPE_5__*,char*,int,TYPE_1__*,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  streamIteratorGetField (int /*<<< orphan*/ *,unsigned char**,unsigned char**,int*,int*) ; 
 scalar_t__ streamIteratorGetID (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  streamIteratorStart (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streamIteratorStop (int /*<<< orphan*/ *) ; 

int rewriteStreamObject(rio *r, robj *key, robj *o) {
    stream *s = o->ptr;
    streamIterator si;
    streamIteratorStart(&si,s,NULL,NULL,0);
    streamID id;
    int64_t numfields;

    if (s->length) {
        /* Reconstruct the stream data using XADD commands. */
        while(streamIteratorGetID(&si,&id,&numfields)) {
            /* Emit a two elements array for each item. The first is
             * the ID, the second is an array of field-value pairs. */

            /* Emit the XADD <key> <id> ...fields... command. */
            if (rioWriteBulkCount(r,'*',3+numfields*2) == 0) return 0;
            if (rioWriteBulkString(r,"XADD",4) == 0) return 0;
            if (rioWriteBulkObject(r,key) == 0) return 0;
            if (rioWriteBulkStreamID(r,&id) == 0) return 0;
            while(numfields--) {
                unsigned char *field, *value;
                int64_t field_len, value_len;
                streamIteratorGetField(&si,&field,&value,&field_len,&value_len);
                if (rioWriteBulkString(r,(char*)field,field_len) == 0) return 0;
                if (rioWriteBulkString(r,(char*)value,value_len) == 0) return 0;
            }
        }
    } else {
        /* Use the XADD MAXLEN 0 trick to generate an empty stream if
         * the key we are serializing is an empty string, which is possible
         * for the Stream type. */
        if (rioWriteBulkCount(r,'*',7) == 0) return 0;
        if (rioWriteBulkString(r,"XADD",4) == 0) return 0;
        if (rioWriteBulkObject(r,key) == 0) return 0;
        if (rioWriteBulkString(r,"MAXLEN",6) == 0) return 0;
        if (rioWriteBulkString(r,"0",1) == 0) return 0;
        if (rioWriteBulkStreamID(r,&s->last_id) == 0) return 0;
        if (rioWriteBulkString(r,"x",1) == 0) return 0;
        if (rioWriteBulkString(r,"y",1) == 0) return 0;
    }

    /* Append XSETID after XADD, make sure lastid is correct,
     * in case of XDEL lastid. */
    if (rioWriteBulkCount(r,'*',3) == 0) return 0;
    if (rioWriteBulkString(r,"XSETID",6) == 0) return 0;
    if (rioWriteBulkObject(r,key) == 0) return 0;
    if (rioWriteBulkStreamID(r,&s->last_id) == 0) return 0;


    /* Create all the stream consumer groups. */
    if (s->cgroups) {
        raxIterator ri;
        raxStart(&ri,s->cgroups);
        raxSeek(&ri,"^",NULL,0);
        while(raxNext(&ri)) {
            streamCG *group = ri.data;
            /* Emit the XGROUP CREATE in order to create the group. */
            if (rioWriteBulkCount(r,'*',5) == 0) return 0;
            if (rioWriteBulkString(r,"XGROUP",6) == 0) return 0;
            if (rioWriteBulkString(r,"CREATE",6) == 0) return 0;
            if (rioWriteBulkObject(r,key) == 0) return 0;
            if (rioWriteBulkString(r,(char*)ri.key,ri.key_len) == 0) return 0;
            if (rioWriteBulkStreamID(r,&group->last_id) == 0) return 0;

            /* Generate XCLAIMs for each consumer that happens to
             * have pending entries. Empty consumers have no semantical
             * value so they are discarded. */
            raxIterator ri_cons;
            raxStart(&ri_cons,group->consumers);
            raxSeek(&ri_cons,"^",NULL,0);
            while(raxNext(&ri_cons)) {
                streamConsumer *consumer = ri_cons.data;
                /* For the current consumer, iterate all the PEL entries
                 * to emit the XCLAIM protocol. */
                raxIterator ri_pel;
                raxStart(&ri_pel,consumer->pel);
                raxSeek(&ri_pel,"^",NULL,0);
                while(raxNext(&ri_pel)) {
                    streamNACK *nack = ri_pel.data;
                    if (rioWriteStreamPendingEntry(r,key,(char*)ri.key,
                                                   ri.key_len,consumer,
                                                   ri_pel.key,nack) == 0)
                    {
                        return 0;
                    }
                }
                raxStop(&ri_pel);
            }
            raxStop(&ri_cons);
        }
        raxStop(&ri);
    }

    streamIteratorStop(&si);
    return 1;
}