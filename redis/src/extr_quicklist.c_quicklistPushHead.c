#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  count; void* zl; } ;
typedef  TYPE_1__ quicklistNode ;
struct TYPE_11__ {TYPE_1__* head; int /*<<< orphan*/  count; int /*<<< orphan*/  fill; } ;
typedef  TYPE_2__ quicklist ;

/* Variables and functions */
 int /*<<< orphan*/  ZIPLIST_HEAD ; 
 int /*<<< orphan*/  _quicklistInsertNodeBefore (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  _quicklistNodeAllowInsert (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 TYPE_1__* quicklistCreateNode () ; 
 int /*<<< orphan*/  quicklistNodeUpdateSz (TYPE_1__*) ; 
 void* ziplistNew () ; 
 void* ziplistPush (void*,void*,size_t,int /*<<< orphan*/ ) ; 

int quicklistPushHead(quicklist *quicklist, void *value, size_t sz) {
    quicklistNode *orig_head = quicklist->head;
    if (likely(
            _quicklistNodeAllowInsert(quicklist->head, quicklist->fill, sz))) {
        quicklist->head->zl =
            ziplistPush(quicklist->head->zl, value, sz, ZIPLIST_HEAD);
        quicklistNodeUpdateSz(quicklist->head);
    } else {
        quicklistNode *node = quicklistCreateNode();
        node->zl = ziplistPush(ziplistNew(), value, sz, ZIPLIST_HEAD);

        quicklistNodeUpdateSz(node);
        _quicklistInsertNodeBefore(quicklist, quicklist->head, node);
    }
    quicklist->count++;
    quicklist->head->count++;
    return (orig_head != quicklist->head);
}