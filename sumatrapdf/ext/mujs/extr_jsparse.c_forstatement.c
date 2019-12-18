#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char lookahead; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  FOR ; 
 int /*<<< orphan*/  FOR_IN ; 
 int /*<<< orphan*/  FOR_IN_VAR ; 
 int /*<<< orphan*/  FOR_VAR ; 
 int /*<<< orphan*/ * STM3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * STM4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char TK_IN ; 
 char TK_VAR ; 
 int /*<<< orphan*/ * expression (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * forexpression (TYPE_1__*,char) ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsP_error (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsP_expect (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsY_tokenstring (char) ; 
 int /*<<< orphan*/ * statement (TYPE_1__*) ; 
 int /*<<< orphan*/ * vardeclist (TYPE_1__*,int) ; 

__attribute__((used)) static js_Ast *forstatement(js_State *J, int line)
{
	js_Ast *a, *b, *c, *d;
	jsP_expect(J, '(');
	if (jsP_accept(J, TK_VAR)) {
		a = vardeclist(J, 1);
		if (jsP_accept(J, ';')) {
			b = forexpression(J, ';');
			c = forexpression(J, ')');
			d = statement(J);
			return STM4(FOR_VAR, a, b, c, d);
		}
		if (jsP_accept(J, TK_IN)) {
			b = expression(J, 0);
			jsP_expect(J, ')');
			c = statement(J);
			return STM3(FOR_IN_VAR, a, b, c);
		}
		jsP_error(J, "unexpected token in for-var-statement: %s", jsY_tokenstring(J->lookahead));
	}

	if (J->lookahead != ';')
		a = expression(J, 1);
	else
		a = NULL;
	if (jsP_accept(J, ';')) {
		b = forexpression(J, ';');
		c = forexpression(J, ')');
		d = statement(J);
		return STM4(FOR, a, b, c, d);
	}
	if (jsP_accept(J, TK_IN)) {
		b = expression(J, 0);
		jsP_expect(J, ')');
		c = statement(J);
		return STM3(FOR_IN, a, b, c);
	}
	jsP_error(J, "unexpected token in for-statement: %s", jsY_tokenstring(J->lookahead));
}