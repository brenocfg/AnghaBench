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
struct TYPE_7__ {int /*<<< orphan*/  dict; int /*<<< orphan*/  zsl; } ;
typedef  TYPE_1__ zset ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_8__ {scalar_t__ encoding; TYPE_1__* ptr; } ;
typedef  TYPE_2__ robj ;
typedef  int /*<<< orphan*/  dictEntry ;

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_SKIPLIST ; 
 scalar_t__ OBJ_ENCODING_ZIPLIST ; 
 int /*<<< orphan*/  dictFreeUnlinkedEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictResize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictUnlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htNeedsResize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int zslDelete (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* zzlDelete (TYPE_1__*,unsigned char*) ; 
 unsigned char* zzlFind (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int zsetDel(robj *zobj, sds ele) {
    if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
        unsigned char *eptr;

        if ((eptr = zzlFind(zobj->ptr,ele,NULL)) != NULL) {
            zobj->ptr = zzlDelete(zobj->ptr,eptr);
            return 1;
        }
    } else if (zobj->encoding == OBJ_ENCODING_SKIPLIST) {
        zset *zs = zobj->ptr;
        dictEntry *de;
        double score;

        de = dictUnlink(zs->dict,ele);
        if (de != NULL) {
            /* Get the score in order to delete from the skiplist later. */
            score = *(double*)dictGetVal(de);

            /* Delete from the hash table and later from the skiplist.
             * Note that the order is important: deleting from the skiplist
             * actually releases the SDS string representing the element,
             * which is shared between the skiplist and the hash table, so
             * we need to delete from the skiplist as the final step. */
            dictFreeUnlinkedEntry(zs->dict,de);

            /* Delete from skiplist. */
            int retval = zslDelete(zs->zsl,score,ele,NULL);
            serverAssert(retval);

            if (htNeedsResize(zs->dict)) dictResize(zs->dict);
            return 1;
        }
    } else {
        serverPanic("Unknown sorted set encoding");
    }
    return 0; /* No such element found. */
}