#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int size; scalar_t__ iskey; scalar_t__ data; scalar_t__ iscompr; } ;
typedef  TYPE_2__ raxNode ;
struct TYPE_15__ {TYPE_2__* node; int /*<<< orphan*/  stack; TYPE_1__* rt; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ raxIterator ;
typedef  int /*<<< orphan*/  n ;
struct TYPE_13__ {scalar_t__ numele; TYPE_2__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAX_ITER_EOF ; 
 size_t floor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__**,TYPE_2__**,int) ; 
 int rand () ; 
 int /*<<< orphan*/  raxIteratorAddChars (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  raxIteratorDelChars (TYPE_3__*,int) ; 
 TYPE_2__** raxNodeFirstChildPtr (TYPE_2__*) ; 
 TYPE_2__* raxStackPop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxStackPush (int /*<<< orphan*/ *,TYPE_2__*) ; 

int raxRandomWalk(raxIterator *it, size_t steps) {
    if (it->rt->numele == 0) {
        it->flags |= RAX_ITER_EOF;
        return 0;
    }

    if (steps == 0) {
        size_t fle = floor(log(it->rt->numele));
        fle *= 2;
        steps = 1 + rand() % fle;
    }

    raxNode *n = it->node;
    while(steps > 0 || !n->iskey) {
        int numchildren = n->iscompr ? 1 : n->size;
        int r = rand() % (numchildren+(n != it->rt->head));

        if (r == numchildren) {
            /* Go up to parent. */
            n = raxStackPop(&it->stack);
            int todel = n->iscompr ? n->size : 1;
            raxIteratorDelChars(it,todel);
        } else {
            /* Select a random child. */
            if (n->iscompr) {
                if (!raxIteratorAddChars(it,n->data,n->size)) return 0;
            } else {
                if (!raxIteratorAddChars(it,n->data+r,1)) return 0;
            }
            raxNode **cp = raxNodeFirstChildPtr(n)+r;
            if (!raxStackPush(&it->stack,n)) return 0;
            memcpy(&n,cp,sizeof(n));
        }
        if (n->iskey) steps--;
    }
    it->node = n;
    return 1;
}