#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int lexline; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/ * EXP1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EXP2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NEW ; 
 char TK_FUNCTION ; 
 char TK_NEW ; 
 int /*<<< orphan*/ * arguments (TYPE_1__*) ; 
 int /*<<< orphan*/ * funexp (TYPE_1__*,int) ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsP_expect (TYPE_1__*,char) ; 
 int /*<<< orphan*/ * memberexp (TYPE_1__*) ; 
 int /*<<< orphan*/ * primary (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *newexp(js_State *J)
{
	js_Ast *a, *b;
	int line = J->lexline;

	if (jsP_accept(J, TK_NEW)) {
		a = memberexp(J);
		if (jsP_accept(J, '(')) {
			b = arguments(J);
			jsP_expect(J, ')');
			return EXP2(NEW, a, b);
		}
		return EXP1(NEW, a);
	}

	if (jsP_accept(J, TK_FUNCTION))
		return funexp(J, line);

	return primary(J);
}