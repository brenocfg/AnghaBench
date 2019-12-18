#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int refcount; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_LAZY_FREE ; 
 size_t LAZYFREE_THRESHOLD ; 
 int /*<<< orphan*/  atomicIncr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bioCreateBackgroundJob (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 size_t lazyfreeGetFreeEffort (TYPE_1__*) ; 
 int /*<<< orphan*/  lazyfree_objects ; 

void freeObjAsync(robj *o) {
    size_t free_effort = lazyfreeGetFreeEffort(o);
    if (free_effort > LAZYFREE_THRESHOLD && o->refcount == 1) {
        atomicIncr(lazyfree_objects,1);
        bioCreateBackgroundJob(BIO_LAZY_FREE,o,NULL,NULL);
    } else {
        decrRefCount(o);
    }
}