#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cstate {char lookahead; } ;
struct TYPE_4__ {struct TYPE_4__* y; struct TYPE_4__* x; } ;
typedef  TYPE_1__ Renode ;

/* Variables and functions */
 int /*<<< orphan*/  P_CAT ; 
 TYPE_1__* newnode (struct cstate*,int /*<<< orphan*/ ) ; 
 void* parserep (struct cstate*) ; 

__attribute__((used)) static Renode *parsecat(struct cstate *g)
{
	Renode *cat, *head, **tail;
	if (g->lookahead && g->lookahead != '|' && g->lookahead != ')') {
		/* Build a right-leaning tree by splicing in new 'cat' at the tail. */
		head = parserep(g);
		tail = &head;
		while (g->lookahead && g->lookahead != '|' && g->lookahead != ')') {
			cat = newnode(g, P_CAT);
			cat->x = *tail;
			cat->y = parserep(g);
			*tail = cat;
			tail = &cat->y;
		}
		return head;
	}
	return NULL;
}