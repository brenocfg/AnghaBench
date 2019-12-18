#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int lexline; int /*<<< orphan*/  lookahead; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  CASE ; 
 int /*<<< orphan*/  DEFAULT ; 
 int /*<<< orphan*/ * STM1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * STM2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TK_CASE ; 
 int /*<<< orphan*/  TK_DEFAULT ; 
 int /*<<< orphan*/ * expression (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ jsP_accept (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsP_error (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsP_expect (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsY_tokenstring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * statementlist (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *caseclause(js_State *J)
{
	js_Ast *a, *b;
	int line = J->lexline;

	if (jsP_accept(J, TK_CASE)) {
		a = expression(J, 0);
		jsP_expect(J, ':');
		b = statementlist(J);
		return STM2(CASE, a, b);
	}

	if (jsP_accept(J, TK_DEFAULT)) {
		jsP_expect(J, ':');
		a = statementlist(J);
		return STM1(DEFAULT, a);
	}

	jsP_error(J, "unexpected token in switch: %s (expected 'case' or 'default')", jsY_tokenstring(J->lookahead));
}