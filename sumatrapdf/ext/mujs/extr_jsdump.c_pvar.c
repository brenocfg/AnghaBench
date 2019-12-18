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
struct TYPE_3__ {scalar_t__ type; scalar_t__ b; scalar_t__ a; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
 scalar_t__ EXP_VAR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pc (char) ; 
 int /*<<< orphan*/  pexp (int,scalar_t__) ; 
 int /*<<< orphan*/  sp () ; 

__attribute__((used)) static void pvar(int d, js_Ast *var)
{
	assert(var->type == EXP_VAR);
	pexp(d, var->a);
	if (var->b) {
		sp(); pc('='); sp();
		pexp(d, var->b);
	}
}