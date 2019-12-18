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
struct TYPE_9__ {int flags; int /*<<< orphan*/  start; int /*<<< orphan*/  nsub; } ;
struct TYPE_8__ {TYPE_1__* sub; int /*<<< orphan*/  nsub; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ep; int /*<<< orphan*/  sp; } ;
typedef  TYPE_2__ Resub ;
typedef  TYPE_3__ Reprog ;

/* Variables and functions */
 int MAXSUB ; 
 int match (int /*<<< orphan*/ ,char const*,char const*,int,TYPE_2__*,int /*<<< orphan*/ ) ; 

int regexec(Reprog *prog, const char *sp, Resub *sub, int eflags)
{
	Resub scratch;
	int i;

	if (!sub)
		sub = &scratch;

	sub->nsub = prog->nsub;
	for (i = 0; i < MAXSUB; ++i)
		sub->sub[i].sp = sub->sub[i].ep = NULL;

	return match(prog->start, sp, sp, prog->flags | eflags, sub, 0);
}