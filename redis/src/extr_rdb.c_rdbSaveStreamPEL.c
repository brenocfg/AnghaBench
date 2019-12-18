#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  delivery_count; int /*<<< orphan*/  delivery_time; } ;
typedef  TYPE_1__ streamNACK ;
typedef  int /*<<< orphan*/  streamID ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  rio ;
struct TYPE_8__ {TYPE_1__* data; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ raxIterator ;
typedef  int /*<<< orphan*/  rax ;

/* Variables and functions */
 scalar_t__ raxNext (TYPE_2__*) ; 
 int /*<<< orphan*/  raxSeek (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxStart (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxStop (TYPE_2__*) ; 
 int rdbSaveLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rdbSaveMillisecondTime (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rdbWriteRaw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

ssize_t rdbSaveStreamPEL(rio *rdb, rax *pel, int nacks) {
    ssize_t n, nwritten = 0;

    /* Number of entries in the PEL. */
    if ((n = rdbSaveLen(rdb,raxSize(pel))) == -1) return -1;
    nwritten += n;

    /* Save each entry. */
    raxIterator ri;
    raxStart(&ri,pel);
    raxSeek(&ri,"^",NULL,0);
    while(raxNext(&ri)) {
        /* We store IDs in raw form as 128 big big endian numbers, like
         * they are inside the radix tree key. */
        if ((n = rdbWriteRaw(rdb,ri.key,sizeof(streamID))) == -1) return -1;
        nwritten += n;

        if (nacks) {
            streamNACK *nack = ri.data;
            if ((n = rdbSaveMillisecondTime(rdb,nack->delivery_time)) == -1)
                return -1;
            nwritten += n;
            if ((n = rdbSaveLen(rdb,nack->delivery_count)) == -1) return -1;
            nwritten += n;
            /* We don't save the consumer name: we'll save the pending IDs
             * for each consumer in the consumer PEL, and resolve the consumer
             * at loading time. */
        }
    }
    raxStop(&ri);
    return nwritten;
}