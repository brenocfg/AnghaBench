#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cstate {int dummy; } ;
struct TYPE_6__ {int ng; int m; int n; struct TYPE_6__* x; } ;
typedef  TYPE_1__ Renode ;

/* Variables and functions */
 int /*<<< orphan*/  P_REP ; 
 int REPINF ; 
 int /*<<< orphan*/  die (struct cstate*,char*) ; 
 scalar_t__ empty (TYPE_1__*) ; 
 TYPE_1__* newnode (struct cstate*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Renode *newrep(struct cstate *g, Renode *atom, int ng, int min, int max)
{
	Renode *rep = newnode(g, P_REP);
	if (max == REPINF && empty(atom))
		die(g, "infinite loop matching the empty string");
	rep->ng = ng;
	rep->m = min;
	rep->n = max;
	rep->x = atom;
	return rep;
}