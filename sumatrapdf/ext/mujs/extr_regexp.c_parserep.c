#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cstate {scalar_t__ lookahead; int yymin; int yymax; } ;
typedef  int /*<<< orphan*/  Renode ;

/* Variables and functions */
 scalar_t__ L_COUNT ; 
 char L_NWORD ; 
 char L_WORD ; 
 int /*<<< orphan*/  P_BOL ; 
 int /*<<< orphan*/  P_EOL ; 
 int /*<<< orphan*/  P_NWORD ; 
 int /*<<< orphan*/  P_WORD ; 
 int REPINF ; 
 scalar_t__ accept (struct cstate*,char) ; 
 int /*<<< orphan*/  die (struct cstate*,char*) ; 
 int /*<<< orphan*/ * newnode (struct cstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newrep (struct cstate*,int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 int /*<<< orphan*/  next (struct cstate*) ; 
 int /*<<< orphan*/ * parseatom (struct cstate*) ; 

__attribute__((used)) static Renode *parserep(struct cstate *g)
{
	Renode *atom;

	if (accept(g, '^')) return newnode(g, P_BOL);
	if (accept(g, '$')) return newnode(g, P_EOL);
	if (accept(g, L_WORD)) return newnode(g, P_WORD);
	if (accept(g, L_NWORD)) return newnode(g, P_NWORD);

	atom = parseatom(g);
	if (g->lookahead == L_COUNT) {
		int min = g->yymin, max = g->yymax;
		next(g);
		if (max < min)
			die(g, "invalid quantifier");
		return newrep(g, atom, accept(g, '?'), min, max);
	}
	if (accept(g, '*')) return newrep(g, atom, accept(g, '?'), 0, REPINF);
	if (accept(g, '+')) return newrep(g, atom, accept(g, '?'), 1, REPINF);
	if (accept(g, '?')) return newrep(g, atom, accept(g, '?'), 0, 1);
	return atom;
}