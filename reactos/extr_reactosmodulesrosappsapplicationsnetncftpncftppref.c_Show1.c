#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* varname; int /*<<< orphan*/  (* proc ) (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  (* PrefProc ) (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  TYPE_1__ PrefOpt ;

/* Variables and functions */
 TYPE_1__* gPrefOpts ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Show1(int t)
{
	PrefOpt *p = &gPrefOpts[t];

	(void) printf("%-30s ", p->varname);
	if (p->proc != (PrefProc) 0)
		(*p->proc)(t, NULL, stdout);
	(void) printf("\n");
}