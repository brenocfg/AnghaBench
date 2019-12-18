#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cstate {scalar_t__ ncclass; TYPE_2__* yycc; TYPE_1__* prog; } ;
struct TYPE_4__ {int /*<<< orphan*/  spans; int /*<<< orphan*/  end; } ;
struct TYPE_3__ {TYPE_2__* cclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (struct cstate*,char*) ; 
 scalar_t__ nelem (TYPE_2__*) ; 

__attribute__((used)) static void newcclass(struct cstate *g)
{
	if (g->ncclass >= nelem(g->prog->cclass))
		die(g, "too many character classes");
	g->yycc = g->prog->cclass + g->ncclass++;
	g->yycc->end = g->yycc->spans;
}