#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
struct TYPE_8__ {unsigned char* lp; unsigned char* lp_flags; scalar_t__ rev; TYPE_5__* stream; int /*<<< orphan*/  end_key; int /*<<< orphan*/  start_key; TYPE_1__ ri; } ;
typedef  TYPE_2__ streamIterator ;
typedef  int /*<<< orphan*/  streamID ;
typedef  int int64_t ;
struct TYPE_9__ {int /*<<< orphan*/  length; int /*<<< orphan*/  rax; } ;

/* Variables and functions */
 int STREAM_ITEM_FLAG_DELETED ; 
 unsigned char* lpFirst (unsigned char*) ; 
 int /*<<< orphan*/  lpFree (unsigned char*) ; 
 int lpGetInteger (unsigned char*) ; 
 unsigned char* lpNext (unsigned char*,unsigned char*) ; 
 unsigned char* lpReplaceInteger (unsigned char*,unsigned char**,int) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxRemove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamDecodeID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  streamIteratorStart (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  streamIteratorStop (TYPE_2__*) ; 

void streamIteratorRemoveEntry(streamIterator *si, streamID *current) {
    unsigned char *lp = si->lp;
    int64_t aux;

    /* We do not really delete the entry here. Instead we mark it as
     * deleted flagging it, and also incrementing the count of the
     * deleted entries in the listpack header.
     *
     * We start flagging: */
    int flags = lpGetInteger(si->lp_flags);
    flags |= STREAM_ITEM_FLAG_DELETED;
    lp = lpReplaceInteger(lp,&si->lp_flags,flags);

    /* Change the valid/deleted entries count in the master entry. */
    unsigned char *p = lpFirst(lp);
    aux = lpGetInteger(p);

    if (aux == 1) {
        /* If this is the last element in the listpack, we can remove the whole
         * node. */
        lpFree(lp);
        raxRemove(si->stream->rax,si->ri.key,si->ri.key_len,NULL);
    } else {
        /* In the base case we alter the counters of valid/deleted entries. */
        lp = lpReplaceInteger(lp,&p,aux-1);
        p = lpNext(lp,p); /* Seek deleted field. */
        aux = lpGetInteger(p);
        lp = lpReplaceInteger(lp,&p,aux+1);

        /* Update the listpack with the new pointer. */
        if (si->lp != lp)
            raxInsert(si->stream->rax,si->ri.key,si->ri.key_len,lp,NULL);
    }

    /* Update the number of entries counter. */
    si->stream->length--;

    /* Re-seek the iterator to fix the now messed up state. */
    streamID start, end;
    if (si->rev) {
        streamDecodeID(si->start_key,&start);
        end = *current;
    } else {
        start = *current;
        streamDecodeID(si->end_key,&end);
    }
    streamIteratorStop(si);
    streamIteratorStart(si,si->stream,&start,&end,si->rev);

    /* TODO: perform a garbage collection here if the ration between
     * deleted and valid goes over a certain limit. */
}