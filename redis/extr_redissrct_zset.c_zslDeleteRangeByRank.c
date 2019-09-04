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
struct TYPE_10__ {int /*<<< orphan*/  ele; TYPE_1__* level; } ;
typedef  TYPE_2__ zskiplistNode ;
struct TYPE_11__ {int level; TYPE_2__* header; } ;
typedef  TYPE_3__ zskiplist ;
typedef  int /*<<< orphan*/  dict ;
struct TYPE_9__ {unsigned long span; TYPE_2__* forward; } ;

/* Variables and functions */
 int ZSKIPLIST_MAXLEVEL ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zslDeleteNode (TYPE_3__*,TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  zslFreeNode (TYPE_2__*) ; 

unsigned long zslDeleteRangeByRank(zskiplist *zsl, unsigned int start, unsigned int end, dict *dict) {
    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
    unsigned long traversed = 0, removed = 0;
    int i;

    x = zsl->header;
    for (i = zsl->level-1; i >= 0; i--) {
        while (x->level[i].forward && (traversed + x->level[i].span) < start) {
            traversed += x->level[i].span;
            x = x->level[i].forward;
        }
        update[i] = x;
    }

    traversed++;
    x = x->level[0].forward;
    while (x && traversed <= end) {
        zskiplistNode *next = x->level[0].forward;
        zslDeleteNode(zsl,x,update);
        dictDelete(dict,x->ele);
        zslFreeNode(x);
        removed++;
        traversed++;
        x = next;
    }
    return removed;
}