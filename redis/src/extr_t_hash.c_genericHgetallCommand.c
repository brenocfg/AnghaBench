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
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  hashTypeIterator ;
struct TYPE_9__ {size_t resp; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_10__ {int /*<<< orphan*/ * emptymap; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  OBJ_HASH ; 
 int OBJ_HASH_KEY ; 
 int OBJ_HASH_VALUE ; 
 int /*<<< orphan*/  addHashIteratorCursorToReply (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_1__*,int) ; 
 int /*<<< orphan*/  addReplyMapLen (TYPE_1__*,int) ; 
 scalar_t__ checkType (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashTypeInitIterator (int /*<<< orphan*/ *) ; 
 int hashTypeLength (int /*<<< orphan*/ *) ; 
 scalar_t__ hashTypeNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashTypeReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupKeyReadOrReply (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 TYPE_2__ shared ; 

void genericHgetallCommand(client *c, int flags) {
    robj *o;
    hashTypeIterator *hi;
    int length, count = 0;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymap[c->resp]))
        == NULL || checkType(c,o,OBJ_HASH)) return;

    /* We return a map if the user requested keys and values, like in the
     * HGETALL case. Otherwise to use a flat array makes more sense. */
    length = hashTypeLength(o);
    if (flags & OBJ_HASH_KEY && flags & OBJ_HASH_VALUE) {
        addReplyMapLen(c, length);
    } else {
        addReplyArrayLen(c, length);
    }

    hi = hashTypeInitIterator(o);
    while (hashTypeNext(hi) != C_ERR) {
        if (flags & OBJ_HASH_KEY) {
            addHashIteratorCursorToReply(c, hi, OBJ_HASH_KEY);
            count++;
        }
        if (flags & OBJ_HASH_VALUE) {
            addHashIteratorCursorToReply(c, hi, OBJ_HASH_VALUE);
            count++;
        }
    }

    hashTypeReleaseIterator(hi);

    /* Make sure we returned the right number of elements. */
    if (flags & OBJ_HASH_KEY && flags & OBJ_HASH_VALUE) count /= 2;
    serverAssert(count == length);
}