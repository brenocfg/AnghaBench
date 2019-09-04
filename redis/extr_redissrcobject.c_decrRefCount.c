#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int refcount; int type; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
#define  OBJ_HASH 134 
#define  OBJ_LIST 133 
#define  OBJ_MODULE 132 
#define  OBJ_SET 131 
 int OBJ_SHARED_REFCOUNT ; 
#define  OBJ_STREAM 130 
#define  OBJ_STRING 129 
#define  OBJ_ZSET 128 
 int /*<<< orphan*/  freeHashObject (TYPE_1__*) ; 
 int /*<<< orphan*/  freeListObject (TYPE_1__*) ; 
 int /*<<< orphan*/  freeModuleObject (TYPE_1__*) ; 
 int /*<<< orphan*/  freeSetObject (TYPE_1__*) ; 
 int /*<<< orphan*/  freeStreamObject (TYPE_1__*) ; 
 int /*<<< orphan*/  freeStringObject (TYPE_1__*) ; 
 int /*<<< orphan*/  freeZsetObject (TYPE_1__*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

void decrRefCount(robj *o) {
    if (o->refcount == 1) {
        switch(o->type) {
        case OBJ_STRING: freeStringObject(o); break;
        case OBJ_LIST: freeListObject(o); break;
        case OBJ_SET: freeSetObject(o); break;
        case OBJ_ZSET: freeZsetObject(o); break;
        case OBJ_HASH: freeHashObject(o); break;
        case OBJ_MODULE: freeModuleObject(o); break;
        case OBJ_STREAM: freeStreamObject(o); break;
        default: serverPanic("Unknown object type"); break;
        }
        zfree(o);
    } else {
        if (o->refcount <= 0) serverPanic("decrRefCount against refcount <= 0");
        if (o->refcount != OBJ_SHARED_REFCOUNT) o->refcount--;
    }
}