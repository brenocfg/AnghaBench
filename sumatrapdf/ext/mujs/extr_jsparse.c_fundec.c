#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  AST_FUNDEC ; 
 int /*<<< orphan*/ * funbody (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * identifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsP_expect (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/ * jsP_newnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parameters (int /*<<< orphan*/ *) ; 

__attribute__((used)) static js_Ast *fundec(js_State *J, int line)
{
	js_Ast *a, *b, *c;
	a = identifier(J);
	jsP_expect(J, '(');
	b = parameters(J);
	jsP_expect(J, ')');
	c = funbody(J);
	return jsP_newnode(J, AST_FUNDEC, line, a, b, c, 0);
}