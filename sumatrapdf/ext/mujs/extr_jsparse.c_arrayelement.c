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
struct TYPE_4__ {int lexline; char lookahead; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/ * EXP0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNDEF ; 
 int /*<<< orphan*/ * assignment (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static js_Ast *arrayelement(js_State *J)
{
	int line = J->lexline;
	if (J->lookahead == ',')
		return EXP0(UNDEF);
	return assignment(J, 0);
}