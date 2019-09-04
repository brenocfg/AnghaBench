#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ encoding; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  rio ;
typedef  int /*<<< orphan*/  quicklistIter ;
struct TYPE_9__ {int sz; int /*<<< orphan*/  longval; scalar_t__ value; } ;
typedef  TYPE_2__ quicklistEntry ;
typedef  int /*<<< orphan*/  quicklist ;

/* Variables and functions */
 int /*<<< orphan*/  AL_START_HEAD ; 
 long long AOF_REWRITE_ITEMS_PER_CMD ; 
 scalar_t__ OBJ_ENCODING_QUICKLIST ; 
 long long listTypeLength (TYPE_1__*) ; 
 int /*<<< orphan*/ * quicklistGetIterator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ quicklistNext (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  quicklistReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ rioWriteBulkCount (int /*<<< orphan*/ *,char,int) ; 
 scalar_t__ rioWriteBulkLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rioWriteBulkObject (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ rioWriteBulkString (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

int rewriteListObject(rio *r, robj *key, robj *o) {
    long long count = 0, items = listTypeLength(o);

    if (o->encoding == OBJ_ENCODING_QUICKLIST) {
        quicklist *list = o->ptr;
        quicklistIter *li = quicklistGetIterator(list, AL_START_HEAD);
        quicklistEntry entry;

        while (quicklistNext(li,&entry)) {
            if (count == 0) {
                int cmd_items = (items > AOF_REWRITE_ITEMS_PER_CMD) ?
                    AOF_REWRITE_ITEMS_PER_CMD : items;
                if (rioWriteBulkCount(r,'*',2+cmd_items) == 0) return 0;
                if (rioWriteBulkString(r,"RPUSH",5) == 0) return 0;
                if (rioWriteBulkObject(r,key) == 0) return 0;
            }

            if (entry.value) {
                if (rioWriteBulkString(r,(char*)entry.value,entry.sz) == 0) return 0;
            } else {
                if (rioWriteBulkLongLong(r,entry.longval) == 0) return 0;
            }
            if (++count == AOF_REWRITE_ITEMS_PER_CMD) count = 0;
            items--;
        }
        quicklistReleaseIterator(li);
    } else {
        serverPanic("Unknown list encoding");
    }
    return 1;
}