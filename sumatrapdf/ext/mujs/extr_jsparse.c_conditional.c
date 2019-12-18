#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int lexline; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  COND ; 
 int /*<<< orphan*/  DECREC () ; 
 int /*<<< orphan*/ * EXP3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/ * assignment (TYPE_1__*,int) ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsP_expect (TYPE_1__*,char) ; 
 int /*<<< orphan*/ * logor (TYPE_1__*,int) ; 

__attribute__((used)) static js_Ast *conditional(js_State *J, int notin)
{
	js_Ast *a = logor(J, notin);
	int line = J->lexline;
	if (jsP_accept(J, '?')) {
		js_Ast *b, *c;
		INCREC();
		b = assignment(J, 0);
		jsP_expect(J, ':');
		c = assignment(J, notin);
		DECREC();
		return EXP3(COND, a, b, c);
	}
	return a;
}