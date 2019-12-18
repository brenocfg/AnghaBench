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
 int /*<<< orphan*/  ADD ; 
 int /*<<< orphan*/ * EXP2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/  POPREC () ; 
 int /*<<< orphan*/  SAVEREC () ; 
 int /*<<< orphan*/  SUB ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/ * multiplicative (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *additive(js_State *J)
{
	js_Ast *a = multiplicative(J);
	int line;
	SAVEREC();
loop:
	INCREC();
	line = J->lexline;
	if (jsP_accept(J, '+')) { a = EXP2(ADD, a, multiplicative(J)); goto loop; }
	if (jsP_accept(J, '-')) { a = EXP2(SUB, a, multiplicative(J)); goto loop; }
	POPREC();
	return a;
}