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
struct TYPE_3__ {int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  pexpi (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps (char const*) ; 
 int /*<<< orphan*/  sp () ; 

__attribute__((used)) static void pbin(int d, int p, js_Ast *exp, const char *op)
{
	pexpi(d, p, exp->a);
	sp();
	ps(op);
	sp();
	pexpi(d, p, exp->b);
}