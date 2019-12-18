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
struct cstate {scalar_t__ lookahead; scalar_t__ yychar; scalar_t__ nsub; TYPE_1__** sub; int /*<<< orphan*/  yycc; } ;
struct TYPE_4__ {scalar_t__ c; size_t n; struct TYPE_4__* x; int /*<<< orphan*/  cc; } ;
typedef  TYPE_1__ Renode ;

/* Variables and functions */
 scalar_t__ L_CCLASS ; 
 scalar_t__ L_CHAR ; 
 char L_NC ; 
 scalar_t__ L_NCCLASS ; 
 char L_NLA ; 
 char L_PLA ; 
 scalar_t__ L_REF ; 
 scalar_t__ MAXSUB ; 
 int /*<<< orphan*/  P_ANY ; 
 int /*<<< orphan*/  P_CCLASS ; 
 int /*<<< orphan*/  P_CHAR ; 
 int /*<<< orphan*/  P_NCCLASS ; 
 int /*<<< orphan*/  P_NLA ; 
 int /*<<< orphan*/  P_PAR ; 
 int /*<<< orphan*/  P_PLA ; 
 int /*<<< orphan*/  P_REF ; 
 scalar_t__ accept (struct cstate*,char) ; 
 int /*<<< orphan*/  die (struct cstate*,char*) ; 
 TYPE_1__* newnode (struct cstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next (struct cstate*) ; 
 void* parsealt (struct cstate*) ; 

__attribute__((used)) static Renode *parseatom(struct cstate *g)
{
	Renode *atom;
	if (g->lookahead == L_CHAR) {
		atom = newnode(g, P_CHAR);
		atom->c = g->yychar;
		next(g);
		return atom;
	}
	if (g->lookahead == L_CCLASS) {
		atom = newnode(g, P_CCLASS);
		atom->cc = g->yycc;
		next(g);
		return atom;
	}
	if (g->lookahead == L_NCCLASS) {
		atom = newnode(g, P_NCCLASS);
		atom->cc = g->yycc;
		next(g);
		return atom;
	}
	if (g->lookahead == L_REF) {
		atom = newnode(g, P_REF);
		if (g->yychar == 0 || g->yychar >= g->nsub || !g->sub[g->yychar])
			die(g, "invalid back-reference");
		atom->n = g->yychar;
		atom->x = g->sub[g->yychar];
		next(g);
		return atom;
	}
	if (accept(g, '.'))
		return newnode(g, P_ANY);
	if (accept(g, '(')) {
		atom = newnode(g, P_PAR);
		if (g->nsub == MAXSUB)
			die(g, "too many captures");
		atom->n = g->nsub++;
		atom->x = parsealt(g);
		g->sub[atom->n] = atom;
		if (!accept(g, ')'))
			die(g, "unmatched '('");
		return atom;
	}
	if (accept(g, L_NC)) {
		atom = parsealt(g);
		if (!accept(g, ')'))
			die(g, "unmatched '('");
		return atom;
	}
	if (accept(g, L_PLA)) {
		atom = newnode(g, P_PLA);
		atom->x = parsealt(g);
		if (!accept(g, ')'))
			die(g, "unmatched '('");
		return atom;
	}
	if (accept(g, L_NLA)) {
		atom = newnode(g, P_NLA);
		atom->x = parsealt(g);
		if (!accept(g, ')'))
			die(g, "unmatched '('");
		return atom;
	}
	die(g, "syntax error");
	return NULL;
}