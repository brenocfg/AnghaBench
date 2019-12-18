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
struct TYPE_7__ {int /*<<< orphan*/  zsl; int /*<<< orphan*/  dict; } ;
typedef  TYPE_1__ zset ;
struct TYPE_8__ {int /*<<< orphan*/  encoding; } ;
typedef  TYPE_2__ robj ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_ENCODING_SKIPLIST ; 
 int /*<<< orphan*/  OBJ_ZSET ; 
 TYPE_2__* createObject (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* zmalloc (int) ; 
 int /*<<< orphan*/  zsetDictType ; 
 int /*<<< orphan*/  zslCreate () ; 

robj *createZsetObject(void) {
    zset *zs = zmalloc(sizeof(*zs));
    robj *o;

    zs->dict = dictCreate(&zsetDictType,NULL);
    zs->zsl = zslCreate();
    o = createObject(OBJ_ZSET,zs);
    o->encoding = OBJ_ENCODING_SKIPLIST;
    return o;
}