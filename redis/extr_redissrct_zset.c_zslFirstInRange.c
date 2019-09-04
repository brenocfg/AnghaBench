#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  score; TYPE_1__* level; } ;
typedef  TYPE_2__ zskiplistNode ;
struct TYPE_9__ {int level; TYPE_2__* header; } ;
typedef  TYPE_3__ zskiplist ;
typedef  int /*<<< orphan*/  zrangespec ;
struct TYPE_7__ {TYPE_2__* forward; } ;

/* Variables and functions */
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zslIsInRange (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zslValueGteMin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zslValueLteMax (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

zskiplistNode *zslFirstInRange(zskiplist *zsl, zrangespec *range) {
    zskiplistNode *x;
    int i;

    /* If everything is out of range, return early. */
    if (!zslIsInRange(zsl,range)) return NULL;

    x = zsl->header;
    for (i = zsl->level-1; i >= 0; i--) {
        /* Go forward while *OUT* of range. */
        while (x->level[i].forward &&
            !zslValueGteMin(x->level[i].forward->score,range))
                x = x->level[i].forward;
    }

    /* This is an inner range, so the next node cannot be NULL. */
    x = x->level[0].forward;
    serverAssert(x != NULL);

    /* Check if score <= max. */
    if (!zslValueLteMax(x->score,range)) return NULL;
    return x;
}