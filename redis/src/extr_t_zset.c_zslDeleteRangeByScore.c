#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ score; int /*<<< orphan*/  ele; TYPE_1__* level; } ;
typedef  TYPE_2__ zskiplistNode ;
struct TYPE_13__ {int level; TYPE_2__* header; } ;
typedef  TYPE_3__ zskiplist ;
struct TYPE_14__ {scalar_t__ min; scalar_t__ max; scalar_t__ maxex; scalar_t__ minex; } ;
typedef  TYPE_4__ zrangespec ;
typedef  int /*<<< orphan*/  dict ;
struct TYPE_11__ {TYPE_2__* forward; } ;

/* Variables and functions */
 int ZSKIPLIST_MAXLEVEL ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zslDeleteNode (TYPE_3__*,TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  zslFreeNode (TYPE_2__*) ; 

unsigned long zslDeleteRangeByScore(zskiplist *zsl, zrangespec *range, dict *dict) {
    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
    unsigned long removed = 0;
    int i;

    x = zsl->header;
    for (i = zsl->level-1; i >= 0; i--) {
        while (x->level[i].forward && (range->minex ?
            x->level[i].forward->score <= range->min :
            x->level[i].forward->score < range->min))
                x = x->level[i].forward;
        update[i] = x;
    }

    /* Current node is the last with score < or <= min. */
    x = x->level[0].forward;

    /* Delete nodes while in range. */
    while (x &&
           (range->maxex ? x->score < range->max : x->score <= range->max))
    {
        zskiplistNode *next = x->level[0].forward;
        zslDeleteNode(zsl,x,update);
        dictDelete(dict,x->ele);
        zslFreeNode(x); /* Here is where x->ele is actually released. */
        removed++;
        x = next;
    }
    return removed;
}