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
struct TYPE_6__ {int lexline; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/ * EXP1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EXP2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VAR ; 
 int /*<<< orphan*/  assignment (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * identifier (TYPE_1__*) ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 

__attribute__((used)) static js_Ast *vardec(js_State *J, int notin)
{
	js_Ast *a = identifier(J);
	int line = J->lexline;
	if (jsP_accept(J, '='))
		return EXP2(VAR, a, assignment(J, notin));
	return EXP1(VAR, a);
}