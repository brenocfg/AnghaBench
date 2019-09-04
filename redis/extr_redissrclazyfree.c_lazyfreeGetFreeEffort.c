#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t len; TYPE_1__* zsl; } ;
typedef  TYPE_2__ zset ;
struct TYPE_10__ {scalar_t__ type; scalar_t__ encoding; TYPE_2__* ptr; } ;
typedef  TYPE_3__ robj ;
typedef  TYPE_2__ quicklist ;
typedef  TYPE_2__ dict ;
struct TYPE_8__ {size_t length; } ;

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_HT ; 
 scalar_t__ OBJ_ENCODING_SKIPLIST ; 
 scalar_t__ OBJ_HASH ; 
 scalar_t__ OBJ_LIST ; 
 scalar_t__ OBJ_SET ; 
 scalar_t__ OBJ_ZSET ; 
 size_t dictSize (TYPE_2__*) ; 

size_t lazyfreeGetFreeEffort(robj *obj) {
    if (obj->type == OBJ_LIST) {
        quicklist *ql = obj->ptr;
        return ql->len;
    } else if (obj->type == OBJ_SET && obj->encoding == OBJ_ENCODING_HT) {
        dict *ht = obj->ptr;
        return dictSize(ht);
    } else if (obj->type == OBJ_ZSET && obj->encoding == OBJ_ENCODING_SKIPLIST){
        zset *zs = obj->ptr;
        return zs->zsl->length;
    } else if (obj->type == OBJ_HASH && obj->encoding == OBJ_ENCODING_HT) {
        dict *ht = obj->ptr;
        return dictSize(ht);
    } else {
        return 1; /* Everything else is a single allocation. */
    }
}