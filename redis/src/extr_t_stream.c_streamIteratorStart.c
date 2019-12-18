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
struct TYPE_9__ {int rev; int /*<<< orphan*/ * lp_ele; int /*<<< orphan*/ * lp; TYPE_3__* stream; int /*<<< orphan*/  ri; void** end_key; void** start_key; } ;
typedef  TYPE_1__ streamIterator ;
struct TYPE_10__ {scalar_t__ seq; scalar_t__ ms; } ;
typedef  TYPE_2__ streamID ;
struct TYPE_11__ {int /*<<< orphan*/  rax; } ;
typedef  TYPE_3__ stream ;

/* Variables and functions */
 void* UINT64_MAX ; 
 scalar_t__ raxEOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxSeek (int /*<<< orphan*/ *,char*,unsigned char*,int) ; 
 int /*<<< orphan*/  raxStart (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streamEncodeID (void**,TYPE_2__*) ; 

void streamIteratorStart(streamIterator *si, stream *s, streamID *start, streamID *end, int rev) {
    /* Initialize the iterator and translates the iteration start/stop
     * elements into a 128 big big-endian number. */
    if (start) {
        streamEncodeID(si->start_key,start);
    } else {
        si->start_key[0] = 0;
        si->start_key[1] = 0;
    }

    if (end) {
        streamEncodeID(si->end_key,end);
    } else {
        si->end_key[0] = UINT64_MAX;
        si->end_key[1] = UINT64_MAX;
    }

    /* Seek the correct node in the radix tree. */
    raxStart(&si->ri,s->rax);
    if (!rev) {
        if (start && (start->ms || start->seq)) {
            raxSeek(&si->ri,"<=",(unsigned char*)si->start_key,
                    sizeof(si->start_key));
            if (raxEOF(&si->ri)) raxSeek(&si->ri,"^",NULL,0);
        } else {
            raxSeek(&si->ri,"^",NULL,0);
        }
    } else {
        if (end && (end->ms || end->seq)) {
            raxSeek(&si->ri,"<=",(unsigned char*)si->end_key,
                    sizeof(si->end_key));
            if (raxEOF(&si->ri)) raxSeek(&si->ri,"$",NULL,0);
        } else {
            raxSeek(&si->ri,"$",NULL,0);
        }
    }
    si->stream = s;
    si->lp = NULL; /* There is no current listpack right now. */
    si->lp_ele = NULL; /* Current listpack cursor. */
    si->rev = rev;  /* Direction, if non-zero reversed, from end to start. */
}