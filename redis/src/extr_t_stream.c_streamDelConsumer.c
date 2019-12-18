#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  streamNACK ;
struct TYPE_12__ {int /*<<< orphan*/  pel; } ;
typedef  TYPE_1__ streamConsumer ;
struct TYPE_13__ {int /*<<< orphan*/  consumers; int /*<<< orphan*/  pel; } ;
typedef  TYPE_2__ streamCG ;
typedef  scalar_t__ sds ;
struct TYPE_14__ {unsigned char* key; int /*<<< orphan*/  key_len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ raxIterator ;

/* Variables and functions */
 scalar_t__ raxNext (TYPE_3__*) ; 
 int /*<<< orphan*/  raxRemove (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxSeek (TYPE_3__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStart (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStop (TYPE_3__*) ; 
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 int /*<<< orphan*/  streamFreeConsumer (TYPE_1__*) ; 
 int /*<<< orphan*/  streamFreeNACK (int /*<<< orphan*/ *) ; 
 TYPE_1__* streamLookupConsumer (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

uint64_t streamDelConsumer(streamCG *cg, sds name) {
    streamConsumer *consumer = streamLookupConsumer(cg,name,0);
    if (consumer == NULL) return 0;

    uint64_t retval = raxSize(consumer->pel);

    /* Iterate all the consumer pending messages, deleting every corresponding
     * entry from the global entry. */
    raxIterator ri;
    raxStart(&ri,consumer->pel);
    raxSeek(&ri,"^",NULL,0);
    while(raxNext(&ri)) {
        streamNACK *nack = ri.data;
        raxRemove(cg->pel,ri.key,ri.key_len,NULL);
        streamFreeNACK(nack);
    }
    raxStop(&ri);

    /* Deallocate the consumer. */
    raxRemove(cg->consumers,(unsigned char*)name,sdslen(name),NULL);
    streamFreeConsumer(consumer);
    return retval;
}