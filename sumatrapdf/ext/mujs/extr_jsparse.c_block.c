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
 int /*<<< orphan*/  BLOCK ; 
 int /*<<< orphan*/ * STM1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsP_expect (TYPE_1__*,char) ; 
 int /*<<< orphan*/ * statementlist (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *block(js_State *J)
{
	js_Ast *a;
	int line = J->lexline;
	jsP_expect(J, '{');
	a = statementlist(J);
	jsP_expect(J, '}');
	return STM1(BLOCK, a);
}