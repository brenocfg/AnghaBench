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
 int /*<<< orphan*/  DIV ; 
 int /*<<< orphan*/ * EXP2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/  MOD ; 
 int /*<<< orphan*/  MUL ; 
 int /*<<< orphan*/  POPREC () ; 
 int /*<<< orphan*/  SAVEREC () ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/ * unary (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *multiplicative(js_State *J)
{
	js_Ast *a = unary(J);
	int line;
	SAVEREC();
loop:
	INCREC();
	line = J->lexline;
	if (jsP_accept(J, '*')) { a = EXP2(MUL, a, unary(J)); goto loop; }
	if (jsP_accept(J, '/')) { a = EXP2(DIV, a, unary(J)); goto loop; }
	if (jsP_accept(J, '%')) { a = EXP2(MOD, a, unary(J)); goto loop; }
	POPREC();
	return a;
}