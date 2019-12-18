#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int lexline; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  COMMA ; 
 int /*<<< orphan*/ * EXP2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/  POPREC () ; 
 int /*<<< orphan*/  SAVEREC () ; 
 int /*<<< orphan*/ * assignment (TYPE_1__*,int) ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 

__attribute__((used)) static js_Ast *expression(js_State *J, int notin)
{
	js_Ast *a = assignment(J, notin);
	SAVEREC();
	int line = J->lexline;
	while (jsP_accept(J, ',')) {
		INCREC();
		a = EXP2(COMMA, a, assignment(J, notin));
		line = J->lexline;
	}
	POPREC();
	return a;
}