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
struct cstate {int dummy; } ;
struct TYPE_4__ {void* y; struct TYPE_4__* x; } ;
typedef  TYPE_1__ Renode ;

/* Variables and functions */
 int /*<<< orphan*/  P_ALT ; 
 scalar_t__ accept (struct cstate*,char) ; 
 TYPE_1__* newnode (struct cstate*,int /*<<< orphan*/ ) ; 
 void* parsecat (struct cstate*) ; 

__attribute__((used)) static Renode *parsealt(struct cstate *g)
{
	Renode *alt, *x;
	alt = parsecat(g);
	while (accept(g, '|')) {
		x = alt;
		alt = newnode(g, P_ALT);
		alt->x = x;
		alt->y = parsecat(g);
	}
	return alt;
}