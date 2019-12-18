#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; int refcount; int lru; void* ptr; int /*<<< orphan*/  encoding; } ;
typedef  TYPE_1__ robj ;
struct TYPE_6__ {int maxmemory_policy; } ;

/* Variables and functions */
 int LFUGetTimeInMinutes () ; 
 int LFU_INIT_VAL ; 
 int LRU_CLOCK () ; 
 int MAXMEMORY_FLAG_LFU ; 
 int /*<<< orphan*/  OBJ_ENCODING_RAW ; 
 TYPE_3__ server ; 
 TYPE_1__* zmalloc (int) ; 

robj *createObject(int type, void *ptr) {
    robj *o = zmalloc(sizeof(*o));
    o->type = type;
    o->encoding = OBJ_ENCODING_RAW;
    o->ptr = ptr;
    o->refcount = 1;

    /* Set the LRU to the current lruclock (minutes resolution), or
     * alternatively the LFU counter. */
    if (server.maxmemory_policy & MAXMEMORY_FLAG_LFU) {
        o->lru = (LFUGetTimeInMinutes()<<8) | LFU_INIT_VAL;
    } else {
        o->lru = LRU_CLOCK();
    }
    return o;
}