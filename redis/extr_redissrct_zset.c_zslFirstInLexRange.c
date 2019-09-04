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
struct TYPE_8__ {int /*<<< orphan*/  ele; TYPE_1__* level; } ;
typedef  TYPE_2__ zskiplistNode ;
struct TYPE_9__ {int level; TYPE_2__* header; } ;
typedef  TYPE_3__ zskiplist ;
typedef  int /*<<< orphan*/  zlexrangespec ;
struct TYPE_7__ {TYPE_2__* forward; } ;

/* Variables and functions */
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zslIsInLexRange (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zslLexValueGteMin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zslLexValueLteMax (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

zskiplistNode *zslFirstInLexRange(zskiplist *zsl, zlexrangespec *range) {
    zskiplistNode *x;
    int i;

    /* If everything is out of range, return early. */
    if (!zslIsInLexRange(zsl,range)) return NULL;

    x = zsl->header;
    for (i = zsl->level-1; i >= 0; i--) {
        /* Go forward while *OUT* of range. */
        while (x->level[i].forward &&
            !zslLexValueGteMin(x->level[i].forward->ele,range))
                x = x->level[i].forward;
    }

    /* This is an inner range, so the next node cannot be NULL. */
    x = x->level[0].forward;
    serverAssert(x != NULL);

    /* Check if score <= max. */
    if (!zslLexValueLteMax(x->ele,range)) return NULL;
    return x;
}