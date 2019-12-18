#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  seen_time; int /*<<< orphan*/  pel; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ streamConsumer ;
struct TYPE_10__ {int /*<<< orphan*/  consumers; } ;
typedef  TYPE_2__ streamCG ;
typedef  scalar_t__ sds ;

/* Variables and functions */
 int /*<<< orphan*/  mstime () ; 
 TYPE_1__* raxFind (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxNew () ; 
 TYPE_1__* raxNotFound ; 
 int /*<<< orphan*/  sdsdup (scalar_t__) ; 
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 TYPE_1__* zmalloc (int) ; 

streamConsumer *streamLookupConsumer(streamCG *cg, sds name, int create) {
    streamConsumer *consumer = raxFind(cg->consumers,(unsigned char*)name,
                               sdslen(name));
    if (consumer == raxNotFound) {
        if (!create) return NULL;
        consumer = zmalloc(sizeof(*consumer));
        consumer->name = sdsdup(name);
        consumer->pel = raxNew();
        raxInsert(cg->consumers,(unsigned char*)name,sdslen(name),
                  consumer,NULL);
    }
    consumer->seen_time = mstime();
    return consumer;
}