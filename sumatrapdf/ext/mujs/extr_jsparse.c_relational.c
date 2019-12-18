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
 int /*<<< orphan*/ * EXP2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GE ; 
 int /*<<< orphan*/  GT ; 
 int /*<<< orphan*/  IN ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/  INSTANCEOF ; 
 int /*<<< orphan*/  LE ; 
 int /*<<< orphan*/  LT ; 
 int /*<<< orphan*/  POPREC () ; 
 int /*<<< orphan*/  SAVEREC () ; 
 char TK_GE ; 
 char TK_IN ; 
 char TK_INSTANCEOF ; 
 char TK_LE ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/ * shift (TYPE_1__*) ; 

__attribute__((used)) static js_Ast *relational(js_State *J, int notin)
{
	js_Ast *a = shift(J);
	int line;
	SAVEREC();
loop:
	INCREC();
	line = J->lexline;
	if (jsP_accept(J, '<')) { a = EXP2(LT, a, shift(J)); goto loop; }
	if (jsP_accept(J, '>')) { a = EXP2(GT, a, shift(J)); goto loop; }
	if (jsP_accept(J, TK_LE)) { a = EXP2(LE, a, shift(J)); goto loop; }
	if (jsP_accept(J, TK_GE)) { a = EXP2(GE, a, shift(J)); goto loop; }
	if (jsP_accept(J, TK_INSTANCEOF)) { a = EXP2(INSTANCEOF, a, shift(J)); goto loop; }
	if (!notin && jsP_accept(J, TK_IN)) { a = EXP2(IN, a, shift(J)); goto loop; }
	POPREC();
	return a;
}