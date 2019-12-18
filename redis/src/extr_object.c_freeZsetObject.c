#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  zsl; int /*<<< orphan*/  dict; } ;
typedef  TYPE_1__ zset ;
struct TYPE_6__ {int encoding; TYPE_1__* ptr; } ;
typedef  TYPE_2__ robj ;

/* Variables and functions */
#define  OBJ_ENCODING_SKIPLIST 129 
#define  OBJ_ENCODING_ZIPLIST 128 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 
 int /*<<< orphan*/  zslFree (int /*<<< orphan*/ ) ; 

void freeZsetObject(robj *o) {
    zset *zs;
    switch (o->encoding) {
    case OBJ_ENCODING_SKIPLIST:
        zs = o->ptr;
        dictRelease(zs->dict);
        zslFree(zs->zsl);
        zfree(zs);
        break;
    case OBJ_ENCODING_ZIPLIST:
        zfree(o->ptr);
        break;
    default:
        serverPanic("Unknown sorted set encoding");
    }
}