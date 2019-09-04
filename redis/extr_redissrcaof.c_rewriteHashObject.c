#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  rio ;
typedef  int /*<<< orphan*/  hashTypeIterator ;

/* Variables and functions */
 long long AOF_REWRITE_ITEMS_PER_CMD ; 
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  OBJ_HASH_KEY ; 
 int /*<<< orphan*/  OBJ_HASH_VALUE ; 
 int /*<<< orphan*/ * hashTypeInitIterator (int /*<<< orphan*/ *) ; 
 long long hashTypeLength (int /*<<< orphan*/ *) ; 
 scalar_t__ hashTypeNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashTypeReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ rioWriteBulkCount (int /*<<< orphan*/ *,char,int) ; 
 scalar_t__ rioWriteBulkObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rioWriteBulkString (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ rioWriteHashIteratorCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int rewriteHashObject(rio *r, robj *key, robj *o) {
    hashTypeIterator *hi;
    long long count = 0, items = hashTypeLength(o);

    hi = hashTypeInitIterator(o);
    while (hashTypeNext(hi) != C_ERR) {
        if (count == 0) {
            int cmd_items = (items > AOF_REWRITE_ITEMS_PER_CMD) ?
                AOF_REWRITE_ITEMS_PER_CMD : items;

            if (rioWriteBulkCount(r,'*',2+cmd_items*2) == 0) return 0;
            if (rioWriteBulkString(r,"HMSET",5) == 0) return 0;
            if (rioWriteBulkObject(r,key) == 0) return 0;
        }

        if (rioWriteHashIteratorCursor(r, hi, OBJ_HASH_KEY) == 0) return 0;
        if (rioWriteHashIteratorCursor(r, hi, OBJ_HASH_VALUE) == 0) return 0;
        if (++count == AOF_REWRITE_ITEMS_PER_CMD) count = 0;
        items--;
    }

    hashTypeReleaseIterator(hi);

    return 1;
}