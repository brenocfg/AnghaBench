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
struct TYPE_9__ {int /*<<< orphan*/  pel; int /*<<< orphan*/  seen_time; } ;
typedef  TYPE_1__ streamConsumer ;
struct TYPE_10__ {int /*<<< orphan*/  consumers; } ;
typedef  TYPE_2__ streamCG ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  rio ;
struct TYPE_11__ {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; TYPE_1__* data; } ;
typedef  TYPE_3__ raxIterator ;

/* Variables and functions */
 scalar_t__ raxNext (TYPE_3__*) ; 
 int /*<<< orphan*/  raxSeek (TYPE_3__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStart (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStop (TYPE_3__*) ; 
 int rdbSaveLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rdbSaveMillisecondTime (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rdbSaveRawString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdbSaveStreamPEL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t rdbSaveStreamConsumers(rio *rdb, streamCG *cg) {
    ssize_t n, nwritten = 0;

    /* Number of consumers in this consumer group. */
    if ((n = rdbSaveLen(rdb,raxSize(cg->consumers))) == -1) return -1;
    nwritten += n;

    /* Save each consumer. */
    raxIterator ri;
    raxStart(&ri,cg->consumers);
    raxSeek(&ri,"^",NULL,0);
    while(raxNext(&ri)) {
        streamConsumer *consumer = ri.data;

        /* Consumer name. */
        if ((n = rdbSaveRawString(rdb,ri.key,ri.key_len)) == -1) return -1;
        nwritten += n;

        /* Last seen time. */
        if ((n = rdbSaveMillisecondTime(rdb,consumer->seen_time)) == -1)
            return -1;
        nwritten += n;

        /* Consumer PEL, without the ACKs (see last parameter of the function
         * passed with value of 0), at loading time we'll lookup the ID
         * in the consumer group global PEL and will put a reference in the
         * consumer local PEL. */
        if ((n = rdbSaveStreamPEL(rdb,consumer->pel,0)) == -1)
            return -1;
        nwritten += n;
    }
    raxStop(&ri);
    return nwritten;
}