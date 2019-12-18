#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned long long count; int /*<<< orphan*/  zl; struct TYPE_9__* prev; struct TYPE_9__* next; } ;
typedef  TYPE_1__ quicklistNode ;
struct TYPE_10__ {unsigned long long offset; int /*<<< orphan*/  longval; int /*<<< orphan*/  sz; int /*<<< orphan*/  value; int /*<<< orphan*/  zi; TYPE_1__* node; TYPE_3__ const* quicklist; } ;
typedef  TYPE_2__ quicklistEntry ;
struct TYPE_11__ {unsigned long long count; TYPE_1__* head; TYPE_1__* tail; } ;
typedef  TYPE_3__ quicklist ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,void*,unsigned long long,unsigned long long,...) ; 
 int /*<<< orphan*/  initEntry (TYPE_2__*) ; 
 scalar_t__ likely (TYPE_1__*) ; 
 int /*<<< orphan*/  quicklistDecompressNodeForUse (TYPE_1__*) ; 
 int /*<<< orphan*/  ziplistGet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ziplistIndex (int /*<<< orphan*/ ,unsigned long long) ; 

int quicklistIndex(const quicklist *quicklist, const long long idx,
                   quicklistEntry *entry) {
    quicklistNode *n;
    unsigned long long accum = 0;
    unsigned long long index;
    int forward = idx < 0 ? 0 : 1; /* < 0 -> reverse, 0+ -> forward */

    initEntry(entry);
    entry->quicklist = quicklist;

    if (!forward) {
        index = (-idx) - 1;
        n = quicklist->tail;
    } else {
        index = idx;
        n = quicklist->head;
    }

    if (index >= quicklist->count)
        return 0;

    while (likely(n)) {
        if ((accum + n->count) > index) {
            break;
        } else {
            D("Skipping over (%p) %u at accum %lld", (void *)n, n->count,
              accum);
            accum += n->count;
            n = forward ? n->next : n->prev;
        }
    }

    if (!n)
        return 0;

    D("Found node: %p at accum %llu, idx %llu, sub+ %llu, sub- %llu", (void *)n,
      accum, index, index - accum, (-index) - 1 + accum);

    entry->node = n;
    if (forward) {
        /* forward = normal head-to-tail offset. */
        entry->offset = index - accum;
    } else {
        /* reverse = need negative offset for tail-to-head, so undo
         * the result of the original if (index < 0) above. */
        entry->offset = (-index) - 1 + accum;
    }

    quicklistDecompressNodeForUse(entry->node);
    entry->zi = ziplistIndex(entry->node->zl, entry->offset);
    ziplistGet(entry->zi, &entry->value, &entry->sz, &entry->longval);
    /* The caller will use our result, so we don't re-compress here.
     * The caller can recompress or delete the node as needed. */
    return 1;
}